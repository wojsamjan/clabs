#include "config.h"
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void print_help();

void print_author();

void print_version();

void SetConfig(int argc, char *argv[])
{

  static struct option long_options[] = 
  {
    {"help", 0, 0, 'h'},
    {"author", 0, 0, 'a'},
    {"autor", 0, 0, 'a'},
    {"version", 0, 0, 'v'},
    {0, 0, 0, 0}
  };

  char c;
  int option_index = 0;

  opterr = 1;

  // najpierw ustawmy parametry 'domyslne'

  cfgUseExtendedFlags = 0;
  cfgEliminateDeadEnds = 0;

  cfgDelay = 100;

  inputfilename = NULL;
  outputfilename = NULL;

  cfgInputWallChars = "#+-|";
  cfgInputStartChars = "S";
  cfgInputExitChars = "E";

  cfgOutputWallChar = "#";
  cfgOutputStartChar = "S";
  cfgOutputExitChar = "E";

  cfgOutputDeadEndChar = "x";
  cfgOutputDeadEndColPair = 2;
  cfgOutputVisitedChar = ".";
  cfgOutputVisitedColPair = 3;
  cfgOutputOnPathChar = "X";
  cfgOutputOnPathColPair = 1;
  cfgOutputFloorChar = " ";

  // teraz sparsujemy sobie parametry

  while (1)
    {
      c = getopt_long(argc, argv, "i:o:xzw:s:e:d:W:S:E:P:F:V:Z:hav", long_options, &option_index);

      if (c == -1)
	break;

      switch (c)
	{
	case 'i' : inputfilename = optarg; break;
	case 'o' : outputfilename = optarg; break;
	case 'x' : cfgUseExtendedFlags = 1; break;
	case 'z' : cfgEliminateDeadEnds = 1; break;
	case 'w' : cfgInputWallChars = optarg; break;
	case 's' : cfgInputStartChars = optarg; break;
	case 'e' : cfgInputExitChars = optarg; break;
	case 'd' : cfgDelay = atoi(optarg); break;
	case 'W' : cfgOutputWallChar = optarg; break;
	case 'S' : cfgOutputStartChar = optarg; break;
	case 'E' : cfgOutputExitChar = optarg; break;
	case 'P' : cfgOutputOnPathChar = optarg; break;
	case 'F' : cfgOutputFloorChar = optarg; break;
	case 'V' : cfgOutputVisitedChar = optarg; break;
	case 'Z' : cfgOutputDeadEndChar = optarg; break;
	case 'h' : print_help(); break;
	case 'a' : print_author(); break;
	case 'v' : print_version(); break;
	case '?' : printf("Uzyto nieznanego parametru!\nUzyj opcji -h w celu przeczytania pomocy.\n"); exit(0);
	}
    }
        
  if (optind < argc)
    {
      printf("Nieprawidlowy paramter: %s\nUzyj parametru -h w celu przeczytania pomocy.\n", argv[optind]); 
      exit(0);
    }
}


void print_help()
{
  printf("Znajduje wyjscie z labiryntu.\n");
  printf("Uzycie:\nmaze -i PLIK_WE [-o PLIK_WY] [-x [-z]] [-w WALL] [-s START] [-e EXIT] [-d ###]\n");
  printf("     [-W #] [-S #] [-E #] [-P #] [-F #] [-V #] [-Z #]\n");
  printf("-i PLIK_WE : Plik z labiryntem wejsciowym o nazwie PLIK_WE, znaki wczytywane\n");
  printf("             wedlug regul z parametrow -w -s -e.\n");
  printf("             UWAGA! Parametr WYMAGANY!!!\n");
  printf("-o PLIK_WY : Plik z labiryntem wyjsciowym, znaki ustawione z opcji -W -S -E.\n");
  printf("             Jezeli brak tego parametru, to przechodzenie labiryntu jest\n");
  printf("             prezentowane jako animacja o wygladzie ustawionym z opcji -W -E -S\n");
  printf("             i odstepie miedzy klatkami z opcji -d.\n");
  printf("-x         : Uzywaj rozszezonych flag: VISITED, ON_PATH, DEAD_END - oznacza\n");
  printf("             uzycie lekko zmodyfikowane algorytmu przechodzenia, ktory radzi\n");
  printf("             sobie nieco lepiej z duzymi 'komnatami' od algorytmu z wykladu.\n");
  printf("-z         : Eliminuj slepe zaulki - dzieki uzyciu tej opcji jeszcze przed\n");
  printf("             przechodzeniem labiryntu wykluczone zostaja slepe korytaze.\n");
  printf("             W przypadku labiryntu doskonalego (bez komnat) daje to od razu\n");
  printf("             rozwiazanie labiryntu - zostaje tylko sciezka laczaca wejscie\n");
  printf("             z wyjsciem.\n");
  printf("-w WALL    : Traktuj znaki z WALL jako sciany przy wczytywaniu labiryntu.\n");
  printf("             W razie braku parametru przyjmuje sie znaki: `#+-|'\n");
  printf("-s START   : Traktuj znaki ze START jako wejscia.\n");
  printf("             W razie braku parametru przyjmuje sie znak: `S'\n");
  printf("-e EXIT    : Traktuj znaki z EXIT jako wyjscia.\n");
  printf("             W razie braku parametru przyjmuje sie znak: `E'\n");
  printf("-d ###     : Przy wyswietlaniu animacji rob przerwy miedzy klatkami trwajace\n");
  printf("             ### milisekund (1/1000 sekundy).\n");
  printf("             W razie braku parametru przyjmuje sie wartosc 100.\n");
  printf("             Jezeli animacja nie jest wyswietlana parametr jest pomijany.\n");
  printf("-W #       : Znak # bedzie symbolizowal sciane w pliku wynikowym lub animacji.\n");
  printf("             W razie braku parametru przyjmuje sie znak: `#'\n");
  printf("-S #       : Znak # bedzie symbolizowal punkt startowy w pliku wynikowym\n");
  printf("             lub animacji.\n");
  printf("             W razie braku parametru przyjmuje sie znak: `S'\n");
  printf("-E #       : Znak # bedzie symbolizowal punkt koncowy w pliku wynikowym\n");
  printf("             lub w animacji.\n");
  printf("             W razie braku parametru przyjmuje sie znak: `W'\n");
  printf("-P #       : Znak # bedzie symbolizowal punkt na sciezce rozwiazania.\n");
  printf("             W razie braku parametru przyjmuje sie znak: `X'\n");
  printf("-F #       : Znak # bedzie symbolizowal punkt nie lezacy na sciezce rozwiazania\n");
  printf("             W razie braku prametru przyjmuje sie znak: ` '\n");
  printf("-V #       : Znak # oznacza pola 'odwiedzone' nie lezace na sciezce rozwiazania\n");
  printf("             W razie braku parametru przyjmuje sie znak: `.'\n");
  printf("             Jezeli nie uzywa sie rozszezonych flag (parametr -x) pomijany.\n");
  printf("-Z #       : Znak # oznacza pola bedace 'slepym zaulkiem'.\n");
  printf("             W razie braku parametru przyjmuje sie znak: `x'\n");
  printf("             Jezeli nie uzywa sie rozszezonych flag (parametr -x) i eliminacji\n");
  printf("             slepych zaulkow (parametr -z) pomijany.\n");

  printf("-h, --help     : Wyswietla te pomoc\n");
  printf("-a, --author   : Informacje o autorze.\n");
  printf("-v, --version  : Wersja programu.\n");

  // skonczmy wykonywanie programu
  exit(0);
}

void
print_author()
{
  printf("Autorem programu jest Remigiusz Specht\n");
  printf("rspecht@manta.univ.gda.pl\n");
  exit(0);
}

void
print_version()
{
  printf("Maze v 1.0\n");
  exit(0);
}









