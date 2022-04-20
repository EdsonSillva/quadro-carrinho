// ---------------------------------------------------
// Rotinas de laitura do sensor de luminosidade LDR
// Utiliza o pino (A1)
// Desenvolvido por Edson Silva
// Date: 22/07/18

// Definição do pino do LDR
// ------------------------
#define     pin_LDR    A0        // Pino de entrada para uso do sensor de luminosidade
#define     Min         0
#define     Max       120


void IniciarSensorLDR(){
  pinMode(pin_LDR, INPUT);    // Habilita o pino para utilização do sensor
}

int inline LerSensor(){
  return (int)analogRead(pin_LDR);
}

int getValorPuroOnLDR(){
  return LerSensor();
}

int getValorMapOnLDR(){
  return map(LerSensor(), 0, 1023, Min, Max);
}

int getValorMapInvertidoOnLDR(){
  return (int)((int)Max - getValorMapOnLDR());
}
