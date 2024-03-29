/*****************************************************
 * Gerenciador das Ações recebidas pela tela Nextion
 * Desenvolvido por Edson Silva
 * Date: 27/05/18  
 ****************************************************/

#define   ChaveAcao(CodeAcao, R, G, B, Brilho) ((String)(String(CodeAcao) + String(R) + String(G) + String(B) + String(Brilho)))
#define   AcaoIcon001  49
#define   AcaoIcon002  AcaoIcon001 + 3
#define   AcaoIcon003  AcaoIcon002 + 3
#define   AcaoIcon004  AcaoIcon003 + 3
#define   AcaoIcon005  AcaoIcon004 + 3
#define   AcaoIcon006  AcaoIcon005 + 3
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

String ChaveAcaoNew           = "";
String ChaveAcaoOldx          = "";


void ExecutarAcao(byte CodeAcao, byte R, byte G, byte B, byte Brilho) {

  //CodeAcao = AcaoIcon005;

  /* *******************************************************************
   * Opções para ação no quadro de Leds 
   * *******************************************************************/

    ChaveAcaoNew  = ChaveAcao(CodeAcao, R, G, B, Brilho);

    switch (CodeAcao) {

        case 0:                                           // Reset Ação
          ResetAcao(ChaveAcaoNew, R, G, B, Brilho);
        break;

        case AcaoIcon001:                                   // Ação Manter os Leds Aceso
                                                            //Serial.println("31-Antes de entrar na rotina LedsAcesos()");
          LedsAcesos(ChaveAcaoNew, R, G, B, Brilho);      
                                                            //Serial.println("31-Depois de entrar na rotina LedsAcesos()");
        break;

        case AcaoIcon002:                                          // Ação acender Xadrez box
//          LedsXadrez(ChaveAcaoNew, R, G, B, Brilho);      
          LedsXadrezFade(ChaveAcaoNew, R, G, B, Brilho);      
        break;  

        case AcaoIcon003:                                          // Ação acender Linhas box
          LedsLinha(ChaveAcaoNew, R, G, B, Brilho);      
        break;  

        case AcaoIcon004:                                          // Ação acender Colunas box 
          LedsColuna(ChaveAcaoNew, R, G, B, Brilho);      
        break;  

        case AcaoIcon005:                                          // Ação Msg box 
          Mensagem(ChaveAcaoNew, R, G, B, Brilho, 2);      
        break;  

        case AcaoIcon006:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsBatmanRGB);      
        break;  

        case AcaoIcon007:                                          // Ação acender Batman box 
          
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsStarWarsRGB);      
        break;  

        case AcaoIcon008:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsVelozesFurososRGB);      
        break;  

        case AcaoIcon009:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsMotosRGB);      
        break;  

        case AcaoIcon010:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsPorcheRGB);      
        break;  

        case AcaoIcon011:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsFerrariRGB);      
        break;  

        case AcaoIcon012:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsPaganiRGB);      
        break;  

        case AcaoIcon013:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsMacLarenRGB);      
        break;  

        case AcaoIcon014:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsCorvetteRGB);      
        break;  

        case AcaoIcon015:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsAstonMartinRGB);      
        break;  

        case AcaoIcon016:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsJaguarRGB);      
        break;  

        case AcaoIcon017:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsAudiRGB);      
        break;  

        case AcaoIcon018:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsBMWRGB);      
        break;  

        case AcaoIcon019:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsMercedesRGB);      
        break;  

        case AcaoIcon020:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsTeslaRGB);      
        break;  

        case AcaoIcon021:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsLamborghiniRGB);      
        break;  

        case AcaoIcon022:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsNissanRGB);      
        break;  

        case AcaoIcon023:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsDodgeRGB);      
        break;  

        case AcaoIcon024:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsBuickRGB);      
        break;  

        case AcaoIcon025:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsVolksRGB);      
        break;  

        case AcaoIcon026:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsFordRGB);      
        break;  

        case AcaoIcon027:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsFiatRGB);      
        break;  

        case AcaoIcon028:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsCadLacRGB);      
        break;  

        case AcaoIcon029:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsHondaRGB);      
        break;  

        case AcaoIcon030:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsAcuraRGB);      
        break;  

        case AcaoIcon031:                                          // Ação acender Batman box 
          LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsBentleyRGB);      
        break;  

        case AcaoIcon032:                                          // Ação acender Batman box 
          //LedsShowBoxFixoAcao(ChaveAcaoNew, R, G, B, Brilho, BoxLedsMasdaRGB);      
          LedsVaiVem(ChaveAcaoNew, R, G, B, Brilho); 
        break;  

        case 30:                                                  // Ação Vai Vem 
          LedsVaiVem(ChaveAcaoNew, R, G, B, Brilho);      
        break;  

        case 31:                                                  // Ação variada 
         // LedsFadeBox(ChaveAcaoNew, R, G, B, Brilho);      
          LedsVaiVem(ChaveAcaoNew, R, G, B, Brilho); 
//          MensagemDebug(ChaveAcaoNew, R, G, B, Brilho, 2);      //Em construção
        break;  

  }
}
