#include <Wire.h>

#define SDA 16
#define SCL 17
#define GY 0x76

uint8_t n;
float rawP, rawT;

void setup() {
  pinMode(19, OUTPUT);
  digitalWrite(19, HIGH);
  Wire.begin(SDA, SCL);
  Serial.begin(115200);
  while(!Serial);

  Wire.beginTransmission(GY);
  Wire.write(0xF4);
  Wire.write(0x53);
  Wire.write(0xF5);
  Wire.write(0x2 << 5);
  Wire.endTransmission();
}

void loop() {


  Wire.beginTransmission(GY);
  Wire.write(0xF7);
  Wire.endTransmission(false);
  
  Wire.requestFrom(GY, 6);
  while(Wire.available())
  {
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    uint8_t xlsb = Wire.read();
    int32_t adc_P = ((int32_t)msb << 16 | (int32_t)lsb << 8 | (int32_t)xlsb) >> 4; // combine 3 bytes into 20-bit integer
    uint8_t mt = Wire.read();
    uint8_t lt = Wire.read();
    uint8_t xt = Wire.read();
    int32_t adc_t = ((int32_t) mt << 16 | (int32_t) lt << 8 | (int32_t) xt) >> 4;
    rawP = ((float)adc_P) / 4 / 1000; // convert to raw pressure value in Pa
    rawT = (float) adc_t;
  }
  


  Serial.print("Pressure = ");
  Serial.print(rawP);
  Serial.println(" kPa");
  // Serial.print("Temp = ");
  // Serial.print(rawT);
  // Serial.println(" °C");
  
  // delay(500);
}
