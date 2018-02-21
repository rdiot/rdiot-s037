/* Air Quality Sensor (MQ135) [S037] : http://rdiot.tistory.com/110 [RDIoT Demo] */

//edit by Lukas Aldersley

//libraries
#include <MQ135.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//constants
const int pin = A4;
const long BAUD = 115200;

//objects
LiquidCrystal_I2C lcd(0x26, 20, 4); // LCD2004
MQ135 gasSensor = MQ135(pin);


void setup() {
  Serial.begin(BAUD);       //Initialize Serial monitor
  lcd.init();               //Initialize LCD
  lcd.backlight();          //enable LCD Backlight
}

void loop()
{
  //get data
  int sensorValue = analogRead(pin);
  float rzero = gasSensor.getRZero();
  float co2_ppm = gasSensor.getPPM();
  //Vrl = val * ( 5.00 / 1024.0  );      // V
  //Rs = 20000 * ( 5.00 - Vrl) / Vrl ;   // Ohm
  //ratio =  Rs/Ro;


  //I don't know why this is relevant
  for (int i = 0; i < 2; i++) {                               //repeat twice
    digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN));      //Toggle built-in LED (pin13)
    delay(100);                                               //Wait for 1/10 Second
  }

  //Print to LCD screen
  lcd.clear();
  lcd.print("MQ135");
  lcd.setCursor(0, 1);
  lcd.print("A0=" + (String)sensorValue + " Resis=" + (String)gasSensor.getResistance() + " ");
  lcd.setCursor(0, 2);
  lcd.print("rzero=" + (String)rzero + "    ");
  lcd.setCursor(0, 3);
  lcd.print("co2 ppm=" + (String)co2_ppm + "    ");

  //Print to Serial monitor
  Serial.print("A0=" + (String)sensorValue + "\tResis=" + (String)gasSensor.getResistance() + "\t");
  Serial.print("rzero=" + (String)rzero + "\t");
  Serial.println("co2 ppm=" + (String)co2_ppm);


  delay(1000);    //delay for one second
}
