
#include "RSISyslib.h"



inline int rsi_pid(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	EntityPID *entity = dynamic_cast<EntityPID*>(config);
	if(entity != NULL) {
		entity->printInfo();
	} else {
		std::cout << "this fb does not have config entity" << std::endl;
	}
	return 0;
}

inline int rsi_comm_interface(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	
	return 0;
}


