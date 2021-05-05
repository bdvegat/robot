//Motores................................//
// Motor A
#define enA 9
#define in1 8
#define in2 7
// Motor B
#define enB 6
#define in3 5
#define in4 4
//Bluetooth................................//
#include <SoftwareSerial.h>
SoftwareSerial bt1(3, 2); // RX | TX
//sensor
#include <QTRSensors.h>
#define NUM_SENSORS   7     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   12     // emitter is controlled by digital pin 2
QTRSensorsRC qtrrc((unsigned char[]) {
  A0, A1, A2, A3, A4, A5, 10
},
NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
int state = 0;

void left() {
  state = 0;
  analogWrite(enA, 60);
  analogWrite(enB, 50);
  while (state == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    qtrrc.read(sensorValues);
    if (sensorValues[6] < 800) {
      state = 1;
    }
  }
  while (state == 1) {
    qtrrc.read(sensorValues);
    if (sensorValues[6] >= 800) {
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      state = 2;
    }
  }
}

void advance() {
  state = 0;
  analogWrite(enA, 60);
  analogWrite(enB, 50);
  while (state == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    qtrrc.read(sensorValues);
    if (sensorValues[6] < 800) {
      state = 1;
    }
  }
  while (state == 1) {
    qtrrc.read(sensorValues);
    if (sensorValues[6] >= 800) {
      state = 2;
    }
  }
  while (state == 2) {
    qtrrc.read(sensorValues);
    if (sensorValues[6] < 800) {
      state = 3;
    }
  }
  while (state == 3) {
    qtrrc.read(sensorValues);
    if (sensorValues[6] >= 800) {
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      state = 4;
    }
  }
}

char bt_read() {
  if (bt1.available()) {
    char c = bt1.read();
    bt1.flush();
    return c;
  }
  return 'z';
}

void stp() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void percept() {
  qtrrc.read(sensorValues);
  char str[4];
  if (sensorValues[0] >= 700) {
    str[0] = '1';
  } else {
    str[0] = '0';
  }
  if (sensorValues[1] >= 700) {
    str[2] = '1';
  } else {
    str[2] = '0';
  }
  if (sensorValues[4] >= 700) {
    str[1] = '1';
  } else {
    str[1] = '0';
  }
  if (sensorValues[5] >= 700) {
    str[3] = '1';
  } else {
    str[3] = '0';
  }
  bt1.write(str);
  for (int i = 0; i < 7; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');

  }
  Serial.println();
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bt1.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // read raw sensor values
  char c = bt_read();
  if (c!='z')
  Serial.println(c);
  switch (c) {
    case 'p': percept();
      break;
    case 'n': stp();
    delay(1000);
      bt1.write('d');
      break;
    case 'a': advance();
      bt1.write('d');
      break;
    case 'r': left();
      bt1.write('d');
      break;
    default: break;
  }
}
