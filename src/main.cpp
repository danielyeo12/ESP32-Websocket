#include <Arduino.h>

//function to initialize PWM to the motor, choose channel, pin and number of bits
void initializeMotor(int pin, int channel, int freq, int resolution_bits){
  ledcSetup(channel, freq, resolution_bits); 
  ledcAttachPin(pin, channel);
}

//sets motor duty cycle, takes in forward and backward channels as well as number of bits
// total counter is equal to 2^res_bits. ex: res_bits = 2, total counter = 4, ranges from 0-3. 4-1=3. Duty cycles maxes out at 3. 
// speed (0 to 100)
void setMotorSpeed(int speed, int channel_driving, int channel_idle, int resolution_bits){
  ledcWrite(channel_idle, 0);//set backward to zero to avoid shorting
  ledcWrite(channel_driving, ((1 << resolution_bits) - 1) * speed/100);//set duty cycle
}

//stops motor
void stopMotor(int channel1, int channel2){
  ledcWrite(channel1, 0);//set to zero
  ledcWrite(channel2, 0);//set to zero
}

//setup file, initializes the forward and backward channels
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Left Motor
  initializeMotor(8, 0, 1000, 8);//forward motor pin 8 on channel 0, 1kHz with 8 bits
  initializeMotor(9, 1, 1000, 8);//backward motor pin 9 on channel 1, 1kHz with 8 bits

  // Right Motor
  initializeMotor(10, 2, 1000, 8);//forward motor pin 10 on channel 2, 1kHz with 8 bits
  initializeMotor(11, 3, 1000, 8);//backward motor pin 11 on channel 3, 1kHz with 8 bits
}

//loop tests if motor works
void loop() {
  setMotorSpeed(30, 0, 1, 8);//go forward at 30% speed, channel 0 is driving
  delay(5000);
  setMotorSpeed(30, 1, 0, 8);//go backward at 30% speed, channel 1 is driving
  delay(5000);

  setMotorSpeed(30, 2, 3, 8);//go forward at 30% speed, channel 2 is driving
  delay(5000);
  setMotorSpeed(30, 3, 2, 8);//go backward at 30% speed, channel 3 is driving
  delay(5000);
}