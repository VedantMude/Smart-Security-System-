#include <SoftwareSerial.h>
#include "Arduino.h"
#include <EMailSender.h>
#include <ESP8266WiFi.h>
#include <Keypad.h>
#include <Servo.h>
Servo myservo; 
int pos = 180;
int count = 0;
int count1 = 0;
const int ROW_NUM = 4;     //four rows
const int COLUMN_NUM = 4;  //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte pin_rows[ROW_NUM] = { D7, D6, D5, D4 };       //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = { D3, D2, D1, D0 };  //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
int num = random(1000,9999);
const String otp = String(num);


String password_1 = otp;
String mypassword;
// const String password_1 = otp; // change your password here
// int input_password[5];
// Servo myservo; 

int counter = 0;
int attempts = 0;
int max_attempts = 3;

// int pos = 0;



const char* ssid = "Redmi 10 Prime";
const char* password = "vedant@2003";

uint8_t connection_state = 0;
uint16_t reconnect_interval = 10000;

EMailSender emailSend("sy10edi@gmail.com", "Vedant@522003");

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
    static uint16_t attempt = 0;
    Serial.print("Connecting to ");
    if(nSSID) {
        WiFi.begin(nSSID, nPassword);
        Serial.println(nSSID);
    }

    uint8_t i = 0;
    while(WiFi.status()!= WL_CONNECTED && i++ < 50)
    {
        delay(200);
        Serial.print(".");
    }
    ++attempt;
    Serial.println("");
    if(i == 51) {
        Serial.print("Connection: TIMEOUT on attempt: ");
        Serial.println(attempt);
        if(attempt % 2 == 0)
            Serial.println("Check if access point available or SSID and Password\r\n");
        return false;
    }
    Serial.println("Connection: ESTABLISHED");
    Serial.print("Got IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void Awaits()
{
    uint32_t ts = millis();
    while(!connection_state)
    {
        delay(50);
        if(millis() > (ts + reconnect_interval) && !connection_state){
            connection_state = WiFiConnect();
            ts = millis();
        }
    }
}
void setup() {
  // put your setup code here, to run once:
 
  Serial.begin(115200);
  Serial.println("Hello");
  // input_password.reserve(32); 
  // myservo.attach(D8);

  connection_state = WiFiConnect(ssid, password);
  if(!connection_state)  // if not connected to WIFI
      Awaits();          // constantly trying to connect
  
  myservo.attach(D8);

    
  Serial.println(num);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  while (Serial.available()){
    int data = Serial.read();

    if(data == '0'){
      count = count + 1;
      if(count == 30){
        mail();
        keypadfunction();
        // servo();
        // keypad1();
      }
      
      
      
    }
    else if(data == '1'){
      count1 = count1 + 1;
      if(count1 == 100){
        mail1();
      }
    }
    
  }
  keypadfunction(); 
}
void mail(){
    EMailSender::EMailMessage message;
    
    message.subject = "Password";
    message.message = "Here is your Password : " + otp;
    

    EMailSender::Response resp = emailSend.send("sy10edi@gmail.com", message);

    Serial.println("Sending status: ");

    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);
}
void mail1(){
    EMailSender::EMailMessage message;
    
    message.subject = "Warning";
    message.message = "Unknown Person Detected";
    

    EMailSender::Response resp = emailSend.send("sy10edi@gmail.com", message);

    Serial.println("Sending status: ");

    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);
}


void keypadfunction() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    counter = counter + 1;
  }
  if (key == '1') {

    mypassword = mypassword + 1;
  }

  if (key == '2') {

    mypassword = mypassword + 2;
  }

  if (key == '3') {

    mypassword = mypassword + 3;
  }

  if (key == '4') {

    mypassword = mypassword + 4;
  }

  if (key == '5') {

    mypassword = mypassword + 5;
  }

  if (key == '6') {

    mypassword = mypassword + 6;
  }

  if (key == '7') {

    mypassword = mypassword + 7;
  }

  if (key == '8') {

    mypassword = mypassword + 8;
  }

  if (key == '9') {

    mypassword = mypassword + 9;
  }

  if (key == '0') {

    mypassword = mypassword + 0;
  }


  if (mypassword.length() == 4) {
    Serial.println(mypassword);

    if (password_1 == mypassword) {
      Serial.println("Correct Password");
     
      servo_1();
      delay(5000);

      mypassword = "";
      counter = 0;

    } else {
      Serial.println("wrong");

      attempts = attempts + 1;
      if (attempts >= max_attempts) {
        attempts = 0;
      }
      mypassword = "";
      counter = 0;
    }
  }
}

void servo_1(){
  for (pos =180; pos >=0; pos -= 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos); // tell servo to go to position in variable 'pos'
     }
  pos=180;
}
