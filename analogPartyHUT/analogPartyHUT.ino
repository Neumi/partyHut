#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 3

int averVal[10];

float averFloat;
int average;

int colorMode = 1;
int charge = 1;
int chargeTime = 10;
int normalTime = 100;

int treshHold = 10;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  /*
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
    pinMode(4, INPUT);
  */
  //Serial.begin(9600);
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 8000000) clock_prescale_set(clock_div_1);
#endif

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  int val = analogRead(A2);
  //treshHold = map(analogRead(A1) , 0,1023, 3,50);
  
  averAging(val);

  /*
    Serial.print("inVal: ");
    Serial.println(val);
    Serial.print("Average: ");
    Serial.println(average);
    Serial.println();
  */
  if (abs(average - val) > treshHold) {
    getCrazy();

    //Serial.println("Moep!");
    //Serial.print("Diff: "); Serial.println((average - val));
  }
  else {
    switch (charge) {
      case 1:
        for (int i = 0; i < 16; i++) {
          strip.setPixelColor(i, strip.Color(5, 0, 0));
        }
        break;
      case 2:
        for (int i = 0; i < 16; i++) {
          strip.setPixelColor(i, strip.Color(0, 0, 5));
        }
        break;
      case 3:
        for (int i = 0; i < 16; i++) {
          strip.setPixelColor(i, strip.Color(0, 5, 0));
        }
        break;
    }
    strip.show();
    //delay(10);

  }





  //delay(10);
}

void paint(int num) {
  switch (num) {
    case 1:
      for (int i = 0; i < 16; i++) {
        strip.setPixelColor(i, strip.Color(0, 255, 0));
        delay(chargeTime);
        strip.show();
      }
      strip.show();
      delay(normalTime);
      break;
    case 2:
      for (int i = 0; i < 16; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 255));
      }
      strip.show();
      delay(normalTime);
      break;
    case 3:
      for (int i = 0; i < 16; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
      }
      strip.show();
      delay(normalTime);
      break;
    case 4:
      for (int i = 0; i < 16; i++) {
        strip.setPixelColor(i, strip.Color(0, 255, 0));
      }
      strip.show();
      delay(normalTime);
      break;
    case 5:

      for (int i = 0; i < 16; i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 0));
      }
      break;
    case 6:
      for (int i = 0; i < 16; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
        delay(chargeTime);
        strip.show();
      }
      break;
    case 7:
      for (int i = 16; i > 0; i--) {
        strip.setPixelColor(i, strip.Color(0, 0, 255));
        delay(chargeTime);
        strip.show();
      }
      break;
    case 8:
      for (int i = 16; i > 0; i--) {
        strip.setPixelColor(i, strip.Color(255, 0, 255));
        delay(chargeTime);
        strip.show();
      }
      break;
    case 9:
      for (int i = 16; i > 0; i--) {
        strip.setPixelColor(i, strip.Color(0, 255, 255));
        delay(chargeTime);
        strip.show();
      }
      break;
    default:
      switch (charge) {
        case 1:
          for (int i = 0; i < 16; i++) {
            strip.setPixelColor(i, strip.Color(5, 0, 0));
          }
          break;
        case 2:
          for (int i = 0; i < 16; i++) {
            strip.setPixelColor(i, strip.Color(0, 0, 5));
          }
          break;
        case 3:
          for (int i = 0; i < 16; i++) {
            strip.setPixelColor(i, strip.Color(0, 5, 0));
          }
          break;

      }
      strip.show();
      delay(normalTime);

      break;

  }
  //strip.show();
}

int averAging(int incoming) {

  averVal[9] = averVal[8];
  averVal[8] = averVal[7];
  averVal[7] = averVal[6];
  averVal[6] = averVal[5];
  averVal[5] = averVal[4];
  averVal[4] = averVal[3];
  averVal[3] = averVal[2];
  averVal[2] = averVal[1];
  averVal[1] = averVal[0];
  averVal[0] = incoming;

  for (int i = 0; i < 10; i = i + 1) {
    averFloat = averFloat + averVal[i];
  }
  averFloat = averFloat / 10;
  //Serial.print("Average1: ");
  //Serial.println(aver);
  average = int(averFloat);
  averFloat = 0;
}

void getCrazy() {

  //delay(10);
  //Serial.println(colorMode);
  colorMode++;
  if (colorMode == 6) {
    colorMode = 1;
  }
  //delay(200);
  randomSeed(analogRead(0));
  paint(random(15)); // min 10! ansonsten nicht alle modi ausgenutzt
  //Serial.println(random(15));
  //strip.show();


  charge++;
  if (charge == 4) {
    charge = 1;
  }
}

