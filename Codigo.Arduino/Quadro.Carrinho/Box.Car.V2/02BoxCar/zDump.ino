// ---------------------------------------------------
// Rotinas de teste q foram usadas 
// Desenvolvido por Edson Silva
// Date: 08/07/18

/*
void setup() {

  //Teste do device DS3231
  Serial.begin(9600);
  while(!Serial);
  TesteSet();
}

void loop() {
  //ExecutarAcao(getAcaoOnScreen());

  // ------ TESTE do DS3231 -------
//  byte Dia, Mes, Ano, dW, Hora, Minuto, Segundo;
  String strDia = getStrDiaOnDS3231();
  String strMes = getStrMesOnDS3231();

//  String  strData = getDDMMAA();
//  String  strHora = getHHMMSS();
//  byte Day  = getDiaOnDS3231(&chDia);
//  byte Day  = getDiaOnDS3231();
//  byte Mon  = getMesOnDS3231();
//  byte Year = getAnoOnDS3231();
//  byte Hor  = getHoraOnDS3231();
//  byte Min  = getMinutoOnDS3231();
//  byte Sec  = getSegundoOnDS3231();
//  Serial.print("  ---> DATA HORA = "), Serial.print(strData), Serial.print(" - "), Serial.print(strHora), Serial.println("  <---");
//  Serial.print("------ Day(String) strDia = "), Serial.print(strDia), Serial.print("  <--");
//  Serial.print("  ------ Month(String) strMes = "), Serial.print(strMes), Serial.println("  <--");
//  Serial.print("  ---> DATA HORA = "), Serial.print(strData), Serial.print(" - "), Serial.print(strHora), Serial.println("  <---");
//  TesteGet(&Dia, &Mes, &Ano, &dW, &Hora, &Minuto, &Segundo);
//  TesteShow(Day, Mon, Year, dW, Hor, Min, Sec);
//  TesteShow(&Dia, &Mes, &Ano, &dW, &Hora, &Minuto, &Segundo);

  delay(5000);

//  TesteShow(Dia, Mes, Ano, dW, Hora, Minuto, Segundo);

}

void TesteShow(byte *pDia, byte *pMes, byte *pAno, byte *pdW, byte *pHora, byte *pMinuto, byte *pSegundo){
//  char valor[] = "19";
//  //memset(valor, 0, sizeof(valor));
//  itoa((int)*pMes, valor, 10);
//  Serial.println(""),     Serial.print("TESTE SHOW(valor) ---> "),       Serial.print("");
//  Serial.print(*pDia),    Serial.print("/"),                             Serial.print(valor),    Serial.print("/"), Serial.print(*pAno),   Serial.print(" ---> ");
//  Serial.print(*pHora),   Serial.print(":"),  Serial.print(*pMinuto),    Serial.print(":"),      Serial.print((int)*pSegundo, DEC);
//  Serial.print(""),       Serial.println(" <--- FIM TESTE SHOW()"),      Serial.println("");
}


//--------------------------------------------------------------------------------


void setup() {
  // Inicializar DS3231
  SetupDS3231(true);      // true set 24hs format // false set 12hs format
//  IniciarNextion();       // set Inicialization Screen Nextion
//  IniciarLeds(50);        // inicializando os leds da fita com o brilho default

// ###########################################
//  Teste do device DS3231
  Serial.begin(9600);
  while(!Serial);
//  TesteSet((byte)9, (byte)6, (byte)68, (byte)7, (byte)13, (byte)47);
   TesteSet();
// ###########################################
}

void loop() {
//  ExecutarAcao(getAcaoOnScreen());

//  String DataHoje = getDiaOnDS3231();
//  String DataHoje = getDDMMAAOnDS3231();
  //byte Data = getMinutoOnDS3231();
//  String HoraHoje = getHHMMSSOnDS3231();
  
  
//  Serial.print("Executando..."), Serial.println(millis());
//  Serial.print("Data:"), Serial.println(Data);
//  delay(1000);
  
  byte  Dia = getDiaOnDS3231(),
        Mes = getMesOnDS3231(),
        Ano = getAnoOnDS3231();

  String  strDia = Dia < 10  ? '0' + (String)Dia + '/' :   (String)Dia + '/',
          strMes = Mes < 10  ? '0' + (String)Mes + '/' :   (String)Mes + '/',
          strAno = Ano < 10  ? '0' + (String)Ano       :   (String)Ano; 

  Serial.print("Data em Loop:"), Serial.println((String)(strDia + strMes + strAno));
//  Serial.print("DataHoje em Loop:"), Serial.println(DataHoje);
//  Serial.print("HoraHoje em Loop:"), Serial.println(HoraHoje);
  delay(3000);


}


// Funções do módulo DateTimeBoxCar ----- INICIO

byte getDiaOnDS3231(){
  return RTC.getDate();
}
byte getMesOnDS3231(){
  bool Century=false;
  return RTC.getMonth(Century);
}
byte getAnoOnDS3231(){
  return RTC.getYear();
}
byte getHoraOnDS3231(){
  bool h12, PM;
  return RTC.getHour(h12,PM);
}
byte getMinutoOnDS3231(){
  return RTC.getMinute();
}
byte getSegundoOnDS3231(){
  return RTC.getSecond();
}




// FIM -----------------------------------------

// DS3231 ----------------------

//
//void TesteSet(){
//  
//  setHoraOnDS3231( 23, 58, 50);
//  setDataOnDS3231( 31, 12, 00);
//
//  bool Centu = false;
//  bool h12, PM;
//  Serial.println("Setup Data ------");
//  Serial.print(RTC.getDate()), Serial.print("/"), Serial.print(RTC.getMonth(Centu)), Serial.print("/"), Serial.println(RTC.getYear());
//  Serial.println("Fim Setup Data --------");
//
////  delay(72000);
//  
//  Serial.println("Setup Hora ------");
//  Serial.print(RTC.getHour(h12, PM)), Serial.print(":"), Serial.print(RTC.getMinute()), Serial.print(":"), Serial.println(RTC.getSecond());
//  Serial.println("Fim Setup Hora --------");
//  
//}
//
//void TesteGet(byte *pDia, byte *pMes, byte *pAno, byte *pdW, byte *pHora, byte *pMinuto, byte *pSegundo){
//
//  byte Dia, Mes, Ano, Hora, Minuto, Segundo;
//
//  bool Centu = false;
//  bool h12, PM;
//
//  getHoraOnDS3231( pHora, pMinuto, pSegundo);
//  getDataOnDS3231( pDia,  pMes,    pAno, pdW);
//
//  Dia     = *pDia;
//  Mes     = *pMes;
//  Ano     = *pAno;
//  Hora    = *pHora;
//  Minuto  = *pMinuto;
//  Segundo = *pSegundo;
//
//
//
//
//  Serial.println("Lendo Data ------");
//  Serial.print(RTC.getDate()), Serial.print("/"), Serial.print(RTC.getMonth(Centu)), Serial.print("/"), Serial.println(RTC.getYear());
//  Serial.println("Fim Lendo Data --------");
//
//  Serial.println("Lendo Hora Variável ------");
//  Serial.print(RTC.getHour(h12, PM)), Serial.print(":"), Serial.print(RTC.getMinute()), Serial.print(":"), Serial.println(RTC.getSecond());
//  Serial.println("Fim Lendo Hora Variável  --------");
//
//
//  Serial.println("Lendo Data da Variável ------");
//  Serial.print(Dia), Serial.print("/"), Serial.print(Mes), Serial.print("/"), Serial.println(Ano);
//  Serial.println("Fim Lendo Data Variável --------");
//
//  Serial.println("Lendo Hora Variável ------");
//  Serial.print(Hora), Serial.print(":"), Serial.print(Minuto), Serial.print(":"), Serial.println(Segundo);
//  Serial.println("Fim Lendo Hora Variável --------");
//
//  
//}






// FIM DS3231



Loop()


//  ShowInfoOLED();

//  byte      Dia,              Mes,         Ano,      Dow,     Hora,     Minuto,     Segundo;
//  double    Temp = 0,         Hum = 0;
//  int       SysTemp,          Luz;
//  String    FimSemana,        ErroLeituraDHT11;
//
//  getDataOnDS3231( &Dia,  &Mes,     &Ano,     &Dow );
//  getHoraOnDS3231( &Hora, &Minuto,  &Segundo );
//  Temp      =   getTemperaturaOnDHT();
//  Hum       =   getHumidadeOnDHT();
//  SysTemp   =   getTemperaturaSysOnDS3231();
//  FimSemana =   getDiaSemanaOnDS3231(); 
//  Luz       =   getValorMapOnLDR();
//
//  if(ErroReadOnDHT11()) ErroLeituraDHT11="Erro na leitura da temperatura e/ou humidade";
//  else ErroLeituraDHT11 = "";
//  
//  String sData = "dd mm aa";
//  String sHora = "hh mm ss";
//  
//  sData = getDataHoraStrOnDS3231(true);
//  sHora = getDataHoraStrOnDS3231(false);

//  Serial.print("-->");
//  Serial.print(sData);
//  Serial.print("<-->");
//  Serial.print(FimSemana);
//  Serial.print("<-->");
//  Serial.print(sHora);
//  Serial.print("<--SomaMacro(4, 10)=");
//  Serial.print(MacroSoma(4, 10));
//  Serial.print("<--Temp ambiente>");
//  Serial.print(Temp, 0);
//  Serial.print("°<--Humidade ambiente>");
//  Serial.print(Hum, 0);
//  Serial.print("%<-->");
//  Serial.print("<--Temp Sys>");
//  Serial.print(SysTemp);
//  Serial.print("°<-- "+ErroLeituraDHT11+"<-->");
//  Serial.print("<-->");
//  Serial.println(Luz);





byte getAcaoOnScreen(){

  uint32_t value = -1;

  NexVariable IDAcaoArduino = NexVariable(JanelaVarGlobais, 1, "VarGlobais.IDAcaoArduino");
  IDAcaoArduino.getValue(&value);

//  delay(400),  BeepBuzzer(), delay(300), BeepBuzzer();
//  Valor++;
//  NexVariable va0 = NexVariable(JanelaMenu_Acao,  31, "va0");
//  va0.setValue(Valor);
//  NexVariable nIDAcao   = NexVariable(JanelaMenu_Acao,  17, "nIDAcao");
//  nIDAcao.getValue(&value);
//  if(value == 5){
//    delay(400),  BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer();
//  }
  
  return (byte)value;
}



//  NexText txtDH = NexText(JanelaConfigDataHora, 5, "txtDH");
//  NexText txtMM = NexText(JanelaConfigDataHora, 7, "txtMM");
//  NexText txtAS = NexText(JanelaConfigDataHora, 9, "txtAS");
//  memset(*pchDH, 0, sizeof(*pchDH));
//  memset(*pchMM, 0, sizeof(*pchMM));
//  memset(*pchAS, 0, sizeof(*pchAS));
//  
//  txtDH.getText(*pchDH, sizeof(pchDH));
//  txtMM.getText(*pchMM, sizeof(pchMM));
//  txtAS.getText(*pchAS, sizeof(pchAS));


//  NexVariable strHora = NexVariable(JanelaVarGlobais, 4, "strHora");
//  byte Hora, Minuto, Segundo;
//  char chHor[2], chMin[2], chSeg[2], chHoraFull[8];
//  
//  memset(chHor,     0, sizeof(chHor));
//  memset(chMin,     0, sizeof(chMin));
//  memset(chSeg,     0, sizeof(chSeg));
//
//  getHoraOnDS3231(&Hora, &Minuto, &Segundo);
//
//  itoa(Hora,    chHor, 2);
//  itoa(Minuto,  chMin, 2);
//  itoa(Segundo, chSeg, 2);
//
//  strcat(chHoraFull, chHor),   strcat(chHoraFull, ":");
//  strcat(chHoraFull, chMin),   strcat(chHoraFull, ":");
//  strcat(chHoraFull, chSeg);
//
//  strHora.setText(chHoraFull);


































*/
