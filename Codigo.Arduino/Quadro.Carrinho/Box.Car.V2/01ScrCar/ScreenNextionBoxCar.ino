
/*******************************************************************
 * Biblioteca Nextion (screen)
 * Desenvolvido por Edson Silva
 * Date: 26/05/18
 * Comunicação Rx e Tx padrão do microcontrolador
 * 
 * Observação: Fiz um ajuste na Lib do Nextion para aceitar 
 * a passagem de parâmetro via ID do objeto do Nextion. 
 * A função original só estava aceitando passagem por string 
 * (nome do objeto criado no nextion). Assim consegui reduzir 
 * o consumo da memória do microcontrolador. No arquivo 
 * zDumpNextion.ino contêm a solução completa e funcionando do
 * código original 'comentado' com a passagem via string e também
 * usando a função F().
 ********************************************************************/

#include <Nextion.h>
//#include <SoftwareSerial.h>
//SoftwareSerial HMISerial(10, 11);


/* Declaração dos ID's das Janelas do Nextion
 * ------------------------------------------ */ 
uint8_t const JanelaSplash              =  0,
              JanelaMenu_Acao           =  1,
              JanelaSelecao             =  2,
              JanelaConfigMain          =  3,
              JanelaConfigDataHora      =  4,
              JanelaConfigArduino       = 12,
              JanelaVarGlobais          =  8,
              JanelaCreditos            =  9;

/* Declaração dos ID's dos Objetos Nextion
 * --------------------------------------- */
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

  nHora.setValueByID((uint32_t)Hora);
  nMinuto.setValueByID((uint32_t)Minuto);
  nSegundo.setValueByID((uint32_t)Segundo);

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
