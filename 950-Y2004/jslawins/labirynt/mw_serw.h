/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik nag³ówkowy do serwera gry maze walker
 * mw_serw.h
 */

#include "mw_lib.h"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#ifndef _JS_MW_SERW_H
#define _JS_MW_SERW_H

#define S_KONIEC	1 
#define S_MAXXY	2	
#define S_WSPOL	4	
#define S_NAME	5	
#define S_OKOLICA	6
#define S_KICKOFF	8
#define K_LOGIN	9	
#define K_LOGOUT	10
#define	K_MOVE	11	
#define S_ACCEPT	12
#define S_EXIT	13	
#define K_ZALOZ	14	
#define S_STARTED	15

typedef struct {
	int fd; /* deskryptor, do którego pisze gracz (serwer z niego czyta) */
	int fd2; /* deskryptor, do którego pisze serwer (klient z niego czyta) */
	int stan; /* flaga stanu gracza */
	int id; /* identyfikator gracza */
	char* name; /* ksywa gracza */
	punktT pozycja; /* pozycja gracza */
	int ruchy; /* ilo¶æ ruchów gracza */
} playerT;

typedef struct {
	char typ; /* typ serwera */
	int jestgra; /* toczy siê w³a¶nie gra */
	int listenfd; /* deskryptor nas³uchuj±cy (przy grze wieloosobowej) */
	socklen_t addrlen; /* wielko¶æ adresu gniazda (przy grze wieloosobowej) */
	int sock[2]; /* kolejka nas³uchuj±ca (przy grze jednoosobowej) */
	int numplay; /* ilo¶æ graczy */
	int numspac; /* ilo¶æ miejsc */
	int zalid; /* id za³o¿yciela serwera */
	playerT* tablica; /* tablica graczy */
	int running; /* czy serwer pracuje */
} serwT;

int Postaw(char, int, char*, char*); /* funkcja stawiaj±ca serwer */
int ZacznijGre(char); /* funkcja zaczynaj±ca grê */
int PiszGracz(int, char, char, char, char, unsigned char[]); /* funkcja wysy³aj±ca wiadomo¶æ do gracza */
void* Przetwarzaj(void*); /* funkcja przetwarzaj±ca ¿±dania */
int Zamknij(int); /* funkcja zamykaj±ca dzia³anie serwera */
int DodajGracza(int, char); /* funkcja dodaj±ca gracza do serwera */
int UsunGracza(int); /* usuwa podanego gracza z serwera */

int PrzeslijOtoczenie(int); /* przesy³a otoczenie do danego gracza */
int PrzeslijWspolrzedne(int); /* przesy³a wspó³rzêdne do danego gracza */
int PrzeslijImie(int); /* przesy³a imiê gracza do pozosta³ych graczy */

int Miejsca(void); /* na ile miejsc jest serwer */
int Ilosc(void); /* ilu jest zalogowanych graczy */
int JestGra(void); /* czy toczy siê aktualnie gra */
char TypS(void); /* typ serwera */
int Zalozyciel(void); /* id za³o¿yciela serwera */
int Rura(void); /* deskryptor rury serwera (tryb jednoosobowy) */
int DzialaSerwer(void); /* czy serwer dzia³a */

#endif
