#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <SD.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(228, 5, NEO_GRB + NEO_KHZ800);

#define button_pin 8

File dataFile;

const int numLeds = 228;                           // Total number of LEDs
const int valuesPerLed = 3;                      // RGB values per LED
const int valuesPerLine = numLeds * valuesPerLed;  // Total values per line

// Placeholder for LED control (replace with your LED library/code)
void setLedColor(int ledIndex, int red, int green, int blue) {
  strip.setPixelColor(ledIndex, red, green, blue);
}

void setup() {
  pinMode(5, OUTPUT);
  pinMode(4, INPUT);   //informaciju suta uz mikrokontrolieri (datu nolasisana)
  pinMode(6, OUTPUT);  //lampinai (deg vai nedeg)
  pinMode(8, INPUT);   //signals iet uz pikstuli (nospiez pgu -> spriegums)
  pinMode(7, OUTPUT);  //pikstulis skan
  digitalWrite(6, LOW);
  delay(100);
  digitalWrite(6, HIGH);
  delay(200);
  strip.begin();  //inicialize visus mainigos
  strip.show();
  Serial.begin(9600);
  //while(!Serial)
  SD.begin();
  while (!SD.begin(4)) {
    Serial.println("No card detected");
    delay(50);
  }

  Serial.println("SD Card found");
  digitalWrite(6, LOW);

  while (digitalRead(button_pin) == LOW) { delay(50); }
  tone(7, 1000, 500);  //suta noteiktas frekvences skanas vilni uz defineto pieslegvietu
  delay(1000);
}

bool buttonPressed = LOW;
bool reading = false;


void loop() {
  buttonPressed = digitalRead(button_pin);

  if (buttonPressed == HIGH && !reading) {
    dataFile = SD.open("image.txt");
    while (!dataFile) {}
    Serial.println("image.txt succesfully opened");
    reading = true;
  }

  if (buttonPressed == HIGH && reading) {

    if (!dataFile.available()) {
      Serial.print("nothing to read anymore, closing and stopping reading..");
      dataFile.close();
      reading = false;
      return;
    }

    Serial.print("reading line");

    for (int ledIndex = 0; ledIndex < 228; ledIndex++) {

      int RGBValues[3];
      int RGBIndex = 0;

      for (int ledColor = 0; ledColor < 3; ledColor++) {  // we extract the 3 RGB color values

        // byte data = dataFile.read();  // this reads the comma

        char chars[3];

        for (int valueChar = 0; valueChar < 3; valueChar++) {  // the values are chars, so we need to combine them into a 3 digit number

          byte data = dataFile.read();

          int integerValue = data - '0';

          chars[valueChar] = integerValue;

        }

        int colorValue = chars[0] * 100 + chars[1] * 10 + chars[2];

        RGBValues[RGBIndex] = colorValue;
        RGBIndex++;
      }
      
      strip.setBrightness(255);
      strip.setPixelColor(ledIndex,RGBValues[0],RGBValues[1],RGBValues[2]);

    }

    strip.setBrightness(64);
    strip.show();

    // read to more bytes, for the end line characters
    // byte endline = dataFile.read();
    // endline = dataFile.read();
  }

  if (buttonPressed == LOW && reading) {
    dataFile.close();
    Serial.println("STOP READING...");
    reading = false;
  }
}
