/*
 * Dany Maulana UART Fingerprint Example
 */
#include <SoftwareSerial.h>
#include <Dany_UartFingerprint.h>
#define NEW_USER_ID 1 //The ID of the user to be newly registered is set here.
#define NEW_USER_PRIV 3 //Set the permissions of the user to be newly registered here.
SoftwareSerial sofSeri(2,3);
Dany_UartFinger fin = Dany_UartFinger(&sofSeri);

void setup() {
  Serial.begin(9600);
  fin.begin();
  fin.AddUser1(NEW_USER_ID,NEW_USER_PRIV);
  //NEW_USER_ID is the user ID, NEW_USER_PRIV is the user privilege. Repeat AddUser1,2,3 3 times
  //the NEW_USER_ID is user ID, NEW_USER_PRIV is users Privilege. AddUser1,2,3  3times repeat
  fin.GetRespon();
  //always have the Respon
  if(ACK_SUCCESS == fin.GetFeedback()){
    Serial.println("Success add user 1/3");
  }
  fin.AddUser2(NEW_USER_ID,NEW_USER_PRIV);
  fin.GetRespon();
  if(ACK_SUCCESS == fin.GetFeedback()){
    Serial.println("Success add user 2/3");
  }
  fin.AddUser3(NEW_USER_ID,NEW_USER_PRIV);
  fin.GetRespon();
  if(ACK_SUCCESS == fin.GetFeedback()){
    Serial.println("Success add user 3/3");
  }
}

void loop() {
  delay(5000);
  fin.Compare();
  //Compare the fingerprint
  fin.GetRespon(); 
  if(ACK_NOUSER != fin.GetFeedback()){
    Serial.print("USER ID: ");
    Serial.println(fin.GetPacket());
  }else {
    Serial.print("ERROR Feedback is: ");
    Serial.println(fin.GetFeedback(),HEX);
  }
}