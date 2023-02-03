#include <Wire.h>
#include "Adafruit_TCS34725.h" // library sensor 
#include <Stepper.h> // library stepper 
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);
float red, green, blue;
int warnasebelum = 2;
const float derajatatas = 369.1; // 65 derajat
const float satuputaran = 2048; // 360 derajat
const float derajatbawah = 170.66; // 30 derajat
int color = 0;
// urutan pin IN1-IN3-IN2-IN4
Stepper stepperatas = Stepper(derajatatas, 11, 10, 9, 8);
Stepper stepperbawah = Stepper(derajatbawah, 7, 6, 5, 4);
void setup()
{
  stepperbawah.setSpeed(60);
  stepperatas.setSpeed(60);
  Serial.begin(9600);
  if (tcs.begin()) {
    Serial.println("Sensor Terdeteksi");
  } else {
    Serial.println("Sensor tidak terdeteksi");
    while (1);
  }

  Serial.flush();
}

void loop()
{
  delay(150);
  delay(165);
  tcs.getRGB(&red, &green, &blue);
  delay(100);
  Serial.print("R: "); Serial.print(red); Serial.print(" ");
  Serial.print("G: "); Serial.print(green); Serial.print(" ");
  Serial.print("B: "); Serial.print(blue); Serial.print(" ");
  Serial.println(" ");
  Serial.flush();
  deteksiwarna();
  delay(100);
  switch (nomorwarna)
  {
    case 1:
      if (warnasebelum == 2)
      {
        warnasebelum = 1;
        float rotation = satuputaran / 12;
        stepperbawah.step(-rotation);
        delay(500);
      }
      if (warnasebelum == 3)
      {
        warnasebelum = 1;
        float rotation = satuputaran / 6;
        stepperbawah.step(-rotation);
        delay(500);
      }
      break;

    case 2:
      if (warnasebelum == 1)
      {
        warnasebelum = 2;
        float rotation = satuputaran / 12;
        stepperbawah.step(rotation);
        delay(500);
      }
      if (warnasebelum == 3)
      {
        warnasebelum = 2;
        float rotation = satuputaran / 12;
        stepperbawah.step(-rotation);
        delay(500);
      }
      break;

    case 3:
      if (warnasebelum == 1)
      {
        warnasebelum = 3;
        float rotation = satuputaran / 6;
        stepperbawah.step(rotation);
        delay(500);
      }
      if (warnasebelum == 2)
      {
        warnasebelum = 3;
        float rotation = satuputaran / 12;
        stepperbawah.step(rotation);
        delay(500);
      }
      break;
  }
  stepperatas.step(derajatatas);
  delay(50);
  stepperatas.step(-derajatatas);
  delay(300);

}
int deteksiwarna() {
  if (red<125 & red>100 & blue < 64) {

    nomorwarna = 1;

    Serial.print("Warna yang terdeteksi ");
    Serial.println("MERAH");

  }

  if (blue > 105 & blue < 125 & red < 42) {

    nomorwarna = 3;
    Serial.print("Warna yang terdeteksi ");
    Serial.println("BIRU");

  }

  if (green > 110 & green < 130 & red < 58) {

    nomorwarna = 2;
    Serial.print("Warna yang terdeteksi ");
    Serial.println("HIJAU");
    Serial.println(nomorwarna);

  }
  return nomorwarna;
}
