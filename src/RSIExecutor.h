

#pragma once

#include <vector>
#include <string>

#include "RSIRuntimeModel.h"


class RSIExecutor {
public:
	RSIExecutor(std::vector<BaseStatement*> &c):code(c) {}

	int execute() {
		for(int i = 0; i < code.size(); i ++) {
			code[i]->execute(NULL);
		}
		return 0;
	}
public:
	std::vector<BaseStatement*> &code;		// code model in memory
};


