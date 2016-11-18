/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik g³ówny mw_maze (maze walker)
 * mw_main.c
 */

#include "mw_maze.h"
#include "grafika.h"
#include "myfunkc.h"
#include "stany.h"
#include <stdlib.h>

int
main(int argc, char** argv)
{
	Inicjuj();
	Intro(); 
	Menu();
	Zakoncz();
	system("clear"); /* by oczy¶ciæ ekran */
	return 0;
}
