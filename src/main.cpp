#include <Arduino.h>

#include <Wire.h>  
#include <RTClib.h>  
RTC_DS1307 rtc;  
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}; 

//Programa: Display LCD 16x2
//Autor: FILIPEFLOP https://www.filipeflop.com/blog/como-utilizar-o-display-lcd-16x2/
 
//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


//Push button

int pushbutton = 2; // declara o push button na porta 2
int led = 13; // declara led na porta 13
bool estadoled = 0; // variavel de controle


void setup() 
{
  while (!Serial); // for Leonardo/Micro/Zero  
  Serial.begin(9600);

  //LCD 
  lcd.begin(16, 2);

  //Piscar LED
  pinMode(LED_BUILTIN, OUTPUT);

  //Push Button https://guiarobotica.com/push-button-arduino/
  pinMode(pushbutton, INPUT_PULLUP); // define o pino do botao como entrada
  pinMode(led, OUTPUT);// define LED como saida

  //Módulo RTC - Relógio https://create.arduino.cc/projecthub/Techatronic/ds1307-rtc-module-with-arduino-54afd1
  if (!rtc.begin()) 
  {  
    Serial.println("Couldn't find RTC");  
    while (1);  
  }
  if (!rtc.isrunning()) 
  {  
    Serial.println("RTC is NOT running!");  
    // following line sets the RTC to the date & time this sketch was compiled  
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  
    // This line sets the RTC with an explicit date & time, for example to set  
    // January 21, 2014 at 3am you would call:  
    //rtc.adjust(DateTime(2019, 3, 3, 20, 0, 0));  
  }  
  //rtc.adjust(DateTime(2019, 3, 3, 20, 0, 0));  
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 

  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() 
{
    
  //Push Button
  if (digitalRead(pushbutton) == LOW) // Se o botão for pressionado
  {
    estadoled = !estadoled; // troca o estado do LED
    digitalWrite(led, estadoled);
    while (digitalRead(pushbutton) == LOW);
    delay(100);
  }

  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(3, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("FILIPEFLOP");
  lcd.setCursor(3, 1);
  lcd.print(" LCD 16x2");
  delay(5000);
    
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
    
  //Rolagem para a direita
  for (int posicao = 0; posicao < 6; posicao++)
  {
    lcd.scrollDisplayRight();
    delay(300);
  }

  //Módulo RTC - Relógio
  DateTime now = rtc.now();  
  Serial.print(now.year(), DEC);  
  Serial.print('/');  
  Serial.print(now.month(), DEC);  
  Serial.print('/');  
  Serial.print(now.day(), DEC);  
  Serial.print(" (");  
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);  
  Serial.print(") ");  
  Serial.print(now.hour(), DEC);  
  Serial.print(':');  
  Serial.print(now.minute(), DEC);  
  Serial.print(':');  
  Serial.print(now.second(), DEC);  
  Serial.println();  
  Serial.print(" since midnight 1/1/1970 = ");  
  Serial.print(now.unixtime());  
  Serial.print("s = ");  
  Serial.print(now.unixtime() / 86400L);  
  Serial.println("d");  
  // calculate a date which is 7 days and 30 seconds into the future  
  DateTime future (now + TimeSpan(7,12,30,6));  
  Serial.print(" now + 7d + 30s: ");  
  Serial.print(future.year(), DEC);  
  Serial.print('/');  
  Serial.print(future.month(), DEC);  
  Serial.print('/');  
  Serial.print(future.day(), DEC);  
  Serial.print(' ');  
  Serial.print(future.hour(), DEC);  
  Serial.print(':');  
  Serial.print(future.minute(), DEC);  
  Serial.print(':');  
  Serial.print(future.second(), DEC);  
  Serial.println();  
  Serial.println();  
  delay(3000);  

  // Piscar LED 
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second

//Bomba D'Água

const int bomba = 13; void setup() {  // inicializando comunicação com a porta serial  Serial.begin(9600);

  pinMode(bomba, OUTPUT);

}

void loop() {

  //Lê o valor do potenciômetro

  int sensorValue = analogRead(A0);   

  //Escreve na tela

  Serial.println(sensorValue);

  if(sensorValue > 800){     

      digitalWrite(bomba, LOW);     

      Serial.println("Bomba Desligada!");          

  }

  if(sensorValue < 600){     

      digitalWrite(bomba, HIGH);

      Serial.println("Bomba Ligada!");    

  }    

  delay(1000);

}




}

//https://labdegaragem.com/profiles/blogs/controle-de-bomba-de-gua  
 
