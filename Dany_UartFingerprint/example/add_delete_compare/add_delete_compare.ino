#include <SoftwareSerial.h>
#include <Dany_UartFingerprint.h>
SoftwareSerial sofSeri(2,3);
Dany_UartFinger fin = MECHA_UARTFinger(&sofSeri);

byte userPriv = 3;
int userId;

void setup() 
{
  Serial.begin(9600);
  fin.begin();
}

String inString = "";
uint16_t integer;

bool rolle = false;
bool match = false;
bool erase = false;

void rollefinger(void)
{
    while(Serial.available())
    {
      int inchar = Serial.read();
      if(isDigit(inchar)){inString+=(char)inchar;} 
      if(inchar == '\n')
      {
        integer = inString.toInt();
        inString = "";
      }
    }
    userId = integer;
    if(userId <= 0){return -1;}
    if(userId > 2000)
    {
      Serial.print("over capacity / rolle exit !!");
      integer = 0; rolle = false; return -1;
    }
    Serial.print("#ID : ");
    Serial.println(userId);
    
    fin.AddUser1(userId,userPriv); fin.PrintSendData();
    fin.GetRespon(); fin.PrintGetData();
    if(ACK_SUCCESS == fin.GetFeedback())
    {Serial.println("1/3");}
    
    fin.AddUser2(userId,userPriv); fin.PrintSendData();
    fin.GetRespon(); fin.PrintGetData();
    if(ACK_SUCCESS == fin.GetFeedback())
    {Serial.println("2/3");}
    
    fin.AddUser3(userId,userPriv); fin.PrintSendData();
    fin.GetRespon(); fin.PrintGetData();
    if(ACK_SUCCESS == fin.GetFeedback())
    {Serial.println("3/3");}
    
    integer = 0;
}

void comparefinger()
{
    delay(2000);
    fin.Compare(); fin.PrintSendData();
    fin.GetRespon(); fin.PrintGetData(); 
    
    if(ACK_NOUSER != fin.GetFeedback())
    {
      Serial.print("USER ID: ");
      Serial.println(fin.GetPacket());
    }
    else 
    {
      Serial.print("ERROR Feedback is: ");
      Serial.println(fin.GetFeedback(),HEX);
      match = false;
    }
}

void cleanfinger()
{
    fin.DelUser(); fin.PrintSendData();
    fin.GetRespon(); fin.PrintGetData();
    Serial.println("Data finger reset !!");
    erase = false;
}

void loop() 
{
  char ext = Serial.read();
  if(ext == 'r'){rolle = true; match = erase = false;} else
  if(ext == 'c'){match = true; rolle = erase = false;} else
  if(ext == 'd'){erase = true; rolle = match = false;}  
    while(rolle){rollefinger();} 
    while(match){comparefinger();}
    while(erase){cleanfinger();}
}
