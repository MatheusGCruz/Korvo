#include <Wire.h>

// Define I2C address of the ES7210 (typically 0x30, but check your device's datasheet)
#define ES7210_ADDRESS 0x18

// Register address for reading mic data (You will need to refer to the datasheet for exact register addresses)
#define MIC_DATA_REG 0x10  // This is just an example address; replace with actual register from the datasheet

void setup() {
  // Start serial communication for debugging/output
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect (only needed for native USB boards)
  }

  // Start I2C communication
  Wire.begin();

  Serial.println("Reading microphone data from ES7210...");
  delay(1000);
}

void loop() {
  // Request data from the ES7210 microphone
  Wire.beginTransmission(ES7210_ADDRESS);
  Wire.write(MIC_DATA_REG);  // Send the register address to read from
  Wire.endTransmission(false); // Keep the connection active for a repeated read

  // Request data from the ES7210 (assume it's a 2-byte value for microphone data)
  Wire.requestFrom(ES7210_ADDRESS, 2);  // Read 2 bytes (adjust this based on your needs)

  if (Wire.available() == 2) {
    byte data1 = Wire.read();
    byte data2 = Wire.read();

    // Combine the two bytes into a single 16-bit value (if applicable)
    int micData = (data1 << 8) | data2;  // Assuming the data is in two bytes, adjust if needed

    // Print the raw microphone data (or process it as necessary)
    Serial.print("Mic Data: ");
    Serial.println(micData, DEC);  // Print as decimal or HEX if you prefer

  } else {
    Serial.println("Error reading mic data!");
  }

  // Delay before the next read cycle
  delay(1000);  // Adjust delay as necessary
}
