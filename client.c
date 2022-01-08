#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<wait.h>
#include<netdb.h>
#include <arpa/inet.h>


#define SUNUCUPORT 2015
#define SUNUCUIP "127.0.0.1"
#define AZAMIUZUNLUK 1024

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    char *gonder = "Hangi ders?";
    char str[AZAMIUZUNLUK];
    int gelenBayt, gidenBayt;

    // AF_UNIX - Unix domain socket
    // AF_INET - Internet Protocol v4 socket
    // SOCK_STREAM TCP Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd) {
        perror("socket");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SUNUCUPORT);
    serverAddr.sin_addr.s_addr = inet_addr(SUNUCUIP);
    memset(&(serverAddr.sin_zero), '\0', 8);

    // sockaddr fonksiyonlarımızın alacağı adres yapısı
    if (-1 == connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr))) {
        perror("connect");
    }

    gidenBayt = send(sockfd, gonder, strlen(gonder), 0);
    if (-1 == gidenBayt) {
        perror("send");
    }
    else if (strlen(gonder) != gidenBayt) {
        printf("Gönderilen: %d\tGiden: %d\n", strlen(gonder), gidenBayt);
    }
    printf("%d bayt gönderdim:\t%s\n", gidenBayt, gonder);

    gelenBayt = recv(sockfd, &str, AZAMIUZUNLUK-1, 0);
    if (-1 == gelenBayt) {
        perror("recv");
    }
    else if (0 == gelenBayt) {
        printf("Bağlantı kapalı.\n");
    }
    printf("%d bayt aldım:\t%s\n", gelenBayt, str);

    close(sockfd);
}