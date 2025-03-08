#include <WiFi.h>
#include <AudioFileSourceHTTPStream.h>
#include <AudioFileSourceBuffer.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>
#include <FastLED.h>
#include "config.h"

// FastLED Settings
#define LED_PIN     14       // Pin connected to the data input of the WS2812 LEDs
#define NUM_LEDS    30       // Number of LEDs in the strip
CRGB leds[NUM_LEDS];

// I2S Settings (for ES8311)
#define SDA_PIN 19
#define SCL_PIN 32
#define BCLK_PIN 25
#define LRC_PIN 22
#define DOUT_PIN 13



// Audio objects
AudioFileSourceHTTPStream file_stream(MP3_URL);
AudioGeneratorMP3 mp3;
AudioOutputI2S i2s;

void setup() {
  Serial.begin(115200);

  // Setup FastLED
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  // Initialize I2S (ES8311)
  i2s.begin();

  // Setup MP3 streaming
  AudioFileSource* fileSource = &file_stream;
  mp3.begin(fileSource, &i2s);

  Serial.println("MP3 streaming setup complete.");
}

void loop() {
  // Continue streaming MP3 and generating audio
  if (mp3.isRunning()) {
    mp3.loop();

    // Process audio to extract amplitude (volume)
    int16_t sample;
    // Note: You no longer need to manually read data from i2s in this example.
    // Just let the AudioGeneratorMP3 handle it automatically.

    // For simple volume-based effects:
    int amplitude = abs(sample);  // Get the amplitude (volume)
    int brightness = map(amplitude, 0, 32767, 0, 255);
    fill_solid(leds, NUM_LEDS, CHSV(160, 255, brightness));  // Blue color with brightness
    FastLED.show();
  } else {
    Serial.println("MP3 file finished or error occurred.");
  }
}
