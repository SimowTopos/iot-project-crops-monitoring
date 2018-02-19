#include <SimpleDHT.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h> 

void vTaskSensor(void *pvParameters);
void vTaskConfiguration(void *pvParameters);

SemaphoreHandle_t xSerialSemaphore;




// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2

// PreProc
#define RED 13
#define CONF_SIZE 20

int pinDHT11 = 2;
SimpleDHT11 dht11;
char charAdmin = 0; //Variable for storing received data
long previousMillis = 0;  // last time data was checked, in ms
volatile unsigned long pub_frequency = 60000; //Un payload par minutes
int command = 1;

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  pinMode(RED, OUTPUT); //Sets digital pin 13 as output pin
  Serial.print("Initial push period : ");Serial.println(pub_frequency);

  // Now set up two tasks to run independently.
  xTaskCreate(
    vTaskSensor
    ,  (const portCHAR *)"TaskSensors"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  1  // priority
    ,  NULL );

  xTaskCreate(
    vTaskConfiguration
    ,  (const portCHAR *) "TaskConf"
    ,  128 // stack size
    ,  NULL
    ,  2  // priority
    ,  NULL );

    xSerialSemaphore = xSemaphoreCreateMutex();
  
}

void loop() {
  // empty.The job is done in different tasks
}

void vTaskSensor(void *pvParameters)
{
  
  for(;;)
  {
    xSemaphoreTake(xSerialSemaphore, 3);
    
    pub_payload_controller(pub_frequency);
    
    xSemaphoreGive(xSerialSemaphore);
    vTaskDelay(1);
   } 
  
}

void vTaskConfiguration(void *pvParameters)
{
  for(;;)
  {
    xSemaphoreTake(xSerialSemaphore, 3);
    
    configurationCheck();
    
    xSemaphoreGive(xSerialSemaphore);
    vTaskDelay(1);
  }
}




void configurationCheck() {

  if(Serial.available())  // on a reçu quelque chose dans le serial (eg. Serial.available != 0).
  {
    char confPayload[CONF_SIZE];
    byte i = 0;
    charAdmin = Serial.read();  // je récupère le premier char reçu.
    if(charAdmin == '<'){
      digitalWrite(RED, HIGH);
      while(i < CONF_SIZE) 
      {
        while(!Serial.available());  // j'attends l'arrivée du prochain.
        charAdmin=Serial.read();
        if(charAdmin != '>'){
          confPayload[i]=charAdmin;       // je récupère celui qui vient d'arriver.
        } else {
           break;   // on a reçu une fin de chaîne, alors on sort du while()
        }
        i++;
      }

      Serial.println("Configuration received : ");
      sscanf(confPayload, "%d.%d", &pub_frequency);
      Serial.println(pub_frequency);
      Serial.println("Configuration updated");

      memset(confPayload, 0, sizeof(confPayload));
      digitalWrite(RED, LOW);


      
     }
  }
  
  
  
}

void pubFromSensors() {
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    return;
  }

  Serial.print("T=");Serial.print((int)temperature);Serial.print(";");Serial.print("H=");Serial.print((int)humidity);Serial.println(";");

}

void pub_payload_controller(unsigned long period) {

  long currentMillis = millis();
  switch (command) {
    case 1:
      // if period in ms have passed, get data and publish them:
      if (currentMillis - previousMillis >= period) {
        previousMillis = currentMillis;
        pubFromSensors();
      }
      break;
    case 0:
      break;
  }
  
}


