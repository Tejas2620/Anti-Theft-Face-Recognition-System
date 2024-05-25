
#include <SoftwareSerial.h>
SoftwareSerial sim800c(0, 1); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted
String textForSMS;

int pirsensor = 10;
int buzzer = 9;
int data;
int flag = 2;

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  sim800c.begin(9600); // original 19200. while enter 9600 for sim800c

  pinMode(pirsensor, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.println("logged in");
  digitalWrite(buzzer, LOW);
  
  delay(100);

}

void loop() {


  if ( digitalRead(pirsensor) == HIGH) 
  {
     while( Serial.available() )
  {
    data = Serial.read();

    if (data == '1')
    {
      flag = 1;
    }
    else if(data == '0')
    {
      flag = 0;
   
    }
  }
   
  }

  if(flag==0){
    
     textForSMS =  "Intruder in your Room  Plz Check It ";

    digitalWrite(buzzer, HIGH);
    sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("message sent.");
    delay(8000);
    
    }
  
  

}


void sendSMS(String message)
{
  sim800c.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(1000);
  sim800c.println("AT + CMGS = \"+91...\"");  // recipient's mobile number, in international format

  delay(1000);
  sim800c.println(message);                         // message to send

  sim800c.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(1000);
  sim800c.println();
  // give module time to send SMS

}
