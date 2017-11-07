/* server <ポート番号> */
/* server linux&windows */

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
#endif /* _WIN32 */

#ifdef _WIN32
#define IS_INVALID_SOCKET(x)	((x) == INVALID_SOCKET)
#else
#define SOCKET	int  /* Linuxでは socketの戻り値は int型 */
#define IS_INVALID_SOCKET(x)	((x) < 0)
#define closesocket(s)			close(s)
#endif

#define SERVERPORTNUM 80
#define MAXNUM          10
#define BUFLEN        1024

int main(int argc, char *argv[])
{
  SOCKET s, csock, portnum = SERVERPORTNUM;
  struct sockaddr_in addr, caddr;
  int  caddr_len, rc;
  char buf[BUFLEN];
  char *html1 = "HTTP/1.1 200 OK＼n＼n";
  char *html2 =
        "<html><head></head><body><H1>SAMPLE PAGE</H1></body></html>＼n";

#ifdef _WIN32
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif

  if (argc>1) {
    portnum = atoi(argv[1]);
    if (portnum < 1) portnum = SERVERPORTNUM;
  }

  s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (IS_INVALID_SOCKET(s)) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  addr.sin_family      = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port        = htons(portnum);

  if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  if (listen(s, MAXNUM) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  while (1) {
    caddr_len = sizeof(caddr);
    csock = accept(s, (struct sockaddr *)&caddr, &caddr_len);
    if ((rc  = recv(csock, buf, BUFLEN, 0)) > 0) {
      /* 接続してきたクライアントの情報を表示 */
      printf("CLIENT ADDRESS: %s＼n", inet_ntoa(caddr.sin_addr));
      /* クライアントからのメッセージを受信して表示 */
      buf[rc] = '＼0'; /* 文字列の最後にヌル文字を入れる */
      printf("REQUEST STRING: %s＼n", buf);
    }

    send(csock, html1, strlen(html1), 0); /*メッセージをクライアントに送信*/
    send(csock, html2, strlen(html2), 0); /*メッセージをクライアントに送信*/
    closesocket(csock);
  }
  closesocket(s);
#ifdef _WIN32
  WSACleanup();
#endif
  return 0;
}
