// (c) Michael Schoeffler 2017, http://www.mschoeffler.de
#include "FastLED.h"

#define DATA_PIN 3
#define LED_TYPE WS2812B
#define COLOR_ORDER RGB
#define NUM_LEDS 132
//#define NUM_LEDS 15
#define BRIGHTNESS 
#define POT_PIN A0
const int buttonPin = 4;

//variables will change
int buttonState = 0;
int click_count = 0;
int r_color = 255;
int g_color = 40;
int b_color = 54;

CRGB leds[NUM_LEDS];

void setup() {
//  Serial.begin(9600);
  delay(3000); // initial delay of a few seconds is recommended
  pinMode(buttonPin, INPUT);  //initialize the pushbutton pin as an output
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // initializes LED strip
  FastLED.setBrightness(BRIGHTNESS);// global brightness
}

// switches off all LEDs
void showProgramCleanUp(long delayTime) {
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(delayTime);
}

// switches on all LEDs. Each LED is shown in random color.
// numIterations: indicates how often LEDs are switched on in random colors
// delayTime: indicates for how long LEDs are switched on.
void showProgramRandom(long delayTime, int r_col, int g_col, int b_col ) {
    for (int i = 0; i < NUM_LEDS; ++i) {
      leds[i] = CRGB(r_col, g_col, b_col); // hue, saturation, value
      FastLED.show();
//    delay(delayTime);
    } 
 }

// main program
void loop() {
  //showProgramCleanUp(2500); // clean up

  buttonState = digitalRead(buttonPin); //read the state of the pushbutton value

//  Serial.println("CLICK COUNT |");
//  Serial.println(click_count);
  
  int sensorValue = analogRead(POT_PIN); //read the input on analog pin 0

//  Serial.println("SENSOR VALUE |");
//  Serial.println(sensorValue);
  
  if (buttonState == HIGH) {
    click_count = click_count + 1;
    if (click_count > 2){
      click_count = 0;
    }
//    Serial.println("Click Detected");
  }

  if (click_count == 0){
      r_color = map(sensorValue, 0, 1023, 0, 255);
  }

  if (click_count == 1){
      g_color = map(sensorValue, 0, 1023, 0, 255);
  }

  if (click_count == 2){
      b_color = map(sensorValue, 0, 1023, 0, 255);
  }
  
  delay(1000); //  delay of a few seconds is recommended
  showProgramRandom(100, r_color, g_color, b_color); // show "random" program
//    Serial.println(r_color);
//    Serial.println(g_color);
//    Serial.println(b_color);
//    Serial.println("-----");
}
