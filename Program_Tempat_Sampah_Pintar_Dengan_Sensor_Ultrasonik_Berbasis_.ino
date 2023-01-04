//Library CT bot dan Servo
#include "CTBot.h"
#include <ESP32_Servo.h>
//#include <TimerOne.h>
//Deklarasi Variabel
CTBot myBot;                                                       
Servo servo; 
float durasi1, durasi2, jarak1, jarak2;
//Deklarasi pin Push Button
int button1 = 18; 
int buttonState1 = 0;
//Deklarasi pin LED
int LED1 = 2; 
int RED1 = 15; 
//Deklarasi pin Sensor Ultrasonik
int pinTRIGGER1 = 22; 
int pinECHO1 = 23;
int pinTRIGGER2 = 21;
int pinECHO2 = 19;

#define interval1 500
#define interval2 100
#define interval3 5000
#define interval4 10000

unsigned long Sebelum1 = 0;
unsigned long Sebelum2 = 0;
unsigned long Sebelum3 = 0;
unsigned long Sebelum4 = 0;

String ssid  = "realme C2"    ; // SSID Wifi
String pass  = "khoirul25"; // Password Wifi
String token = "5911137707:AAEA70d8Kj6_XrAlii6_kQi8UsoCyXKPCdE"   ; //Token Bot Telegram
const int id1 = 1074133593; //id Bot telegram
const int id2 = 2022401204;

void setup() {
  Serial.begin(9600); // inisialisasi Serial
  Serial.println("Starting TelegramBot...");//Memulai bot telegram  
    myBot.wifiConnect(ssid, pass);  // Menghubungkan ESP32 untuk menjadi access point
    myBot.setTelegramToken(token);  // set token bot telegram 
  // Mengecek koneksi
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");
      servo.attach(27);
      servo.write(180);
        //Sensor Ultrasonik 1 & 2
        pinMode(pinTRIGGER1, OUTPUT);
        pinMode(pinECHO1, INPUT);
        pinMode(pinTRIGGER2, OUTPUT);
        pinMode(pinECHO2, INPUT);
        //Push Button
        pinMode(button1, INPUT_PULLUP);
        //Led Merah & Led Hijau
        pinMode(LED1, OUTPUT);
        digitalWrite(LED1, LOW);
        pinMode(RED1, OUTPUT);
        digitalWrite(RED1, LOW);
}

void loop() {
  buttonState1 = digitalRead(button1);  
    Ultrasonik1();
    Ultrasonik2(); 
    Kondisi_1();
    Kondisi_2();
    Kondisi_3(); 
}
//kalibrasi sensor ultrasonik 1
void Ultrasonik1(){
  unsigned long Sekarang1 = millis();  
  if (Sekarang1 - Sebelum1>=interval1)  {   
    digitalWrite(pinTRIGGER1, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTRIGGER1, LOW);
    
    durasi1 = pulseIn(pinECHO1, HIGH);
    jarak1 = ((durasi1 * 0.034) / 2);
    Serial.print("Jarak1= ");
    Serial.println(jarak1);
  }
}
//Kalibrasi sensor ultrasonik 2
void Ultrasonik2(){
  unsigned long Sekarang2 = millis();
  if (Sekarang2 - Sebelum2>=interval2)  {
    digitalWrite(pinTRIGGER2, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTRIGGER2, LOW);

    durasi2 = pulseIn(pinECHO2, HIGH);
    jarak2 = ((durasi2 * 0.034) / 2);
    Serial.print("Jarak2= "); 
    Serial.println(jarak2);
  }
}
void Kondisi_1(){
  if ((jarak1 >5)&&(jarak2<30)&&(buttonState1==LOW))
    { 
  unsigned long Sekarang3 = millis();  
  if (Sekarang3 - Sebelum3>=interval3)  {   
    Sebelum3 = Sekarang3;
        servo.write(0);
          digitalWrite(RED1, LOW);
          digitalWrite(LED1, HIGH);
            myBot.sendMessage(id1, "Ada orang membuang sampah");//Mengirimkan pesan ke bot telegram  
            myBot.sendMessage(id2, "Ada orang membuang sampah");//Mengirimkan pesan ke bot telegram 
          Serial.print("Ada orang membuang sampah");    
  }
}
    else {
      servo.write(180);
         digitalWrite(RED1, LOW);
         digitalWrite(LED1, LOW);
  }  
}
void Kondisi_2(){
  if ((jarak1 < 5)&&(jarak2>30)&&(buttonState1==LOW))
   {
        servo.write(180);
          digitalWrite(RED1, HIGH);
          digitalWrite(LED1, LOW);
            myBot.sendMessage(id1, "Tempat Sampah Penuh");//Mengirimkan pesan ke bot telegram     
            myBot.sendMessage(id2, "Tempat Sampah Penuh");//Mengirimkan pesan ke bot telegram  
          Serial.print("Tempat Sampah Penuh");
    }   
  } 
void Kondisi_3(){
  if ((jarak1 < 5)&&(jarak2>30)&&(buttonState1==HIGH))
  {
  unsigned long Sekarang4 = millis();  
  if (Sekarang4 - Sebelum4>=interval4)  {  
    Sebelum4 = Sekarang4;
        servo.write(0);
          digitalWrite(RED1, LOW);
          digitalWrite(LED1, HIGH);
            myBot.sendMessage(id1, "Ambil sampah di Tempat Sampah");//Mengirimkan pesan ke bot telegram      
            myBot.sendMessage(id2, "Ambil sampah di Tempat Sampah");//Mengirimkan pesan ke bot telegram    
          Serial.print(" Ambil sampah di Tempat Sampah");
    }
  }
    else {
      servo.write(180);
        digitalWrite(RED1, LOW);
        digitalWrite(LED1, LOW);
    }
}
