/******************************************************
 * Rotinas para controle de acesso na memória EEPROM
 * Desenvolvido por Edson Silva
 * I2C - Utiliza os pinos SDA(4) e SCL(5)
 * Date: 01/06/19  
 *****************************************************/

#include <Wire.h>

#define pinLedUsandoEEPROM    11
#define pinLedAlerta          13

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
  Wire.begin();                           // entra no barramento I2c
  pinMode(pinLedAlerta, OUTPUT);
  digitalWrite(pinLedAlerta, LOW);
}

byte getPinLedUsoEEPROM(){
  return pinLedUsandoEEPROM;
}

void AlertaEEPROMNaoResponde(){
    BeepBuzzer(),digitalWrite(pinLedAlerta,HIGH),delay(500),BeepBuzzer(),digitalWrite(pinLedAlerta,LOW), delay(200);
    BeepBuzzer(),digitalWrite(pinLedAlerta,HIGH),delay(500),BeepBuzzer(),digitalWrite(pinLedAlerta,LOW);
}

void getDadosOnEEPROM(byte *pCodeAcao, byte *pR, byte *pG, byte *pB, byte *pBrilho) {

  digitalWrite(pinLedUsandoEEPROM, HIGH);
    *pCodeAcao  = LerEEPROM((int)AddressCodeAcao);
    if(*pCodeAcao == 254){
      AlertaEEPROMNaoResponde();
      return;
    }
    *pR         = LerEEPROM((int)AddressR);
    *pG         = LerEEPROM((int)AddressG);
    *pB         = LerEEPROM((int)AddressB);
    *pBrilho    = LerEEPROM((int)AddressBrilho);
  digitalWrite(pinLedUsandoEEPROM,LOW);
}

void setDadosOnEEPROM(byte CodeAcao, byte R, byte G, byte B, byte Brilho) {

  digitalWrite(pinLedUsandoEEPROM, HIGH);
    GravarEEPROM((int)AddressR, R);
    GravarEEPROM((int)AddressG, G);
    GravarEEPROM((int)AddressB, B);
    GravarEEPROM((int)AddressBrilho, Brilho);
    GravarEEPROM((int)AddressCodeAcao, CodeAcao);
  digitalWrite(pinLedUsandoEEPROM,LOW);
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

//  Serial.print("Gravando Dado = "), Serial.print(Dado), Serial.print(" Address = "), Serial.println(offSet);
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
