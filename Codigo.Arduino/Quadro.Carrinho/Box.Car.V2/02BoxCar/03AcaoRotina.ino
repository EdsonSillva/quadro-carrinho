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

//void ResetAcao(String ChaveAcaoNew, led_t Led){
//  if(ChaveAcaoNew != ChaveAcaoOld){
//    BoxLedsRGB(Led.R, Led.G, Led.B, Led.Brilho);            // Apaga os leds
//    ChaveAcaoOld = ChaveAcaoNew;                            // Guarda a chave atual
//  }
//}

void LedsAcesos(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho){

  if(ChaveAcaoNew == ChaveAcaoOld){
      Serial.println("...ChaveAcaoNew = ChaveAcaoOld  !!!");
  }

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

   String sMsg;
   byte CodeAcao         = 0;
   char Msg[50]          = {0};
   byte QtdeChar         = 0;
   byte QtdeCharDebug    = 0;

   getDadosOnEEPROM(&CodeAcao, &R, &G, &B, &Brilho);       // Busca novamente os valores da EEPROM porque é usado o array de gamma no RGB 

   getTextoOnEEPROM(Msg, &QtdeChar);

   sMsg.concat("<Code:>"),         sMsg.concat(CodeAcao);
   sMsg.concat(" <R:>"),           sMsg.concat(R);
   sMsg.concat(" <G:>"),           sMsg.concat(G);
   sMsg.concat(" <B:>"),           sMsg.concat(B);
   sMsg.concat(" <Br:>"),          sMsg.concat(Brilho);
   sMsg.concat(" <MSG:>"),         sMsg.concat(Msg); 

   QtdeCharDebug = sMsg.length() + 1;
   char MsgDebug[QtdeCharDebug];

   sMsg.toCharArray(MsgDebug, QtdeCharDebug);

   while(getValorPinAcao()) {
     ShowMsgBoxDebug(MsgDebug, QtdeCharDebug - 2, R, G, B, Brilho, LinhaShow);
   }
   ChaveAcaoOld = ChaveAcaoNew;                  // Guarda a chave atual
}

void InicializaCascata(cascata_t cascata[], uint8_t SizeCascata){

//  uint8_t qtdColunas            = SizeCascata;
 uint8_t colunas[SizeCascata]   = {0};

//  Serial.print("\n.....Chamando randomUnico(colunas, pSizeCascata):"),Serial.print(qtdColunas),Serial.print("\n");
//  Serial.print("\n.....Chamando randomUnico(colunas, SizeCascata):"),Serial.print("\n");
 randomUnico(colunas, SizeCascata);

 for(uint8_t i = 0; i < (SizeCascata - 1); i++){
   cascata[i].Coluna       = colunas[i];
   cascata[i].Linha        = random(-3, 2);
   cascata[i].Arrasto      = random(3,  6);
   cascata[i].Percentual   = 100 / cascata[i].Arrasto;      // percentual usado para fazer o arrasto
   cascata[i].Finalizado   = false;

//    Serial.print("\n.....cascata[i]=:"),Serial.print(i),Serial.print("\n");
//    Serial.print(".....cascata[i].Coluna:"),Serial.print(cascata[i].Coluna),Serial.print("\n");
//    Serial.print(".....cascata[i].Linha:"),Serial.print(cascata[i].Linha),Serial.print("\n");
//    Serial.print(".....cascata[i].Arrasto:"),Serial.print(cascata[i].Arrasto),Serial.print("\n");
//    Serial.print(".....cascata[i].Percentual:"),Serial.print(cascata[i].Percentual),Serial.print("\n");
//    Serial.print(".....cascata[i].Finalizado:"),Serial.print(cascata[i].Finalizado),Serial.print("\n");
   delay(250);

 }
}

void LedsCascata(String ChaveAcaoNew, byte R, byte G, byte B, byte Brilho) {

 if(ChaveAcaoNew != ChaveAcaoOld){
   
   tmpWaitRotina                     = 11000;
   uint8_t sizeCascata               = 15;
   uint8_t colunasFeitas             = 0;
   cascata_t cascata[sizeCascata];

  //  Serial.print("\n.....R:"),Serial.print(R),Serial.print("\n");
  //  Serial.print("\n.....G:"),Serial.print(G),Serial.print("\n");
  //  Serial.print("\n.....B:"),Serial.print(B),Serial.print("\n");
   
   // Mantem a vitrine acesa
   VitrineLedsRGB(R, G, B, Brilho);

   while(getValorPinAcao()) {

     if(tmpWaitRotina > 10000){

     
      //  Serial.print("\n.....Chamando InicializaCascata(sizeCascata):"),Serial.print(sizeCascata),Serial.print("\n");
       InicializaCascata(cascata, sizeCascata);
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

void randomUnico(uint8_t bufferValores[], uint8_t SizeBuffer){

 bool      valorExiste;
 uint8_t   coluna        = 0;
 uint8_t   minimo        = 1;
 uint8_t   maximo        = SizeBuffer + 1;
 uint8_t   valor;

 //Serial.print("\n.....Dentro randomUnico(colunas, SizeBuffer):");
 
 randomSeed(random());

 while(coluna < SizeBuffer){

   valor = random(minimo, maximo);

   valorExiste = false;
   for(int i = 0; i <= SizeBuffer; i++ ){
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



