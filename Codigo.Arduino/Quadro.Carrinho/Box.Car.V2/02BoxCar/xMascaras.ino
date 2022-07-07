/* ***********************************************************************
 * Rotinas para tratamento e geração de array com a mascara de uma letra
 * 
 * Desenvolvido por Edson Silva
 * Date: 21/07/19
 *************************************************************************/


void MascararLetra(char Letra, char LetraMascarada[], byte *pFimBitMascara){

  switch (Letra){

    case ' ':
      *pFimBitMascara=7;
      LetraMascarada[0]=0b00000000;
      LetraMascarada[1]=0b00000000;
      LetraMascarada[2]=0b00000000;
      LetraMascarada[3]=0b00000000;
      LetraMascarada[4]=0b00000000;
    break;

    case '.':
      *pFimBitMascara=7;
      LetraMascarada[0]=0b00000000;
      LetraMascarada[1]=0b00000000;
      LetraMascarada[2]=0b00000000;
      LetraMascarada[3]=0b00000000;
      LetraMascarada[4]=0b10000000;
    break;

    case '/':
      *pFimBitMascara=3;
      LetraMascarada[0]=0b00001000;
      LetraMascarada[1]=0b00010000;
      LetraMascarada[2]=0b00100000;
      LetraMascarada[3]=0b01000000;
      LetraMascarada[4]=0b10000000;
    break;

    case '?':
      *pFimBitMascara=4;
      LetraMascarada[0]=0b01100000;
      LetraMascarada[1]=0b10010000;
      LetraMascarada[2]=0b00100000;
      LetraMascarada[3]=0b01000000;
      LetraMascarada[4]=0b10000000;
    break;

    case '0':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b10100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b11100000;
    break;

    case '1':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b01000000;
      LetraMascarada[1]=0b01000000;
      LetraMascarada[2]=0b01000000;
      LetraMascarada[3]=0b01000000;
      LetraMascarada[4]=0b11100000;
    break;

    case '2':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b00100000;
      LetraMascarada[2]=0b01000000;
      LetraMascarada[3]=0b10000000;
      LetraMascarada[4]=0b11100000;
    break;

    case '3':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b00100000;
      LetraMascarada[2]=0b01100000;
      LetraMascarada[3]=0b00100000;
      LetraMascarada[4]=0b11100000;
    break;

    case '4':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b10100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b00100000;
      LetraMascarada[4]=0b00100000;
    break;

    case '5':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10000000;
      LetraMascarada[2]=0b11000000;
      LetraMascarada[3]=0b00100000;
      LetraMascarada[4]=0b11000000;
    break;

    case '6':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10000000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b11100000;
    break;

    case '7':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b00100000;
      LetraMascarada[2]=0b00100000;
      LetraMascarada[3]=0b00100000;
      LetraMascarada[4]=0b00100000;
    break;

    case '8':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b11100000;
    break;

    case '9':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b00100000;
      LetraMascarada[4]=0b11100000;
    break;

    case 'a': case 'A':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b10100000;
    break;

    case 'b': case 'B':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b10000000;
      LetraMascarada[1]=0b10000000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b11100000;
    break;

    case 'c': case 'C':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10000000;
      LetraMascarada[2]=0b10000000;
      LetraMascarada[3]=0b10000000;
      LetraMascarada[4]=0b11100000;
    break;
    
    case 'ç': case 'Ç':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10000000;
      LetraMascarada[2]=0b10000000;
      LetraMascarada[3]=0b10000000;
      LetraMascarada[4]=0b11100000;
      LetraMascarada[5]=0b01000000;
    break;
    
    case 'd': case 'D':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b00100000;
      LetraMascarada[1]=0b00100000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b11100000;
    break;

    case 'e': case 'E':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10000000;
      LetraMascarada[2]=0b11000000;
      LetraMascarada[3]=0b10000000;
      LetraMascarada[4]=0b11100000;
    break;

    case 'f': case 'F':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10000000;
      LetraMascarada[2]=0b11000000;
      LetraMascarada[3]=0b10000000;
      LetraMascarada[4]=0b10000000;
    break;

    case 'g': case 'G':
      *pFimBitMascara=4;
      LetraMascarada[0]=0b11110000;
      LetraMascarada[1]=0b10000000;
      LetraMascarada[2]=0b10110000;
      LetraMascarada[3]=0b10010000;
      LetraMascarada[4]=0b11110000;
    break;

    case 'h': case 'H':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b10100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b10100000;
    break;

    case 'i': case 'I':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b01000000;
      LetraMascarada[2]=0b01000000;
      LetraMascarada[3]=0b01000000;
      LetraMascarada[4]=0b11100000;
    break;

    case 'j': case 'J':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b00100000;
      LetraMascarada[1]=0b00100000;
      LetraMascarada[2]=0b00100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b11100000;
    break;

    case 'k': case 'K':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b10100000;
      LetraMascarada[1]=0b11000000;
      LetraMascarada[2]=0b10000000;
      LetraMascarada[3]=0b11000000;
      LetraMascarada[4]=0b10100000;
    break;

    case 'l': case 'L':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b10000000;
      LetraMascarada[1]=0b10000000;
      LetraMascarada[2]=0b10000000;
      LetraMascarada[3]=0b10000000;
      LetraMascarada[4]=0b11100000;
    break;

    case 'm': case 'M':
      *pFimBitMascara=3;
      LetraMascarada[0]=0b11011000;
      LetraMascarada[1]=0b11111000;
      LetraMascarada[2]=0b11111000;
      LetraMascarada[3]=0b10101000;
      LetraMascarada[4]=0b10101000;
    break;

    case 'n': case 'N':
      *pFimBitMascara=4;
      LetraMascarada[0]=0b10010000;
      LetraMascarada[1]=0b11010000;
      LetraMascarada[2]=0b10110000;
      LetraMascarada[3]=0b10110000;
      LetraMascarada[4]=0b10010000;
    break;

    case 'o': case 'O':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b10100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b11100000;
    break;

    case 'p': case 'P':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b10000000;
      LetraMascarada[4]=0b10000000;
    break;

    case 'q': case 'Q':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b10100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b11000000;
    break;

    case 'r': case 'R':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b11000000;
      LetraMascarada[4]=0b10100000;
    break;

    case 's': case 'S':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b10000000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b00100000;
      LetraMascarada[4]=0b11100000;
    break;

    case 't': case 'T':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b01000000;
      LetraMascarada[2]=0b01000000;
      LetraMascarada[3]=0b01000000;
      LetraMascarada[4]=0b01000000;
    break;

    case 'u': case 'U':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b10100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b10100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b11100000;
    break;

    case 'v': case 'V':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b10100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b10100000;
      LetraMascarada[3]=0b10100000;
      LetraMascarada[4]=0b01000000;
    break;

    case 'w': case 'W':
      *pFimBitMascara=3;
      LetraMascarada[0]=0b10101000;
      LetraMascarada[1]=0b10101000;
      LetraMascarada[2]=0b11111000;
      LetraMascarada[3]=0b11111000;
      LetraMascarada[4]=0b11011000;
    break;

    case 'x': case 'X':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b10100000;
      LetraMascarada[1]=0b11100000;
      LetraMascarada[2]=0b01000000;
      LetraMascarada[3]=0b11100000;
      LetraMascarada[4]=0b10100000;
    break;

    case 'y': case 'Y':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b10100000;
      LetraMascarada[1]=0b10100000;
      LetraMascarada[2]=0b10100000;
      LetraMascarada[3]=0b01000000;
      LetraMascarada[4]=0b01000000;
    break;

    case 'z': case 'Z':
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b00100000;
      LetraMascarada[2]=0b01000000;
      LetraMascarada[3]=0b10000000;
      LetraMascarada[4]=0b11100000;
    break;

    default:
      *pFimBitMascara=5;
      LetraMascarada[0]=0b11100000;
      LetraMascarada[1]=0b11100000;
      LetraMascarada[2]=0b11100000;
      LetraMascarada[3]=0b11100000;
      LetraMascarada[4]=0b11100000;
  }
}
