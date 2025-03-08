#include "driver/i2s.h"

#define BCLK_PIN 25  // I2S Bit Clock Pin (BCLK)
#define LRC_PIN 22   // I2S Left Right Clock Pin (LRCK)
#define DOUT_PIN 13  // I2S Data Out Pin (DOUT)

void setup() {
    Serial.begin(115200);

    // Configure I2S
    i2s_config_t i2s_config = {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX,          // Master mode, transmit
        .sample_rate = 44100,                          // 44.1kHz sample rate
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,   // 16-bit sample depth
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,   // Stereo
        .communication_format = I2S_COMM_FORMAT_I2S,    // I2S standard
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,       // Interrupt flags
        .dma_buf_count = 8,                             // Buffer count
        .dma_buf_len = 64,                              // Buffer length
    };

    // Set I2S pins
    i2s_pin_config_t pin_config = {
        .bck_io_num = BCLK_PIN,    // Bit clock
        .ws_io_num = LRC_PIN,      // Word select (LRCK)
        .data_out_num = DOUT_PIN,  // Data out
        .data_in_num = I2S_PIN_NO_CHANGE, // No input pin
    };

    // Install I2S driver
    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);

    Serial.println("I2S Initialized successfully.");

    // Set a test tone pattern (1kHz square wave)
    uint16_t sample = 0;
    uint16_t volume = 32767;  // Max 16-bit value

    Serial.println("Starting I2S test pattern...");
}

void loop() {
    static uint32_t lastMillis = 0;
    static uint16_t sample = 0;
    static uint16_t volume = 32767;  // Max 16-bit value

    // Generate a simple square wave pattern (1kHz)
    if (millis() - lastMillis > 1) {
        lastMillis = millis();
        sample = (sample == 0) ? volume : 0;  // Toggle between 0 and max volume
        
        // Write the sample to I2S data out (16-bit left channel, right channel same)
        i2s_write_bytes(I2S_NUM_0, (const char*)&sample, sizeof(sample), portMAX_DELAY);  
    }
}
