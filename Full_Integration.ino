#include <Servo.h>
#include <SoftwareSerial.h>
#define Rx 10 // DOUT to pin 10
#define Tx 11 // DIN to pin 11
///////////////////////
int redLEDPin = 33;
int yellowLEDPin = 35;
int greenLEDPin = 31;
//////////////////////
const int TxPin = 5;
const int yIn = 3;
char medal;
String ramp;

SoftwareSerial mySerial = SoftwareSerial(255, TxPin);
SoftwareSerial Xbee (Rx, Tx);

Servo leftServo;
Servo rightServo;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Xbee.begin(9600);
  leftServo.attach(13);
  rightServo.attach(12);

  pinMode(TxPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);

  digitalWrite(TxPin, HIGH);
  LCDprint("","");
  //runLightShow();
  firstRun();


}

void loop() {
  // right line following sensor 6
  // middle line following sensor 7
  // left line following 8

  if (RCTime(8) > 100 && RCTime(6) > 100) {
    stopNow();
    communicate();
    stopForever();
  }

  else if (RCTime(8) < 80 && RCTime(8) > 60) {
    turnLeft();
  }
  else if (RCTime(6) < 70 && RCTime(6) > 50) {
    turnRight();
  }
  else if (RCTime(7) < 50 && RCTime(7) > 30) {
    forward();
  }

}

/////////////////////// Movement functions///////////////////////////
void turnLeft() {
  leftServo.writeMicroseconds(1400);
  rightServo.writeMicroseconds(1400);

}
void turnRight() {
  leftServo.writeMicroseconds(1600);
  rightServo.writeMicroseconds(1600);
}
void forward() {
  leftServo.writeMicroseconds(1550);
  rightServo.writeMicroseconds(1450);
}

void stopNow() {
  leftServo.writeMicroseconds(1500);
  rightServo.writeMicroseconds(1500);
  delay(1000);
}

void backUp() {
  leftServo.writeMicroseconds(1450);
  rightServo.writeMicroseconds(1550);
}

void stopForever() {
  leftServo.detach();
  rightServo.detach();
}
///////////////////////////////////////////////////////////
void communicate() { // communicate with other robots
  //Xbee.bexgin(9600);
  Xbee.print(medal);
  //Xbee.print('A');
  while (1) {
    if (Xbee.available()) {
      char incoming = Xbee.read();
      delay(100);
      if (incoming == 'P') {
        LCDprint(ramp,"   10 Gold");
        anthem();
        break;
      }
      else if (incoming == 'Q') {
        LCDprint(ramp,"   01 Silver");
        runLightShow();
        break;
      }
      else if (incoming == 'R') {
        LCDprint(ramp,"   00 Bronze");
        performDance();
        break;
      }
    }
  }



}

void firstRun() { // starting sequence that checks the tilt of the robot on the ramp
  leftServo.writeMicroseconds(1650);
  rightServo.writeMicroseconds(1350);
  delay(1800);
  stopNow();
  int pulseY = pulseIn(yIn, HIGH); // Read Y pulse
  if (pulseY > 5100 && pulseY < 5350) {
    ramp = "   Small Ramp";
    LCDprint(ramp,"");
    medal = 'H';

  }
  else if (pulseY > 5350 && pulseY < 5800) {
    ramp = "   Large Ramp";
    LCDprint(ramp,"");
    medal = 'G';
  }
  else {
    ramp = "   No Ramp";
    LCDprint(ramp,"");
    medal = 'I';
  }

  backUp();
  delay(1700);
  while (!(RCTime(6) > 50 && RCTime(8) > 70)) { // recently test value and add left sensor

  }
  stopNow();
  turnRight();
  delay(500);
  stopNow();
  forward();
  delay(200);

}
long RCTime(int sensorIn) { // allows the line following sensor that can interpret shades of black and white
  long duration = 0;
  pinMode(sensorIn, OUTPUT);     // Make pin OUTPUT
  digitalWrite(sensorIn, HIGH);  // Pin HIGH (discharge capacitor)
  delay(1);                      // Wait 1ms
  pinMode(sensorIn, INPUT);      // Make pin INPUT
  digitalWrite(sensorIn, LOW);   // Turn off internal pullups
  while (digitalRead(sensorIn)) { // Wait for pin to go LOW
    duration++;
  }
  return duration;
}

void LCDprint (String s, String x) { // Print text on the LCD
  mySerial.write(12);                 // Clear
  mySerial.write(17);                 // Turn backlight on
  delay(5);                           // Required delay
  mySerial.print(s);  // First line
  mySerial.write(13);
  mySerial.print(x);
}
///////////////////////Celebrations/////////////////////////////
void anthem(){

int A = 220;
int Bf = 221;
int B = 22;
int C= 223;
int Cs=224;
int Fs=229;
int Gs=231;
int D = 225;
int E =227;
int F = 228;
int G = 230;
int sixteenth = 210;
int eight = 211;
int quarter = 212;
int half = 213;
mySerial.write(quarter); 
mySerial.write(216); 
mySerial.write(Fs);
mySerial.write(quarter);
mySerial.write(Fs);
mySerial.write(quarter);
mySerial.write(Fs);
mySerial.write(eight);
mySerial.write(D);
mySerial.write(217);
mySerial.write(sixteenth);
mySerial.write(A);
mySerial.write(216);
mySerial.write(quarter);
mySerial.write(Fs);
mySerial.write(eight);
mySerial.write(D);
mySerial.write(217);
mySerial.write(sixteenth);
mySerial.write(A);
mySerial.write(216);
mySerial.write(half);
mySerial.write(Fs);
mySerial.write(217); 
mySerial.write(quarter);
mySerial.write(Cs);
mySerial.write(quarter);
mySerial.write(Cs);
mySerial.write(quarter);
mySerial.write(Cs);
mySerial.write(eight);
mySerial.write(D);
mySerial.write(sixteenth);
mySerial.write(Cs);
mySerial.write(216); 
mySerial.write(quarter);
mySerial.write(F);
mySerial.write(eight);
mySerial.write(D);
mySerial.write(217);
mySerial.write(sixteenth);
mySerial.write(A);
mySerial.write(216);
mySerial.write(half);
mySerial.write(Fs);
mySerial.write(quarter);
}
///////////////// Light Show /////////////////////////
void runLightShow() {
  clockwiseCircle(200);
  clockwiseCircle(200);
  clockwiseCircle(100);
  clockwiseCircle(100);
  clockwiseCircle(100);
  clockwiseCircle(100);
  
  counterclockwiseCircle(200);
  counterclockwiseCircle(200);
  counterclockwiseCircle(100);
  counterclockwiseCircle(100);
  counterclockwiseCircle(100);

  flashAll(3000);  
}

void clockwiseCircle(int time){
  digitalWrite(redLEDPin, HIGH);
  delay(time);
  digitalWrite(redLEDPin, LOW);
  digitalWrite(yellowLEDPin, HIGH);
  delay(time);
  digitalWrite(yellowLEDPin, LOW);
  digitalWrite(greenLEDPin, HIGH);
  delay(time);
  digitalWrite(greenLEDPin, LOW);
}
void counterclockwiseCircle(int time){
  digitalWrite(greenLEDPin, HIGH);
  delay(time);
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(yellowLEDPin, HIGH);
  delay(time);
  digitalWrite(yellowLEDPin, LOW);
  digitalWrite(redLEDPin, HIGH);
  delay(time);
  digitalWrite(redLEDPin, LOW);
}

void flashAll(int time){
  digitalWrite(redLEDPin, HIGH);
  digitalWrite(yellowLEDPin, HIGH);
  digitalWrite(greenLEDPin, HIGH);
  delay(time);
  digitalWrite(redLEDPin, LOW);
  digitalWrite(yellowLEDPin, LOW);
  digitalWrite(greenLEDPin, LOW);
}
////////////// Dance /////////////////////
void performDance(){
  pivotRight(500, 200);   
  pivotLeft(500, 200);    
  stopBot(100);
  pivotRight(500, 200);   
  pivotLeft(500, 200);   
  stopBot(100);
  pivotLeft(500, 200);   
  pivotRight(550, 200);  
  stopBot(100);
  pivotLeft(500, 200);  
  pivotRight(500, 200);  
  stopBot(100);
  goBackward(600, 200);
  goForward(500, 200);
  pivotLeft(2550, 200);
  stopBot(1000);
}

void goForward(int time, int spd) {
  leftServo.writeMicroseconds(1500 + spd);  // left motor ccw
  rightServo.writeMicroseconds(1500 - spd);  // right motor cw
  // Once the servos have their orders, we just let them do their thing for the specified time
  delay(time);
}

void goBackward(int time, int spd) {
  leftServo.writeMicroseconds(1500 - spd);     //left motor cw
  rightServo.writeMicroseconds(1500 + spd);    // right motor ccw
  delay(time);
}

void pivotRight(int time, int spd) {
  leftServo.writeMicroseconds(1500 + spd);    // left motor counterclockwise
  rightServo.writeMicroseconds(1500 + spd);   // right motor counterclockwise
  delay(time);
}

void pivotLeft(int time, int spd) {
  leftServo.writeMicroseconds(1500 - spd);    // left motor clockwise
  rightServo.writeMicroseconds(1500 - spd);   // right motor clockwise
  delay(time);
}

void arcRight(int time, double spd) {
  leftServo.writeMicroseconds(1500.0 + spd);    // left motor counterclockwise
  rightServo.writeMicroseconds(1500.0 - spd/2.0);   // right motor clockwise slower than left
  delay(time);
}

void arcLeftBack(int time, double spd) {
  leftServo.writeMicroseconds(1500.0 - spd/2.0);    // left motor counterclockwise slower than right
  rightServo.writeMicroseconds(1500.0 + spd);   // right motor clockwise
  delay(time);
}
void stopBot(int time)
{
  leftServo.writeMicroseconds(1500);
  rightServo.writeMicroseconds(1500);
  delay(time);
}



