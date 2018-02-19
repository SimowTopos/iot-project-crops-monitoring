/*
  Bluetooh Basic: LED ON OFF - Avishkar
  Coder - Mayoogh Girish
  Website - http://bit.do/Avishkar
  Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
  This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/
char data = 0;            //Variable for storing received data
int value = 0;


// Define Pins
#define RED 3
#define GREEN 5
#define BLUE 6

#define delayTime 10 // fading time between colors


void setup()
{
  Serial.begin(9600); //Sets the baud for serial data transmission

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

void loop()
{
  
  if (Serial.available() > 0)     // Send data only when you receive data:
  {
    data = Serial.read();        //Read the incoming data & store into data
    Serial.println(data);
    if (data == 'R') {
      Serial.println("RED");
      analogWrite(RED, 255);
      delay(2000);
      digitalWrite(RED, LOW);

    } else if (data == 'G') {
      Serial.println("GREEN");
      analogWrite(GREEN, 255);
      delay(2000);
      digitalWrite(GREEN, LOW);

    } else if (data == 'B') {
      Serial.println("BLUE");
      analogWrite(BLUE, 255);
      delay(2000);
      digitalWrite(BLUE, LOW);

    } else if (data == 'P') {
      Serial.println("PINK");
      analogWrite(RED, 255);
      analogWrite(BLUE, 255);
      delay(2000);
      digitalWrite(RED, LOW);
      digitalWrite(BLUE, LOW);

    } else if (data == 'Y') {
      Serial.println("YELLOW");
      analogWrite(RED, 255);
      analogWrite(GREEN, 255);
      delay(2000);
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);

    } else if (data == 'C') {
      Serial.println("CYAN");
      analogWrite(BLUE, 255);
      analogWrite(GREEN, 255);
      delay(2000);
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, LOW);

    } else if (data == 'W') {
      Serial.println("WHITE");
      analogWrite(BLUE, 255);
      analogWrite(GREEN, 255);
      analogWrite(RED, 255);
      delay(2000);
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, LOW);
      

    } else if (data == 'S') {
      Serial.println("STOPALL");
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);

    }
  }
}
