/*******************************************
 * NeoPixel Controlador dos Led's no quadro
 * Desenvolvido por Edson Silva
 * Date: 04/06/18  
 ******************************************/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

/***********************************************
 * Declaração das variáveis Globais de controle
 ***********************************************/

// Porta sendo usada para o Box e Vitrine
//****************************************
#define pin_Led             13

// Definições para controle do Box
//*********************************
#define qtd_Colunas         15
#define qtd_Linhas          14
#define qtd_Boxes           qtd_Colunas * qtd_Linhas

// Definições para o controle da Vitrine
//***************************************
#define Star_Led_Vitrine    qtd_Boxes                           // Seta para a posição inicial dos Leds da Vitrine
#define qtd_Leds_Vitrine    20

// Definições para o controle geral
//**********************************
#define Total_Leds          qtd_Boxes + qtd_Leds_Vitrine        // O Valor é 230
#define BrightnessDefault   75                                  // Guarda o valor default de Brilho
#define BoxTop              01
#define BoxBottom           02
#define BoxLeft             03
#define BoxRight            04
#define LinhaPosicaoDada    05
#define ColunaPosicaoDada   06

// Definições do Objeto de controle dos Led
//******************************************

Adafruit_NeoPixel Leds = 
                  Adafruit_NeoPixel(Total_Leds, pin_Led, 
                  NEO_GRB + NEO_KHZ800);

int StartFadeUp = 0;

word MapaBox[qtd_Linhas + 1] = {0b0000000000000000      // Linha 01 do quadro
                               ,0b0000000000000000      // Linha 02 do quadro
                               ,0b0000000000000000      // Linha 03 do quadro
                               ,0b0000000000000000      // Linha 04 do quadro
                               ,0b0000000000000000      // Linha 05 do quadro
                               ,0b0000000000000000      // Linha 06 do quadro
                               ,0b0000000000000000      // Linha 07 do quadro
                               ,0b0000000000000000      // Linha 08 do quadro
                               ,0b0000000000000000      // Linha 09 do quadro
                               ,0b0000000000000000      // Linha 10 do quadro
                               ,0b0000000000000000      // Linha 11 do quadro
                               ,0b0000000000000000      // Linha 12 do quadro
                               ,0b0000000000000000      // Linha 13 do quadro
                               ,0b0000000000000000      // Linha 14 do quadro
                               };

/***********************************
 * ROTINAS DE INTERAÇÃO COM OS LEDs 
 ***********************************/
void IniciarLeds(int IntensidadeBrilho){
    setBrilho(IntensidadeBrilho);
    Leds.begin();
    Leds.show();
    delay(500);                           // Aguardar um tempo para refletir o comando nos Leds
}

void IniciarMapaBox(){
  for(byte Indice = 0; Indice <= 14; Indice++){
    MapaBox[Indice] = 0b0000000000000000;
  }
}

void setBrilho(int Intensidade){
  Leds.setBrightness(Intensidade);
}

void setCorBoxFade(int Inicio, int R, int G, int B){

    for(int i = Inicio; i < Total_Leds; i++){
        //Configura a cor do Led
        Leds.setPixelColor(i, Leds.Color(R, G, B));
        i++; // Necessário para pular um Led
    }
    delay(5);
}
//***************************************/
// ROTINAS DE MAPEAMENTO DO BOX (QUADRO) 
//***************************************/

int PosicaoBoxTop(int PosicaoDada) {
    return PosicaoBox(PosicaoDada, BoxTop);
}

int PosicaoBoxBotton(int PosicaoDada) {
    return PosicaoBox(PosicaoDada, BoxBottom);
}

int PosicaoBoxLeft(int PosicaoDada) {
    return PosicaoBox(PosicaoDada, BoxLeft);
}

int PosicaoBoxRight(int PosicaoDada) {
    return PosicaoBox(PosicaoDada, BoxRight);
}

int PosicaoBox(int PosicaoDada, int PosicaoSolicitada) {

    int LinhaCalculada                = PosicaoDada / (int)qtd_Colunas;
    int LinhaPosicao                  = LinhaCalculada + 1;
    int NumLeft                       = (LinhaPosicao % 2) == 0 ? -1 :  1;
    int NumRight                      = (LinhaPosicao % 2) == 0 ?  1 : -1;
    int DeslocamentoPosicaoCalculado  = (int)(PosicaoDada % (int)qtd_Colunas) + 1;
    int ColunaPosicao                 = (LinhaCalculada % 2) == 0 ? (int)qtd_Colunas - (DeslocamentoPosicaoCalculado - 1) : DeslocamentoPosicaoCalculado;
    int LinhaPosicaoBottom            = LinhaCalculada + 1;
    int DeslocamentoPosicaoBottom     = (LinhaPosicaoBottom % 2) == 0 ? (int)qtd_Colunas - DeslocamentoPosicaoCalculado : (int)ColunaPosicao - 1;
    int PosicaoTop                    = (LinhaCalculada * qtd_Colunas) - DeslocamentoPosicaoCalculado;
    int PosicaoBottom                 = ((LinhaCalculada + 1) * qtd_Colunas) + DeslocamentoPosicaoBottom;
    int PosicaoLeftCalculada          = (PosicaoDada + NumLeft);
    int PosicaoRightCalculada         = (PosicaoDada + NumRight);
    int PosicaoLeft                   = PosicaoLeftCalculada == PosicaoTop || PosicaoLeftCalculada == PosicaoBottom ? -1 : PosicaoLeftCalculada;
    int PosicaoRight                  = PosicaoRightCalculada == PosicaoTop || PosicaoRightCalculada == PosicaoBottom ? -1 : PosicaoRightCalculada;

    switch (PosicaoSolicitada)
    {
    case BoxTop: 
      return PosicaoTop;
      break;
    case BoxBottom:
      return PosicaoBottom;
      break;
    case BoxLeft:
      return PosicaoLeft;
      break;
    case BoxRight:
      return PosicaoRight;
      break;
    case LinhaPosicaoDada:
      return LinhaPosicao;
      break;
    case ColunaPosicaoDada:
      return ColunaPosicao;
      break;
    }
}

// ROTINA PARA RETORNAR A POSICAO DADO A LINHA E COLUNA
// ****************************************************
int PosicaoBoxCell(int Linha, int Coluna){
    return (int)(qtd_Colunas * (Linha - 1)) + ((Linha % 2) == 0 ? 
                                                qtd_Colunas - Coluna :
                                                Coluna - 1);
}

int PosicaoBoxCellInvertido(int Linha, int Coluna){
    return (int)(qtd_Colunas * (Linha - 1)) + ( (Linha % 2) == 0 ? 
                                                ( (Coluna - 1) )  : 
                                                ( (qtd_Colunas - (Coluna) )) );
}

//FIM

void inline ShowLeds(int Wait){
  Leds.show();
  delay(Wait);
}

void VitrineLedsRGB(byte R, byte G, byte B, byte Br){

    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }
    
    for(int Led = Star_Led_Vitrine; Led < Total_Leds; Led++){
      Leds.setPixelColor(Led, Leds.Color(G, R, B));
    }
}

void BoxLedsRGB(byte R, byte G, byte B, byte Br){

    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }
    
    for(int Led = 0; Led < Total_Leds; Led++){
      Leds.setPixelColor(Led, Leds.Color(G, R, B));
    }
    ShowLeds(500);
}

void BoxLedsRGBXadrezFade(bool IniciarImpar, byte R, byte G, byte B, byte Br, int PercentualRecebido){

    byte  RLow, GLow, BLow, RHigh, GHigh, BHigh, RShow,  GShow,  BShow;
    float PercentualEntrada = (float)(PercentualRecebido / 100.0);
    float PercentualInverso = ((100 - PercentualRecebido) / 100.0);

    RHigh = (byte)(R * PercentualEntrada);
    GHigh = (byte)(G * PercentualEntrada);
    BHigh = (byte)(B * PercentualEntrada);

    RLow  = (byte)(R * PercentualInverso),    
    GLow  = (byte)(G * PercentualInverso),  
    BLow  = (byte)(B * PercentualInverso);

    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }

    if(IniciarImpar){ RShow = RHigh,  GShow = GHigh,  BShow = BHigh; }
    else            { RShow = RLow,   GShow = GLow,   BShow = BLow; }
    
    for(int Led = 0; Led < qtd_Boxes; Led++){
      
      Leds.setPixelColor(Led, Leds.Color(GShow, RShow, BShow));
      
      RShow = RShow == RHigh  ?   RLow : RHigh;
      GShow = GShow == GHigh  ?   GLow : GHigh;
      BShow = BShow == BHigh  ?   BLow : BHigh;
    }
    
    VitrineLedsRGB(105, 248, 196, Br);
    ShowLeds(500);
}

void BoxLedsRGBXadrez(bool IniciarImpar, byte R, byte G, byte B, byte Br){

    byte Rb = 20,  Gb = 20,  Bb = 20;
    byte Rd = 0,  Gd = 0,  Bd = 0;

    if(IniciarImpar){ Rd = R, Gd = G, Bd = B; }
    else { Rd = Rb, Gd = Gb, Bd = Bb; }

    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }
    
    for(int Led = 0; Led < qtd_Boxes; Led++){
      Leds.setPixelColor(Led, Leds.Color(Gd, Rd, Bd));
      Rd = Rd == R ? Rb : R;
      Gd = Gd == G ? Gb : G;
      Bd = Bd == B ? Bb : B;
    }
    VitrineLedsRGB(R, G, B, Br);
    ShowLeds(500);
}

void BoxLedsRGBColuna(bool IniciarImpar, byte R, byte G, byte B, byte Br){

    byte Rb = 20,  Gb = 20,  Bb = 20;
    byte Rd = 0,  Gd = 0,  Bd = 0;

    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }

    for(byte L = 1; L <= qtd_Linhas; L++){

      if(IniciarImpar){ Rd = R, Gd = G, Bd = B; }
      else { Rd = Rb, Gd = Gb, Bd = Bb; }

      for(byte C = 1; C <= qtd_Colunas; C++){
        Leds.setPixelColor(PosicaoBoxCellInvertido(L, C), Leds.Color(Gd, Rd, Bd));
        Rd = Rd == R ? Rb : R;
        Gd = Gd == G ? Gb : G;
        Bd = Bd == B ? Bb : B;
      }
    }
    VitrineLedsRGB(R, G, B, Br);
    ShowLeds(500);

}

void BoxLedsRGBLinha(bool IniciarImpar, byte R, byte G, byte B, byte Br){

    byte Rb = 20,  Gb = 20,  Bb = 20;
    byte Rd = 0,  Gd = 0,  Bd = 0;

    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }

    for(byte C = 1; C <= qtd_Colunas; C++){

      if(IniciarImpar){ Rd = R, Gd = G, Bd = B; }
      else { Rd = Rb, Gd = Gb, Bd = Bb; }

      for(byte L = 1; L <= qtd_Linhas; L++){
        Leds.setPixelColor(PosicaoBoxCellInvertido(L, C), Leds.Color(Gd, Rd, Bd));
        Rd = Rd == R ? Rb : R;
        Gd = Gd == G ? Gb : G;
        Bd = Bd == B ? Bb : B;
      }
    }
    VitrineLedsRGB(R, G, B, Br);
    ShowLeds(500);

}

 void BoxFade(bool Par, int R, int G, int B){

    int Inicio;
    if(Par)
      Inicio = 0;
    else
      Inicio = 1;
    FadeUp(Inicio, R, G, B);
    FadeDown(Inicio, R, G, B);    
}

void FadeUp(int Inicio, int R, int G, int B){

      for(int j = StartFadeUp; j < 256; j++){
        setCorBoxFade(Inicio, j, j, j);        
        Leds.show();
    }
    delay(1000);
}

void FadeDown(int Inicio, int R, int G, int B){

    int BottonFadeTransition = 100;

    for(int j = 255; j >= 0; j--){
    
      setCorBoxFade(Inicio, j, j, j);        
    
      if(j <= BottonFadeTransition){
      
        Leds.show();
        StartFadeUp = BottonFadeTransition;
        
        if(Inicio == 0){    // Par
           setCorBoxFade(Inicio + 1, (StartFadeUp - (j)), (StartFadeUp - (j)), (StartFadeUp - (j)));        
        }
        else{               // Impar
           setCorBoxFade(Inicio - 1, (StartFadeUp - (j)), (StartFadeUp - (j)), (StartFadeUp - (j)));        
        }
        delay(17);
        Leds.show();

      }
    }
}

void BoxLedsVaiVem(byte R, byte G, byte B, byte Br) {

    DesceSobeEmColuna(R, G, B, 40);
    if(!getValorPinAcao()) return;
    DesceEmColuna(G, B, R, 50);
    if(!getValorPinAcao()) return;
    SobeEmColuna(0, G/4, 0, 60);
    if(!getValorPinAcao()) return;
    VitrineLedsRGB(R, G, B, Br);
    if(!getValorPinAcao()) return;
    DoMeioParaPontas(90, 0, 30, false);
    if(!getValorPinAcao()) return;
    SoVai(0, 90, 10, true);
    if(!getValorPinAcao()) return;
    DesceEmColuna(R/4, G*4, B/8, 40);
    if(!getValorPinAcao()) return;
    SobeEmColunaInvertido(R/6, G/4, B*4, 50);
    VaiVem();
    if(!getValorPinAcao()) return;
    VaiVemDupla();
    if(!getValorPinAcao()) return;
}

void SoVai(byte R, byte G, byte B, bool ApagaApos){
  
     // Acende o Led
    for(int i = 0; i < qtd_Boxes; i++){
      Leds.setPixelColor(i, Leds.Color(G, R, B)); 
      ShowLeds(100);
    }
    if(ApagaApos == true) {
       SoVai(0, 0, 0, false);     //Apaga o Led
    }
}

void VaiVem() {

    // Acende o Led
    for(int i = 0; i < qtd_Boxes; i++){
      Leds.setPixelColor(i, Leds.Color(random(30, 100), random(20,100), random(50,255))); 
      ShowLeds(100);
    }

    //Apaga o Led
    for(int i = qtd_Boxes; i >= 0; i--){
      Leds.setPixelColor(i, Leds.Color(0,0,0)); // Moderately bright green color.
      ShowLeds(100);
  }
}

void VaiVemDupla(){

    // Acende o Led
    for(int i = 0; i < (qtd_Boxes/2); i++){
      Leds.setPixelColor(i, Leds.Color(random(30, 100), random(20,100), random(50,255))); 
      ShowLeds(10);

      Leds.setPixelColor(i+(qtd_Boxes/2), Leds.Color(random(30, 100), random(20,100), random(50,255))); 
      ShowLeds(100);
    }

    //Apaga o Led
    for(int i = qtd_Boxes; i >= 0; i--){
      Leds.setPixelColor(i, Leds.Color(0,0,0)); 
      ShowLeds(10);

      Leds.setPixelColor(i-(qtd_Boxes/2), Leds.Color(0,0,0)); 
      ShowLeds(100);
    }
    delay(100);
}

void DoMeioParaPontas(byte R, byte G, byte B, bool EuChamei){
  
    // Acende o Led
    for(int i = 0; i < (qtd_Boxes/2)+1;i++){
      Leds.setPixelColor(((qtd_Boxes / 2) - i), Leds.Color(R, G, B)); 
      Leds.setPixelColor(((qtd_Boxes / 2) + i)-1, Leds.Color(R, G, B-B)); 
      ShowLeds(100);
    }

    //Apaga o Led
    if (!EuChamei){
      DoMeioParaPontas(0, 0, 0, true);
    }
}

void DesceSobeEmColuna(byte R, byte G, byte B, int wait) {

    for(int c = 1; c <= qtd_Colunas+19; c++) {
      for(int l = 1; l <= qtd_Linhas; l++) {
            DesceEmColuna(R, G, B, c, l, wait);
            SobeEmColuna(R/4, G*4, B/4, c+1, qtd_Linhas-(l-1), wait);
            ShowLeds(wait);
      }
    }
}

void DesceEmColuna(byte R, byte G, byte B, int Col, int Lin, int wait) {

//    for(int c = 1; c <= qtdeCol; c++) {
//      for(int l = 1; l <= qtdeLin; l++) {
//          Leds.setPixelColor(PosicaoBoxCellInvertido(l, c), Leds.Color(G, R, B)); 
          Leds.setPixelColor(PosicaoBoxCellInvertido(Lin, Col), Leds.Color(G, R, B)); 
//          ShowLeds(wait);
//      }
//    }
}

void SobeEmColuna(byte R, byte G, byte B, int Col, int Lin, int wait) {

//    for(int c = 1; c <= qtdeCol; c++) {
//      for(int l = qtdeLin; l >= 1; l--) {
//          Leds.setPixelColor(PosicaoBoxCellInvertido(l, c), Leds.Color(G, R, B)); 
          Leds.setPixelColor(PosicaoBoxCellInvertido(Lin, Col), Leds.Color(G, R, B)); 
//          ShowLeds(wait);
//      }
//    }
}




void DesceEmColuna(byte R, byte G, byte B, int wait) {

    for(int c = 1; c <= qtd_Colunas; c++) {
      for(int l = 1; l <= qtd_Linhas; l++) {
          Leds.setPixelColor(PosicaoBoxCellInvertido(l, c), Leds.Color(G, R, B)); 
          ShowLeds(wait);
      }
    }
}


void SobeEmColuna(byte R, byte G, byte B, int wait) {

    for(int c = 1; c <= qtd_Colunas; c++) {
      for(int l = qtd_Linhas; l >= 1; l--) {
          Leds.setPixelColor(PosicaoBoxCellInvertido(l, c), Leds.Color(G, R, B)); 
          ShowLeds(wait);
      }
    }
}


void SobeEmColunaInvertido(byte R, byte G, byte B, int wait) {

    for(int c = qtd_Colunas; c >= 1; c--) {
      for(int l = qtd_Linhas; l >= 1; l--) {
          Leds.setPixelColor(PosicaoBoxCellInvertido(l, c), Leds.Color(G, R, B)); 
          ShowLeds(wait);
      }
    }
}



//void VaiEmColuna(byte R, byte G, byte B) {
//
//    for(int c = 1; c <= qtd_Colunas; c++) {
//      for(int l = 1; l <= qtd_Linhas; l++) {
//          Leds.setPixelColor(PosicaoBoxCellInvertido(l, c), Leds.Color(G, R, B)); 
//          ShowLeds(80);
//      }
//    }
//
//    for(int c = 1; c <= qtd_Colunas; c++) {
//      for(int l = qtd_Linhas; l >= 1; l--) {
//          Leds.setPixelColor(PosicaoBoxCellInvertido(l, c), Leds.Color(G/4, 0, 0)); 
//          ShowLeds(60);
//      }
//    }
//
//    for(int c = 1; c <= qtd_Colunas; c++) {
//      for(int l = 1; l <= qtd_Linhas; l++) {
//          Leds.setPixelColor(PosicaoBoxCellInvertido(l, c), Leds.Color(G/2, R/4, B/6)); 
//          ShowLeds(70);
//      }
//    }
//
//    for(int c = qtd_Colunas; c >= 1; c--) {
//      for(int l = qtd_Linhas; l >= 1; l--) {
//          Leds.setPixelColor(PosicaoBoxCellInvertido(l, c), Leds.Color(G*2, R/4, B*2)); 
//          ShowLeds(40);
//      }
//    }
//}


/*****************************************************
 *  Rotinas de posição fixa dos carros
 * 
 *****************************************************/


void BoxLedsBatmanRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[2] = 0b1110000000000001;      // Linha 03 do quadro
    MapaBox[3] = 0b1110000000000001;      // Linha 04 do quadro
    MapaBox[4] = 0b1110000000000001;      // Linha 05 do quadro
    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsMotosRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[2] = 0b0000000001111111;      // Linha 03 do quadro
    MapaBox[3] = 0b0000000000000011;      // Linha 04 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsStarWarsRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[5] = 0b1110000000000001;      // Linha 06 do quadro
    MapaBox[6] = 0b1110000000000001;      // Linha 07 do quadro
    MapaBox[7] = 0b1100000000000001;      // Linha 08 do quadro
    MapaBox[8] = 0b1100000000000001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsLamborghiniRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[8] = 0b0000000000000111;      // Linha 09 do quadro
    MapaBox[9] = 0b0000000000001111;      // Linha 10 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsPorcheRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[10] = 0b0000000000001111;      // Linha 11 do quadro
    MapaBox[11] = 0b0000000000001111;      // Linha 12 do quadro
    MapaBox[12] = 0b0000000000001111;      // Linha 13 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsTeslaRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[13] = 0b0000000000111001;      // Linha 12 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsBMWRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[13] = 0b0000000111000001;      // Linha 12 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsFordRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[8]  = 0b0000001110000001;      // Linha 09 do quadro
    MapaBox[9]  = 0b0000111110000001;      // Linha 10 do quadro
    MapaBox[10] = 0b0000111100000001;      // Linha 11 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsAstonMartinRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[10] = 0b0000000011110001;      // Linha 11 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsPaganiRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[8]  = 0b0000000000011001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsMacLarenRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[9]  = 0b0000000001110001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsAudiRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[6]  = 0b0000000010000001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsCorvetteRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[11]  = 0b0000011111110001;      // Linha 09 do quadro
    MapaBox[12]  = 0b0000011111110001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsNissanRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[5]  = 0b0000000000011111;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsFerrariRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[4]  = 0b0000001000000001;      // Linha 09 do quadro
    MapaBox[7]  = 0b0000000000001111;      // Linha 09 do quadro
    
    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsMercedesRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[6]  = 0b0000000000000111;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsHondaRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[6]   = 0b0000000000111001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsAcuraRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[13]  = 0b0000000000000111;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsJaguarRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[7]  = 0b0000000000110001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsVelozesFurososRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[2]  = 0b0000111100000001;      // Linha 09 do quadro
    MapaBox[3]  = 0b0001110000000001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsDodgeRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[7]  = 0b0000000111000001;      // Linha 09 do quadro
    MapaBox[8]  = 0b0000000001100001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsVolksRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[6]  = 0b0000001000000001;      // Linha 09 do quadro
    MapaBox[7]  = 0b0000111000000001;      // Linha 09 do quadro
    MapaBox[8]  = 0b0000110000000001;      // Linha 09 do quadro
    MapaBox[9]  = 0b0000100000000001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsFiatRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[6]  = 0b0000000100000001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsCadLacRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[5]  = 0b0000000000100001;      // Linha 09 do quadro
    MapaBox[8]  = 0b0010000000000001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsBentleyRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[3]  = 0b0000000000000101;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsMasdaRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[4]  = 0b0000000001100001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void BoxLedsBuickRGB(byte R, byte G, byte B, byte Br){
    IniciarMapaBox();
    MapaBox[5]  = 0b0000000001000001;      // Linha 09 do quadro

    ShowMapaBoxes(R, G, B, Br, 50);
}

void ShowMsgBox(char Msg[], byte TamanhoMsg, byte R, byte G, byte B, byte Brilho, byte LinhaShow){

    LinhaShow       = LinhaShow - 1;    // Necessário porque os arrays começam na posição 0
    byte LinhaBox   = LinhaShow;
    IniciarMapaBox();
    for(byte Letra = 0; Letra <= TamanhoMsg; Letra++){
      
      byte FimBitMascara      = 0;
      char LetraMascarada[5]  = {0x00,0x00,0x00,0x00,0x00};
      MascararLetra(Msg[Letra], LetraMascarada, &FimBitMascara);
      
      for(byte BitLetra = 7; BitLetra >= FimBitMascara; BitLetra--){
        for(byte PosicaoDaLetra = 0;PosicaoDaLetra <= 4; PosicaoDaLetra++){
          bitWrite(MapaBox[LinhaBox], 0, bitRead(LetraMascarada[PosicaoDaLetra], BitLetra));    //Set o bit 0 da mascara com o bit da mascara da letra
          LinhaBox++;
        }
        ShowMapaBoxes(R, G, B, Brilho, 40);                                                       // ShowMapaBoxes
        ShifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);                                       
        LinhaBox   = LinhaShow;
        delay(60);
      }
      if(Msg[Letra] != ' '){
        ShowMapaBoxes(R, G, B, Brilho, 40);                                                       // ShowMapaBoxes
        ShifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);                                         // Shift para espaço entre letras
        delay(60);
      }
      if(!getValorPinAcao()){Letra = TamanhoMsg+1;}
    }
    for(byte ColunasBranco = 1; ColunasBranco <= 15; ColunasBranco++ ){
       ShifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);                                         // Shift para espaço entre letras
       ShowMapaBoxes(R, G, B, Brilho, 40);                                                       // ShowMapaBoxes
       delay(60);
    }
}

void ShifEsquerdaMapaBox(byte PrimeiraLinha, byte UltimaLinha, byte QtdeBit){

    for(byte PosicaoShift = PrimeiraLinha; PosicaoShift <= UltimaLinha; PosicaoShift++ ){   // Shift Mascarabox
      MapaBox[PosicaoShift] = (MapaBox[PosicaoShift] << QtdeBit);
    }
}

void ShowMapaBoxes(byte R, byte G, byte B, byte Br, byte LuzFundo){

    word MapaBoxLinha = 0x00;
    byte Rb = LuzFundo,  Gb = LuzFundo,  Bb = LuzFundo;
    byte Rd = 0,  Gd = 0,  Bd = 0;
    
    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }

    for(byte L = 1; L <= qtd_Linhas; L++){

      MapaBoxLinha = MapaBox[L - 1];
      
      for(byte C = 1; C <= qtd_Colunas; C++){

        if(bitRead(MapaBoxLinha, 16 - C)){ Rd = R, Gd = G, Bd = B; }
        else { Rd = Rb, Gd = Gb, Bd = Bb; }
      
        Leds.setPixelColor(PosicaoBoxCellInvertido(L, C), Leds.Color(Gd, Rd, Bd));
      }
    }
    VitrineLedsRGB(R, G, B, Br);
    ShowLeds(500);
}

void TodosLedsAcesos(uint8_t r, uint8_t g, uint8_t b){
    for(int Led = 0; Led < Total_Leds; Led++){
      Leds.setPixelColor(Led, Leds.Color(g, r, b));
    }
    Leds.show();
    delay(500);
}

void TodosLedsApagados(){
    TodosLedsAcesos(0,0,0);   // Apaga os Leds mandando o RGB=0
}

void setAcendeBox(int Linha, int Coluna, byte R, byte G, byte B, byte Br){
    if (Leds.getBrightness() != (uint8_t)Br) {  setBrilho((int)Br);  }
    Leds.setPixelColor(PosicaoBoxCellInvertido(Linha, Coluna), Leds.Color(G, R, B));
}

void setApagaBox(int Linha, int Coluna, byte R, byte G, byte B, byte Br){
    Leds.setPixelColor(PosicaoBoxCellInvertido(Linha, Coluna), Leds.Color(G, R, B));
}

void setLedBox(int NumBox, byte R, byte G, byte B, byte Br){
    if (Leds.getBrightness() != (uint8_t)Br) {  setBrilho((int)Br);  }
    Leds.setPixelColor(NumBox, Leds.Color(G, R, B));
}




/*  bkp com degub */

//
///*******************************************
// * NeoPixel Controlador dos Led's no quadro
// * Desenvolvido por Edson Silva
// * Date: 04/06/18  
// ******************************************/
//
//#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//  #include <avr/power.h>
//#endif
//
///***********************************************
// * Declaração das variáveis Globais de controle
// ***********************************************/
//
//// Porta sendo usada para o Box e Vitrine
////****************************************
//#define pin_Led             13
//
//// Definições para controle do Box
////*********************************
//#define qtd_Colunas         15
//#define qtd_Linhas          14
//#define qtd_Boxes           qtd_Colunas * qtd_Linhas
//
//// Definições para o controle da Vitrine
////***************************************
//#define Star_Led_Vitrine    qtd_Boxes                           // Seta para a posição inicial dos Leds da Vitrine
//#define qtd_Leds_Vitrine    20
//
//// Definições para o controle geral
////**********************************
//#define Total_Leds          qtd_Boxes + qtd_Leds_Vitrine        // O Valor é 230
//#define BrightnessDefault   75                                  // Guarda o valor default de Brilho
//#define BoxTop              01
//#define BoxBottom           02
//#define BoxLeft             03
//#define BoxRight            04
//#define LinhaPosicaoDada    05
//#define ColunaPosicaoDada   06
//
//// Definições do Objeto de controle dos Led
////******************************************
//
//Adafruit_NeoPixel Leds = 
//                  Adafruit_NeoPixel(Total_Leds, pin_Led, 
//                  NEO_GRB + NEO_KHZ800);
//
//int StartFadeUp = 0;
//
//word MapaBox[qtd_Linhas + 1] = {0b0000000000000000      // Linha 01 do quadro
//                               ,0b0000000000000000      // Linha 02 do quadro
//                               ,0b0000000000000000      // Linha 03 do quadro
//                               ,0b0000000000000000      // Linha 04 do quadro
//                               ,0b0000000000000000      // Linha 05 do quadro
//                               ,0b0000000000000000      // Linha 06 do quadro
//                               ,0b0000000000000000      // Linha 07 do quadro
//                               ,0b0000000000000000      // Linha 08 do quadro
//                               ,0b0000000000000000      // Linha 09 do quadro
//                               ,0b0000000000000000      // Linha 10 do quadro
//                               ,0b0000000000000000      // Linha 11 do quadro
//                               ,0b0000000000000000      // Linha 12 do quadro
//                               ,0b0000000000000000      // Linha 13 do quadro
//                               ,0b0000000000000000      // Linha 14 do quadro
//                               };
///*
//word MapaBox[qtd_Linhas + 1] = {0b0000000000000000      // Linha 01 do quadro
//                               ,0b0000000000000000      // Linha 02 do quadro
//                               ,0b1110000000000001      // Linha 03 do quadro
//                               ,0b1110000000000001      // Linha 04 do quadro
//                               ,0b1110000000000001      // Linha 05 do quadro
//                               ,0b0000000000000000      // Linha 06 do quadro
//                               ,0b0000000000000000      // Linha 07 do quadro
//                               ,0b0000000000000000      // Linha 08 do quadro
//                               ,0b0111000010011100      // Linha 09 do quadro
//                               ,0b0100000010010000      // Linha 10 do quadro
//                               ,0b0110001110011100      // Linha 11 do quadro
//                               ,0b0100001010000100      // Linha 12 do quadro
//                               ,0b0111001110011100      // Linha 13 do quadro
//                               ,0b0000000000000000      // Linha 14 do quadro
//                               };*/
//
//
///***********************************
// * ROTINAS DE INTERAÇÃO COM OS LEDs 
// ***********************************/
//void IniciarLeds(int IntensidadeBrilho){
//    setBrilho(IntensidadeBrilho);
//    Leds.begin();
//    Leds.show();
//    delay(500);                           // Aguardar um tempo para refletir o comando nos Leds
//}
//
//void IniciarMapaBox(){
//  for(byte Indice = 0; Indice <= 14; Indice++){
//    MapaBox[Indice] = 0b0000000000000000;
//  }
//}
//
//void setBrilho(int Intensidade){
//  Leds.setBrightness(Intensidade);
//}
//
//void setCorBoxFade(int Inicio, int R, int G, int B){
//
//    for(int i = Inicio; i < Total_Leds; i++){
//        //Configura a cor do Led
//        Leds.setPixelColor(i, Leds.Color(R, G, B));
//        i++; // Necessário para pular um Led
//    }
//    delay(5);
//}
////***************************************/
//// ROTINAS DE MAPEAMENTO DO BOX (QUADRO) 
////***************************************/
//
//int PosicaoBoxTop(int PosicaoDada) {
//    return PosicaoBox(PosicaoDada, BoxTop);
//}
//
//int PosicaoBoxBotton(int PosicaoDada) {
//    return PosicaoBox(PosicaoDada, BoxBottom);
//}
//
//int PosicaoBoxLeft(int PosicaoDada) {
//    return PosicaoBox(PosicaoDada, BoxLeft);
//}
//
//int PosicaoBoxRight(int PosicaoDada) {
//    return PosicaoBox(PosicaoDada, BoxRight);
//}
//
//int PosicaoBox(int PosicaoDada, int PosicaoSolicitada) {
//
//    int LinhaCalculada                = PosicaoDada / (int)qtd_Colunas;
//    int LinhaPosicao                  = LinhaCalculada + 1;
//    int NumLeft                       = (LinhaPosicao % 2) == 0 ? -1 :  1;
//    int NumRight                      = (LinhaPosicao % 2) == 0 ?  1 : -1;
//    int DeslocamentoPosicaoCalculado  = (int)(PosicaoDada % (int)qtd_Colunas) + 1;
//    int ColunaPosicao                 = (LinhaCalculada % 2) == 0 ? (int)qtd_Colunas - (DeslocamentoPosicaoCalculado - 1) : DeslocamentoPosicaoCalculado;
//    int LinhaPosicaoBottom            = LinhaCalculada + 1;
//    int DeslocamentoPosicaoBottom     = (LinhaPosicaoBottom % 2) == 0 ? (int)qtd_Colunas - DeslocamentoPosicaoCalculado : (int)ColunaPosicao - 1;
//    int PosicaoTop                    = (LinhaCalculada * qtd_Colunas) - DeslocamentoPosicaoCalculado;
//    int PosicaoBottom                 = ((LinhaCalculada + 1) * qtd_Colunas) + DeslocamentoPosicaoBottom;
//    int PosicaoLeftCalculada          = (PosicaoDada + NumLeft);
//    int PosicaoRightCalculada         = (PosicaoDada + NumRight);
//    int PosicaoLeft                   = PosicaoLeftCalculada == PosicaoTop || PosicaoLeftCalculada == PosicaoBottom ? -1 : PosicaoLeftCalculada;
//    int PosicaoRight                  = PosicaoRightCalculada == PosicaoTop || PosicaoRightCalculada == PosicaoBottom ? -1 : PosicaoRightCalculada;
//
//    switch (PosicaoSolicitada)
//    {
//    case BoxTop: 
//      return PosicaoTop;
//      break;
//    case BoxBottom:
//      return PosicaoBottom;
//      break;
//    case BoxLeft:
//      return PosicaoLeft;
//      break;
//    case BoxRight:
//      return PosicaoRight;
//      break;
//    case LinhaPosicaoDada:
//      return LinhaPosicao;
//      break;
//    case ColunaPosicaoDada:
//      return ColunaPosicao;
//      break;
//    }
//}
//
//// ROTINA PARA RETORNAR A POSICAO DADO A LINHA E COLUNA
//// ****************************************************
//int PosicaoBoxCell(int Linha, int Coluna){
//    return (int)(qtd_Colunas * (Linha - 1)) + ((Linha % 2) == 0 ? 
//                                                qtd_Colunas - Coluna :
//                                                Coluna - 1);
//}
//
//int PosicaoBoxCellInvertido(int Linha, int Coluna){
//    return (int)(qtd_Colunas * (Linha - 1)) + ( (Linha % 2) == 0 ? 
//                                                ( (Coluna - 1) )  : 
//                                                ( (qtd_Colunas - (Coluna) )) );
//}
//
////FIM
//
//void inline ShowLeds(int Wait){
//  Leds.show();
//  delay(Wait);
//}
//
//void VitrineLedsRGB(byte R, byte G, byte B, byte Br){
//
//    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }
//    
//    for(int Led = Star_Led_Vitrine; Led < Total_Leds; Led++){
//      Leds.setPixelColor(Led, Leds.Color(G, R, B));
//    }
//    //Serial.println("Fim BoxLedsAcesos");
//}
//
//void BoxLedsRGB(byte R, byte G, byte B, byte Br){
//
//    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }
//    
//    for(int Led = 0; Led < Total_Leds; Led++){
//      Leds.setPixelColor(Led, Leds.Color(G, R, B));
//    }
//    ShowLeds(500);
//    //Serial.println("Fim BoxLedsAcesos");
//}
//
//void BoxLedsRGBXadrezFade(bool IniciarImpar, byte R, byte G, byte B, byte Br, int PercentualRecebido){
//
//    byte  RLow, GLow, BLow, RHigh, GHigh, BHigh, RShow,  GShow,  BShow;
//    float PercentualEntrada = (float)(PercentualRecebido / 100.0);
//    float PercentualInverso = ((100 - PercentualRecebido) / 100.0);
//
//    RHigh = (byte)(R * PercentualEntrada);
//    GHigh = (byte)(G * PercentualEntrada);
//    BHigh = (byte)(B * PercentualEntrada);
//
//    RLow  = (byte)(R * PercentualInverso),    
//    GLow  = (byte)(G * PercentualInverso),  
//    BLow  = (byte)(B * PercentualInverso);
//
//    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }
//
//    if(IniciarImpar){ RShow = RHigh,  GShow = GHigh,  BShow = BHigh; }
//    else            { RShow = RLow,   GShow = GLow,   BShow = BLow; }
//    
//    for(int Led = 0; Led < qtd_Boxes; Led++){
//      
//      Leds.setPixelColor(Led, Leds.Color(GShow, RShow, BShow));
//      
//      RShow = RShow == RHigh  ?   RLow : RHigh;
//      GShow = GShow == GHigh  ?   GLow : GHigh;
//      BShow = BShow == BHigh  ?   BLow : BHigh;
//    }
//    
//    VitrineLedsRGB(105, 248, 196, Br);
//    ShowLeds(500);
//    //Serial.println("Fim BoxLedsAcesos");
//}
//
//void BoxLedsRGBXadrez(bool IniciarImpar, byte R, byte G, byte B, byte Br){
//
//    byte Rb = 20,  Gb = 20,  Bb = 20;
//    byte Rd = 0,  Gd = 0,  Bd = 0;
//
//    if(IniciarImpar){ Rd = R, Gd = G, Bd = B; }
//    else { Rd = Rb, Gd = Gb, Bd = Bb; }
//
//    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }
//    
//    for(int Led = 0; Led < qtd_Boxes; Led++){
//      Leds.setPixelColor(Led, Leds.Color(Gd, Rd, Bd));
//      Rd = Rd == R ? Rb : R;
//      Gd = Gd == G ? Gb : G;
//      Bd = Bd == B ? Bb : B;
//    }
//    VitrineLedsRGB(R, G, B, Br);
//    ShowLeds(500);
//    //Serial.println("Fim BoxLedsAcesos");
//}
//
//void BoxLedsRGBColuna(bool IniciarImpar, byte R, byte G, byte B, byte Br){
//
//    byte Rb = 20,  Gb = 20,  Bb = 20;
//    byte Rd = 0,  Gd = 0,  Bd = 0;
//
//    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }
//
//    for(byte L = 1; L <= qtd_Linhas; L++){
//
//      if(IniciarImpar){ Rd = R, Gd = G, Bd = B; }
//      else { Rd = Rb, Gd = Gb, Bd = Bb; }
//
//      for(byte C = 1; C <= qtd_Colunas; C++){
//        Leds.setPixelColor(PosicaoBoxCellInvertido(L, C), Leds.Color(Gd, Rd, Bd));
//        Rd = Rd == R ? Rb : R;
//        Gd = Gd == G ? Gb : G;
//        Bd = Bd == B ? Bb : B;
//      }
//    }
//    VitrineLedsRGB(R, G, B, Br);
//    ShowLeds(500);
//    //Serial.println("Fim BoxLedsAcesos");
//}
//
//void BoxLedsRGBLinha(bool IniciarImpar, byte R, byte G, byte B, byte Br){
//
//    byte Rb = 20,  Gb = 20,  Bb = 20;
//    byte Rd = 0,  Gd = 0,  Bd = 0;
//
//    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }
//
//    for(byte C = 1; C <= qtd_Colunas; C++){
//
//      if(IniciarImpar){ Rd = R, Gd = G, Bd = B; }
//      else { Rd = Rb, Gd = Gb, Bd = Bb; }
//
//      for(byte L = 1; L <= qtd_Linhas; L++){
//        Leds.setPixelColor(PosicaoBoxCellInvertido(L, C), Leds.Color(Gd, Rd, Bd));
//        Rd = Rd == R ? Rb : R;
//        Gd = Gd == G ? Gb : G;
//        Bd = Bd == B ? Bb : B;
//      }
//    }
//    VitrineLedsRGB(R, G, B, Br);
//    ShowLeds(500);
//    //Serial.println("Fim BoxLedsAcesos");
//}
//
// void BoxFade(bool Par, int R, int G, int B){
//
//    int Inicio;
//    if(Par)
//      Inicio = 0;
//    else
//      Inicio = 1;
//    FadeUp(Inicio, R, G, B);
//    FadeDown(Inicio, R, G, B);    
//}
//
//void FadeUp(int Inicio, int R, int G, int B){
//
//      for(int j = StartFadeUp; j < 256; j++){
//        // Configura a intensidade do Brilho (Não usar esta estrutura por recomendação da NeoPixel.
//        // Usar somente o setBrightness em Setup.
//        //        pixels.setBrightness(Brightness * j);
//        //        setCorBox(Inicio, R, G, B);        
//        setCorBoxFade(Inicio, j, j, j);        
//        Leds.show();
//    }
//    delay(1000);
//}
//
//void FadeDown(int Inicio, int R, int G, int B){
//
//    int BottonFadeTransition = 100;
//
//    for(int j = 255; j >= 0; j--){
//    
//     setCorBoxFade(Inicio, j, j, j);        
//    
//      if(j <= BottonFadeTransition){
//      
//        Leds.show();
//        StartFadeUp = BottonFadeTransition;
//        
//        if(Inicio == 0){    // Par
//           setCorBoxFade(Inicio + 1, (StartFadeUp - (j)), (StartFadeUp - (j)), (StartFadeUp - (j)));        
//        }
//        else{               // Impar
//           setCorBoxFade(Inicio - 1, (StartFadeUp - (j)), (StartFadeUp - (j)), (StartFadeUp - (j)));        
//        }
//        delay(17);
//        Leds.show();
//
//      }
//    }
//}
//
//void BoxLedsVaiVem(byte R, byte G, byte B, byte Br) {
//
//    VitrineLedsRGB(R, G, B, Br);
//    DoMeioParaPontas(90, 0, 30, false);
//    SoVai(0, 90, 10, true);
//    VaiVem();
//    VaiVemDupla;
//}
//
//
//void SoVai(byte R, byte G, byte B, bool ApagaApos){
//  
//     // Acende o Led
//    for(int i = 0; i < qtd_Boxes; i++){
//      Leds.setPixelColor(i, Leds.Color(G, R, B)); 
//      ShowLeds(100);
//    }
//    if(ApagaApos == true) {
//       SoVai(0, 0, 0, false);     //Apaga o Led
//    }
//}
//
//void VaiVem() {
//
//    // Acende o Led
//    for(int i = 0; i < qtd_Boxes; i++){
//      Leds.setPixelColor(i, Leds.Color(random(30, 100), random(20,100), random(50,255))); 
//      ShowLeds(100);
//    }
//
//    //Apaga o Led
//    for(int i = qtd_Boxes; i >= 0; i--){
//      Leds.setPixelColor(i, Leds.Color(0,0,0)); // Moderately bright green color.
//      ShowLeds(100);
//  }
//}
//
//void VaiVemDupla(){
//
//    // Acende o Led
//    for(int i = 0; i < qtd_Boxes; i++){
//      
//      Leds.setPixelColor(i, Leds.Color(random(30, 100), random(20,100), random(50,255))); 
//      ShowLeds(10);
//
//      Leds.setPixelColor(i+50, Leds.Color(random(30, 100), random(20,100), random(50,255))); 
//      ShowLeds(100);
//    }
//
//    //Apaga o Led
//    for(int i = qtd_Boxes; i >= 0; i--){
//
//      Leds.setPixelColor(i, Leds.Color(0,0,0)); 
//      ShowLeds(10);
//
//      Leds.setPixelColor(i-50, Leds.Color(0,0,0)); 
//      ShowLeds(100);
//    }
//    delay(100);
//}
//
//void DoMeioParaPontas(byte R, byte G, byte B, bool EuChamei){
//  
//    // Acende o Led
//    for(int i = 0; i < (qtd_Boxes/2)+1;i++){
//
//      Leds.setPixelColor(((qtd_Boxes / 2) - i), Leds.Color(R, G, B)); 
//      Leds.setPixelColor(((qtd_Boxes / 2) + i)-1, Leds.Color(R, G, B-B)); 
//      ShowLeds(100);
//    }
//
//    //Apaga o Led
//    if (!EuChamei){
//      DoMeioParaPontas(0, 0, 0, true);
//    }
//}
//
//
//
//
///*****************************************************
// *  Rotinas de posição fixa dos carros
// * 
// *****************************************************/
//
//
//void BoxLedsBatmanRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[2] = 0b1110000000000001;      // Linha 03 do quadro
//    MapaBox[3] = 0b1110000000000001;      // Linha 04 do quadro
//    MapaBox[4] = 0b1110000000000001;      // Linha 05 do quadro
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsMotosRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[2] = 0b0000000001111111;      // Linha 03 do quadro
//    MapaBox[3] = 0b0000000000000011;      // Linha 04 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsStarWarsRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[5] = 0b1110000000000001;      // Linha 06 do quadro
//    MapaBox[6] = 0b1110000000000001;      // Linha 07 do quadro
//    MapaBox[7] = 0b1100000000000001;      // Linha 08 do quadro
//    MapaBox[8] = 0b1100000000000001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsLamborghiniRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[8] = 0b0000000000000111;      // Linha 09 do quadro
//    MapaBox[9] = 0b0000000000001111;      // Linha 10 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsPorcheRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[10] = 0b0000000000001111;      // Linha 11 do quadro
//    MapaBox[11] = 0b0000000000001111;      // Linha 12 do quadro
//    MapaBox[12] = 0b0000000000001111;      // Linha 13 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsTeslaRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[13] = 0b0000000000111001;      // Linha 12 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsBMWRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[13] = 0b0000000111000001;      // Linha 12 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsFordRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[8]  = 0b0000001110000001;      // Linha 09 do quadro
//    MapaBox[9]  = 0b0000111110000001;      // Linha 10 do quadro
//    MapaBox[10] = 0b0000111100000001;      // Linha 11 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsAstonMartinRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[10] = 0b0000000011110001;      // Linha 11 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsPaganiRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[8]  = 0b0000000000011001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsMacLarenRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[9]  = 0b0000000001110001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsAudiRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[6]  = 0b0000000010000001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsCorvetteRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[11]  = 0b0000011111110001;      // Linha 09 do quadro
//    MapaBox[12]  = 0b0000011111110001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsNissanRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[5]  = 0b0000000000011111;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsFerrariRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[4]  = 0b0000001000000001;      // Linha 09 do quadro
//    MapaBox[7]  = 0b0000000000001111;      // Linha 09 do quadro
//    
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsMercedesRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[6]  = 0b0000000000000111;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsHondaRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[6]   = 0b0000000000111001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsAcuraRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[13]  = 0b0000000000000111;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsJaguarRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[7]  = 0b0000000000110001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsVelozesFurososRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[2]  = 0b0000111100000001;      // Linha 09 do quadro
//    MapaBox[3]  = 0b0001110000000001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsDodgeRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[7]  = 0b0000000111000001;      // Linha 09 do quadro
//    MapaBox[8]  = 0b0000000001100001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsVolksRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[6]  = 0b0000001000000001;      // Linha 09 do quadro
//    MapaBox[7]  = 0b0000111000000001;      // Linha 09 do quadro
//    MapaBox[8]  = 0b0000110000000001;      // Linha 09 do quadro
//    MapaBox[9]  = 0b0000100000000001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsFiatRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[6]  = 0b0000000100000001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsCadLacRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[5]  = 0b0000000000100001;      // Linha 09 do quadro
//    MapaBox[8]  = 0b0010000000000001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsBentleyRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[3]  = 0b0000000000000101;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsMasdaRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[4]  = 0b0000000001100001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//void BoxLedsBuickRGB(byte R, byte G, byte B, byte Br){
//    IniciarMapaBox();
//    MapaBox[5]  = 0b0000000001000001;      // Linha 09 do quadro
//
//    ShowMapaBoxes(R, G, B, Br, 50);
//}
//
//
//
//
//void ShowMsgBox(char Msg[], byte TamanhoMsg, byte R, byte G, byte B, byte Brilho, byte LinhaShow){
//
////  Serial.println("Dentro da rotina ShowMsgBox... ");
////  Serial.print("Tamnho da Msg... "), Serial.println(TamanhoMsg);
//  
//  LinhaShow       = LinhaShow - 1;    // Necessário porque os arrays começam na posição 0
//  byte LinhaBox   = LinhaShow;
//  IniciarMapaBox();
//  for(byte Letra = 0; Letra <= TamanhoMsg; Letra++){
//    byte FimBitMascara      = 0;
//    char LetraMascarada[5]  = {0x00,0x00,0x00,0x00,0x00};
//    MascararLetra(Msg[Letra], LetraMascarada, &FimBitMascara);
//  
////    Serial.print("---- >>>>>> Letra = "), Serial.print(Msg[Letra]), Serial.print(" | Posição Letra = "), Serial.print(Letra),
////    Serial.print(" | Mascara = "), Serial.println(LetraMascarada);
//    
//    for(byte BitLetra = 7; BitLetra >= FimBitMascara; BitLetra--){
////      Serial.print("BitLetra = "), Serial.println(BitLetra);
//      for(byte PosicaoDaLetra = 0;PosicaoDaLetra <= 4; PosicaoDaLetra++){
//        bitWrite(MapaBox[LinhaBox], 0, bitRead(LetraMascarada[PosicaoDaLetra], BitLetra));    //Set o bit 0 da mascara com o bit da mascara da letra
////        Serial.print("LinhaBox = "), Serial.print(LinhaBox);
////        Serial.print(" | LinhaShow = "), Serial.print(LinhaShow);
//
//        LinhaBox++;
//        
////        Serial.print(" | PosicaoDaLetra = "), Serial.print(PosicaoDaLetra);
////        Serial.print(" | Valor do Bit ( "), Serial.print(BitLetra), 
////        Serial.print(" ) da Letra Mascarada = "),  Serial.println(bitRead(LetraMascarada[PosicaoDaLetra], BitLetra));
//      }
////      Serial.println("ShowMapaBoxes");
//      
//      ShowMapaBoxes(R, G, B, Brilho, 40);                                                       // ShowMapaBoxes
//      ShifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);                                       
//      LinhaBox   = LinhaShow;
//      delay(60);
//    }
//    if(Msg[Letra] != ' '){
////      Serial.print("---- >>>>>> Letra = "), Serial.print(Msg[Letra]), Serial.print(" | Posição Letra = "), Serial.println(Letra),
//      ShowMapaBoxes(R, G, B, Brilho, 40);                                                       // ShowMapaBoxes
//      ShifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);                                         // Shift para espaço entre letras
//      delay(60);
//    }
//    if(!getValorPinAcao()){Letra = TamanhoMsg+1;}
//  }
//  for(byte ColunasBranco = 1; ColunasBranco <= 15; ColunasBranco++ ){
//     ShifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);                                         // Shift para espaço entre letras
//     ShowMapaBoxes(R, G, B, Brilho, 40);                                                       // ShowMapaBoxes
//     delay(60);
//  }
//
//}
//
//void ShifEsquerdaMapaBox(byte PrimeiraLinha, byte UltimaLinha, byte QtdeBit){
////  Serial.println(""), Serial.println("");
////  Serial.println("ANTES DO SHIFT ....");
//
////  for(byte PosicaoShift = PrimeiraLinha; PosicaoShift <= UltimaLinha; PosicaoShift++ ){   // Shift Mascarabox
////    Serial.println(MapaBox[PosicaoShift], BIN);
////  }
////
////  Serial.println(""), Serial.println("");
////  Serial.println("Iniciando o Shift....");
//
//  for(byte PosicaoShift = PrimeiraLinha; PosicaoShift <= UltimaLinha; PosicaoShift++ ){   // Shift Mascarabox
//    MapaBox[PosicaoShift] = (MapaBox[PosicaoShift] << QtdeBit);
////    Serial.println(MapaBox[PosicaoShift], BIN);
//  }
////  Serial.println("Finalizado o Shift....");
////  Serial.println(""), Serial.println("");
//
//}
//
//void ShowMapaBoxes(byte R, byte G, byte B, byte Br, byte LuzFundo){
//
//    word MapaBoxLinha = 0x00;
//    byte Rb = LuzFundo,  Gb = LuzFundo,  Bb = LuzFundo;
//    byte Rd = 0,  Gd = 0,  Bd = 0;
//    
//    if (Leds.getBrightness() != (uint8_t)Br) { setBrilho((int)Br); }
//
//    for(byte L = 1; L <= qtd_Linhas; L++){
//
//      MapaBoxLinha = MapaBox[L - 1];
//      
//      for(byte C = 1; C <= qtd_Colunas; C++){
//
//        if(bitRead(MapaBoxLinha, 16 - C)){ Rd = R, Gd = G, Bd = B; }
//        else { Rd = Rb, Gd = Gb, Bd = Bb; }
//      
//        Leds.setPixelColor(PosicaoBoxCellInvertido(L, C), Leds.Color(Gd, Rd, Bd));
//      
//      }
//    }
//    VitrineLedsRGB(R, G, B, Br);
//    ShowLeds(500);
//}
//
//void TodosLedsAcesos(uint8_t r, uint8_t g, uint8_t b){
//    for(int Led = 0; Led < Total_Leds; Led++){
//      Leds.setPixelColor(Led, Leds.Color(g, r, b));
//    }
//    Leds.show();
//    delay(500);
//}
//
//void TodosLedsApagados(){
//    TodosLedsAcesos(0,0,0);   // Apaga os Leds mandando o RGB=0
//}
//
//void setAcendeBox(int Linha, int Coluna, byte R, byte G, byte B, byte Br){
//    if (Leds.getBrightness() != (uint8_t)Br) {  setBrilho((int)Br);  }
//    Leds.setPixelColor(PosicaoBoxCellInvertido(Linha, Coluna), Leds.Color(G, R, B));
//}
//
//void setApagaBox(int Linha, int Coluna, byte R, byte G, byte B, byte Br){
//    Leds.setPixelColor(PosicaoBoxCellInvertido(Linha, Coluna), Leds.Color(G, R, B));
//}
//
//void setLedBox(int NumBox, byte R, byte G, byte B, byte Br){
//    if (Leds.getBrightness() != (uint8_t)Br) {  setBrilho((int)Br);  }
//    Leds.setPixelColor(NumBox, Leds.Color(G, R, B));
//}
//
