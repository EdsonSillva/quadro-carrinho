  // ---------------------------------------------------
// Rotinas para saída de sons
// Utiliza o pino (7)
// Desenvolvido por Edson Silva
// Date: 21/07/18

// Definição do pino do Buzzer
// ---------------------------
#define    pin_Buzzer  7               // Pino de saida para uso do Buzzer

void IniciarBuzzer(){
  pinMode(pin_Buzzer, OUTPUT);          // Habilita o pino para utilização do Buzzer
}

void BeepBuzzer(){
  tone(pin_Buzzer,14000,6);
}
