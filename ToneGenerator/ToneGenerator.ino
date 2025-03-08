#include <WiFi.h>
#include <HTTPClient.h>
#include <Audio.h>

#define I2S_DOUT  13  // Data out
#define I2S_BCLK  25  // Bit clock
#define I2S_LRC   22  // Left-right clock



// Audio object
Audio audio;

void setup() {
    Serial.begin(115200);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");

    // Configure I2S
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(21);  // Set volume (0-21)

    // Start streaming from URL
    audio.connecttohost(mp3_url);
}

void loop() {
    audio.loop();  // Keep decoding and playing audio
}

// Callback for audio events
void audio_info(const char *info) {
    Serial.print("INFO: "); Serial.println(info);
}
