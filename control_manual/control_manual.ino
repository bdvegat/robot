//Motores................................//
// Motor A
#define enA 9
#define in1 8
#define in2 7
// Motor B
#define enB 6
#define in3 5
#define in4 4
//motor speed
int sp = 80;
//moving time
int t=250; 
char c='s';
//falta tiempo para giro
//Bluetooth................................//
#include <SoftwareSerial.h>
SoftwareSerial bt1(3, 2); // RX | TX

void setup(){
  //Motores...............................//
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  set_speed(sp);
  //bluetooth.............................//
  bt1.begin(9600);
  Serial.begin(9600);
}
//funciones motores.......................//
void set_speed(int spd){
  if (sp>180) spd=180;
  analogWrite(enA,spd);
  analogWrite(enB,spd+22);
}

void advance(int ti){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
//  delay(ti); 
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, LOW);  
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, LOW);
}

void left (int ti){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
//  delay(ti); 
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, LOW);  
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, LOW);
}

void right (int ti){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);   
//  delay(ti); 
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, LOW);  
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, LOW);
}

void back(int ti){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
//  delay(ti); 
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, LOW);  
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, LOW);
}
void stp(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);  
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enA,0);
    analogWrite(enB,0);
}
//funciones bletooth............//
char bt_read(){
  if (bt1.available()){
    char cr=bt1.read();
    bt1.flush();
    return c;
  }
  return 'z';
}

void loop(){
  //char c = bt_read();
  if (bt1.available()){
    c=bt1.read();
    Serial.print(c);
  }
//  switch (c){
//    case 'a':
//      set_speed(sp);
//      advance(t);
//      break;
//    case 'l':
//      set_speed(sp);
//      left(t);
//      break;
//    case 'r':
//      set_speed(sp);
//      right(t);
//      break;
//    case 'b':
//      set_speed(sp);
//      back(t);
//      break;
//    default:
//      stp();
//      break; 
//  }
    //left(t);
}
