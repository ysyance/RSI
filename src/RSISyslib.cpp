
#include "RSISyslib.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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
		return -1;
	}

    struct sockaddr_in addr;
    int sockfd;

    if(entity->initflag != true) {
    	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

	    bzero(&addr, sizeof(addr));
	    addr.sin_family = AF_INET;
	    addr.sin_port = htons(atoi(entity->port.c_str()));
	    addr.sin_addr.s_addr = inet_addr(entity->ip.c_str());

	    entity->initflag = true;
    }

    sprintf(entity->sendBuffer, "Hello, world!");
    int sn = sendto(sockfd, entity->sendBuffer, strlen(entity->sendBuffer), 0, (struct sockaddr *)&addr, sizeof(addr));
    std::cout << sn << std::endl;

    // int rn = recvfrom(sockfd, entity->recvBuffer, strlen(entity->recvBuffer), 0, NULL, NULL);
    // std::cout << rn << std::endl;

    close(sockfd);
    
	return 0;
}


