/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik nag³ówkowy do obs³ugi sieci
 * siec.h
 */

#ifndef _JS_SIEC_H
#define _JS_SIEC_H

int tcpSluchaj(int*, const char*, const char*, socklen_t*); /* tworzy nas³uchuj±ce gniazdo tcp */
int tcpPolacz(int*, const char*, const char*); /* ³±czy siê przez tcp */

#endif
