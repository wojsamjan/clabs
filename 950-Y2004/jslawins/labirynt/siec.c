/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik implementuj±cy obs³ugê sieci
 * siec.c
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

int
tcpSluchaj(int* listenfd, const char *host, const char *serv, socklen_t *addrlenp)
{
	const int		on = 1;
	struct addrinfo	hints, *res, *ressave;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(host, serv, &hints, &res) != 0) {
		return 1;
	}
	ressave = res;

	do {
		(*listenfd) = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if ((*listenfd) < 0)
			continue;		/* b³±d -> próbujemy nastêpne */

		setsockopt((*listenfd), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		if (bind((*listenfd), res->ai_addr, res->ai_addrlen) == 0)
			break;			/* uda³o siê */

		close(*listenfd);	/* nie uda³o siê zbindowaæ -> zamykamy i próbujemy nastêpne */
	} while ( (res = res->ai_next) != NULL);

	if (res == NULL) {	/* w ogóle nie uda³o siê nic znale¼æ */
		return 1;
	}

	listen((*listenfd), 10);

	if (addrlenp)
		*addrlenp = res->ai_addrlen;	/* zwracamy wielko¶æ struktury adresu dla danego protoko³u */

	freeaddrinfo(ressave);

	return 0;
}

int
tcpPolacz(int* sockfd, const char *host, const char *serv)
{
	struct addrinfo	hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(host, serv, &hints, &res) != 0) {
		return 1;
	}
	ressave = res;

	do {
		(*sockfd) = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if ((*sockfd) < 0)
			continue;	/* b³±d -> próbujemy nastêpne */

		if (connect((*sockfd), res->ai_addr, res->ai_addrlen) == 0)
			break;		/* uda³o siê */

		close((*sockfd));	/* nie uda³o siê -> zamykamy i próbujemy nastêpne */
	} while ( (res = res->ai_next) != NULL);

	if (res == NULL) {	/* nie uda³o siê w ogóle po³±czyæ */
		return 1;
	}

	freeaddrinfo(ressave);

	return 0;
}



