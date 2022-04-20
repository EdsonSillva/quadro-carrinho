// ---------------------------------------------------
// Biblioteca DHT
// Utiliza o pino Analógico A1
// Desenvolvido por Edson Silva
// Date: 03/06/18

#include <dht.h>

// Definição do pino do DHT
// ------------------------
#define pin_dht     A1    // Pino para recedber o sinal do DHT11

// Variável com o objeto DHT
// -------------------------
dht Dht;

void inline readDHT(){
  Dht.read11(pin_dht);
}

double getTemperaturaOnDHT(){
  readDHT();
  return Dht.temperature;
}

double getHumidadeOnDHT(){
  readDHT();
  return Dht.humidity;
}

bool ErroReadOnDHT11(){
  if(isnan(Dht.temperature || Dht.humidity)) return true;
  else return false;
}
