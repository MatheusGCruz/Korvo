#include <Wire.h>

void setup() {
  Serial.begin(115200);  // Start the serial communication at 115200 baud rate

  Wire.begin(19, 32);  // Initialize I2C with SDA pin 19 and SCL pin 32 (Korvo V1.1 pins)

  Serial.println("\nI2C Scanning...");

  // Scan the I2C bus for devices
  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    // Try to communicate with the I2C device at this address
    Serial.print("checking - ");
    Serial.println(address, HEX);
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      // Device found
      Serial.print("I2C device found at address 0x");
      Serial.print(address, HEX);
      Serial.println("  (click to see the part)");

      nDevices++;
      delay(500);  // Wait for half a second
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found");
  } else {
    Serial.println("I2C scan complete.");
  }
}

void loop() {
  // Nothing to do here
}
