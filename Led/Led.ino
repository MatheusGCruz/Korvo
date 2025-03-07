void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("ESP32 Internal Temperature Sensor");
}

void loop() {
    float temp = temperatureRead();  // Read ESP32 internal temperature
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");

    delay(1000);  // Update every second
}
