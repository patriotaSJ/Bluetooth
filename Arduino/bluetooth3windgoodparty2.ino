//#include "DHT.h"
//#define DHTPIN 7
//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);
 
int led = 13; //led Rojo de prueba de conexión

float voltageValue[4] = {0,0,0,0};
char inbyte = 0; //Char para leer el led
 
void setup() {
  // initialise serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  //dht.begin();
}
 
void loop() {
  getVoltageValue();
  //when serial values have been received this will be true
  
  if (Serial.available() > 0)
  {
    inbyte = Serial.read();
    Serial.println(inbyte);
    if (inbyte == '2')
    {
      digitalWrite(led, LOW); //LED off
      voltageValue[0] = 0;
    }
    if (inbyte == '1')
    {
      digitalWrite(led, HIGH); //LED on
      voltageValue[0] = 1;
    }
  }
  sendAndroidValues();
  delay(2000); 
}
 
void getVoltageValue()
{
  voltageValue[0] = 1; //led
  voltageValue[1] = 2;
  voltageValue[2] = 3;
  voltageValue[3] = 4;
  
}

//enviar los valores por el dipositivo android por el modulo Bluetooth
void sendAndroidValues()
 {
  Serial.print('#'); //hay que poner # para el comienzo de los datos, así Android sabe que empieza el String de datos
  for(int k=0; k<4; k++)
  {
    Serial.print(voltageValue[k]);
    Serial.print('+'); //separamos los datos con el +, así no es más fácil debuggear la información que enviamos
  }
 Serial.print('~'); //con esto damos a conocer la finalización del String de datos
 Serial.println();
 delay(10);        //agregamos este delay para eliminar tramisiones faltantes
}
