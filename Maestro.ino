//MAESTRO

#include <Wire.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
byte charGrado[8] = {
  0b01110,
  0b01010,
  0b01110,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000 };

int estado=0;
void setup()
{
    pinMode(9, OUTPUT); //LED
    pinMode(8, OUTPUT); //BUZZER
    pinMode(12, INPUT); //SILENCIO
    pinMode(13, INPUT); //PANICO
    Wire.begin();               
    Serial.begin(9600);
    lcd.begin(20, 4);
    /*lcd.setCursor(6,1);
    lcd.print("PARCIAL");
    lcd.setCursor(7,3);
    lcd.print("FINAL");
    delay(100);
    lcd.clear();*/
    lcd.createChar(0,charGrado);  
}

void Alarma(int est)
{
  if (est == 0 ) //Apagar
  {
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      lcd.setCursor(14,1);
      lcd.print("Normal"); 
      lcd.setCursor(14,2);
      lcd.print("Normal"); 
      lcd.setCursor(14,3);
      lcd.print("Normal"); 
  }
  if (est == 1) //Prender
  {
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      delay(250);
      digitalWrite(9, LOW);     
  }
}

void loop()
{
  int temp1, temp2, temp3;

  Wire.requestFrom(1, 1);    
  while(Wire.available())     
  {
    temp1 = Wire.read(); 
  }
  Wire.requestFrom(2, 1);    
  while(Wire.available())     
  {
    temp2 = Wire.read(); 
  }
  Wire.requestFrom(3, 1);    
  while(Wire.available())     
  {
    temp3 = Wire.read(); 
  }
  
  lcd.setCursor(0,0);
  lcd.print("Estacion|[");
  lcd.write(byte(0));
  lcd.print("C]|Estado");
  //ESTACION 1
  lcd.setCursor(3,1);
  lcd.print("1");
  lcd.setCursor(8,1);
  lcd.print("|");
  lcd.setCursor(10,1);
  lcd.print(temp1);
  lcd.print(" ");
  lcd.setCursor(13,1);
  lcd.print("|");
  //ESTACION 2
  lcd.setCursor(3,2);
  lcd.print("2");
  lcd.setCursor(8,2);
  lcd.print("|");
  lcd.setCursor(10,2);
  lcd.print(temp2);  //TEMP2
  lcd.print(" ");
  lcd.setCursor(13,2);
  lcd.print("|");
  //ESTACION 3
  lcd.setCursor(3,3);
  lcd.print("3");
  lcd.setCursor(8,3);
  lcd.print("|");
  lcd.setCursor(10,3);
  lcd.print(temp3);  //TEMP3
  lcd.print(" ");
  lcd.setCursor(13,3);
  lcd.print("|");

  
  if (digitalRead(13) == HIGH) //PANICO
  {
      estado = 1;
      Wire.beginTransmission(1);
      Wire.write(1);
      Wire.endTransmission();
      Wire.beginTransmission(2);
      Wire.write(1);
      Wire.endTransmission();
      Wire.beginTransmission(3);
      Wire.write(1);
      Wire.endTransmission();
  }
  if (digitalRead(12) == HIGH)  //SILENCIO
  {
      estado = 0;
      Wire.beginTransmission(1);
      Wire.write(0);
      Wire.endTransmission();
      Wire.beginTransmission(2);
      Wire.write(0);
      Wire.endTransmission();
      Wire.beginTransmission(3);
      Wire.write(0);
      Wire.endTransmission();
  }
  
  Serial.print("Est 1: ");
  Serial.print(temp1);
  Serial.print("°C ");
  if (temp1 >= 40)
  {
       estado = 1;
       Serial.print("Alarma \t");
       lcd.setCursor(14,1);
       lcd.print("Alarma");
       Wire.beginTransmission(1);
       Wire.write(1);
       Wire.endTransmission();      
  }
  if (temp1 < 40){Serial.print("Normal \t");}

  Serial.print("Est 2: ");
  Serial.print(temp2);
  Serial.print("°C ");
  if (temp2 >= 40)
  {
       estado = 1;
       Serial.print("Alarma \t");
       lcd.setCursor(14,2);
       lcd.print("Alarma");
       Wire.beginTransmission(2);
       Wire.write(1);
       Wire.endTransmission();      
  }
  if (temp2 < 40){Serial.print("Normal \t");}

  Serial.print("Est 3: ");
  Serial.print(temp3);
  Serial.print("°C ");
  if (temp3 >= 40)
  {
       estado = 1;
       Serial.print("Alarma \n");
       lcd.setCursor(14,3);
       lcd.print("Alarma");
       Wire.beginTransmission(3);
       Wire.write(1);
       Wire.endTransmission();
  }
  if (temp3 < 40){Serial.print("Normal \n");}
  
  Alarma(estado);
}
