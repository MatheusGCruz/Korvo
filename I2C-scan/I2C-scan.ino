#include <Wire.h>

// Codes for Korvo V1.1
#define I2C_SDA 19  
#define I2C_SCL 32

//Devices found:
//0x18
//0x40

void setup() {
    Wire.begin(I2C_SDA, I2C_SCL);
    Serial.begin(115200);
}
void scanI2C() {
    Serial.println("Scanning I2C...");
    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            Serial.print("Device found at 0x");
            Serial.println(address, HEX);
        }
    }
}

void loop() {
    scanI2C();
    delay(5000);
}
