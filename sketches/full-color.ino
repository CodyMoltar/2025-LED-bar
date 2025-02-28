#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <SD.h>


Adafruit_NeoPixel strip = Adafruit_NeoPixel(228, 5, NEO_GRB + NEO_KHZ800);
int j, i;

void setup() {
  pinMode(5, OUTPUT);
  pinMode(4, INPUT); //informaciju suta uz mikrokontrolieri (datu nolasisana)
  pinMode(6, OUTPUT); //lampinai (deg vai nedeg)
  pinMode(8, INPUT); //signals iet uz pikstuli (nospiez pgu -> spriegums)
  pinMode(7, OUTPUT); //pikstulis skan
  digitalWrite(6, LOW);
  delay(100);
  digitalWrite(6,HIGH);
  delay(200);
  strip.begin();  //inicialize visus mainigos
  strip.show();
  Serial.begin(9600); 
  //while(!Serial)
  SD.begin(); 
  if(!SD.begin(4)) {
    Serial.println("No card detected"); 
    while(1);
  }
  else {Serial.println("SD Card found");
    digitalWrite(6, LOW);}
  while(digitalRead(8)==LOW) {delay(50);}
  tone(7, 1000, 500); //suta noteiktas frekvences skanas vilni uz defineto pieslegvietu
  delay(1000);
}

void loop() {
  File fails=SD.open("ROMBI.txt", FILE_READ); //lauj pieklut failam
  if(fails) {    
    for(i=0;i<=1140;i++){
      for (j=0;j<=229;j++) {    
         byte baits=fails.read();
         if(baits=='1') 
            strip.setPixelColor(j,0,0,50);          
         else strip.setPixelColor(j,0,0,0); 
       }
       strip.show(); 
       //strip.setPixelColor(j,0,0,0); strip.show();
    }
    fails.close();
  } else {
    Serial.println("Nevar atvert ROMBI.txt");
   }
}
