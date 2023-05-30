#include "Dany_UartFingerprint.h"

Dany_UartFinger::Dany_UartFinger(SoftwareSerial *Serial){
  sofSeri = Serial;
  Seri    = sofSeri;
}

Dany_UartFinger::Dany_UartFinger(HardwareSerial *Serial){
  hwSeri  = Serial;
  Seri    = hwSeri;
}

int Dany_UartFinger::begin(){
  if(hwSeri){hwSeri->begin(UART_BAUD); return 0;}
  if(sofSeri){sofSeri->begin(UART_BAUD); return 0;}
  return -1;
}

void Dany_UartFinger::Sleep(){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_SLEEP;
  send(CMD);
}

void Dany_UartFinger::Mode(byte value){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_MODE;
  CMD[4] = value;
  send(CMD);
}

void Dany_UartFinger::GetBase(uint16_t id){
  if(id>0xfff) return -1;
  byte idL = (id & 0x00ff);
  byte idH = (id & 0xff00) >> 8;
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_GET_BASE;
  CMD[2] = idH;
  CMD[3] = idL;
  send(CMD);
}


int Dany_UartFinger::AddUser1(uint16_t id,byte privilege){
  if(id>0xfff) return -1;
  byte idL = (id & 0x00ff);
  byte idH = (id & 0xff00) >> 8;
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_ADD1;
  CMD[2] = idH;
  CMD[3] = idL;
  CMD[4] = privilege;
  send(CMD);
}

int Dany_UartFinger::AddUser2(uint16_t id,byte privilege){
  if(id>0xfff) return -1;
  byte idL = (id & 0x00ff);
  byte idH = (id & 0xff00) >> 8;
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_ADD2;
  CMD[2] = idH;
  CMD[3] = idL;
  CMD[4] = privilege;
  send(CMD);
  return 0;
}

int Dany_UartFinger::AddUser3(uint16_t id,byte privilege){
  if(id>0xfff) return -1;
  byte idL = (id & 0x00ff);
  byte idH = (id & 0xff00) >> 8;
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_ADD3;
  CMD[2] = idH;
  CMD[3] = idL;
  CMD[4] = privilege;
  send(CMD);
  return 0;
}

int Dany_UartFinger::DelUser(){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_D_ALL_USER;
  send(CMD);
  return 0;
}

int Dany_UartFinger::DelUser(uint16_t id){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_DEL_USER;
  if(id>0xfff) return -1;
  byte idL = (id & 0x00ff);
  byte idH = (id & 0xff00) >> 8;
  CMD[2] = idH;
  CMD[3] = idL;
  send(CMD);
  return 0;
}

void Dany_UartFinger::CountUser(){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_CNT_USER;
  send(CMD);
}

void Dany_UartFinger::GetVersion(){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_UPLOAD_EX;
  send(CMD);
}

int Dany_UartFinger::Compare(uint16_t id){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_COMP_1_1;
  if(id>0xfff) return -1;
  byte idL = (id & 0x00ff);
  byte idH = (id & 0xff00) >> 8;
  CMD[2] = idH;
  CMD[3] = idL;
  send(CMD);
  return 0;
}

int Dany_UartFinger::Compare(){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_COMP_I_N;
  send(CMD);
  return 0;
}

void Dany_UartFinger::GetRespon(){
  int cnt = 0;
  while(cnt < 20){
    if(Seri->available()){
      DATA[cnt++] = Seri->read();
    }
  }
  return;
}


// void Dany_UartFinger::GetDataPacket()
// {
//   int cnt = 0;
//   int l_packet = 0;
//   while(cnt < 8)
//   {
//     if(Seri->available()){
//       DATA[cnt++] = Seri->read();
//     }
//   }
//   if(l_packet > 0){
//     while(l_packet >= 0){
//         if(Seri->available()){
//         DATA[cnt++] = Seri->read();
//       }
//     }
//   }
//   return;
// }


// Editor by Dany Maulana :
void Dany_UartFinger::PrintGetData(){
  int i;
  Serial.print("RX : ");
  for(i = 0; i<20; i++){
    Serial.print(DATA[i],HEX);
    Serial.print(",");
  }
  Serial.print("::");
  Serial.print(i);
  Serial.print("::");
  Serial.println();
  return;
}


uint16_t Dany_UartFinger::GetPacket(){
  return ((DATA[2] << 8)|(DATA[3]));
}

byte Dany_UartFinger::GetFeedback(){
  return DATA[4];
}


int Dany_UartFinger::GetPrivilege(uint16_t id){
  byte CMD[8];
  for(int i = 0; i<8;i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_USER_PRIV;
  if(id>0xfff) return -1;
  byte idL = (id & 0x00ff);
  byte idH = (id & 0xff00) >> 8;
  CMD[2] = idH;
  CMD[3] = idL;
  send(CMD);
  return 0;
}

int Dany_UartFinger::send(byte *data){
  byte cheker = 0x00;
  for(int i = 1; i < 6; i++){
    cheker ^= data[i];
  }
  data[6] = cheker;
  for(int i = 0;i < 8;i++){
    trans[i] = data[i];
    Seri->write(data[i]);
  }
}


// Editor by Dany Maulana :
void Dany_UartFinger::PrintSendData(){
  Serial.print("TX : ");
  for(int i = 0; i<8; i++){
    Serial.print(trans[i],HEX);
    Serial.print(",");
  }
  Serial.println();
  return;
}