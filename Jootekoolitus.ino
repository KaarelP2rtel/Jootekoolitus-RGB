 // MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ;

void setup(){
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(20, OUTPUT);
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(2000000);

  digitalWrite(20,LOW);
}
void loop(){
  
  updateGyro();
  float sens=32000;
  
  float x = (float)abs(AcX) /sens;
  float y = (float)abs(AcY) /sens;
  float z = (float)abs(AcZ) /sens;
 
  int r =(255*x);
  int g =(255*y);
  int b =(255*z);
  
  analogWrite(3,r);
  analogWrite(9,r);
  
  analogWrite(5,g);
  analogWrite(10,g);

  analogWrite(6,b);
  analogWrite(11,b);

  Serial.print(r);
  Serial.print(g);
  Serial.println(b);
  
}
void updateGyro(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,6,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  }
