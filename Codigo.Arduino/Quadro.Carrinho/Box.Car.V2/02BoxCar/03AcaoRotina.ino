/****************************************************************
 * Gerenciador das Rotinas das Ações recebidas pela tela Nextion
 * Desenvolvido por Edson Silva
 * Date: 07/07/19  
 * Alteração: jul/22
 ****************************************************************/

#define     pinAcao             12

String    ChaveAcaoOld          = "";
long      tmpWaitRotina         = 0x00;


byte getPinAcao(){
  return pinAcao;
}

void ResetAcao(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho){
  if(ChaveAcaoNew != ChaveAcaoOld){
    BoxLedsRGB(R, G, B, Brilho);                  // Apaga os leds
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
  }
}

void ResetAcao(String ChaveAcaoNew, led_t Led){
  if(ChaveAcaoNew != ChaveAcaoOld){
    BoxLedsRGB(Led.R, Led.G, Led.B, Led.Brilho);            // Apaga os leds
    ChaveAcaoOld = ChaveAcaoNew;                            // Guarda a chave atual
  }
}

void LedsAcesos(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho){
  if(ChaveAcaoNew != ChaveAcaoOld){
    BoxLedsRGB(R, G, B, Brilho);
    while(getValorPinAcao());                     // Aguarda o cancelamento da ação 
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
  }
}

void LedsXadrezFade(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho){
  if(ChaveAcaoNew != ChaveAcaoOld){
    bool  IniciarImpar = true;
    int   Percentual   = 100;
    int   Intervalo    = 10;

    tmpWaitRotina = 11000;
    while(getValorPinAcao()) {
      
      if(tmpWaitRotina > 5000){
        
        BoxLedsRGBXadrezFade(IniciarImpar, R, G, B, Brilho, Percentual);
        Percentual -= Intervalo;
        if((Percentual < 0) || (Percentual > 100)) {
          Intervalo *=-1;
          Percentual -= Intervalo;
        }
        tmpWaitRotina = 0;
      } else { tmpWaitRotina++; delayMicroseconds(100); }
    }
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
  }
}

void Mensagem(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho, byte LinhaShow){

    char Msg[50]  = {0};
    byte QtdeChar = 0;

    getTextoOnEEPROM(Msg, &QtdeChar);

    while(getValorPinAcao()) {
      ShowMsgBox(Msg, QtdeChar - 1, R, G, B, Brilho, LinhaShow);
    }
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
}

void MensagemDebug(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho, byte LinhaShow){

    char Msg[50]  = {0};
    byte QtdeChar = 0;
    byte QtdeCharDebug = 0;

    getTextoOnEEPROM(Msg, &QtdeChar);

    char MsgDebug[QtdeChar + 25];

    if(QtdeChar < 50) {
      int p = 0;
      MsgDebug[p++] = 'M', MsgDebug[p++] = 'S', MsgDebug[p++] = 'G', MsgDebug[p++] = '.';

      byte i = 0;
      for(i; i < (QtdeChar); i++) {
        MsgDebug[p++] = Msg[i];
      }
      MsgDebug[p++] = ' ';
      MsgDebug[p++] = 'R', MsgDebug[p++] = '.', MsgDebug[p++] = (int)R;
      MsgDebug[p++] = ' ';
      MsgDebug[p++] = 'G', MsgDebug[p++] = '.', MsgDebug[p++] = (byte)G;
      MsgDebug[p++] = ' ';
      MsgDebug[p++] = 'B', MsgDebug[p++] = '.', MsgDebug[p++] = (byte)B;
      MsgDebug[p++] = ' ';
      MsgDebug[p++] = 'B', MsgDebug[p++] = 'r', MsgDebug[p++] = '.', MsgDebug[p++] = (byte)Brilho;
      
    }
    QtdeCharDebug = QtdeChar + 25;

    while(getValorPinAcao()) {
      ShowMsgBox(MsgDebug, QtdeChar - 1, R, G, B, Brilho, LinhaShow);
    }
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
}

void InicializaCascata(cascata_t cascata[], uint8_t *pSizeCascata = 1){

  uint8_t qtdColunas            = *pSizeCascata;
  uint8_t colunas[qtdColunas]   = {0};

  randomUnico(colunas, *pSizeCascata);

  for(uint8_t i = 0; i < (*pSizeCascata - 1); i++){

    cascata[i].Coluna       = colunas[i];
    cascata[i].Linha        = random(-3, 2);
    cascata[i].Arrasto      = random(3,  6);
    cascata[i].Percentual   = 100 / cascata[i].Arrasto;      // percentual usado para fazer o arrasto
    cascata[i].Finalizado   = false;
    
  }

}

void LedsCascata(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho) {

  if(ChaveAcaoNew != ChaveAcaoOld){
    
    tmpWaitRotina                     = 11000;
    uint8_t sizeCascata               = 15;
    uint8_t colunasFeitas             = 0;
    cascata_t cascata[sizeCascata];

    // Mantem a vitrine acesa
    VitrineLedsRGB(R, G, B, Brilho);

    while(getValorPinAcao()) {

      if(tmpWaitRotina > 10000){

        InicializaCascata(cascata, &sizeCascata);
        colunasFeitas = 0;
        
        while(getValorPinAcao() && colunasFeitas < 14){

          for(uint8_t coluna = 0; coluna <= 14 && getValorPinAcao(); coluna++){

            if(cascata[coluna].Linha > 0 && (!cascata[coluna].Finalizado)){

              LedsShowBoxCascata(R, G, B, Brilho, cascata, coluna);
              
            }

            if((cascata[coluna].Linha - cascata[coluna].Arrasto) > 14){
              colunasFeitas++;
              cascata[coluna].Finalizado = true;
            }

            cascata[coluna].Linha++;
          }
        }
        
        tmpWaitRotina = 0;
        
      } else { tmpWaitRotina++; delayMicroseconds(100);}
    
    }
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
  }
     
}

void LedsFuncaoAcao(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho, pTipoVoid pFuncaoAcao){
  if(ChaveAcaoNew != ChaveAcaoOld){
    bool IniciarImpar = true;
    tmpWaitRotina = 11000;
    while(getValorPinAcao()) {
      if(tmpWaitRotina > 10000){
        pFuncaoAcao(IniciarImpar, R, G, B, Brilho);
        IniciarImpar = !IniciarImpar;
        tmpWaitRotina = 0;
      }else { tmpWaitRotina++; delayMicroseconds(100);}
    }
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
  }
}

void LedsShowBoxFixoAcao(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho, pTipoVoidBox pFuncaoBox ){
  if(ChaveAcaoNew != ChaveAcaoOld){
    IniciarMapaBox();
    pFuncaoBox(R, G, B, Brilho);
    while(getValorPinAcao());                     // Aguarda o cancelamento da ação 
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
  }
}

void LedsFadeBox(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho) {
  if(ChaveAcaoNew != ChaveAcaoOld){
    bool IniciarImpar = true;
    tmpWaitRotina = 11000;
    while(getValorPinAcao()) {
      if(tmpWaitRotina > 10000){
        BoxFade(IniciarImpar, R, G, B);  
        IniciarImpar = !IniciarImpar;
        tmpWaitRotina = 0;
      }else { tmpWaitRotina++; delayMicroseconds(100);}
    }
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
  }
}

void LedsVaiVem(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho){
  if(ChaveAcaoNew != ChaveAcaoOld){
    tmpWaitRotina = 11000;
    while(getValorPinAcao()) {
      if(tmpWaitRotina > 10000){
        BoxLedsVaiVem(R, G, B, Brilho);  
        tmpWaitRotina = 0;
      }else { tmpWaitRotina++; delayMicroseconds(100);}
    }
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
  }
}

void randomUnico(uint8_t bufferValores[], uint8_t *pSizeBuffer){

  uint8_t   coluna       = 0;
  bool      valorExiste;
  uint8_t   minimo        = 1;
  uint8_t   maximo        = *pSizeBuffer + 1;
  uint8_t   valor;

  randomSeed(random());

  while(coluna < *pSizeBuffer){

    valor = random(minimo, maximo);

    valorExiste = false;
    for(int i = 0; i <= *pSizeBuffer; i++ ){
      if(valor == bufferValores[i]){
        valorExiste = true;
        break;
      }
    }
    if(!valorExiste){
      bufferValores[coluna] = valor;
      coluna++;
    }
  }
}
