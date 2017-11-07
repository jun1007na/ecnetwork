/* client <IPÉAÉhÉåÉX> <É|Å[Égî‘çÜ> */
/* client linux&windows */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>     /* gethostbyname() */
#endif /* _WIN32 */

#ifdef _WIN32
#define IS_INVALID_SOCKET(x)	((x) == INVALID_SOCKET)
#else
#define SOCKET	int  /* LinuxÇ≈ÇÕ socketÇÃñﬂÇËílÇÕ intå^ */
#define IS_INVALID_SOCKET(x)	((x) < 0)
#define closesocket(s)			close(s)
#endif


#define SERVERPORTNUM 80
#define BUFLEN        1024

int main(int argc, char *argv[])
{
  SOCKET s;
  struct sockaddr_in addr;
  char *getcmd = "GET / HTTP/1.0Å_rÅ_nÅ_rÅ_n";
  char buf[BUFLEN];
  int  portnum = SERVERPORTNUM, rc;
  struct hostent *pe;
  struct in_addr hostaddr;

#ifdef _WIN32
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2,0), &wsaData);
#endif

  s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (IS_INVALID_SOCKET(s)) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  if (argc > 2) portnum = atoi(argv[2]); /* É|Å[Égî‘çÜê›íË */
  if (argc > 1) {
    pe = gethostbyname(argv[1]);
    if (pe == NULL) addr.sin_addr.s_addr = inet_addr(argv[1]);
    else {
      memcpy(&hostaddr.s_addr, pe->h_addr_list[0], pe->h_length);
      addr.sin_addr.s_addr = hostaddr.s_addr;
    }      
  }

  addr.sin_family      = AF_INET;
  addr.sin_port        = htons(portnum);

  if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  if (send(s, getcmd, strlen(getcmd), 0) < 0) {
    perror("send");
    exit(EXIT_FAILURE);
  }

  while ((rc = recv(s, buf, BUFLEN, 0)) > 0) {
    buf[rc] = 'Å_0';
    printf("%s", buf);
  }
  closesocket(s);
#ifdef _WIN32
  WSACleanup();
#endif
  return 0;
}
