#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX
int led =13;
void setup()
  {  Serial.begin(9600);
     BT1.begin(9600);
     pinMode(led, OUTPUT);
     //digitalWrite(led,LOW);
  }

void loop()
  {  
     if (BT1.available())
         { char c = BT1.read() ;
           Serial.print(c);
         }
     if (Serial.available())
         {  char c = Serial.read();
            BT1.print(c);
         }
   }
