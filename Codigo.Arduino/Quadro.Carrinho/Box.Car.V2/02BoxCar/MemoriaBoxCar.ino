/******************************************************
 * Rotinas para controle de acesso na memória EEPROM
 * Desenvolvido por Edson Silva
 * I2C - Utiliza os pinos SDA(4) e SCL(5)
 * Date: 01/06/19
 * Alteração: jul/22
 *****************************************************/

#include <Wire.h>

#define pinLedUsandoEEPROM    11

#define deviceEEPROM          0x50
#define AddressDataSeg        0x00
#define AddressCodeAcao       AddressDataSeg + 0x00
#define AddressR              AddressDataSeg + 0x01
#define AddressG              AddressDataSeg + 0x02
#define AddressB              AddressDataSeg + 0x03
#define AddressBrilho         AddressDataSeg + 0x04
#define AddressBeep           AddressDataSeg + 0x05

#define AddressDataSegTxt     16
#define AddressQtdeChar       AddressDataSegTxt + 0x00
#define AddressIniTexto       AddressDataSegTxt + 0x01

#define CODE_EEPROM_NOT_AVAILABLE         254

char    TextoMsg[50] = {0};

void SetupEEPROM(){
  Wire.begin();                       // entra no barramento I2c (passivo)
}

byte getPinLedUsoEEPROM(){
  return pinLedUsandoEEPROM;
}

void getDadosOnEEPROM(byte *pCodeAcao, byte *pR, byte *pG, byte *pB, byte *pBrilho) {

  *pCodeAcao  = LerEEPROM((int)AddressCodeAcao);
  if(*pCodeAcao == 254){
    // AlertaEEPROMNaoResponde();   // Não implementado neste segundo arduino
    return;
  }
  *pR         = LerEEPROM((int)AddressR);
  *pG         = LerEEPROM((int)AddressG);
  *pB         = LerEEPROM((int)AddressB);
  *pBrilho    = LerEEPROM((int)AddressBrilho);
}


void setDadosOnEEPROM(byte CodeAcao, byte R, byte G, byte B, byte Brilho) {

  GravarEEPROM((int)AddressR, R);
  GravarEEPROM((int)AddressG, G);
  GravarEEPROM((int)AddressB, B);
  GravarEEPROM((int)AddressBrilho, Brilho);
  GravarEEPROM((int)AddressCodeAcao, CodeAcao);
}

void setTextoOnEEPROM(char Texto[], byte QtdeChar) {
  
  int Address   = AddressIniTexto;                      // Pega o endereço inicial da mensagem

  GravarEEPROM((int)AddressQtdeChar, QtdeChar);         // Grava o tamanho da Mensagem
  for(byte P = 0; P <= QtdeChar; P++) {
      GravarEEPROM((int)Address, Texto[P]);
      Address++;
  }
}

void getTextoOnEEPROM(char Texto[], byte *pQtdeChar) {
 
  int Address   = AddressIniTexto;                          // Pega o endereço inicial da mensagem
  int QtdeChar  = LerEEPROM((int)AddressQtdeChar);          // Le o tamanho da Mensagem

  *pQtdeChar = QtdeChar;
  for(byte P = 0; P <= QtdeChar; P++) {
      Texto[P] = LerEEPROM((int)Address);
      Address++;
  }
}

void GravarEEPROM(int offSet, unsigned int Dado) {

  starEEPROMsetOffSet(offSet);
  Wire.write((byte)Dado);
  Wire.endTransmission();
  delay(5);
}

byte LerEEPROM(int offSet) {

  byte            Dado = 0xFF;
  unsigned long   MaxWait = millis() + 10000;        // Seta o tempo máximo de 10 segundos aguardando a resposta do device EEPROM
  bool            IsMaxWait = false;
  
  starEEPROMsetOffSet(offSet);
  Wire.endTransmission();
  Wire.requestFrom(deviceEEPROM, 1);
  
    while(!Wire.available()){
      if(MaxWait < millis()){
        IsMaxWait = true;
        Dado = CODE_EEPROM_NOT_AVAILABLE;
        break;              // Sai do loop
      }
    }

    if(!IsMaxWait) {
      Dado = Wire.read();
    }
    Wire.endTransmission();
  return Dado;
}

void starEEPROMsetOffSet(unsigned int offSet) {
  Wire.beginTransmission(deviceEEPROM);
    Wire.write( (int)(offSet >>    8) );
    Wire.write( (int)(offSet &  0xFF) );
}
