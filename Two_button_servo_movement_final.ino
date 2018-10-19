/* Code to move a servo using two push buttons. Motion of the servo will change depending on buttons pushed
 *  most servos need to be powered by external source from arduino
 *  
 *  Code written by Sean M. Rogers -2018
 *  
 *  adapted from code written by zoomkat
 *  LCD code adapted from https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay
 *  Basic Servo breadboard setup adapted from https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors/if-the-servo-misbehaves
 *  Button usage adapted from https://www.arduino.cc/en/Tutorial/Button
 *  
 *  LCD utilized for determining servo position and trouble shooting -- basic 16x2 LCD used
 *  
 */

#include <LiquidCrystal.h>
#include <Servo.h>

// LCD pin assignments and setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// constants won't change throughout code -- used to set pin numbers
const int buttonONE = 8; // push button one pin - connect to ground to move servo
const int buttonTWO = 9; // push button two pin - connect to ground to move servo
const int servoPIN = 7;  // servo pin assignment
Servo servo1;

// variables which are modifiable
int buttonstateONE = 0;    // variable for reading button one state
int buttonstateTWO = 0;    // variable for reading button two state
int pos = 90;              // variable to store and set the servo position

void setup() {
  lcd.begin(16, 2);        // initialize LCD into columns and rows
  Serial.begin(9600);      // initialize serial connection to servo motor
  // initialize push buttons as inputs
  pinMode(buttonONE, INPUT);
  pinMode(buttonTWO, INPUT);
  // initialize LEDs as outputs
  servo1.attach(servoPIN);   // attach servo to designated pin
  servo1.write(pos);  // starting position
  lcd.setCursor(0,0); // force cursor to first line
  lcd.print("Servo Position");
}

void loop() {
  lcd.setCursor(0,0); // force cursor to first line
  lcd.print("Servo Position");
  lcd.setCursor(1,1);
  lcd.print(pos); // print position in degrees on second line
  delay(10);
  buttonstateONE = digitalRead(buttonONE);
  if (buttonstateONE == HIGH) {
    pos=(pos+1); // move servo 1 degree positively
    if(pos>180) pos=180; //limit upper value
    Serial.println(pos); //for serial monitoring debug
    servo1.write(pos); // move servo to position in variable "pos"
    delay(20); // wait 20ms to slow down servo movement
    // decrease delay time to increase servo speed, increase delay to decrease servo speed
  }

  buttonstateTWO = digitalRead(buttonTWO);
  if (buttonstateTWO == HIGH) {
    pos=(pos-1);     // move servo 1 degree negatively
    if(pos<0) pos=0; // lower value limit
    Serial.println(pos); // for serial monitor debug
    servo1.write(pos); // tell servo to move to variable "pos"
    delay(20); // wait 20ms to slow down servo movement 
    // decrease delay time to increase servo speed, increase delay to decrease servo speed
    lcd.clear();
    delay(1); // clear display when push button is pressed 
  } 
}
