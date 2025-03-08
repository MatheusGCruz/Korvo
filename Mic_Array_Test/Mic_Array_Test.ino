#include <Wire.h>
#include <driver/i2s.h>  // Correct include for I2S in ESP32

// Pin Definitions for Korvo V1.1 with ES7210
#define SDA_PIN 19
#define SCL_PIN 32
#define BCLK_PIN 27
#define LRC_PIN 26
#define DOUT_PIN 36

// I2S Configuration
#define I2S_DATA_IN_PIN DOUT_PIN
#define I2S_CLOCK_BCLK_PIN BCLK_PIN
#define I2S_CLOCK_LRC_PIN LRC_PIN
#define SAMPLE_RATE 16000
#define BUFFER_SIZE 1024  // Set buffer size for I2S (adjust as needed)
#define BUFFER_COUNT 4    // Set buffer count (must be between 2 and 128)

void setup() {
  // Start Serial for debugging
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Korvo V1.1 with ES7210 Audio Test");

  // Initialize I2S configuration
  i2s_config_t i2s_config;
  i2s_config.mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_RX);  // Combine flags with explicit cast
  i2s_config.sample_rate = SAMPLE_RATE;                    // Sample rate (Hz)
  i2s_config.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;  // 16-bit sample size
  i2s_config.channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT;  // Mono, right channel only
  i2s_config.communication_format = I2S_COMM_FORMAT_I2S;  // I2S protocol
  i2s_config.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;
  i2s_config.dma_buf_count = BUFFER_COUNT;  // Set buffer count
  i2s_config.dma_buf_len = BUFFER_SIZE;    // Set buffer length

  // I2S pins configuration
  i2s_pin_config_t pin_config;
  pin_config.bck_io_num = I2S_CLOCK_BCLK_PIN;   // Bit clock pin
  pin_config.ws_io_num = I2S_CLOCK_LRC_PIN;     // Word select pin (Left-Right clock)
  pin_config.data_out_num = I2S_DATA_IN_PIN;    // Data input pin from ES7210
  pin_config.data_in_num = I2S_PIN_NO_CHANGE;   // We are not transmitting data, just receiving

  // Initialize I2S driver
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);

  // Set up the I2S clock (Optional, depending on codec configuration)
  // Set codec to 16-bit mono input
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000);

  // Initialize the audio codec (ES7210)
  // You will need to configure the ES7210 codec over I2C (set up sample rate, resolution, etc.)
  initES7210();
}

void loop() {
  int16_t audio_sample = 0;
  size_t bytes_read;

  // Read one audio sample (16-bit)
  i2s_read(I2S_NUM_0, &audio_sample, sizeof(audio_sample), &bytes_read, portMAX_DELAY);

  // If audio data is available, print it out (for testing purposes)
  if (bytes_read > 0) {
    Serial.print("Audio Sample: ");
    Serial.println(audio_sample);
  }

  delay(50);  // Add delay to avoid overwhelming the Serial Monitor
}

// Function to initialize the ES7210 codec
void initES7210() {
  // Example I2C register write to initialize the codec
  // Replace with actual register addresses and values according to the ES7210 datasheet
  Wire.beginTransmission(0x40);  // ES7210 I2C address (check your setup for accuracy)
  
  // Example: Set the codec to use a 16-bit sample resolution and mono input
  // Send I2C commands to the codec to configure it as needed
  
  // Write example initialization commands
  Wire.write(0x00);  // Register address for codec settings
  Wire.write(0x01);  // Value to set for this register (example)

  // You will need to refer to the ES7210 datasheet for exact register and values needed.
  Wire.endTransmission();
}
