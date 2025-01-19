#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip. Check wiring.");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 initialized successfully!");
}

void loop() {
  sensors_event_t acc, gyro, temp;
  mpu.getEvent(&acc, &gyro, &temp);

  Serial.print("Acceleration along X-axis: ");
  Serial.print(acc.acceleration.x);
  Serial.println(" m/s^2");

  static unsigned long prevTime = 0;
  static float velocityX = 0.0;

  unsigned long curTime = millis(); 
  float deltaTime = (curTime - prevTime) / 1000.0;

  velocityX += acc.acceleration.x * deltaTime;

  Serial.print("Speed along X-axis: ");
  Serial.print(velocityX);
  Serial.println(" m/s");

  prevTime = curTime; 
  delay(100);        
}
