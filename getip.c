/* getip.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
int main(int argc, char *argv[])
{
  struct hostent *pe;
  struct in_addr addr;
  int   i;
  char  *p;
  if (argc < 2) {
    printf("(usage) %s hostname\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  pe = gethostbyname(argv[1]);
  if (pe == NULL) {
    printf("host not found\n");
    exit(EXIT_SUCCESS);
  }
  printf("name:%s\n", pe->h_name);
  for (i=0; pe->h_addr_list[i] != NULL; i++) {
    p = pe->h_addr_list[i];
    memcpy(&addr.s_addr, p, pe->h_length);
    printf("ip(%d): %s\n", i, inet_ntoa(addr));
  }
  return 0;
}
