
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
#ifdef RSI_DEBUG
		entity->printInfo();
#endif
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
#ifdef RSI_DEBUG
		entity->printInfo();
#endif
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

    entity->xmlGenerate(addrspace);
    std::cout << entity->sendBuffer << std::endl;
    int sn = sendto(sockfd, entity->sendBuffer, strlen(entity->sendBuffer), 0, (struct sockaddr *)&addr, sizeof(addr));
    std::cout << "send ==> " << sn << "bytes" << std::endl;

    std::string str = "<?xml version=\"1.0\" encoding=\"GBK\"?>\
    <Root>\
          <RKorr X=\"1.2\" Y=\"2.3\" Z=\"3.4\" A=\"4.5\" B=\"5.6\" C=\"6.7\"/>\
          <FREE>100</FREE>\
          <STOP stopFlag=\"0\" />\
	<Root>";  
	sprintf(entity->recvBuffer, "%s", str.c_str());

	// std::cout << entity->recvBuffer << std::endl;
    // int rn = recvfrom(sockfd, entity->recvBuffer, strlen(entity->recvBuffer), 0, NULL, NULL);
    // std::cout << rn << std::endl;

    entity->xmlParse(addrspace);

    close(sockfd);
    
	return 0;
}


