// Motor A
#define enA 9
#define in1 A0
#define in2 A1
// Motor B
#define enB 6
#define in3 A2
#define in4 A3
int sp = 100;
int t=500; 
void setup(){
 // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void set_speed(int spd){
  if (sp>180) spd=180;
  analogWrite(enA,sp);
  analogWrite(enB,sp);
}

void advance(int ti){
  analogWrite(in1, LOW);
  analogWrite(in2, HIGH);  
  analogWrite(in3, LOW);
  analogWrite(in4, HIGH);
  delay(ti); 
  analogWrite(in1, LOW);
  analogWrite(in2, LOW);  
  analogWrite(in3, LOW);
  analogWrite(in4, LOW);
}

void left (int ti){
  analogWrite(in1, LOW);
  analogWrite(in2, HIGH);  
  delay(ti); 
  analogWrite(in1, LOW);
  analogWrite(in2, LOW);  
  analogWrite(in3, LOW);
  analogWrite(in4, LOW);
}

void right (int ti){
  analogWrite(in3, LOW);
  digitalWrite(in4, HIGH);  
  delay(ti); 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void back(int ti){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(ti); 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
 
void loop(){
 set_speed(sp);
 advance(t); 
}
