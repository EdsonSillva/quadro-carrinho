/******************************************************
 * Rotinas para controle de acesso na memória EEPROM
 * Desenvolvido por Edson Silva
 * I2C - Utiliza os pinos SDA(4) e SCL(5)
 * Date: 01/06/19  
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

#define AddressDataSegTxt 16
#define AddressQtdeChar   AddressDataSegTxt + 0x00
#define AddressIniTexto   AddressDataSegTxt + 0x01

char    TextoMsg[50] = {0};

byte      pinAcaoCtr              = 0x00;
bool      pinAcaoCtrValor         = false;

void SetupEEPROM(){
  int addressI2c = 0x0A;
  Wire.begin(addressI2c);           // entra no barramento I2c

#if DEBUG  
  if(Serial) Serial.print("\nIniciado o I2c no endereço: 0x0"), Serial.print(addressI2c, HEX), Serial.print("  Decimal: "), Serial.print(addressI2c, DEC);
#endif
}

byte getPinLedUsoEEPROM(){
  return pinLedUsandoEEPROM;
}

void StartSerial() {
  Serial.begin(9600);
  while(!Serial);  
}

void getDadosOnEEPROM(byte *pCodeAcao, byte *pR, byte *pG, byte *pB, byte *pBrilho) {

  *pCodeAcao  = LerEEPROM((int)AddressCodeAcao);
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

//  Serial.print("Gravando Dado = "), Serial.print(Dado), Serial.print(" Address = "), Serial.println(offSet);
  starEEPROMsetOffSet(offSet);
  Wire.write((byte)Dado);
  Wire.endTransmission();
  delay(5);
}

//byte LerEEPROM(int offSet) {
//
//  byte Dado = 0xFF;
//  
//  pinAcaoCtr = getPinAcao();
//
//  starEEPROMsetOffSet(offSet);
//  Wire.endTransmission();
//  Wire.requestFrom(deviceEEPROM, 1);
//    while(!Wire.available()){
//     Serial.print("Aguardando o Wire ficar Available"), Serial.print("..."), Serial.print(" para Address = "), Serial.println(offSet);      
//     Serial.print("Lendo Pino Ação"), Serial.println("...");
//      pinAcaoCtrValor = digitalRead(pinAcaoCtr);
//     Serial.println("Lido Pino Ação");
//      if(pinAcaoCtrValor==false){
//          Serial.print("Pino ação Desligado"), Serial.println("...");
//          Wire.endTransmission();
//          return 0;
//      }
//    }
//    Serial.print("Wire Disponível... Lendo Dado"), Serial.println("...");
//    Dado = Wire.read();
//    Serial.print("Wire Disponível... Dado Lido:"), Serial.println(Dado);
//  Wire.endTransmission();
////  if(Serial) {
////    Serial.print("Lendo Dado = "), Serial.print(Dado), Serial.print(" Char("), Serial.write(Dado), Serial.print(") Address = "), Serial.println(offSet);
////  }
//  return Dado;
//}


byte LerEEPROM(int offSet) {

  byte Dado = 0xFF;
  
//  pinAcaoCtr = getPinAcao();

  starEEPROMsetOffSet(offSet);
  Wire.endTransmission();
  Wire.requestFrom(deviceEEPROM, 1);
    while(!Wire.available()){
//     Serial.print("Aguardando o Wire ficar Available"), Serial.print("..."), Serial.print(" para Address = "), Serial.println(offSet);      
//     Serial.print("Lendo Pino Ação"), Serial.println("...");
//      pinAcaoCtrValor = digitalRead(pinAcaoCtr);
//     Serial.println("Lido Pino Ação");
//      if(pinAcaoCtrValor==false){
//          Serial.print("Pino ação Desligado"), Serial.println("...");
//          Wire.endTransmission();
//          return 0;
//      }
    }
//    Serial.print("Wire Disponível... Lendo Dado"), Serial.println("...");
    Dado = Wire.read();
//    Serial.print("Wire Disponível... Dado Lido:"), Serial.println(Dado);
  Wire.endTransmission();
  
//  if(Serial) {
//    Serial.print("Lendo Dado = "), Serial.print(Dado), Serial.print(" Char("), Serial.write(Dado), Serial.print(") Address = "), Serial.println(offSet);
//  }
  
  return Dado;
}



/* DIFERENTE
byte LerEEPROM(int offSet) {

  byte Dado = 0xFF;
  starEEPROMsetOffSet(offSet);
  Wire.endTransmission();
  Wire.requestFrom(deviceEEPROM, 1);
//    while(!Wire.available());
    if(Wire.available())
      Dado = Wire.read();
    else {
       if(Serial) {
          Serial.print(".....Wire não disponível..."), Serial.print(" Address = "), Serial.println(offSet);
       } 
    }
  Wire.endTransmission();
  if(Serial) {
    Serial.print("Lendo Dado = "), Serial.print(Dado), Serial.print(" Address = "), Serial.println(offSet);
  }
  return Dado;
}
*/
void starEEPROMsetOffSet(unsigned int offSet) {
  Wire.beginTransmission(deviceEEPROM);
    Wire.write( (int)(offSet >>    8) );
    Wire.write( (int)(offSet &  0xFF) );
}

/* *******************************************************************
 * Definição da classe de controle das informações na menória EEPROM 
 * *******************************************************************/
/*
class DadosEEPROM {
  private:
    byte _CodeAcao;
    byte _R;
    byte _G;
    byte _B;
    byte _Brilho;

  public:
    void setCodeAcao(byte);
    void setR(byte);
    void setG(byte);
    void setB(byte);
    void setBrilho(byte);

    byte getCodeAcao();
    byte getR();
    byte getG();
    byte getB();
    byte getBrilho();

};
void DadosEEPROM::setCodeAcao(byte CodeAcao){
  _CodeAcao = CodeAcao;
}
void DadosEEPROM::setR(byte R) {
  _R = R;
}
void DadosEEPROM::setG(byte G) {
  _G = G;
}
void DadosEEPROM::setB(byte B) {
  _B = B;
}
void DadosEEPROM::setBrilho(byte Brilho) {
  _Brilho = Brilho;
}
byte DadosEEPROM::getCodeAcao(){
  return _CodeAcao;
}
byte DadosEEPROM::getR() {
  return _R;
}
byte DadosEEPROM::getG() {
  return _G;
}
byte DadosEEPROM::getB() {
  return _B;
}
byte DadosEEPROM::getBrilho() {
  return _Brilho;
}

void getDadosOnEEPROM() {

  Dados.setCodeAcao(LerEEPROM((int)AddressCodeAcao));
  Dados.setR(LerEEPROM((int)AddressR));
  Dados.setG(LerEEPROM((int)AddressG));
  Dados.setB(LerEEPROM((int)AddressB));
  Dados.setBrilho(LerEEPROM((int)AddressBrilho));
}

DadosEEPROM Dados;
*/
/*
byte CByteSerial(){

  byte  Byte[] = {0xff, 0xff, 0xff};
  byte  NumByte = 0xff;
  char  Letra = 0xff;
  String  strNum          = "";
  
  for( int x = 0; x < (Serial.available()+ 15); x++){
    Letra = char(Serial.read());
    if(isAlphaNumeric(Letra)) strNum.concat(Letra);
    delay(1);
  }
  NumByte = byte(strNum.toInt());
  return byte(strNum.toInt());
  
}
*/
