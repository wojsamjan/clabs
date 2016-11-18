/*
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/605-Ncurses/keypressed.c $
    $revision:$
 */

#include <stdio.h>
#include <termios.h>
#include <term.h>
#include <unistd.h>

static struct termios domyslne_ustawienia;
static struct termios nowe_ustawienia;

int keypressed()
{
  char key;
  int n;

  nowe_ustawienia.c_cc[VMIN] = 0;
  tcsetattr(0, TCSANOW, &nowe_ustawienia);

  n = read(0, &key, 1);

  nowe_ustawienia.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &nowe_ustawienia);

  if (n == 1)
    return 1;
  else
    return 0;
}

int readchar() {
  char ch;
  read(0, &ch, 1);
  return ch;
}

void nowa_klawiatura(void);
void domyslna_klawiatura(void);

int main() 
{
  int ch = 0;

  nowa_klawiatura();
  while (ch != 'q') {
    puts("w pętli");
    sleep(1);
    if (keypressed()) {
      ch = readchar();
      printf("nacisnąłeś: %c\n", ch);
    }
  }
  domyslna_klawiatura();

  return 0;
}

void nowa_klawiatura(void)
{
  tcgetattr(0, &domyslne_ustawienia);
  nowe_ustawienia = domyslne_ustawienia;
  nowe_ustawienia.c_lflag &= ~ICANON;
  nowe_ustawienia.c_lflag &= ~ECHO;
  nowe_ustawienia.c_lflag &= ~ISIG;
  nowe_ustawienia.c_cc[VMIN] = 1;
  nowe_ustawienia.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &nowe_ustawienia);
}

void domyslna_klawiatura(void)
{
  tcsetattr(0, TCSANOW, &domyslne_ustawienia);
}


