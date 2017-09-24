/* Air Quality Sensor (MQ135) [S037] : http://rdiot.tistory.com/110 [RDIoT Demo] */

#include <MQ135.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // LCD2004
int pin = A0;
int sensorValue;
int ledPin = 13;

MQ135 gasSensor = MQ135(pin);
float rzero = gasSensor.getRZero();
int ppm = gasSensor.getPPM();

void loop()
{
 
  lcd.setCursor(0,0);
  lcd.print("S037:MQ135");


  sensorValue = analogRead(pin);
  lcd.setCursor(0,1);
  lcd.print("A0=" + (String)sensorValue + " Resis="+(String)gasSensor.getResistance() +" ");

  float rzero = gasSensor.getRZero();
  digitalWrite(ledPin, HIGH);      // turn the ledPin on
  delay(100);                      // stop the program for some time
  digitalWrite(ledPin, LOW);       // turn the ledPin off
  delay(100);  // stop the program for some time
 
  lcd.setCursor(0,2);
  lcd.print("rzero=" + (String)rzero + "    ");
 

  float co2_ppm = gasSensor.getPPM();
  int ppm = co2_ppm / 4;
  //Vrl = val * ( 5.00 / 1024.0  );      // V
  //Rs = 20000 * ( 5.00 - Vrl) / Vrl ;   // Ohm 
  //ratio =  Rs/Ro;     
  lcd.setCursor(0,3);
  lcd.print("co2 ppm=" + (String)co2_ppm + "    ");
    
  delay(1000);
}
