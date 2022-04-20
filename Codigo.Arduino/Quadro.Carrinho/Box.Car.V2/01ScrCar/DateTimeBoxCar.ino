/**********************************************************************
 * Biblioteca DS3231
 * Rotinas para configurar e ler a data, hora , humidade e temperatura
 * Utiliza os pinos SDA(4) e SCL(5)
 * Desenvolvido por Edson Silva
 * Date: 13/05/18
 * ********************************************************************/

#include <DS3231.h>
#include <Wire.h>

// Variável com o objeto DS3231
// ----------------------------
DS3231 RTC;

void SetupDS3231(bool Clock24hs){
  Wire.begin();                                     // Entra no barramento I2c
  RTC.setClockMode(!Clock24hs);                     // set  true=12hs false=24hs format
  RTC.setDoW(0);                                    // set the Day-of-Week to SUNDAY (0)
}

byte getDoW() {
  return RTC.getDoW();
}

byte getDoWork(byte *Dia, byte *Mes, byte *Ano, int *Milenio) {
  int AnoComMilenio = *Milenio + *Ano;
  return CalculoDoW(Dia, Mes, &AnoComMilenio);
}

bool setHoraOnDS3231(byte Hora, byte Minuto, byte Segundo) {
  RTC.setHour(Hora);
  RTC.setMinute(Minuto);
  RTC.setSecond(Segundo);
}

void getHoraOnDS3231(byte *Hora, byte *Minuto, byte *Segundo) {
  bool h12, PM;
  *Hora=RTC.getHour(h12,PM);
  *Minuto=RTC.getMinute();
  *Segundo=RTC.getSecond();
}

bool setDataOnDS3231(byte Dia, byte Mes, byte Ano, byte DoW) {
  RTC.setDate(Dia);
  RTC.setMonth(Mes);
  RTC.setYear(Ano);
  RTC.setDoW(DoW);
}

void getDataOnDS3231(byte *Dia, byte *Mes, byte *Ano, byte *DoW) {
  
  bool Century=false;
  
  *Dia=RTC.getDate();
  *Mes=RTC.getMonth(Century);
  *Ano=RTC.getYear();
  *DoW=RTC.getDoW();
}

void getDataOnDS3231(byte *Dia, byte *Mes, byte *Ano, byte *DoW, int *Milenio) {
  
  bool Century=false;
  
  *Dia=RTC.getDate();
  *Mes=RTC.getMonth(Century);
  *Ano=RTC.getYear();
  // *DoW=RTC.getDoW();
  *DoW = getDoWork(Dia, Mes, Ano, Milenio);
}


int getTemperaturaSysOnDS3231(){
  return RTC.getTemperature();
}

byte CalculoDoW(byte *dia, byte *mes, int *ano) {

//  byte  mesZeller = *mes < 3 ? *mes + 12  : mes;
//  int   anoZeller = *mes < 3 ? *ano - 1   : ano;
//  Formula k = dia + 2 * mesZeller + [3*(mesZeller + 1) / 5] + anoZeller + (anoZeller / 4) - (anoZeller / 100) + (anoZeller / 400) + 2
//          DoW =  k mod 7, onde 0 = Sabado e Sexta = 6

  byte  mesZeller = *mes < 3 ? *mes + 12  : *mes;
  int   anoZeller = *mes < 3 ? *ano - 1   : *ano;

  size_t k =  *dia + (2 * mesZeller) + (3 * (mesZeller + 1) / 5) + 
              anoZeller + (anoZeller / 4) - (anoZeller / 100) + (anoZeller / 400) + 2;

  return k % 7;
}


/* ******************************************************************************
 * ROTINAS AUXILIARES
 * ******************************************************************************/

/*
 * Não estou usando para economizar espaço de memória de programa
 * 
bool setDataOnDS3231(byte Dia, byte Mes, byte Ano, byte DoW) {
  RTC.setDate(Dia);
  RTC.setMonth(Mes);
  RTC.setYear(Ano);
  RTC.setDoW(DoW);
}
*/
/*
 * Não estou usando para economizar espaço de memória de programa
 *
bool setHoraOnDS3231(byte Hora, byte Minuto, byte Segundo, bool ClockMode24hs) {
  //RTC.setTime(Hora, Minuto, Segundo);
  RTC.setHour(Hora);
  RTC.setMinute(Minuto);
  RTC.setSecond(Segundo);
  RTC.setClockMode(!ClockMode24hs);
}
*/


/*
String getDiaSemanaOnDS3231(){
  switch (getDoW()) {
    case 1:
      return "Dom";
    break;
    case 2:
      return "Seg";
    break;
    case 3:
      return "Ter";
    break;
    case 4:
      return "Qua";
    break;
    case 5:
      return "Qui";
    break;
    case 6:
      return "Sex";
    break;
    case 7:
      return "Sab";
    break;
  }
}
*/
/*
String getDataHoraStrOnDS3231(bool Data){

  String strDataHora = String("");
  byte Zero = 0, DH, MM, AS, DoW;
  char Separador;

  if(Data){
    Separador = '/';
    getDataOnDS3231(&DH,  &MM,    &AS,     &DoW);
  }else{
    Separador = ':';
    getHoraOnDS3231(&DH, &MM, &AS);
  }

  strDataHora += (DH <= 9) ? String(Zero) + String(DH) + String(Separador) : String(DH) + String(Separador);
  strDataHora += (MM <= 9) ? String(Zero) + String(MM) + String(Separador) : String(MM) + String(Separador);
  strDataHora += (AS <= 9) ? String(Zero) + String(AS)                     : String(AS);

  return strDataHora;
}
*/
