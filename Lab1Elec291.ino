// C++ code
//
#include <LiquidCrystal.h>

const int RS = 12, EN = 11, D4 = 7, D5 = 6, D6 = 5, D7 = 4;
const int PWM_pin = 3;

LiquidCrystal myLCD (RS, EN, D4, D5, D6, D7);

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(PWM_pin, OUTPUT);
  myLCD.begin(16,2);
}

void loop()
{
  int x = analogRead(A0);
  float r = valToResistance(x);
  
  Serial.print("Resistance = ");
  Serial.print(r/1000.0);
  Serial.print(" kOhms ");
  if (r >= 2500){
   Serial.println("(Dark)");
  }else if (r <= 600){
   Serial.println("(Bright)");
  }else{
   Serial.println("(Normal)");
  }
  
  //PWM:
  float rate = r * (255.0/181000.0);
  //Serial.println((int)rate);
  analogWrite(PWM_pin,rate);
  printResistanceToLCD(r);
  delay(250);
  myLCD.clear();
}

float valToResistance(int x){
  float a_volt = x * (5.0/1023.0);
  float resistance = 9500*((5.0/a_volt)-1);

  return resistance;
}

void printResistanceToLCD(float resistance){
  float kohm = resistance/1000.0;
  myLCD.print("R = ");
  myLCD.print(kohm);
  myLCD.print(" k ohm");
  myLCD.setCursor(0,0);
  
}
