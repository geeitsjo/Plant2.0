#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

#define BLYNK_PRINT Serial
char auth[] = "62fc05b95b9a422f9eacfd75bd25ca3e";
int moisturePin =0;
int pumpWater = 13;
int moisVal;
int twoDays = 17280000000000;
boolean notSent = true;

  void setup() {
   Serial.begin(9600);
   pinMode(pumpWater, OUTPUT);
   Blynk.begin(auth);
     while (Blynk.connect() == false) {
        // Wait until connected
      }
    Blynk.email("rubijoanna@gmail.com", "Soil20", "Your plant was watered, she will live! Check water supply! ");
}//end of setUp 

  void loop() {
    moisVal=analogRead(moisturePin);
    //Serial.print(moisVal); //debug
    delay(twoDays); 
    if(moisVal<150){ //if dying
      water();
    }
}

  void water(){
      while(moisVal<720){ 
        digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)          
          if(notSent){
            Serial.println("Email is sent."); // This can be seen in the Serial Monitor
            Blynk.email("rubijoanna@gmail.com", "Subject: Button Logger", "You just pushed the button...");
            notSent = false;
          }
         Blynk.run();
      }//end of while
     digitalWrite(13, LOW);
     notSent = true;
     loop();
}//end of watering;
