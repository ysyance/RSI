#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>


char buff[] = "<?xml version=\"1.0\" encoding=\"GBK\"?>\
    <Root>\
          <RKorr X=\"1.2\" Y=\"2.3\" Z=\"3.4\" A=\"4.5\" B=\"5.6\" C=\"6.7\"/>\
          <FREE>100</FREE>\
          <STOP stopFlag=\"0\" />\
	<Root>"; 



int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(49152);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

 	struct sockaddr_in clientAddr;
    int len = sizeof(clientAddr);
    
    for(int i = 0; i < 10; i ++) {
    	std::cout << "[===>    " << i << "    <====]" << std::endl;
    	char recvline[1024] = {0};
	    recvfrom(sockfd, recvline, 1024, 0, (struct sockaddr*)&clientAddr, (socklen_t*)&len);

	    sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&clientAddr, len);
	    printf("%s\n", recvline);
    }
    
    close(sockfd);
}

