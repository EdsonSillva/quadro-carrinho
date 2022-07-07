/****************************************************************
 * Gerenciador das Rotinas das Ações recebidas pela tela Nextion
 * Desenvolvido por Edson Silva
 * Date: 07/07/19  
 * Alteração: jun/22
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

void LedsAcesos(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho){
  if(ChaveAcaoNew != ChaveAcaoOld){
    BoxLedsRGB(R, G, B, Brilho);
    while(getValorPinAcao());                     // Aguarda o cancelamento da ação 
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
  }
}

//void LedsXadrez(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho){
//  if(ChaveAcaoNew != ChaveAcaoOld){
//    bool IniciarImpar = true;
//    tmpWaitRotina = 11000;
//    while(getValorPinAcao()) {
//      if(tmpWaitRotina > 10000){
//        BoxLedsRGBXadrez(IniciarImpar, R, G, B, Brilho);
//        IniciarImpar = !IniciarImpar;
//        tmpWaitRotina = 0;
//      }else { tmpWaitRotina++; delayMicroseconds(100);}
//    }
//    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
//  }
//}

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

/*
// TODO: Apagar depois de testar
//        if(Percentual < 0) {
//          Intervalo *=-1;
//          Percentual -= Intervalo;
//        }
//        else if(Percentual > 100) {
//          Intervalo *=-1;
//          Percentual -= Intervalo;
//        }
*/
        tmpWaitRotina = 0;
      }else { tmpWaitRotina++; delayMicroseconds(100); }
    }
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
  }
}

//void LedsColuna(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho){
//  if(ChaveAcaoNew != ChaveAcaoOld){
//    bool IniciarImpar = true;
//    tmpWaitRotina = 11000;
//    while(getValorPinAcao()) {
//      if(tmpWaitRotina > 10000){
//        BoxLedsRGBColuna(IniciarImpar, R, G, B, Brilho);
//        IniciarImpar = !IniciarImpar;
//        tmpWaitRotina = 0;
//      }else { tmpWaitRotina++; delayMicroseconds(100);}
//    }
//    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
//  }
//}

//void LedsLinha(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho){
//  if(ChaveAcaoNew != ChaveAcaoOld){
//    bool IniciarImpar = true;
//    tmpWaitRotina = 11000;
//    while(getValorPinAcao()) {
//      if(tmpWaitRotina > 10000){
//        BoxLedsRGBLinha(IniciarImpar, R, G, B, Brilho);
//        IniciarImpar = !IniciarImpar;
//        tmpWaitRotina = 0;
//      }else { tmpWaitRotina++; delayMicroseconds(100);}
//    }
//    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
//  }
//}

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

//    Serial.print(MsgDebug);
    
    while(getValorPinAcao()) {
      ShowMsgBox(MsgDebug, QtdeChar - 1, R, G, B, Brilho, LinhaShow);
    }
    ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
}

void LedsCascata(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho) {
  
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
