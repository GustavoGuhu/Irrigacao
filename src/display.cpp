#include <Arduino.h>
#include <Wire.h>  
#include <RTClib.h> 
#include <SPI.h> 
#include <LiquidCrystal.h>

//Relógio https://create.arduino.cc/projecthub/Techatronic/ds1307-rtc-module-with-arduino-54afd1
RTC_DS1307 rtc;  
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}; 


//Autor: FILIPEFLOP https://www.filipeflop.com/blog/como-utilizar-o-display-lcd-16x2/
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//Push button https://guiarobotica.com/push-button-arduino/
int pushbutton = 8; 
int led = 9; 
bool estadoled = 0; 


void setup() 
{ 
  Serial.begin(9600);

  //Módulo RTC - Relógio 
  if (!rtc.begin()) 
  {  
    Serial.println("Couldn't find RTC");  
    while (1);  
  }
  if (!rtc.isrunning()) 
  {  
    Serial.println("RTC is NOT running!");  
  }  
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 

  //LCD 
  lcd.begin(16, 2);

  //Push Button 
  pinMode(pushbutton, INPUT_PULLUP); 
  pinMode(led, OUTPUT);

  //Piscar LED
  pinMode(LED_BUILTIN, OUTPUT);

  
}

void loop() 
{
    


  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(3, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Teste");
  lcd.setCursor(3, 1);
  lcd.print("LCD 16x2");


  //Módulo RTC - Relógio
  DateTime horario = rtc.now();  
  DateTime horario2 = rtc.now();

  // Piscar LED 
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(500);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(500);                      

  if (horario == horario2)
  {
    digitalWrite(LED_BUILTIN, HIGH);  
    delay(500);                      
    digitalWrite(LED_BUILTIN, LOW);   
    delay(500);       
  }

  //Push Button - irrigar agora
  if (digitalRead(pushbutton) == LOW) // Se o botão for pressionado
  {
    estadoled = !estadoled; // troca o estado do LED
    digitalWrite(led, estadoled);
    while (digitalRead(pushbutton) == LOW);
    delay(100);
  }

}


 
