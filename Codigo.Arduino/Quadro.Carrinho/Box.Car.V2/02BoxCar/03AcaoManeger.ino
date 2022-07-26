/*****************************************************
 * Gerenciador das Ações recebidas pela tela Nextion
 * Desenvolvido por Edson Silva
 * Date: 27/05/18
 * Alteração: jun/22
 ****************************************************/

#define   ChaveAcao(CodeAcao, R, G, B, Brilho) ((String)(String(CodeAcao) + String(R) + String(G) + String(B) + String(Brilho)))

#define   AcaoIcon001  49
#define   AcaoIcon002  AcaoIcon001 + 3
#define   AcaoIcon003  AcaoIcon002 + 3
#define   AcaoIcon004  AcaoIcon003 + 3

#define   AcaoIcon005  AcaoIcon004 + 3    // Ação cascata
#define   AcaoIcon006  AcaoIcon005 + 3    // Ação Mensagem
#define   AcaoIcon007  AcaoIcon006 + 3

#define   AcaoIcon008  AcaoIcon007 + 3
#define   AcaoIcon009  AcaoIcon008 + 3
#define   AcaoIcon010  AcaoIcon009 + 3
#define   AcaoIcon011  AcaoIcon010 + 3

#define   AcaoIcon012  AcaoIcon011 + 3
#define   AcaoIcon013  AcaoIcon012 + 3
#define   AcaoIcon014  AcaoIcon013 + 3
#define   AcaoIcon015  AcaoIcon014 + 3

#define   AcaoIcon016  AcaoIcon015 + 3
#define   AcaoIcon017  AcaoIcon016 + 3
#define   AcaoIcon018  AcaoIcon017 + 3
#define   AcaoIcon019  AcaoIcon018 + 3

#define   AcaoIcon020  AcaoIcon019 + 3
#define   AcaoIcon021  AcaoIcon020 + 3
#define   AcaoIcon022  AcaoIcon021 + 3
#define   AcaoIcon023  AcaoIcon022 + 3

#define   AcaoIcon024  AcaoIcon023 + 3
#define   AcaoIcon025  AcaoIcon024 + 3
#define   AcaoIcon026  AcaoIcon025 + 3
#define   AcaoIcon027  AcaoIcon026 + 3

#define   AcaoIcon028  AcaoIcon027 + 3
#define   AcaoIcon029  AcaoIcon028 + 3
#define   AcaoIcon030  AcaoIcon029 + 3
#define   AcaoIcon031  AcaoIcon030 + 3

#define   AcaoIcon032  AcaoIcon031 + 3
#define   AcaoIcon033  AcaoIcon032 + 3
#define   AcaoIcon034  AcaoIcon033 + 3
#define   AcaoIcon035  AcaoIcon034 + 3

String ChaveAcaoNew           = "";
String ChaveAcaoOldx          = "";


void ExecutarAcao(byte CodeAcao, byte R, byte G, byte B, byte Brilho) {

  //CodeAcao = AcaoIcon005;

  /* *******************************************************************
   * Opções para ação no quadro de Leds 
   * *******************************************************************/

    ChaveAcaoNew  = ChaveAcao(CodeAcao, R, G, B, Brilho);

    switch (CodeAcao) {

        case 0:                                                     // Reset Ação
          ResetAcao(ChaveAcaoNew, R, G, B, Brilho);
        break;

        case AcaoIcon001:                                           // Ação Manter os Leds Aceso
          LedsAcesos(ChaveAcaoNew, R, G, B, Brilho);      
        break;

        case AcaoIcon002:                                          // Ação acender Xadrez box
//          LedsXadrez(ChaveAcaoNew, R, G, B, Brilho);             // OLD Apagar após testes
//          LedsFuncaoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsRGBXadrez);      
          LedsXadrezFade(ChaveAcaoNew, R, G, B, Brilho);         

        break;  

        case AcaoIcon003:                                          // Ação acender Linhas box
//          LedsLinha(ChaveAcaoNew, R, G, B, Brilho);              // OLD Apagar após testes
          LedsFuncaoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsRGBLinha);      
        break;  

        case AcaoIcon004:                                          // Ação acender Colunas box 
//          LedsColuna(ChaveAcaoNew, R, G, B, Brilho);             // OLD Apagar após testes
          LedsFuncaoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsRGBColuna);      
        break;  

        case AcaoIcon005:                                          /// Ação cascata 
          LedsCascata(ChaveAcaoNew, R, G, B, Brilho);              
        break;  

        case AcaoIcon006:                                          // Ação Msg box 
          Mensagem(ChaveAcaoNew, R, G, B, Brilho, 2);      
        break;  

        case AcaoIcon007:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsBatmanRGB);      
        break;  

        case AcaoIcon008:                                          // Ação acender star War box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsStarWarsRGB);      
        break;  

        case AcaoIcon009:                                          // Ação acender Veloz. fur. box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsVelozesFurososRGB);      
        break;  

        case AcaoIcon010:                                          // Ação acender moto box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsMotosRGB);      
        break;  

        case AcaoIcon011:                                          // Ação acender porche box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsPorcheRGB);      
        break;  

        case AcaoIcon012:                                          // Ação acender ferrari box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsFerrariRGB);      
        break;  

        case AcaoIcon013:                                          // Ação acender pagani box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsPaganiRGB);      
        break;  

        case AcaoIcon014:                                          // Ação acender mclaren box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsMacLarenRGB);      
        break;  

        case AcaoIcon015:                                          // Ação acender chevrolet box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsCorvetteRGB);      
        break;  

        case AcaoIcon016:                                          // Ação acender astom mart box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsAstonMartinRGB);      
        break;  

        case AcaoIcon017:                                          // Ação acender jaguar box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsJaguarRGB);      
        break;  

        case AcaoIcon018:                                          // Ação acender audi box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsAudiRGB);      
        break;  

        case AcaoIcon019:                                          // Ação acender bmw box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsBMWRGB);      
        break;  

        case AcaoIcon020:                                          // Ação acender mercedes box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsMercedesRGB);      
        break;  

        case AcaoIcon021:                                          // Ação acender tesla box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsTeslaRGB);      
        break;  

        case AcaoIcon022:                                          // Ação acender lamborghini box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsLamborghiniRGB);      
        break;  

        case AcaoIcon023:                                          // Ação acender nissan box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsNissanRGB);      
        break;  

        case AcaoIcon024:                                          // Ação acender dodge box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsDodgeRGB);      
        break;  

        case AcaoIcon025:                                          // Ação acender buick box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsBuickRGB);      
        break;  

        case AcaoIcon026:                                          // Ação acender volks box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsVolksRGB);      
        break;  

        case AcaoIcon027:                                          // Ação acender ford box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsFordRGB);      
        break;  

        case AcaoIcon028:                                          // Ação acender fiat box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsFiatRGB);      
        break;  

        case AcaoIcon029:                                          // Ação acender cadillac box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsCadLacRGB);      
        break;  

        case AcaoIcon030:                                          // Ação acender honda box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsHondaRGB);      
        break;  

        case AcaoIcon031:                                          // Ação acender acura box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsAcuraRGB);      
        break;  

        case AcaoIcon032:                                          // Ação acender bentley box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsBentleyRGB);      
        break;  

        case AcaoIcon033:                                          // Ação acender mazda box 
          //LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsMasdaRGB);      
          LedsVaiVem(ChaveAcaoNew, R, G, B, Brilho); 
        break;  

        case AcaoIcon034:                                          // Sem Ação 
          LedsVaiVem(ChaveAcaoNew, R, G, B, Brilho);      
        break;  

        case Aca0Icon035:                                          // Ação variada 
          MensagemDebug(ChaveAcaoNew, R, G, B, Brilho, 2);
        break;  

  }
}
