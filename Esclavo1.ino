//ESCLAVO 1

#include <Wire.h> 
unsigned int temp=0;  
unsigned int pedido=0; 

void respuestaEvento()                  //Funcion que se ejecuta al recibir una peticion.      
{
    Wire.write(temp);                 
}
void recibidoEvento(int recepcion)      //Funcion que se ejecuta al recibir datos.
{
    
    while( Wire.available())
    {
        pedido = Wire.read();                
                       
    }
}

void setup()
{
    pinMode (8, OUTPUT);               //BUZZER
    pinMode (9, OUTPUT);               //LED
    Wire.begin(1);                     //Nos conectamos al bus de i2c con la direccion 1
    Wire.onRequest(respuestaEvento); 
    Wire.onReceive(recibidoEvento);  
}

void loop()
{
   temp = (5.0 * analogRead(0)*100.0)/1023.0;     //Lee la temperatura.
  
   if (pedido == 1)                               //Activa alarma.
   {
     digitalWrite(8,HIGH);
     digitalWrite(9,HIGH);
     delay(250);
     digitalWrite(8,LOW);
     delay(250);
   }
   if (pedido == 0)                               //Apaga alarma.
   {
     digitalWrite(8,LOW);
     digitalWrite(9,LOW);
   }
}
