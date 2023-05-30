#include <SoftwareSerial.h>
#include <Dany_UartFingerprint.h>
SoftwareSerial sofSeri(2,3);
Dany_UartFinger fin = Dany_UartFinger(&sofSeri);
void setup() {
  Serial.begin(9600);
  fin.begin();
  fin.DelUser();
  fin.GetRespon();
}

void loop() {
}
