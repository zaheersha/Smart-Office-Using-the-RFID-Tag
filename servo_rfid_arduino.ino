// WELCOME TO THE BACKBENCHERS YOUTUBE CHANNEL
// PLEASE SUBSCRIBE TO MY CHANNEL
// PRESS THE BELL ICON TO GET NOTIFIED MY LATEST VIDEO UPDATE
// THEANKS FOR WATCHING
//zaheer before going to access it u need to go to msc522 lib. and click on dumpinfo and change the sada(ss_pin) and rst pins and upload the codes;
// next u have to place the cards one after the other and note the keys 
//copy one of the key of the card and past it in the code so that u can give access to only that card.

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 6
#define RST_PIN 9

#define BUZZER 2 //buzzer pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  //
  //
  //
  //("xxxxxxxxxxxxxxxxxxxx")= paste the card key hear after getting the ids of the card from files>>examples>>msc522>>dumpinfo>>card1+card2
  
  if (content.substring(1) == "83 8D 1B 03") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
    myServo.write(180);
    delay(5000);
    myServo.write(0);
  }
 
 else   {
    Serial.println(" Access denied");
    tone(BUZZER, 300);
    delay(1000);
    noTone(BUZZER);
  }
}
