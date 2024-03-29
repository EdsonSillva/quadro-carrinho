/* ***********************************************************
 * Projeto Quadro de Carrinhos - >> CONTROLADOR PARA TELA <<
 *                                  *********************
 * Este projeto tera uma tela como inteface das ações 
 * que serão executadas no quadro.
 * Função deste sketch: Interagir com a tela e passar os comandos para a memória EEPROM,
 *                      onde o outro arduino irá interpretar e executar a função
 * Autor: Edson Silva
 * Data Inicio: 27/05/18
 * Data Fim:    Ago/20 - 1º versão
 * ***********************************************************/
// Exemplo de Macro
//#define MacroSoma(NumA, NumB) (NumA + NumB)

bool TelaStarted = false;                     // Guarda flag se a inicialização da tela aconteceu

/*Função de Reset apontando para o endereço 0 do microcontrolador*/

void (*ResetArduino)() = 0;           // para uso futuro com opção de reset no arduino

void setup() {

//  Serial.begin(9600);
//  while(!Serial);

  delay(3000);                                // Necessário para aguardar a inicialização física da tela e arduino Box.
  
  pinMode(getPinControl(), OUTPUT);           // Pino de controle indicando quando este arduino pode iniciar suas rotinas baseado na Ação da tela
  pinMode(getPinLedUsoEEPROM(), OUTPUT);      // Pino com o Led indicando o uso na Leitura/Gravação da EEPROM
  digitalWrite(getPinControl(), LOW);
  digitalWrite(getPinLedUsoEEPROM(), LOW);
  delay(10);                                  // Necessário para aguardar a inicialização do componente anterior.
  SetupDS3231(true);                          // Inicializar DS3231 - true set 24hs format and false set 12hs format
  delay(10);                                  // Necessário para aguardar a inicialização do componente anterior.

  SetupEEPROM();                              // Inicializar Wire para a comunicação com a EEPROM
  delay(10);                                  // Necessário para aguardar a inicialização do componente anterior.

  IniciarBuzzer();                            // Inicializar Buzzer
  delay(10);                                  // Necessário para aguardar a inicialização do componente anterior.
  IniciarSensorLDR();                         // inicializar a porta do sensor para entrada;
  delay(10);                                  // Necessário para aguardar a inicialização do componente anterior.

  while(true) {

      TelaStarted = IniciarNextion();         // Inicialization Screen Nextion
      delay(100);                             // Necessário para aguardar a inicialização do componente anterior.

      if(TelaStarted){
        
        byte  R,  G,  B, Brilho, CodeAcao;

        getDadosOnEEPROM(&CodeAcao, &R, &G, &B, &Brilho);
        setCodeRGBBrilhoOnScreen(CodeAcao, R, G, B, Brilho);
        ShowDataOnScreen();                             // Mantêm a variável de Data Atualizada        
        ShowHoraOnScreen();                             // Mantêm a variável de Hora Atualizada
        ShowTempSysOnScreen();                          // Mantêm a variável de temperatura do sistema atualizada
        ShowTemperaturaOnScreen();                      // Mantêm a variável de temperatura atualizada
        ShowHumidadeOnScreen();                         // Mantêm a variável de humidade atualizada
        setLDROnScreen();                               // Informa ao Screen o valor da variável de luminosidade
        break;
        
      } else {
        BeepBuzzer(),delay(500),BeepBuzzer(),delay(500),BeepBuzzer();     //Fica beepando se a inicialização da tela não for Ok
        delay(5000);
      }
  }

}

void loop() {

  if(getStandByOnScreen() == 1) {
    delay(1000);
  } else {
    ExecutarAcao(getAcaoOnScreen());
  }
}


//void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
//{
//asm volatile ("  jmp 0");  
//}  
