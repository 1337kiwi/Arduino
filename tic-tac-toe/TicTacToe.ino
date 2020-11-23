#define IR_SMALLD_NEC

                              // DEFINING NOTES FOR BUZZER CODE
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0
                              // END NOTES
                              
#include <IRsmallDecoder.h>         //Needed Libraries for the IR remote

const int DATA_PIN = 11;      //Constant for data pin from Arduino.
const int SHIFT_CLK = 12;     //Constant for shift clock pin from Arduino.
const int LATCH_PIN = 8;      //Constant for latch pin from Arduino.
const int TOTAL_OUTPUTS = 24; //Number of register chips (factor of 8 for each chip).
const int IR_PIN = 2;         //Constant for the IR reciever digital pin.
const int BUZZER_PIN = 10;    //Const for buzzer pin
const int tempo = 114;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Never Gonna Give You Up - Rick Astley
  // Arranged by Chlorondria

  NOTE_D5,2, NOTE_E5,8, NOTE_FS5,8, NOTE_D5,8, //13
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, NOTE_A4,4,
  REST,2, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8,
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

 NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8, 
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  //23
  NOTE_E5,4, NOTE_D5,2, REST,4,
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;  



IRsmallDecoder irDecoder(IR_PIN);       //IR reciever
irSmallD_t irData;
int currentPlayer = 1;
int arrayLED[TOTAL_OUTPUTS] = {0};  //LED array.

boolean gameOver = false;           //Boolean argument for active game

void setup() {
  // put your setup code here, to run once:
  pinMode(DATA_PIN, OUTPUT);  //Set data pin for output.
  pinMode(SHIFT_CLK, OUTPUT); //Set shift clock pin for output.
  pinMode(LATCH_PIN, OUTPUT); //Set latch pin for output.
  pinMode(IR_PIN, INPUT);     //Set the IR reciever for input.
  pinMode(BUZZER_PIN, OUTPUT);//Set the Buzzer pin for output
  Serial.begin(250000);       //Used for input/output.
  Serial.println("Reset");    //Tell serial output that the program reset.
  allOn();                    //Just a little start up routine where it blinks all
  delay(500);                 //and then scrolls the LEDs on and off
  allOff();
  delay(500);
  scrollLED();
  resetArrayLED();
  arrayLED[18] = 1;           //Start with the player 1 LED lit.
  registerWrite();            //Register all LED's off to start program (all arrayLED = 0).
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irDecoder.dataAvailable(irData)) {  //If a button has been pressed
    int btnPress = getButtonPressed(irData.cmd);  //Variable for the button pressed
    if (!gameOver) {  //If the game is active...
      Serial.println(irData.cmd);
      //If the button pressed was 1-9 then...
      if (btnPress != 0 && btnPress != 69) {
        Serial.print("Button Pressed: ");
        Serial.print(btnPress);
        Serial.println("");

        if (checkSpace(btnPress) == false) {   //Check to see if the space is playable
          if (checkWinning(currentPlayer) == false) {  //If the move was not a winning move, change player
            //Change Player
            changePlayer();           
          }
        }
      } else if (btnPress == 69) {   //If the power button is pressed anytime during the game then reset game
        resetGame();
      }
    } else if (btnPress == 69) {   //If the game is over, the only button allowed is the power/reset button.
    resetGame();
    }
    
    registerWrite();   //Update Player LED
    delay(500);
  }

}

//Gets the integer value of the button pressed
int getButtonPressed(int data) {
  int btn = 0;
  switch (data) { //These are the command inputs from this particular IR remote.
                  //Would need to change possibly if using a different remote.
      case 12 :  //Button 1
        btn = 1; //Assign the integer to return. 
        break;
        
      case 24 :  //Button 2
        btn = 2;
        break;
        
      case 94 :  //Button 3
        btn = 3;
        break;
        
      case 8 :   //Button 4
        btn = 4;
        break;

      case 28 :  //Button 5
        btn = 5;
        break;

      case 90 :  //Button 6
        btn = 6;
        break;
        
      case 66 :  //Button 7
        btn = 7;
        break;
        
      case 82 :  //Button 8
        btn = 8;
        break;

      case 74 :  //Button 9
        btn = 9;
        break;

      case 69 :  //Power Button
        btn = 69;
        break;
    }

    return btn;  //Returns the number of the button hit
}

//reset Game
void resetGame() {
  Serial.println("Reset");
  gameOver = false;                               //update boolean operator
  allOff();                                       //Turn off all LEDs
  currentPlayer = 1;                              //Make Player 1 the current player.
  resetArrayLED();                                //Reset LED array
  arrayLED[18] = 1;                               //Light the player 1 LED.
  registerWrite();                                //Update shift register.
  
}

//Reset the LED array
void resetArrayLED() {
  for (int i = 0; i < TOTAL_OUTPUTS - 1; i++) {   //Reset the LED Array to all zeros.
    arrayLED[i] = 0;
  }
}

//Change Player
void changePlayer() {
  if (currentPlayer == 1) {
    currentPlayer++;          //Change to player 2
    arrayLED[18] = 0;         //Turn off player 1 LED
    arrayLED[19] = 1;         //Turn on player 2 LED
  } 
  else {
    currentPlayer--;          //Change to player 1
    arrayLED[18] = 1;         //Turn on plyaer 1 LED
    arrayLED[19] = 0;         //Turn off player 2 LED
  }
}

//Winner
void winGame(int win1, int win2, int win3){
  gameOver = true;                              //set game to over

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
  {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) 
    {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) 
    {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER_PIN, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(BUZZER_PIN);
    // Lines 306-317 will flash in accordance to the music. Delay will be 10 ms per on/off sequence, will not affect music significantly
    arrayLED[win1] = 0;
    arrayLED[win2] = 0;
    arrayLED[win3] = 0;
    arrayLED[17 + currentPlayer] = 0;
    registerWrite();
    delay(10);
    arrayLED[17 + currentPlayer] = 1;           
    arrayLED[win1] = 1;                         
    arrayLED[win2] = 1;
    arrayLED[win3] = 1;
    registerWrite();                            
    delay(10);
  }

}

//Checks the space to see if it is filled
boolean checkSpace(int num) {
  num--;
  if (arrayLED[num * 2] == 0 && arrayLED[(num * 2) + 1] == 0) {     //Check the LED for the correct LED for that box.
    if (currentPlayer == 1)                                         //If it is free and current player is 1, light the LED.
      arrayLED[num * 2] = 1;
    else if (currentPlayer == 2)                                   //If it is free and current player is 2, light the LED.
      arrayLED[(num * 2) + 1] = 1;
    return false;                                                  //Return false to show that that spot was free.
  }
  else {
    return true;                                                   //Return true to show that that spot was already filled
  }
}                                                                  //and another choice must be made.

//Checks to see if current player wins
boolean checkWinning(int player) {
  player--;                        //Makes it player 0 or player 1 (just easier programming wise).  
  if (arrayLED[8 + player] == 1){  //Checks middle box first (most possibilites of winning score).
    if (arrayLED[0 + player] == 1 && arrayLED[16 + player] == 1) {  //Diagonal Right
      winGame(0 + player, 8 + player, 16 + player);  //Win game and the LED combo that won.
      return true;
    }
    if (arrayLED[2 + player] == 1 && arrayLED[14 + player] == 1) {  //Vertical Middle
      winGame(2 + player, 8 + player, 14 + player);
      return true;
    }
    if (arrayLED[4 + player] == 1 && arrayLED[12 + player] == 1) {  //Diagonal Left
      winGame(4 + player, 8 + player, 12 + player);
      return true;
    }
    if (arrayLED[6 + player] == 1 && arrayLED[10 + player] == 1) {  //Horizontal Middle
      winGame(6 + player, 8 + player, 10 + player);
      return true;
    }
  } else if (arrayLED[0 + player] == 1) {  //Need to check the possibilities that do not use the middle box this is top left box.
      if (arrayLED[2 + player] == 1 && arrayLED[4 + player] == 1) {   //Horizontal Top
        winGame(0 + player, 2 + player, 4 + player);
        return true;
      }
      if (arrayLED[6 + player] == 1 && arrayLED[12 + player] == 1) {  //Vertical Left
        winGame(0 + player, 6 + player, 12 + player);
        return true;
      }
  } else if (arrayLED[16 + player] == 1) { //Checking bottom right box
      if (arrayLED[12 + player] == 1 && arrayLED[14 + player] == 1) {  //Horizontal Bottom
        winGame(12 + player, 14 + player, 16 + player);
        return true;
      }
      if (arrayLED[10 + player] == 1 && arrayLED[4 + player] == 1) {   //Vertical Right
        winGame(4 + player, 10 + player, 16 + player);
        return true;
      }
  } 

  return false;           //If no winning combonation is found, return false.
}

//Turns on an LED no matter what previous state was.
void onLED(int i) {
  arrayLED[i] = 1;
  registerWrite();
}

//Turns off an LED no matter what previous state was.
void offLED(int i) {
  arrayLED[i] = 0;
  registerWrite();
}

//Turns all LEDs ON
void allOn() {
  for (int i = 0; i < TOTAL_OUTPUTS; i++) {
    arrayLED[i] = 1;
  }

  registerWrite();
}

//Turns all LEDs OFF
void allOff() {
  resetArrayLED();  //All LEDs = 0
  registerWrite();
}

//Scrolls leds up and down
void scrollLED() {
  allOff();
  for (int i = 0; i < TOTAL_OUTPUTS; i++) {
    onLED(i);
    delay(50);
  }
  for (int i = TOTAL_OUTPUTS - 1; i >= 0; --i) {
    offLED(i);
    delay(50);
  }
}

//This shifts out the LED array into the registers
//Then Locks in the output pins (Latch)
void registerWrite() {
  
  //Ready the latch pin to accept new outputs
  digitalWrite(LATCH_PIN, LOW);
  
  //Read the array from biggest number first down to 0
  //This is because the registers shift from largest bit
  //To the smallest bit (Pushes bit from Right to Left).
  for (int i = (TOTAL_OUTPUTS - 1); i >= 0; i--) {
    
    //Read from the LED array to get LED ON = 1 or LED OFF = 0
    if (arrayLED[i] == 1)
      digitalWrite(DATA_PIN, HIGH);
    else
      digitalWrite(DATA_PIN, LOW);

    //Pulse the shift clock to shift the new bit into the register.
    digitalWrite(SHIFT_CLK, HIGH);
    digitalWrite(SHIFT_CLK, LOW); 
  }

  //Latch the output pin to allow the outputs to function.
  digitalWrite(LATCH_PIN, HIGH);
}
