#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <FastLED.h>

Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x18); // Default I2C address is 0x40

#define ADC_PIN 39  // Buttons Serial Controller
// Buttons values:
// VOL+ - 305-306
// VOL- - 842-846
// SET  - 1210-1213
// PLAY - 1879-1881
// MODE - 2289-2292
// REC  - 2825-2827

#define LED_PIN 33      // GPIO pin connected to WS2812 data
#define NUM_LEDS 12     // Number of LEDs in your strip

int cycleCount = 0;
int cycles = 100;
int buttonPress = 10;
int brightness = 64;
CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200);
    pinMode(ADC_PIN, INPUT);
    Wire.begin(19,32); // SDA, SCL for ESP32
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();  
    FastLED.show();  
}

void loop() {
    static uint8_t offset = 0;  // Position offset for circular motion
    FastLED.setBrightness(brightness);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[(i + offset) % NUM_LEDS] = CHSV((i * 255 / NUM_LEDS), 255, 255); // Cycle colors
    }
    FastLED.show();
    offset = (offset + 1) % NUM_LEDS;

    if(cycleCount % buttonPress == 0){
      int buttonValue = analogRead(ADC_PIN)/100;

      switch (buttonValue) {
          case 3:
            brightness = brightness+5;
            break;
          case 8:
            brightness = brightness-5;
            break;
          default:
            break;
      }

      if(brightness>255){brightness = 255;};
      if(brightness<0){brightness = 0;};
    }




    if (cycleCount % cycles == 0) {
      cycleCount = 0;
    float temp = temperatureRead();  // Read ESP32 internal temperature
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");   

    int adcValue = analogRead(ADC_PIN);
    Serial.print("ADC Value: ");
    Serial.println(adcValue);
    Serial.print("ADC Value: ");
    Serial.print(brightness);
    Serial.println(adcValue);

    }

    cycleCount++;


    delay(20);
}
