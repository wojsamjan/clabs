/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik nag³ówkowy do klienta gry maze walker
 * mw_klie.h
 */

#include "mw_lib.h"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#ifndef _JS_MW_KLIE_H
#define _JS_MW_KLIE_H

typedef struct {
	char type; /* typ po³±czenia z serwerem */
	int fds; /* deskryptor do komunikacji z serwerem */
	int fd; /* deskryptor gracza, do którego siê pisze (serwer) */
	int fd2; /* deskryptor gracza, z którego siê nas³uchuje (klient) */
	punktT pozycja; /* pozycja gracza */
	int id; /* identyfikator gracza */
	char name[10]; /* ksywa gracza */
	int ruchy; /* ilo¶æ wykonanych do tej pory ruchów*/
	int miejsca; /* ilo¶æ miejsc na graczy */
	char* czygracz; /* czy dany gracz jest w grze */
	punktT* pozgraczy; /* pozycje wszystkich graczy */
	char** imionagraczy; /* imiona wszystkich graczy */
	struct timeval tv; /* znacznik czasowy klienta */
} klientT;

int KlientInicjuj(char, char*, char*); /* zainicjowanie dzia³ania klienta */
int PiszDoSerwera(char, char, char, char, char*); /* pisanie wiadomo¶ci do serwera */
int Dzialaj(void); /* g³ówna funkcja klienta (grafika - klawiatura - w grze) */
int DajFd(void); /* daje deskryptor klienta */
int DajRuchy(void); /* daje ruchy gracza */
int RozpPoj(void); /* rozpoczyna grê jednoosobow± */
int RozpMulti(char); /* rozpoczyna grê wieloosobow± */
char* WprTekst(char*, int); /* wprowadzanie okre¶lonego tekstu */

#endif
