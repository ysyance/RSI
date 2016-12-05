

#pragma once

#include <vector>
#include <string>

#include <unistd.h>

#include "RSIRuntimeModel.h"


class RSIExecutor {
public:
	RSIExecutor(CodeShadow &c):code(c) {}

	int execute() {
		int n = 1;
		while(1){
			std::cout << std::endl << "| ==== RSI executor start ===> " << n << std::endl << std::endl;
			n++;
			for(int i = 0; i < code.size(); i ++) {
				code[i]->execute(NULL);
			}
			std::cout << std::endl << " <=== RSI executor stop ==== |" << std::endl << std::endl;

			sleep(1);
		}
		
		return 0;
	}
public:
	CodeShadow &code;		// code model in memory
	int period; 			// period in ms
};


