
#include "RSISyslib.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>



inline int rsi_pid(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	EntityPID *entity = dynamic_cast<EntityPID*>(config);
	if(entity != NULL) {
		entity->printInfo();
	} else {
		std::cout << "this fb does not have config entity" << std::endl;
	}
	return 0;
}

inline int rsi_comm_interface( 	std::vector<int>& params, 
								EntityBase* config, 
								std::vector<IValue>& addrspace) 
{
	EntityComm *entity = dynamic_cast<EntityComm*>(config);
	if(entity != NULL) {
		entity->printInfo();
	} else {
		std::cout << "this fb does not have config entity" << std::endl;
	}

    // struct sockaddr_in addr;
    // int sock;

    // if ( (sock=socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    //     perror("socket");
    //     exit(1);
    // }
    // addr.sin_family = AF_INET;
    // addr.sin_port = htons(atoi(argv[2]));
    // addr.sin_addr.s_addr = inet_addr(argv[1]);
    // if (addr.sin_addr.s_addr == INADDR_NONE) {
    //     printf("Incorrect ip address!");
    //     close(sock);
    //     exit(1);
    // }

    // char buff[512];
    // int len = sizeof(addr);
    // while(1) {
    //     gets(buff);
    //     int n;
    //     n = sendto(sock, buff, strlen(buff), 0, (struct sockaddr *)&addr, sizeof(addr));
    //     if(n < 0) {
    //         perror("sendto");
    //         close(sock);
    //         break;
    //     }
    //     n = recvfrom(sock, buff, 512, 0, (struct sockaddr *)&addr, &len);
    //     if(n > 0) {
    //         buff[n] = 0;
    //         printf("received:");
    //         puts(buff);
    //     } else if (n==0) {
    //         printf("server closed\n");
    //         close(sock);
    //         break;
    //     } else if (n == -1) {
    //         perror("recvfrom");
    //         close(sock);
    //         break;
    //     }
    // }
    
	return 0;
}


