#include "knightmoves.h"

#define bok       8
#define boksize  45

char *title = "Wio koniku, a jak siê postarasz...";
char *message = "By oczy¶ciæ szachownicê &#151; kliknij w pole ze skoczkiem.";
char *jeden = "white", *drugi = "black", *temp;

int *trasa_skoczka;
char *ch;
char str[16];
int pole;



void Header(char *title);
void Footer();

void ChessBoard();
void PustePola(int i);
void WypelnionePola(int i, int pole);



int main()
{

    ch = (char *) malloc(17);
    scanf("pole=%16s", ch);
    sprintf(str, "%s", ch);

    pole = atoi(str);

    trasa_skoczka = (int *) malloc(bok * bok * sizeof(int));
    trasa_skoczka = Wio(pole);

    Header(title);
    ChessBoard();
    Footer();

    return 0;
}



void Header(char *title)
{
    printf("Content-type:text/html;charset=iso-8859-2\n\n");
    printf
	("<!doctype html public \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n");
    printf("<html>\n<head><title>%s</title>\n", title);
    printf
	("<meta http-equiv=Content-Type content=\"text/html;charset=iso-8859-2\">\n");
    printf
	("<link href=\"./style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
    printf
	("<script src=\"./script.js\" type=\"text/javascript\"></script>\n");



    printf("</head>\n\n");
    printf("<body>\n");
    printf("<center>\n");

}





void Footer()
{
    printf("</center>\n");
    printf("</body>\n");
    printf("</html>\n");

}



void ChessBoard()
{
    int i;

    if (strlen(str))
  	printf("<h1>%s</h1>\n", message);
    else
	printf("<h1>%s</h1>\n", title);

    printf("<form method=post><input type=hidden name=pole></form>\n");

    printf("\n<table border=0 cellpadding=0 cellspacing=0 width=%d>",
	   boksize * bok+3);

    for (i = 0; i < bok * bok; i++) {

	if (i % bok == 0) {
	    printf
		("\n<tr>\n\t<th width=3><img src=\"./img/blank.gif\" height=%d width=1 border=0></th>",
		 boksize);
	    temp = jeden;
	    jeden = drugi;
	    drugi = temp;
	}
	printf("\n\t<th class=%s width=%d>", (i % 2) ? jeden : drugi, boksize);


	if (strlen(str))
	  WypelnionePola(i, pole);
	else
	    PustePola(i);



	printf("</th>"); /*  */

    }

    printf("\n</table>\n\n");

}



void PustePola(int i)
{
    printf("<a href=\"javascript:go(%d);\"\n", i);
    printf("onmouseover=on('./img/skoczek%s%d',1);\n", (i < 10) ? "0" : "",
	   i);
    printf("onmouseout=off(1);\n");
    printf("onmousedown=down('./img/skoczek%s%d',1);\n",
	   (i < 10) ? "0" : "", i);
    printf("onmouseup=up('./img/skoczek%s%d',1);\n", (i < 10) ? "0" : "",
	   i);
    printf("onfocus=blur()>");
    printf("<img src=\"./img/skoczek_off.gif\" ");
    printf("name=\"./img/skoczek%s%d\" ", (i < 10) ? "0" : "", i);
    printf("width=%d height=%d border=0>", boksize, boksize);
    printf("</a>");
}



void WypelnionePola(int i, int pole)
{

    if (i == pole) {

    printf("<a href=\"javascript:history.go(-1);\"\n");
    printf("onmouseover=on('./img/skoczek%s%d',1);\n", (i < 10) ? "0" : "",
	   i);
    printf("onmousedown=down('./img/skoczek%s%d',1);\n",
	   (i < 10) ? "0" : "", i);
    printf("onmouseup=on('./img/skoczek%s%d',1);\n", (i < 10) ? "0" : "",
	   i);
    printf("onfocus=blur()>");
    printf("<img src=\"./img/skoczek_on.gif\" ");
    printf("name=\"./img/skoczek%s%d\" ", (i < 10) ? "0" : "", i);
    printf("width=%d height=%d border=0>", boksize, boksize);
    printf("</a>");
   
 } else if(trasa_skoczka[i]>63){
	printf("&nbsp;");
 } else {
	printf("%d", trasa_skoczka[i]);
 }
}
