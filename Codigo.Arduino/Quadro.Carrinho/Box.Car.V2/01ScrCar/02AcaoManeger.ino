/*****************************************************
 * Gerenciador das Ações recebidas pela tela Nextion
 * Desenvolvido por Edson Silva
 * Date: 27/05/18  
 ****************************************************/

#define   ChaveAcao(CodeAcao, R, G, B, Brilho) ((String)(String(CodeAcao) + String(R) + String(G) + String(B) + String(Brilho)))

#define   pinControl        12

String ChaveAcaoNew          = "";
String ChaveAcaoOld          = "";
byte  R,  G,  B, Brilho;
bool Beep = true;

//long TempoProc          = millis() + 1000;

byte getPinControl(){
  return pinControl;
}

void ExecutarAcao(byte CodeAcao) {

      getRGBBrilhoOnScreen(&R, &G, &B, &Brilho);
      ChaveAcaoNew  = ChaveAcao(CodeAcao, R, G, B, Brilho);

//      Serial.println(""), Serial.println("");
//      Serial.print("================ Validacao ============="), Serial.println("");
//      Serial.print("ChaveAcaoNew = "), Serial.print(ChaveAcaoNew), Serial.println("");
//      Serial.print("================ Validacao ============="), Serial.println("");
//      Serial.println(""), Serial.println("");
      
      switch (CodeAcao) {
    
        case 0:    case 255:                                        // Reset Ação
          if(ChaveAcaoNew != ChaveAcaoOld){
              digitalWrite(pinControl, LOW);                        // Sinaliza Off para o outro Arduino
              delay(50);
              //setDadosOnEEPROM(0, 0, 0, 0, Brilho);               // reseta dados da EEPROM 
              ChaveAcaoOld = ChaveAcaoNew;                          // Guarda a chave atual
          }
        break;
        
        /* *******************************************************************
         * Opções para configuração do sistema e screen
         * *******************************************************************/
        case 1:                                           // Ação Configurar Data
            setAcaoOnScreen(-1);                          // reset Ação Modo Idle
            ConfigData();        
        break;
        case 2:                                           // Ação Configurar Hora
            setAcaoOnScreen(-1);                          // reset Ação Modo Idle
            ConfigHora();
        break;
        case 3:                                           // Ação Configurar RGB Brilho dos Led's
            setAcaoOnScreen(-1);                          // reset Ação Modo Idle
        break;
        case 4:                                           // Ação Configurar Beep
            setExecArduinoOnScreen(2);                    // Informando ao Screem que está processando o pedido
            Beep = getBeepOnScreen();
            setExecArduinoOnScreen(3);                    // Informando ao Screem que processou o pedido
        break;
  
        default:
            
          /* *******************************************************************
           * Opções para ação no quadro de Leds 
           * *******************************************************************/
            switch(CodeAcao) {                                       

              case 61:                                      // Mensagem na Tela
                  if(ChaveAcaoNew != ChaveAcaoOld){
                      char Texto[50] = {0};
                      byte QtdeChar = 0;
                      getTextoOnScreen(Texto, &QtdeChar);
                      setDadosOnEEPROM(CodeAcao,  R,  G,  B,  Brilho);
                      setTextoOnEEPROM(Texto, QtdeChar);
                      ChaveAcaoOld = ChaveAcaoNew;              // Guarda a chave atual
                      digitalWrite(pinControl, HIGH);
                  }
              break;
              
              default:
                  if(ChaveAcaoNew != ChaveAcaoOld){
                      setDadosOnEEPROM(CodeAcao,  R,  G,  B,  Brilho);
                      ChaveAcaoOld = ChaveAcaoNew;              // Guarda a chave atual
                      digitalWrite(pinControl, HIGH);

                  }
              break;
      
            }

      }

//      getDadosOnEEPROM(&CodeAcao, &R, &G, &B, &Brilho);
//      setCodeRGBBrilhoOnScreen(CodeAcao, R, G, B, Brilho);
//      delay(50);
      
  /******************************************************************************
   * Rotinas de configuração das variáveis de Data, hora, tempertura e humidade
   ******************************************************************************/
 
 // if(millis() >= TempoProc){
    if(Beep) BeepBuzzer();
    ShowDataOnScreen();                             // Mantêm a variável de Data Atualizada        
    ShowHoraOnScreen();                             // Mantêm a variável de Hora Atualizada
    ShowTempSysOnScreen();                          // Mantêm a variável de temperatura do sistema atualizada
    ShowTemperaturaOnScreen();                      // Mantêm a variável de temperatura atualizada
    ShowHumidadeOnScreen();                         // Mantêm a variável de humidade atualizada
    setLDROnScreen();                               // Informa ao Screen o valor da variável de luminosidade
   
 //     TempoProc = millis() + 1000;                    // Acrescenta mais 1 segundo
 // }
}

/* ******************************************************************************
 * ROTINAS DAS AÇÕES DE CONFIGURAÇÃO
 * ******************************************************************************/

void ConfigData(){
    setExecArduinoOnScreen(2);                      // Informando ao Screem que está processando o pedido
    byte Dia, Mes, Ano, DoW;
    getDataOnScreen(&Dia, &Mes, &Ano, &DoW);        // Le a data indicada da tela de configurações
    setDataOnDS3231(Dia, Mes,  Ano, DoW);           // Seta a data no dispositivo DS3231
    setExecArduinoOnScreen(3);                      // Informando ao Screem que processou o pedido
}

void ConfigHora(){
    setExecArduinoOnScreen(2);                      // Informando ao Screem que está processando o pedido
    byte Hora, Minuto, Segundo;
    getHoraOnScreen(&Hora, &Minuto, &Segundo);      // Le a hora selecionada da tela de configuração
    setHoraOnDS3231(Hora, Minuto,  Segundo);        // Seta a hora no dispositivo DS3231
    setExecArduinoOnScreen(3);                      // Informando ao Screem que processou o pedido
}


/* OLD ########


void ExecutarAcao(byte IDAcao) {

  delay(400),  BeepBuzzer(), delay(100), BeepBuzzer();

  static long Numero = 1;

  switch (IDAcao) {

    case 0:     //Ação Configurar Data
        delay(400),  BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer();

    setAcaoOnScreen(-1);    // reset Ação Modo Idle
    delay(2000);
//    setExecArduinoOnScreen(2);                      // Informando ao Screem que está processando o pedido
//    delay(5000);
//    setExecArduinoOnScreen(3);                      // Informando ao Screem que processou o pedido


//        ConfigData();        
    break;

    case 1:     //Ação Configurar Hora
        delay(400),  BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer();
//  setAcaoOnScreen(-1);    // reset Ação Modo Idle

//        ConfigHora();
    break;

    case 2:     //Ação Configurar Brilho dos Led's
        delay(400),  BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer();
//  setAcaoOnScreen(-1);    // reset Ação Modo Idle

    break;
    
    case 10:     //Ação Manter os Leds Aceso
        delay(400),  BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer(), delay(100), BeepBuzzer();
//        LedsAcesos();
    break;
  
  }

// Resetar a variável IDAcaoArduino em -1 para não virar um loop configurando várias vezes 

//  delay(1000);
  setAcaoOnScreen((uint32_t)Numero);    // reset Ação Modo Idle

  Numero++; 

//  delay(2000);
//  ShowTempSysOnScreen();                            // Mantêm a variável de temperatura do sistema atualizada
//  ShowTemperaturaOnScreen();                        // Mantêm a variável de temperatura atualizada
//  ShowHumidadeOnScreen();                           // Mantêm a variável de humidade atualizada
//  setExecArduinoOnScreen(3);                        // Informando ao Screem que processou o pedido

}

/* ******************************************************************************
 * ROTINAS DAS AÇÕES DE CONFIGURAÇÃO
 * ******************************************************************************/

/*
void ConfigData(){
    setExecArduinoOnScreen(2);                      // Informando ao Screem que está processando o pedido
    byte Dia, Mes, Ano;
    getDataOnScreen(&Dia, &Mes, &Ano);              // Le a data selecionada da tela
    setDataOnDS3231(Dia, Mes,  Ano);                // Seta a data no dispositivo DS3231
    ShowDataOnScreen();
//    setExecArduinoOnScreen(3);                      // Informando ao Screem que processou o pedido
}

void ConfigHora(){
    setExecArduinoOnScreen(2);                      // Informando ao Screem que está processnado o pedido
    byte Hora, Minuto, Segundo;
    getHoraOnScreen(&Hora, &Minuto, &Segundo);      // Le a hora selecionada da tela
    setHoraOnDS3231(Hora, Minuto,  Segundo);        // Seta a hora no dispositivo DS3231
    ShowHoraOnScreen();
//    setExecArduinoOnScreen(3);                      // Informando ao Screem que processou o pedido
}


*/
