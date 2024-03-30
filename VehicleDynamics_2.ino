#include <SoftwareSerial.h>

//Defining pin setup for steering servo (motor A):
int enA = 5;
int in1 = 10;
int in2 = 11;

//Defining pin setup for prime mover (motor B):
int enB =  6;
int in3 = 12;
int in4 = 13;

int td = 30; //time delay in milliseconds
int motion = 0; //no motion in the start
int test_td = 100;

int drivespeed = 255;
int steerspeed = 200;

int btRx = 2;
int btTx = 9; // prev 3

SoftwareSerial btSerial(btRx, btTx);

void testForward(int d){
  forward(d);
  stopMotors();
}

void testReverse(int d){
  reverse(d);
  stopMotors();
}

void testLeft(int d){
  left(d);
  stopMotors();
}

void testRight(int d){
  right(d);
  stopMotors();
}

void setup() {
  // setting pin modes
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  Serial.begin(9600);
  btSerial.begin(9600);
  testForward(test_td);
  testReverse(test_td);
  testLeft(test_td);
  testRight(test_td);
}


void loop() {
  // checking for data availability at serial port:
  if (btSerial.available()>0){
    motion = btSerial.read();
    Serial.println(motion);
    decide(motion, td);
  }else{
    stopMotors();
  }
}

//defining the motion functions:

void forward(int time){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, drivespeed);
  delay(time);
}

void reverse(int time){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, drivespeed);
  delay(time);
}

void left(int time){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, steerspeed);
  delay(time);
}

void right(int time){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, steerspeed);
  delay(time);
}

void fleft(int time){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, steerspeed);
  analogWrite(enB, drivespeed);
  delay(time);
}

void fright(int time){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, steerspeed);
  analogWrite(enB, drivespeed);
  delay(time);
}

void Rleft(int time){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, steerspeed);
  analogWrite(enB, drivespeed);
  delay(time);
}

void Rright(int time){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, steerspeed);
  analogWrite(enB, drivespeed);
  delay(time);
}

void brake(int time){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 20);
  delay(time);
}


void stopMotors(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

//the following function will decide which motion to call 
//based on the signal received from raspberry pi

void decide(int motion, int td){
  switch (motion){
    case 0: stopMotors(); break;
    case 1: forward(td); break;
    case 2: reverse(td); break;
    case 3: left(td); break;
    case 4: right(td); break;
    case 5: fleft(td); break;
    case 6: fright(td); break;
    case 7: Rleft(td); break;
    case 8: Rright(td); break;
    case 9: brake(td); break;

    default: Serial.println("No motion commanded");
  }
}