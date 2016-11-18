#include <unistd.h>
#include "knightmoves.h"

#define PUSTE 9999

static void CreateBoard(int position);
static void ShowBoard();

int * temp_chessboard;
int * xchessboard;
int * chessboard;

int main(int argc, char * argv[])
{
  int start=0,i,a;
  start=(argc>1)? atoi(argv[1]): start;

  

  temp_chessboard=(int *)malloc(64*sizeof(int));
  xchessboard=(int *)malloc(64*sizeof(int));
  chessboard=(int *)malloc(64*sizeof(int));

  CreateBoard(start);

  temp_chessboard=Wio(start);

  system("clear");
  ShowBoard();

  getchar();


  for(a=1;a<64;a++){
  system("clear");
  ShowBoard();

   for(i=0;i<=64;i++){
    if(temp_chessboard[i]==a){
    chessboard[i]=a;
    break;}
   }
  sleep(1);
  }



  return 0;
}



static void CreateBoard(int position)
{
    int i;
    for (i = 0; i < 64; i++)
	chessboard[i] = PUSTE;
    chessboard[position] = 0;
}

static void ShowBoard()
{
    int i, temp = 0;
    int kolor_pola = 0;
    int czarne = 32;
    int biale = 33;
    int ruchy = 35;

    printf("\n\n\n");
    for (i = 0; i < 64; i++) {
	if (i % 8 == 0) {
	    temp = czarne;
	    czarne = biale;
	    biale = temp;
	}
	kolor_pola = (i % 2) ? czarne : biale;

	printf("%s\033[1;%dm%4d\033[m",
	       (i % 8) ? "  " : "\n\n\t      ",
	       (chessboard[i] < 100) ? ruchy : kolor_pola, chessboard[i]);
    }
    printf("\n\n\n\n");
}
