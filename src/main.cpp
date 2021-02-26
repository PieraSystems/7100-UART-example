#include <Arduino.h>

#define RXPIN 16
#define TXPIN 17

String serial2Out;
String serialIn;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial2.begin(115200, SERIAL_8N1, RXPIN, TXPIN);
  Serial.println("");
  Serial.println("****  7100 ESP32 Example ****");
  Serial.println("****  Piera Systems      ****");
  Serial.println("");
  Serial.println("Warming up 7100...");

  // Wait 5 seconds for 7100 to boot up before sending commands
  delay(5000);

  // Send commands to the 7100 (see datasheet for full list)
  // Reset settings to defaults
  Serial2.write("$Wfactory=\r\n");
  delay(100);

  // Disable Azure integration
  Serial2.write("$Wazure=0\r\n");
  delay(100);

}

void loop() {
  delay(200);
  // Check serial data from sensor
  if (Serial2.available())
  {
    serial2Out = Serial2.readStringUntil('\n');
    String fullOutput = serial2Out + "\r\n";
    if (serial2Out)
    {
      // Write sensor data to USB serial output
      Serial.write(fullOutput.c_str());
    }
  }
}