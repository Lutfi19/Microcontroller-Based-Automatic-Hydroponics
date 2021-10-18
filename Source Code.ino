#include <SoftwareSerial.h>
#include <dht.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(4,3,12,5,6,13);
#define ON LOW
#define OFF HIGH
#define DHT11_PIN 7
#define ON LOW
#define OFF HIGH
dht DHT;

const int TRIGPIN = 8 ;
const int ECHOPIN = A5 ;
unsigned int jarak, k, timer;
int T_air ;
const int Relay1 = A1 ;
int StatRelay1;
int luasalas ;
long vol , Vol ;
int air=A2; 
int i ;
//boolean replay = true;
boolean henti = false ;

SoftwareSerial SIM800L(2, A3); // tx | rX
// Connect the TX to Arduino pin 2 RX. 
// Connect the RX to Arduino pin 3 TX. 
void setup() {
    pinMode (Relay1 , OUTPUT); 
    digitalWrite (Relay1, HIGH);
    pinMode(ECHOPIN, INPUT);
    pinMode(TRIGPIN, OUTPUT); 
    lcd.begin(16,2);
    lcd.setCursor(3,0);
    lcd.print("KKN ITERA 2019 DESA DURIAN "); 
    Serial.begin(9600);   
    luasalas = 950 ;
    
   //menggunakan baut komunikasi 9600 pada serial monitor
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Arduino with Module GSM is ready");
 
    //menggunakan baut komunikasi 9600 antara module gsm dengan arduino
    SIM800L.begin(9600);  
    Serial.println("Module dimulai pada serial komunikasi 9600");
    delay(500);//waktu jeda 1 detik
    Serial.println("SIM800L SIAP DIGUNAKAN!");
   

}

boolean henti_loop () {
  int value= analogRead(air);

  if (henti==false) {
  if (value <= 500 ){
  Serial.println("Set format SMS ke ASCII"); //menset format SMS
  SIM800L.write("AT+CMGF=1\r\n"); //Prosedur penulisan oleh module sim800l
  delay(500); //waktu jeda 1 detik
 
  Serial.println("SIM800 Set SMS ke Nomor Tujuan");
  //silahkan ganti no hp nya menjadi no hp ANDA
  SIM800L.write("AT+CMGS=\"085273362277\"\r\n");
  delay(500);
   
  Serial.println("Module mengirimkan SMS ke no tujuan");
  //isi SMS yang ditujukan ke no hp diatas
  
  SIM800L.write("Peringatan Tandon Habis "); 
  delay(500);
   
  Serial.println("Ketik pada keyboard Ctrl+Z atau ESC > keluar menu ini");
  SIM800L.write((char)26);
  delay(500);
     
  Serial.println("SMS Selesai Dikirim!");
  
  } }
  henti = true ;
  return henti ;
}

void loop() {
  digitalWrite(Relay1, StatRelay1);
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  timer = pulseIn(ECHOPIN, HIGH);
  jarak= timer/58;
  T_air = 28.5 - jarak;
  Vol = luasalas * T_air;
  vol = Vol / 1000; 
//sms 

henti = henti_loop () ;
// tandon 

if (vol <= 5  ) {
  
    StatRelay1= ON ;
    delay (10) ;
   } 
   else if (vol>= 18 ) {
  
    StatRelay1 = OFF ;
    delay (10) ;

    
   }
   
   
  int value= analogRead(air);  
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Level Air = ");
  Serial.println(value);           
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
   int i;
 
  lcd.setCursor(1,1 );
  lcd.print("SUHU = ");
  lcd.println(DHT.temperature);
  lcd.print("KELEMBAPAN = ");
  lcd.println(DHT.humidity);
  for (i = 0 ; i < 16; i ++) {
      lcd.scrollDisplayLeft();
      delay(300);
}
  delay(1010);  

}
