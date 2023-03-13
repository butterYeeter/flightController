#include <Wire.h>

#define SDA 16
#define SCL 17
#define PWR 19
#define ADR 0x76
#define CNF 0xF4
#define OUT 0xF7
#define TSB 0xF5
#define CLB 0x88
#define NUM 24

uint16_t dig_T1, dig_P1;
int16_t dig_T2, dig_T3;
int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9; 

int32_t adc_T, t_fine;

void readCalibs

double compenstate_T(int32_t adc_T)
{
  double var1, var2, T;
  var1 = (((double) adc_T)/16384.0 - ((double) dig_T1/1024.0 * (double) dig_T2);
  var2 = ((((double)adc_T)/131072.0 – ((double)dig_T1)/8192.0) * (((double)adc_T)/131072.0 – ((double) dig_T1)/8192.0)) * ((double)dig_T3);
}

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Wire.begin(SDA, SCL);
  while(!Wire);

  Wire.beginTransmission(ADR);
  Wire.write(CNF);
  Wire.write(0x53);
  Wire.endTransmission();
}