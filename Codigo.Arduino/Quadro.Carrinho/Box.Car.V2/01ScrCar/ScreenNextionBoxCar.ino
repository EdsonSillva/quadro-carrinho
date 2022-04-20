// ************************************************
// Biblioteca Nextion (screen)
// Desenvolvido por Edson Silva
// Date: 26/05/18
// Comunicação Rx e Tx
// ************************************************

#include <Nextion.h>
//#include <SoftwareSerial.h>
//SoftwareSerial HMISerial(10, 11);


/* Declaração dos ID's das Janelas
 * ------------------------------- */ 
uint8_t const JanelaSplash              =  0,
              JanelaMenu_Acao           =  1,
              JanelaSelecao             =  2,
              JanelaConfigMain          =  3,
              JanelaConfigDataHora      =  4,
              JanelaConfigArduino       = 12,
              JanelaVarGlobais          =  8,
              JanelaCreditos            =  9;

/* Declaração dos ID's dos Objetos
 * ------------------------------- */
uint8_t const IDAcaoArduino             =  1,
              IDStandBy                 = 29,
              IDArduinoExec             =  3,
              IDLDR                     = 24,
              IDR                       = 20,
              IDG                       = 21,
              IDB                       = 22,
              IDBrilho                  = 23,
              IDCorRGB                  = 19,
              IDCode                    = 25,
              IDDoW                     = 26,
              IDTexto                   = 26,
              IDTextoQtde               = 27,
              IDDia                     =  8,
              IDMes                     =  9,
              IDAno                     = 10,
              IDDoWGlobal               = 12,
              IDHora                    = 13,
              IDMin                     = 14,
              IDSeg                     = 15,
              IDBeep                    = 28,
              IDTempSys                 = 17,
              IDTemp                    = 16,
              IDHumidade                = 18,
              IDDH                      = 11,
              IDMM                      = 12,
              IDAS                      = 13;
 
int           Milenio                   = 2000;

// Declaração dos Objetos das Janelas que serão usados
// ---------------------------------------------------

bool IniciarNextion(){
    bool Ok = false;
    Ok = nexInit();                                        // Necessário usar esta função para estabelecer a conexão com a tela
    delay(500);
    return Ok;
}

void setVarNextion(char VarGlobal[], int TextoLength, String NomeVar) {
//  setVarNextion(VarGlobalID, 24, F("VarGlobais.IDAcaoArduino"));
  
  for(int i=0;i<=TextoLength;i++) {
    VarGlobal[i] = NomeVar.charAt(i);
  }
  VarGlobal[TextoLength] = '\0';    // Indica fim do array de char
}

byte getAcaoOnScreen(){

  uint32_t value = 0;

  NexVariable AcaoArduino = NexVariable(JanelaVarGlobais, IDAcaoArduino, "");
  AcaoArduino.getValueByID(&value);
 
  return (byte)value;
}

byte getStandByOnScreen(){

  uint32_t value = 1;     //Se não retorna nada mantem em stand by

  NexVariable StandBy = NexVariable(JanelaVarGlobais, IDStandBy, "");  
  StandBy.getValueByID(&value);
 
  return (byte)value;
}

void setAcaoOnScreen(uint32_t Acao){
  
  NexVariable AcaoArduino = NexVariable(JanelaVarGlobais, IDAcaoArduino, "");
  AcaoArduino.setValueByID(Acao);
}

/**------------------------------------------------------------------
 * Valores de CodeExec
 * ------------------------------------------------------------------
 * 0 = Estado inicial / sem pedido de execução  - Usado pelo Nextion
 * 1 = Screeen solicitando Execução no Arduino  - Usado pelo Nextion
 * 2 = Arduino Executando                       - Usado pelo Arduino
 * 3 = Execução finalizada pelo Arduino         - Usado pelo Arduino
 * ------------------------------------------------------------------
**/
void setExecArduinoOnScreen(byte CodeExec){

  uint32_t Code = (uint32_t)CodeExec;
    
  NexVariable ArduinoExec = NexVariable(JanelaVarGlobais, IDArduinoExec, ""); 
  ArduinoExec.setValueByID(Code);

}

void setLDROnScreen(){
  
  uint32_t ValorSensor = (uint32_t)getValorMapInvertidoOnLDR();

  NexVariable LDR = NexVariable(JanelaVarGlobais, IDLDR, "");
  LDR.setValueByID(ValorSensor);
  
}

void getRGBBrilhoOnScreen(byte *R, byte *G, byte *B, byte *Brilho){

  uint32_t  value     = -1;

  NexVariable nR      = NexVariable(JanelaVarGlobais,  IDR,       "");
  NexVariable nG      = NexVariable(JanelaVarGlobais,  IDG,       "");
  NexVariable nB      = NexVariable(JanelaVarGlobais,  IDB,       "");
  NexVariable nBrilho = NexVariable(JanelaVarGlobais,  IDBrilho,  "");

  nR.getValueByID(&value),        *R      = (byte)value;
  nG.getValueByID(&value),        *G      = (byte)value;
  nB.getValueByID(&value),        *B      = (byte)value;
  nBrilho.getValueByID(&value),   *Brilho = (byte)value;  
}

void setCodeRGBBrilhoOnScreen(byte CodeAcao, byte R, byte G, byte B, byte Brilho){
  
  NexVariable vaCode = NexVariable(JanelaVarGlobais, IDCode, "");
  vaCode.setValueByID((uint32_t)CodeAcao);

  NexVariable vaR = NexVariable(JanelaVarGlobais, IDR, "");
  vaR.setValueByID((uint32_t)R);

  NexVariable vaG = NexVariable(JanelaVarGlobais, IDG, "");
  vaG.setValueByID((uint32_t)G);

  NexVariable vaB = NexVariable(JanelaVarGlobais, IDB, "");
  vaB.setValueByID((uint32_t)B);

  NexVariable vaBrilho = NexVariable(JanelaVarGlobais, IDBrilho, "");
  vaBrilho.setValueByID((uint32_t)Brilho);

  NexVariable vaRGBNextion = NexVariable(JanelaVarGlobais, IDCorRGB, "");

  uint32_t RGBNextion = (R / 8 * 2048) + (G / 4 *32) + (B / 8);   // Cálculo necessário porque o Nextion trata a cor RGB diferente
  vaRGBNextion.setValueByID(RGBNextion);
  
}

byte getDoWOnScreen(){

  uint32_t    value =   0;
 
  NexSlider   sDoW   =   NexSlider(JanelaConfigDataHora, IDDoW, "sDoW");

  sDoW.getValue(&value);
  return (byte)value;

}

void getDataOnScreen(byte *pDia, byte *pMes, byte *pAno, byte *DoW){

  byte  bDH,  bMM,  bAS, bDoW;

  DataHoraOnScreen(&bDH, &bMM, &bAS);
  bDoW    = getDoWOnScreen();
  *pDia   = bDH;
  *pMes   = bMM;
  *pAno   = bAS;
  *DoW    = bDoW;  
}

void getHoraOnScreen(byte *Hora, byte *Minuto, byte *Segundo) {

  byte  bDH,  bMM,  bAS;
  
  DataHoraOnScreen(&bDH, &bMM, &bAS);
  *Hora      = bDH;
  *Minuto    = bMM;
  *Segundo   = bAS;  
}

void getTextoOnScreen(char Texto[], byte *pQtdeChar){

  uint32_t    value =   -1;

  NexVariable txtTexto      = NexVariable(JanelaVarGlobais, IDTexto,      "");
  NexVariable txtTextoQtde  = NexVariable(JanelaVarGlobais, IDTextoQtde,  "");

  txtTextoQtde.getValueByID(&value);
  *pQtdeChar = (byte)value;

  memset(Texto, 0, sizeof(Texto));    // Inicializa o array de char
  txtTexto.getTextByID(Texto, value);

}

void ShowDataOnScreen(){

  byte       Dia, Mes, Ano, DoW;

  NexVariable nDia    = NexVariable(JanelaVarGlobais,  IDDia, "");
  NexVariable nMes    = NexVariable(JanelaVarGlobais,  IDMes, "");
  NexVariable nAno    = NexVariable(JanelaVarGlobais,  IDAno, "");
  NexVariable nDoW    = NexVariable(JanelaVarGlobais,  IDDoWGlobal, "");
  
  getDataOnDS3231(&Dia, &Mes, &Ano, &DoW, &Milenio);

  nDia.setValueByID((uint32_t)Dia);
  nMes.setValueByID((uint32_t)Mes);
  nAno.setValueByID((uint32_t)(Milenio + Ano));  
  
  nDoW.setValueByID((uint32_t)DoW);

}

void ShowHoraOnScreen(){
  
  byte    Hora, Minuto, Segundo;

  NexVariable nHora    = NexVariable(JanelaVarGlobais, IDHora, "");
  NexVariable nMinuto  = NexVariable(JanelaVarGlobais, IDMin, "");
  NexVariable nSegundo = NexVariable(JanelaVarGlobais, IDSeg, "");

  getHoraOnDS3231(&Hora, &Minuto, &Segundo);

  nHora.setValueByID((uint32_t)Hora), nMinuto.setValueByID((uint32_t)Minuto), nSegundo.setValueByID((uint32_t)Segundo);

}

/*********************************************************************
 * Le a variável Beep do Screen
 *********************************************************************/
bool getBeepOnScreen(){

  uint32_t      value   =   0;

  NexVariable   nBeep   =   NexVariable(JanelaVarGlobais, IDBeep, "");

  nBeep.getValueByID(&value);
  if((bool)value == 1)
    return true;
  return false;
}

/*********************************************************************
 * Le a temperatura do sistema. O sensor fica no device DS3231
 *********************************************************************/
void ShowTempSysOnScreen(){
  
  NexVariable nTempSys = NexVariable(JanelaVarGlobais, IDTempSys, "");
  nTempSys.setValueByID(getTemperaturaSysOnDS3231());

}

/************************************************************************ 
 * Le a temperatura do device DH11 e coloca o valor na variável da Tela
 ************************************************************************/
void ShowTemperaturaOnScreen(){

  uint32_t ValorSensor = (uint32_t)getTemperaturaOnDHT();
   
  NexVariable nTemperatura = NexVariable(JanelaVarGlobais, IDTemp, "");
  nTemperatura.setValueByID(ValorSensor);

}

/********************************************************************** 
 * Le a humidade do device DH11 e coloca o valor na variável  da Tela
 **********************************************************************/
void ShowHumidadeOnScreen(){

  uint32_t ValorSensor = (uint32_t)getHumidadeOnDHT();
  
  NexVariable nHumidade = NexVariable(JanelaVarGlobais, IDHumidade, "");  
  nHumidade.setValueByID(ValorSensor);

}

/***********************************************************
 *  Funções Auxiliares
 ***********************************************************/
void DataHoraOnScreen(byte *pDH, byte *pMM, byte *pAS){

  uint32_t    value =   -1;

  NexSlider   sDH   =   NexSlider(JanelaConfigDataHora, IDDH, "sDH");
  NexSlider   sMM   =   NexSlider(JanelaConfigDataHora, IDMM, "sMM");
  NexSlider   sAS   =   NexSlider(JanelaConfigDataHora, IDAS, "sAS");

  sDH.getValue(&value),   *pDH = (byte)value;
  sMM.getValue(&value),   *pMM = (byte)value;
  sAS.getValue(&value);
  
  if (value < 60) {    // Tela no Screen em Configuração de Hora
   *pAS = (byte)value;
  }
  else {               // Tela no Screen em Configuração de Data
    if (value < 2000) 
       Milenio = 1900;
    else 
       Milenio = 2000;

    *pAS = (byte)(value - Milenio);
  }
}




/*************************************************************
 * 
 * 
 * CÓDIGO QUE EXECUTA BEM, MAS CONSOME MUITA MEMÓRIA SRAM
 * 
 * 
 *************************************************************/

//bool IniciarNextion(){
//    bool Ok = false;
//    Ok = nexInit();                                        // Necessário usar esta função para estabelecer a conexão com a tela
//    delay(500);
//    return Ok;
//}
// 
//byte getAcaoOnScreen(){
//
//  uint32_t value = 0;
//
//  NexVariable IDAcaoArduino = NexVariable(JanelaVarGlobais, 1, "VarGlobais.IDAcaoArduino");
//  IDAcaoArduino.getValue(&value);
// 
//  return (byte)value;
//}
//
//byte getStandByOnScreen(){
//
//  uint32_t value = 1;
//
//  NexVariable IDAcaoArduino = NexVariable(JanelaVarGlobais, 33, "VarGlobais.nStandBy");
//  IDAcaoArduino.getValue(&value);
// 
//  return (byte)value;
//}
//
//
//void setAcaoOnScreen(uint32_t Acao){
//  NexVariable IDAcaoArduino = NexVariable(JanelaVarGlobais, 1, "VarGlobais.IDAcaoArduino");
//  IDAcaoArduino.setValue(Acao);
//}
//
///**------------------------------------------------------------------
// * Valores de CodeExec
// * ------------------------------------------------------------------
// * 0 = Estado inicial / sem pedido de execução  - Usado pelo Nextion
// * 1 = Screeen solicitando Execução no Arduino  - Usado pelo Nextion
// * 2 = Arduino Executando                       - Usado pelo Arduino
// * 3 = Execução finalizada pelo Arduino         - Usado pelo Arduino
// * ------------------------------------------------------------------
//**/
//void setExecArduinoOnScreen(byte CodeExec){
//
//  uint32_t Code = (uint32_t)CodeExec;
//  NexVariable ArduinoExec = NexVariable(JanelaVarGlobais, 3, "VarGlobais.ArduinoExec"); 
//  
//  ArduinoExec.setValue(Code);
//
//}
//
//void setLDROnScreen(){
//  
//  uint32_t ValorSensor = (uint32_t)getValorMapInvertidoOnLDR();
//  NexVariable nLDR = NexVariable(JanelaVarGlobais, 24, "VarGlobais.nLDR");
//  nLDR.setValue(ValorSensor);
//  
//}
//
//void getRGBBrilhoOnScreen(byte *R, byte *G, byte *B, byte *Brilho){
//
//  uint32_t  value     = -1;
//  NexVariable nR      = NexVariable(JanelaVarGlobais,  20, "VarGlobais.nR");
//  NexVariable nG      = NexVariable(JanelaVarGlobais,  21, "VarGlobais.nG");
//  NexVariable nB      = NexVariable(JanelaVarGlobais,  22, "VarGlobais.nB");
//  NexVariable nBrilho = NexVariable(JanelaVarGlobais,  23, "VarGlobais.nBrilho");
//
//  nR.getValue(&value),        *R      = (byte)value;
//  nG.getValue(&value),        *G      = (byte)value;
//  nB.getValue(&value),        *B      = (byte)value;
//  nBrilho.getValue(&value),   *Brilho = (byte)value;  
//}
//
//void setCodeRGBBrilhoOnScreen(byte CodeAcao, byte R, byte G, byte B, byte Brilho){
//  
//  NexVariable vaCode = NexVariable(JanelaVarGlobais, 24, "VarGlobais.vaCode");
//  vaCode.setValue((uint32_t)CodeAcao);
//
//  NexVariable vaR = NexVariable(JanelaVarGlobais, 24, "VarGlobais.vaR");
//  vaR.setValue((uint32_t)R);
//
//  NexVariable vaG = NexVariable(JanelaVarGlobais, 24, "VarGlobais.vaG");
//  vaG.setValue((uint32_t)G);
//
//  NexVariable vaB = NexVariable(JanelaVarGlobais, 24, "VarGlobais.vaB");
//  vaB.setValue((uint32_t)B);
//
//  NexVariable vaBrilho = NexVariable(JanelaVarGlobais, 24, "VarGlobais.vaBrilho");
//  vaBrilho.setValue((uint32_t)Brilho);
//  
//}
//
//byte getDoWOnScreen(){
//
//  uint32_t    value =   0;
//  NexSlider   sDoW   =   NexSlider(JanelaConfigDataHora, 26, "sDoW");
//
//  sDoW.getValue(&value);
//  return (byte)value;
//
//}
//
//void getDataOnScreen(byte *pDia, byte *pMes, byte *pAno, byte *DoW){
//
//  byte  bDH,  bMM,  bAS, bDoW;
//
//  DataHoraOnScreen(&bDH, &bMM, &bAS);
//  bDoW    = getDoWOnScreen();
//  *pDia   = bDH;
//  *pMes   = bMM;
//  *pAno   = bAS;
//  *DoW    = bDoW;  
//}
//
//void getHoraOnScreen(byte *Hora, byte *Minuto, byte *Segundo) {
//
//  byte  bDH,  bMM,  bAS;
//  
//  DataHoraOnScreen(&bDH, &bMM, &bAS);
//  *Hora      = bDH;
//  *Minuto    = bMM;
//  *Segundo   = bAS;  
//}
//
//void getTextoOnScreen(char Texto[], byte *pQtdeChar){
//
//  uint32_t    value =   -1;
//
//  NexVariable txtTexto      = NexVariable(JanelaVarGlobais, 30, "VarGlobais.txtTexto");
//  NexVariable txtTextoQtde  = NexVariable(JanelaVarGlobais, 31, "VarGlobais.txtTextoQtde");
//
//  txtTextoQtde.getValue(&value);
//  *pQtdeChar = (byte)value;
//
//  memset(Texto, 0, sizeof(Texto));    // Inicializa o array de char
//  txtTexto.getText(Texto, value);
//
////  Serial.print(".........Screen *pQtdeChar = "), Serial.println(*pQtdeChar);
////  Serial.print(".........Screen Texto = "), Serial.println(Texto);
// 
//}
//
//void ShowDataOnScreen(){
//
//  byte    Dia, Mes, Ano, DoW;
//  
//  NexVariable nDia    = NexVariable(JanelaVarGlobais,  8, "VarGlobais.nDia");
//  NexVariable nMes    = NexVariable(JanelaVarGlobais,  9, "VarGlobais.nMes");
//  NexVariable nAno    = NexVariable(JanelaVarGlobais, 10, "VarGlobais.nAno");
//  NexVariable nDoW    = NexVariable(JanelaVarGlobais, 12, "VarGlobais.nDoW");
//  
//  getDataOnDS3231(&Dia, &Mes, &Ano, &DoW);
//
//  nDia.setValue((uint32_t)Dia);
//  nMes.setValue((uint32_t)Mes);
//  nAno.setValue((uint32_t)(Milenio + Ano));  
//  nDoW.setValue((uint32_t)DoW);
//
//}
//
//void ShowHoraOnScreen(){
//  
//  byte    Hora, Minuto, Segundo;
//
//  NexVariable nHora    = NexVariable(JanelaVarGlobais, 13, "VarGlobais.nHora");
//  NexVariable nMinuto  = NexVariable(JanelaVarGlobais, 14, "VarGlobais.nMinuto");
//  NexVariable nSegundo = NexVariable(JanelaVarGlobais, 15, "VarGlobais.nSegundo");
//
//  getHoraOnDS3231(&Hora, &Minuto, &Segundo);
//
//  nHora.setValue((uint32_t)Hora), nMinuto.setValue((uint32_t)Minuto), nSegundo.setValue((uint32_t)Segundo);
//
//}
//
///*********************************************************************
// * Le a variável Beep do Screen
// *********************************************************************/
//bool getBeepOnScreen(){
//
//  uint32_t      value   =   0;
//  NexVariable   nBeep   =   NexVariable(JanelaVarGlobais, 32, "nBeep");
//
//  nBeep.getValue(&value);
//  if(value != 0) {
//    return true;
//  }
//  return false;
//}
//
///*********************************************************************
// * Le a temperatura do sistema. O sensor fica no device DS3231
// *********************************************************************/
//void ShowTempSysOnScreen(){
//  
//  NexVariable nTempSys = NexVariable(JanelaVarGlobais, 17, "VarGlobais.nTempSys");
//  nTempSys.setValue(getTemperaturaSysOnDS3231());
//
//}
//
///************************************************************************ 
// * Le a temperatura do device DH11 e coloca o valor na variável da Tela
// ************************************************************************/
//void ShowTemperaturaOnScreen(){
//
//  uint32_t ValorSensor = (uint32_t)getTemperaturaOnDHT();
//   
//  NexVariable nTemperatura = NexVariable(JanelaVarGlobais, 16, "VarGlobais.nTemperatura");
//  nTemperatura.setValue(ValorSensor);
//
//}
//
///********************************************************************** 
// * Le a humidade do device DH11 e coloca o valor na variável  da Tela
// **********************************************************************/
//void ShowHumidadeOnScreen(){
//
//  uint32_t ValorSensor = (uint32_t)getHumidadeOnDHT();
//  
//  NexVariable nHumidade = NexVariable(JanelaVarGlobais, 18, "VarGlobais.nHumidade");  
//  nHumidade.setValue(ValorSensor);
//
//}
//
///***********************************************************
// *  Funções Auxiliares
// ***********************************************************/
//void DataHoraOnScreen(byte *pDH, byte *pMM, byte *pAS){
//
//  uint32_t    value =   -1;
//  NexSlider   sDH   =   NexSlider(JanelaConfigDataHora, 11, "sDH");
//  NexSlider   sMM   =   NexSlider(JanelaConfigDataHora, 12, "sMM");
//  NexSlider   sAS   =   NexSlider(JanelaConfigDataHora, 13, "sAS");
//
//  sDH.getValue(&value),   *pDH = (byte)value;
//  sMM.getValue(&value),   *pMM = (byte)value;
//  sAS.getValue(&value);
//  
//  if (value < 60) {    // Tela no Screen em Configuração de Hora
//   *pAS = (byte)value;
//  }
//  else {               // Tela no Screen em Configuração de Data
//    if (value < 2000) 
//       Milenio = 1900;
//    else 
//       Milenio = 2000;
//
//    *pAS = (byte)(value - Milenio);
//  }
//}
//
//void ShowNumOnScreen(uint32_t valor){
//  
//  NexVariable nTemp = NexVariable(JanelaVarGlobais, 25, "VarGlobais.nTemp");
//  nTemp.setValue((uint32_t)valor);
//
//}




/*********************************************************************
 * 
 * 
 * CÓDIGO QUE EXECUTA BEM, USANDO A FUNÇÃO F() E AS CHAMADAS 
 * NO NEXTION SÃO VIA OBJECNAME (CONSOME MUITA MEMÓRIA DE PROGRAMA)
 * 
 * 
 ********************************************************************/
//
//
//// ************************************************
//// Biblioteca Nextion (screen)
//// Desenvolvido por Edson Silva
//// Date: 26/05/18
//// Comunicação Rx e Tx
//// ************************************************
//
//#include <Nextion.h>
////#include <SoftwareSerial.h>
////SoftwareSerial HMISerial(10, 11);
//
//
//// Declaração dos ID's das Janelas
//// --------------------------------
//byte JanelaSplash          = 0,
//     JanelaMenu_Acao       = 1,
//     JanelaSelecao         = 2,
//     JanelaConfigMain      = 3,
//     JanelaConfigDataHora  = 4,
//     JanelaConfigArduino   = 12,
//
//     JanelaVarGlobais      = 8,
//     JanelaCreditos        = 9;
//
//int  Milenio               = 2000;
//
//// Declaração dos Objetos das Janelas que serão usados
//// ---------------------------------------------------
//
//
//bool IniciarNextion(){
//    bool Ok = false;
//    Ok = nexInit();                                        // Necessário usar esta função para estabelecer a conexão com a tela
//    delay(500);
//    return Ok;
//}
//
//void setVarNextion(char VarGlobal[], int TextoLength, String NomeVar) {
//  for(int i=0;i<=TextoLength;i++) {
//    VarGlobal[i] = NomeVar.charAt(i);
//  }
//  VarGlobal[TextoLength] = '\0';    // Indica fim do array de char
//}
//
//byte getAcaoOnScreen(){
//
//  uint32_t value = 0;
//  char VarGlobalID[25];
//
//  setVarNextion(VarGlobalID, 24, F("VarGlobais.IDAcaoArduino"));
//
//  NexVariable IDAcaoArduino = NexVariable(JanelaVarGlobais, 1, VarGlobalID);
//  IDAcaoArduino.getValue(&value);
// 
//  return (byte)value;
//}
//
//byte getStandByOnScreen(){
//
//  uint32_t value = 1;     //Se não retorna nada mantem em stand by
////  char VarGlobal[20];
////  setVarNextion(VarGlobal, 19, F("VarGlobais.nStandBy"));
////  char VarGlobal[11];
////  setVarNextion(VarGlobal, 10, F("p[8].b[29]"));
//
////  NexVariable IDAcaoArduino = NexVariable(JanelaVarGlobais, 29, VarGlobal);  
//  NexVariable IDAcaoArduino = NexVariable(JanelaVarGlobais, 29, "");  
//  IDAcaoArduino.getValueByIDs(&value);
// 
//  return (byte)value;
//}
//
//void setAcaoOnScreen(uint32_t Acao){
//  
//  char VarGlobal[25];
//  setVarNextion(VarGlobal, 24, F("VarGlobais.IDAcaoArduino"));
//    
//  NexVariable IDAcaoArduino = NexVariable(JanelaVarGlobais, 1, VarGlobal);
//  IDAcaoArduino.setValue(Acao);
//}
//
///**------------------------------------------------------------------
// * Valores de CodeExec
// * ------------------------------------------------------------------
// * 0 = Estado inicial / sem pedido de execução  - Usado pelo Nextion
// * 1 = Screeen solicitando Execução no Arduino  - Usado pelo Nextion
// * 2 = Arduino Executando                       - Usado pelo Arduino
// * 3 = Execução finalizada pelo Arduino         - Usado pelo Arduino
// * ------------------------------------------------------------------
//**/
//void setExecArduinoOnScreen(byte CodeExec){
//
//  uint32_t Code = (uint32_t)CodeExec;
//  char VarGlobal[23];
//  setVarNextion(VarGlobal, 22, F("VarGlobais.ArduinoExec"));
//    
//  NexVariable ArduinoExec = NexVariable(JanelaVarGlobais, 3, VarGlobal); 
//  ArduinoExec.setValue(Code);
//
//}
//
//void setLDROnScreen(){
//  
//  uint32_t ValorSensor = (uint32_t)getValorMapInvertidoOnLDR();
//
//  char VarGlobal[16];
//  setVarNextion(VarGlobal, 15, F("VarGlobais.nLDR"));
//
//  NexVariable nLDR = NexVariable(JanelaVarGlobais, 24, VarGlobal);
//  nLDR.setValue(ValorSensor);
//  
//}
//
//void getRGBBrilhoOnScreen(byte *R, byte *G, byte *B, byte *Brilho){
//
//  uint32_t  value     = -1;
//  char VarGlobalR[14];
//  char VarGlobalG[14];
//  char VarGlobalB[14];
//  char VarGlobalBr[19];
//
//  setVarNextion(VarGlobalR,   13, F("VarGlobais.nR"));
//  setVarNextion(VarGlobalG,   13, F("VarGlobais.nG"));
//  setVarNextion(VarGlobalB,   13, F("VarGlobais.nB"));
//  setVarNextion(VarGlobalBr,  18, F("VarGlobais.nBrilho"));
//    
//  NexVariable nR      = NexVariable(JanelaVarGlobais,  20, VarGlobalR);
//  NexVariable nG      = NexVariable(JanelaVarGlobais,  21, VarGlobalG);
//  NexVariable nB      = NexVariable(JanelaVarGlobais,  22, VarGlobalB);
//  NexVariable nBrilho = NexVariable(JanelaVarGlobais,  23, VarGlobalBr);
//
//  nR.getValue(&value),        *R      = (byte)value;
//  nG.getValue(&value),        *G      = (byte)value;
//  nB.getValue(&value),        *B      = (byte)value;
//  nBrilho.getValue(&value),   *Brilho = (byte)value;  
//}
//
//void setCodeRGBBrilhoOnScreen(byte CodeAcao, byte R, byte G, byte B, byte Brilho){
//  
//  char VarGlobalC[18];
//  char VarGlobalR[14];
//  char VarGlobalG[14];
//  char VarGlobalB[14];
//  char VarGlobalBr[19];
//  char VarGlobalRGBNextion[19];
//
//  setVarNextion(VarGlobalC,           17, F("VarGlobais.vaCode"));
//  setVarNextion(VarGlobalR,           13, F("VarGlobais.nR"));
//  setVarNextion(VarGlobalG,           13, F("VarGlobais.nG"));
//  setVarNextion(VarGlobalB,           13, F("VarGlobais.nB"));
//  setVarNextion(VarGlobalBr,          18, F("VarGlobais.nBrilho"));
//  setVarNextion(VarGlobalRGBNextion,  18, F("VarGlobais.nCorRGB"));
//
//  NexVariable vaCode = NexVariable(JanelaVarGlobais, 25, VarGlobalC);
//  vaCode.setValue((uint32_t)CodeAcao);
//
//  NexVariable vaR = NexVariable(JanelaVarGlobais, 20, VarGlobalR);
//  vaR.setValue((uint32_t)R);
//
//  NexVariable vaG = NexVariable(JanelaVarGlobais, 21, VarGlobalG);
//  vaG.setValue((uint32_t)G);
//
//  NexVariable vaB = NexVariable(JanelaVarGlobais, 22, VarGlobalB);
//  vaB.setValue((uint32_t)B);
//
//  NexVariable vaBrilho = NexVariable(JanelaVarGlobais, 23, VarGlobalBr);
//  vaBrilho.setValue((uint32_t)Brilho);
//
//  NexVariable vaRGBNextion = NexVariable(JanelaVarGlobais, 19, VarGlobalRGBNextion);
//
//  uint32_t RGBNextion = (R / 8 * 2048) + (G / 4 *32) + (B / 8);   // Cálculo necessário porque o Nextion trata a cor RGB diferente
//  vaRGBNextion.setValue(RGBNextion);
//  
//}
//
//byte getDoWOnScreen(){
//
//  uint32_t    value =   0;
// 
//  NexSlider   sDoW   =   NexSlider(JanelaConfigDataHora, 26, "sDoW");
//
//  sDoW.getValue(&value);
//  return (byte)value;
//
//}
//
//void getDataOnScreen(byte *pDia, byte *pMes, byte *pAno, byte *DoW){
//
//  byte  bDH,  bMM,  bAS, bDoW;
//
//  DataHoraOnScreen(&bDH, &bMM, &bAS);
//  bDoW    = getDoWOnScreen();
//  *pDia   = bDH;
//  *pMes   = bMM;
//  *pAno   = bAS;
//  *DoW    = bDoW;  
//}
//
//void getHoraOnScreen(byte *Hora, byte *Minuto, byte *Segundo) {
//
//  byte  bDH,  bMM,  bAS;
//  
//  DataHoraOnScreen(&bDH, &bMM, &bAS);
//  *Hora      = bDH;
//  *Minuto    = bMM;
//  *Segundo   = bAS;  
//}
//
//void getTextoOnScreen(char Texto[], byte *pQtdeChar){
//
//  uint32_t    value =   -1;
//  char VarGlobalT[20];  
//  char VarGlobalQ[24];  
//
//  setVarNextion(VarGlobalT, 19, F("VarGlobais.txtTexto"));
//  setVarNextion(VarGlobalQ, 23, F("VarGlobais.txtTextoQtde"));
//
//  NexVariable txtTexto      = NexVariable(JanelaVarGlobais, 30, VarGlobalT);
//  NexVariable txtTextoQtde  = NexVariable(JanelaVarGlobais, 31, VarGlobalQ);
//
//  txtTextoQtde.getValue(&value);
//  *pQtdeChar = (byte)value;
//
//  memset(Texto, 0, sizeof(Texto));    // Inicializa o array de char
//  txtTexto.getText(Texto, value);
//
////  Serial.print(".........Screen *pQtdeChar = "), Serial.println(*pQtdeChar);
////  Serial.print(".........Screen Texto = "), Serial.println(Texto);
// 
//}
//
//void ShowDataOnScreen(){
//
//  byte       Dia, Mes, Ano, DoW;
//  char VarGlobalD[16];
//  char VarGlobalM[16];
//  char VarGlobalA[16];
//  char VarGlobalDo[16];
//
//  setVarNextion(VarGlobalD,  15, F("VarGlobais.nDia"));
//  setVarNextion(VarGlobalM,  15, F("VarGlobais.nMes"));
//  setVarNextion(VarGlobalA,  15, F("VarGlobais.nAno"));
//  setVarNextion(VarGlobalDo, 15, F("VarGlobais.nDoW"));
//  
//  NexVariable nDia    = NexVariable(JanelaVarGlobais,  8, VarGlobalD);
//  NexVariable nMes    = NexVariable(JanelaVarGlobais,  9, VarGlobalM);
//  NexVariable nAno    = NexVariable(JanelaVarGlobais, 10, VarGlobalA);
//  NexVariable nDoW    = NexVariable(JanelaVarGlobais, 12, VarGlobalDo);
//  
//  getDataOnDS3231(&Dia, &Mes, &Ano, &DoW);
//
//  nDia.setValue((uint32_t)Dia);
//  nMes.setValue((uint32_t)Mes);
//  nAno.setValue((uint32_t)(Milenio + Ano));  
//  nDoW.setValue((uint32_t)DoW);
//
//}
//
//void ShowHoraOnScreen(){
//  
//  byte    Hora, Minuto, Segundo;
//  char VarGlobalH[17];
//  char VarGlobalM[19];
//  char VarGlobalS[20];
//
//  setVarNextion(VarGlobalH, 16, F("VarGlobais.nHora"));
//  setVarNextion(VarGlobalM, 18, F("VarGlobais.nMinuto"));
//  setVarNextion(VarGlobalS, 19, F("VarGlobais.nSegundo"));
//    
//  NexVariable nHora    = NexVariable(JanelaVarGlobais, 13, VarGlobalH);
//  NexVariable nMinuto  = NexVariable(JanelaVarGlobais, 14, VarGlobalM);
//  NexVariable nSegundo = NexVariable(JanelaVarGlobais, 15, VarGlobalS);
//
//  getHoraOnDS3231(&Hora, &Minuto, &Segundo);
//
//  nHora.setValue((uint32_t)Hora), nMinuto.setValue((uint32_t)Minuto), nSegundo.setValue((uint32_t)Segundo);
//
//}
//
///*********************************************************************
// * Le a variável Beep do Screen
// *********************************************************************/
//bool getBeepOnScreen(){
//
//  uint32_t      value   =   0;
//  char VarGlobal[17];
//  setVarNextion(VarGlobal, 16, F("VarGlobais.nBeep"));
//
//  NexVariable   nBeep   =   NexVariable(JanelaVarGlobais, 32, VarGlobal);
//
//  nBeep.getValue(&value);
//  if((bool)value == 1)
//    return true;
//  return false;
//}
//
///*********************************************************************
// * Le a temperatura do sistema. O sensor fica no device DS3231
// *********************************************************************/
//void ShowTempSysOnScreen(){
//  
//  char VarGlobal[20];
//  setVarNextion(VarGlobal, 19, F("VarGlobais.nTempSys"));
//    
//  NexVariable nTempSys = NexVariable(JanelaVarGlobais, 17, VarGlobal);
//  nTempSys.setValue(getTemperaturaSysOnDS3231());
//
//}
//
///************************************************************************ 
// * Le a temperatura do device DH11 e coloca o valor na variável da Tela
// ************************************************************************/
//void ShowTemperaturaOnScreen(){
//
//  uint32_t ValorSensor = (uint32_t)getTemperaturaOnDHT();
//  char VarGlobal[24];
//  setVarNextion(VarGlobal, 23, F("VarGlobais.nTemperatura"));
//   
//  NexVariable nTemperatura = NexVariable(JanelaVarGlobais, 16, VarGlobal);
//  nTemperatura.setValue(ValorSensor);
//
//}
//
///********************************************************************** 
// * Le a humidade do device DH11 e coloca o valor na variável  da Tela
// **********************************************************************/
//void ShowHumidadeOnScreen(){
//
//  uint32_t ValorSensor = (uint32_t)getHumidadeOnDHT();
//
//  char VarGlobal[21];
//  setVarNextion(VarGlobal, 20, F("VarGlobais.nHumidade"));
//  
//  NexVariable nHumidade = NexVariable(JanelaVarGlobais, 18, VarGlobal);  
//  nHumidade.setValue(ValorSensor);
//
//}
//
///***********************************************************
// *  Funções Auxiliares
// ***********************************************************/
//void DataHoraOnScreen(byte *pDH, byte *pMM, byte *pAS){
//
//  uint32_t    value =   -1;
//
//  NexSlider   sDH   =   NexSlider(JanelaConfigDataHora, 11, "sDH");
//  NexSlider   sMM   =   NexSlider(JanelaConfigDataHora, 12, "sMM");
//  NexSlider   sAS   =   NexSlider(JanelaConfigDataHora, 13, "sAS");
//
//  sDH.getValue(&value),   *pDH = (byte)value;
//  sMM.getValue(&value),   *pMM = (byte)value;
//  sAS.getValue(&value);
//  
//  if (value < 60) {    // Tela no Screen em Configuração de Hora
//   *pAS = (byte)value;
//  }
//  else {               // Tela no Screen em Configuração de Data
//    if (value < 2000) 
//       Milenio = 1900;
//    else 
//       Milenio = 2000;
//
//    *pAS = (byte)(value - Milenio);
//  }
//}
//
//void ShowNumOnScreen(uint32_t valor){
//  
//  char VarGlobal[17];
//  setVarNextion(VarGlobal, 16, F("VarGlobais.nTemp"));
//
//  NexVariable nTemp = NexVariable(JanelaVarGlobais, 25, VarGlobal);
//  nTemp.setValue((uint32_t)valor);
//
//}
