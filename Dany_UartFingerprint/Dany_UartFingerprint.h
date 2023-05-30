#ifndef UARTF
#define UARTF

#if ARDUINO < 100
  #include <WProgram.h>
#else
    #include <Arduino.h>
#endif
#include  <SoftwareSerial.h>

#define ACK_SUCCESS 		0x00
#define ACK_FAIL		  	0x01
#define ACK_FULL		  	0x04
#define ACK_NOUSER			0x05
#define ACK_USER_EXIST	0x06
#define ACK_FIN_EXIST		0x07
#define ACK_TIMEOUT			0x08

#define CMD_SLEEP		  	0x2c
#define CMD_MODE		  	0x2d
#define CMD_ADD1		  	0x01
#define CMD_ADD2		  	0x02
#define CMD_ADD3		  	0x03
#define CMD_DEL_USER		0x04
#define CMD_D_ALL_USER	0x05
#define CMD_CNT_USER		0x09
#define CMD_COMP_1_1  	0x0b
#define CMD_COMP_I_N		0x0c
#define CMD_USER_PRIV		0x0A
#define CMD_GET_VER			0x26
#define CMD_COMP_LV			0x28
#define CMD_UPLOAD			0x24
#define CMD_UPLOAD_EX	  0x23
#define CMD_GET_BASE    0x31

#define IMAGE_LENGTH          9800
#define EIGENVALUE_LENGTH     193
#define BUFFER_SIZE           8
#define DATA_SIZE             4

#define UART_BAUD       19200


class Dany_UartFinger {
  public:

    Dany_UartFinger(SoftwareSerial *);
    Dany_UartFinger(HardwareSerial *);
    
    int begin();
    void Sleep();
    void Mode(byte value);
    int AddUser1(uint16_t id,byte privilege);
    int AddUser2(uint16_t id,byte privilege);
    int AddUser3(uint16_t id,byte privilege);
    int DelUser();
    int DelUser(uint16_t id);
    void CountUser();
    int Compare(uint16_t id);
    int Compare();
    int GetPrivilege(uint16_t id);
    void GetRespon();
    void GetDataPacket();
    void GetBase(uint16_t id);
    void GetVersion();
    void PrintGetData();
    uint16_t GetPacket();
    byte GetFeedback();
    void PrintSendData();

    
  private:
    byte FORMAT[8] = {0xf5,0x00,0x00,0x00,0x00,0x00,0x00,0xf5};
    
    SoftwareSerial *sofSeri = NULL;
    HardwareSerial *hwSeri = NULL;
    Stream *Seri;
    int send(byte *);
    byte DATA[8] = {0,};
    byte trans[8] = {0,};
};


#endif
