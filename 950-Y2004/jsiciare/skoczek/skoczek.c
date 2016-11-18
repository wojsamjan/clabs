#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int PUSTE = 8888;
int licznik = 0;
int chessboard[64];

typedef struct {
    int position;
    int abilities[8];
} skoczekT;

skoczekT skoczek = { 0, {0, 0, 0, 0, 0, 0, 0, 0} };

skoczekT stack[64];

int *sPointer;
int sPtr;
int tmpP;

int direction = -1, wybiera = 1;
int start = 56, ile_ruchow = 63, speed = 1;

static void ShowBoard();

void Wio(int *stackPointer);
void CreateBoard(int position);
int CheckAbilities(int *stackPointer);
int MakeMove(int *stackPointer);


int main(int argc, char *argv[])
{
    int c;
    sPtr = 0;
    sPointer = &sPtr;

    start = (argc > 1) ? atoi(argv[1]) : start;
    ile_ruchow = (argc > 2) ? atoi(argv[2]) - 1 : ile_ruchow;
    speed = (argc > 3) ? atoi(argv[3]) : speed;

    CreateBoard(start);

    stack[*sPointer].position = start;
    CheckAbilities(sPointer);

    system("clear");
    ShowBoard();
    sleep(speed);

    if ((c = getchar()) == ' ') {;
    } else {
	system("clear");
	exit(0);
    }

    Wio(sPointer);
    ShowBoard();
    printf("\n");
    return 0;
}

void Wio(int *stackPointer)
{
    if (*stackPointer <= ile_ruchow) {

	if (CheckAbilities(stackPointer)) {

	    MakeMove(stackPointer);
	    system("clear");
	    ShowBoard();
	    sleep(speed);

	} else {

	    printf("\t\033[1;32m****************************");
	    printf("********************************\033[m");
	    printf("\n\t\033[1;32m****************************");
	    printf("********************************\033[m");

	    tmpP = *stackPointer;
	    while (*stackPointer > tmpP - (tmpP / 3)) {
		chessboard[stack[*stackPointer].position] = PUSTE;
		(*stackPointer)--;
	    }



	}

	Wio(stackPointer);

    } else {
	system("clear");
	printf("\t\033[1;32mG  O  T  O  W  E  !\033[m");
	return;
    }

}


int MakeMove(int *stackPointer)
{
    int x, y;
    x = stack[*stackPointer].position % 8;
    y = stack[*stackPointer].position / 8;

    skoczek = stack[*stackPointer];

    if (CheckAbilities(stackPointer) == 0)
	return 0;

    srand(time(NULL));

    wybiera = 1;
    while (wybiera) {
	direction = (int) (8.0 * rand() / (RAND_MAX + 1.0));
	if (skoczek.abilities[direction])
	    wybiera = 0;
    }

    switch (direction) {
    case 0:
	chessboard[(x + 2) + (y + 1) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[0] = 0;
	skoczek.position = (x + 2) + (y + 1) * 8;
	break;
    case 1:
	chessboard[(x + 2) + (y - 1) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[1] = 1;
	skoczek.position = (x + 2) + (y - 1) * 8;
	break;
    case 2:
	chessboard[(x + 1) + (y - 2) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[2] = 0;
	skoczek.position = (x + 1) + (y - 2) * 8;
	break;
    case 3:
	chessboard[(x - 1) + (y - 2) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[3] = 0;
	skoczek.position = (x - 1) + (y - 2) * 8;
	break;
    case 4:
	chessboard[(x - 2) + (y - 1) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[4] = 0;
	skoczek.position = (x - 2) + (y - 1) * 8;
	break;
    case 5:
	chessboard[(x - 2) + (y + 1) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[5] = 0;
	skoczek.position = (x - 2) + (y + 1) * 8;
	break;
    case 6:
	chessboard[(x - 1) + (y + 2) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[6] = 0;
	skoczek.position = (x - 1) + (y + 2) * 8;
	break;
    case 7:
	chessboard[(x + 1) + (y + 2) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[7] = 0;
	skoczek.position = (x + 1) + (y + 2) * 8;
	break;
    }

    stack[++(*stackPointer)].position = skoczek.position;
    return 1;
}

int CheckAbilities(int *stackPointer)
{
    int dir, x, y, stan = 0;
    x = stack[*stackPointer].position % 8;
    y = stack[*stackPointer].position / 8;

    for (dir = 0; dir < 8; dir++) {
	switch (dir) {
	case 0:
	    if (x + 2 < 8 && y + 1 < 8
		&& chessboard[(x + 2) + (y + 1) * 8] == PUSTE) {
		stack[*stackPointer].abilities[0] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[0] = 0;
	    }
	    break;
	case 1:
	    if (x + 2 < 8 && y - 1 >= 0
		&& chessboard[(x + 2) + (y - 1) * 8] == PUSTE) {
		stack[*stackPointer].abilities[1] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[1] = 0;
	    }
	    break;
	case 2:
	    if (x + 1 < 8 && y - 2 >= 0
		&& chessboard[(x + 1) + (y - 2) * 8] == PUSTE) {
		stack[*stackPointer].abilities[2] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[2] = 0;
	    }
	    break;
	case 3:
	    if (x - 1 >= 0 && y - 2 >= 0
		&& chessboard[(x - 1) + (y - 2) * 8] == PUSTE) {
		stack[*stackPointer].abilities[3] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[3] = 0;
	    }
	    break;
	case 4:
	    if (x - 2 >= 0 && y - 1 >= 0
		&& chessboard[(x - 2) + (y - 1) * 8] == PUSTE) {
		stack[*stackPointer].abilities[4] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[4] = 0;
	    }
	    break;
	case 5:
	    if (x - 2 >= 0 && y + 1 < 8
		&& chessboard[(x - 2) + (y + 1) * 8] == PUSTE) {
		stack[*stackPointer].abilities[5] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[5] = 0;
	    }
	    break;
	case 6:
	    if (x - 1 >= 0 && y + 2 >= 0
		&& chessboard[(x - 1) + (y + 2) * 8] == PUSTE) {
		stack[*stackPointer].abilities[6] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[6] = 0;
	    }
	    break;
	case 7:
	    if (x + 1 < 8 && y + 2 < 8
		&& chessboard[(x + 1) + (y + 2) * 8] == PUSTE) {
		stack[*stackPointer].abilities[7] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[7] = 0;
	    }
	    break;
	}
    }

    return stan;

}



void CreateBoard(int position)
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
    int czarne = 34;
    int biale = 55;
    int ruchy = 32;

    printf("\n\n");
    for (i = 0; i < 64; i++) {
	if (i % 8 == 0) {
	    temp = czarne;
	    czarne = biale;
	    biale = temp;
	}
	kolor_pola = (i % 2) ? czarne : biale;

	printf("%s\033[1;%dm%4d\033[m",
	       (i % 8) ? "\t" : "\n\n\t",
	       (chessboard[i] < 100) ? ruchy : kolor_pola, chessboard[i]);
    }
    printf("\n\n\n");
}
