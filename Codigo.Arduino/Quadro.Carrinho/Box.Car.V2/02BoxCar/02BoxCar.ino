/* ***********************************************************
 * Projeto Quadro de Carrinhos - >> CONTROLADOR QUADRO LED (BOX) <<
 *                                  ****************************
 * Este projeto tera uma tela como inteface das ações 
 * que serão executadas no quadro.
 * Autor: Edson Silva
 * Data Inicio: 27/05/18
 * Data Fim:    Ago/20 - 1º versão
 * Release:     jun/22
 * **********************************************************/
// Exemplo de Macro
//#define MacroSoma(NumA, NumB) (NumA + NumB)

/* DEFINIÇÃO DE VARIÁVEL PARA USO NA COMPILAÇÃO PARA DEBUG */
#define DEBUG true


/*
 * PONTEIRO PARA AS FUNÇÕES ACENDER BOX TEMATICOS (FIXOS)
 */
typedef void (*pTipoVoidBox)(byte, byte, byte, byte);
typedef void (*pTipoVoid)(bool, byte, byte, byte, byte);
typedef int (*pTipoFuncaoInt)(...);

byte      CodeAcao          = 0xff,
          R                 = 0xff,
          G                 = 0xff,
          B                 = 0xff,
          Brilho            = 0xff;

long      tmpWait           = 0x00;
byte      pinAcao           = 0x00;
bool      pinAcaoValor      = false;
bool      ResetEfetuado     = false;

const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };
  
void setup() {

#if DEBUG == true
  Serial.begin(9600);
  while(!Serial);
#endif

  pinAcao = getPinAcao();                     // Obtem o Pino de controle da Ação
  pinMode(pinAcao, INPUT);
  IniciarLeds(50);                            // inicializando os leds da fita com o brilho em default em 50
  TodosLedsAcesos(255, 255, 255);             // Acende todos os Leds do quadro
  
  SetupEEPROM();                              // Inicializar Wire para a comunicação com a EEPROM
  delay(2000);                                // Necessário para aguardar a inicialização física Tela e periféricos

}

bool inline getValorPinAcao() {
    #if DEBUG == true
        return true;
    #endif
    return digitalRead(pinAcao);
}

void loop() {

  pinAcaoValor = getValorPinAcao();
    
  if(tmpWait >= 20000 || pinAcaoValor){

      if(pinAcaoValor){

        #if DEBUG == true
          Serial.print("\n << MODO DEBUG >>"),Serial.print("\n");
          Serial.print("\n Lendo a EEPROM..."),Serial.print("\n");
        #endif

        getDadosOnEEPROM(&CodeAcao, &R, &G, &B, &Brilho);

        #if DEBUG == true

          Serial.print("\n EEPROM Lida"),Serial.print("\n");
          Serial.print("\nCode:"),Serial.print(CodeAcao),Serial.print("\n");
          Serial.print("R:"),Serial.print(R),Serial.print("\n");
          Serial.print("G:"),Serial.print(G),Serial.print("\n");
          Serial.print("B:"),Serial.print(B),Serial.print("\n");
          Serial.print("Br:"),Serial.print(Brilho),Serial.print("\n");
          

          char Msg[50]  = {0};
          byte QtdeChar = 0;

          getTextoOnEEPROM(Msg, &QtdeChar);

          Serial.print("\nQtdeMsg:"),Serial.print(QtdeChar),Serial.print("\n");
          Serial.print("\nMsg:"),Serial.print(Msg),Serial.print("\n");
          
          
          Serial.print("\nScan finalizado. Processando Comando...\n");
          ExecutarAcao(CodeAcao, pgm_read_byte(&gamma8[R]), pgm_read_byte(&gamma8[G]), pgm_read_byte(&gamma8[B]), Brilho);
          delay(5);   // da  um tempo para os resets das portas
          ResetEfetuado = !ResetEfetuado;

          
          Serial.print("\nScan finalizado. Novo Scan em 1 minuto...\n");
          delay(60000);
          Serial.print("\nIniciando o Scan da EEPROM novamente\n\n");

        #else
          ExecutarAcao(CodeAcao, pgm_read_byte(&gamma8[R]), pgm_read_byte(&gamma8[G]), pgm_read_byte(&gamma8[B]), Brilho);
          ResetEfetuado = false;
          delay(5);   // da  um tempo para os resets das portas
        #endif

      } else {
        if(!ResetEfetuado){
          ExecutarAcao(0, 0, 0, 0, Brilho);   //Reset comandos 
          ResetEfetuado = !ResetEfetuado;
        }

      }
      tmpWait = 0;
  } else {
      tmpWait++;
  }
}


/* bkp - com debug  */

//  
//void setup() {
//
//  pinAcao = getPinAcao();                     // Obtem o Pino de controle da Ação
//  pinMode(pinAcao, INPUT);
//  IniciarLeds(50);                            // inicializando os leds da fita com o brilho em default em 50
//  TodosLedsAcesos(255, 255, 255);             // Acende todos os Leds do quadro
//  SetupEEPROM();                              // Inicializar Wire para a comunicação com a EEPROM
//  //IniciarBuzzer();                          // Inicializar Buzzer
//
////  StartSerial();                              // Usado somente para Debug
//  delay(2000);                                // Necessário para aguardar a inicialização física Tela e periféricos
//
////  if(Serial) {
////    Serial.println("Iniciado o Debug via Serial a 9600 kbps...");
////  }
////  
//}
//
//bool inline getValorPinAcao() {
//  return digitalRead(pinAcao);
//  //return true;    // Usar para Teste
//}
//
//void loop() {
//
//  pinAcaoValor = getValorPinAcao();
//  
//  if(tmpWait >= 20000 || pinAcaoValor){
//      if(pinAcaoValor){
//
////        Serial.println("PinAcao Ligado ...");
////        Serial.print("Iniciando Rotina Leitura EEPROM"), Serial.println("...");
//        
//        getDadosOnEEPROM(&CodeAcao, &R, &G, &B, &Brilho);
//        
////        Serial.print("Voltou da Rotina Leitura EEPROM"), Serial.println("...");
//        //CodeAcao = 52, R = 0, G = 120, B = 210;   // Usado para testar este arduino stand alone
//        
////        Serial.print("Iniciando Rotina de Ação no quadro"), Serial.println("...");
//        ExecutarAcao(CodeAcao, pgm_read_byte(&gamma8[R]), pgm_read_byte(&gamma8[G]), pgm_read_byte(&gamma8[B]), Brilho);
////        Serial.print("Finalizando Rotina de Ação no quadro"), Serial.println("...");
//        delay(5);   // da  um tempo para os resets das portas
////        Serial.println("PinAcao Desligado ...");
//
//       } else {
//        //resetCodeAcaoAnt();                 //reset o código de ação anterior    
//        ExecutarAcao(0, 0, 0, 0, Brilho);   //Reset comandos 
//        //Serial.print("PinAcao Not Is True......."), Serial.println(tmpWait);
//      }
//      tmpWait = 0;
//  } else {
//      tmpWait++;
//
////      if(Serial && tmpWait >= 20000 ) {
////        Serial.println("Aguardando Ativação do Pino Ação...");
////      }
//  
//  }
//  
//}
//
