// Demonstrates use of the WireSlave library for ESP32.
// Receives data as an I2C/TWI slave device; data must
// be packed using WirePacker.

#include <Arduino.h>
#include <Wire.h>
#include <WireSlave.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define I2C_SLAVE_ADDR 0x04

void receiveEvent(int howMany);

void setup()
{
  Serial.begin(115200);

  bool success = WireSlave1.begin(SDA_PIN, SCL_PIN, I2C_SLAVE_ADDR);
  if (!success)
  {
    Serial.println("I2C slave init failed");
    while (1)
      delay(100);
  }

  WireSlave1.onReceive(receiveEvent);
}

void loop()
{
  // the slave response time is directly related to how often
  // this update() method is called, so avoid using long delays
  // inside loop(), and be careful with time-consuming tasks
  WireSlave1.update();

  // let I2C and other ESP32 peripherals interrupts work
  delay(1);
}

// function that executes whenever a complete and valid packet
// is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while (1 < WireSlave1.available()) // loop through all but the last byte
  {
    char c = WireSlave1.read(); // receive byte as a character
    Serial.print(c);            // print the character
  }

  int x = WireSlave1.read(); // receive byte as an integer
  Serial.println(x);         // print the integer
}
