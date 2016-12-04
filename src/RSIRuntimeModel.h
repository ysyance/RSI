
#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "IValue.h"
#include "RSISyslib.h"

// #define RSI_DEBUG 

extern std::vector<IValue> dataspace;			// RSI address space

extern std::vector<IValue> addrspace;			// RSI address space --- simple version



class BaseStatement {
public:
	BaseStatement() {}
	BaseStatement(std::vector<IValue> *as) : addr(as) {}

	virtual int execute(void *cookie) = 0;
public:
	std::vector<IValue> *addr;
};

class AssignStatement : public BaseStatement {
public:
	AssignStatement(){}
	AssignStatement(std::vector<IValue> *as) : BaseStatement(as), caller(NULL) {}

	virtual int execute(void *cookie) override{
#ifdef RSI_DEBUG
		std::cout << "=====assign state execute=====" << std::endl;
#endif
		if(caller == NULL) {
			(*addr)[left] = (*addr)[right];
		} else {
			caller->execute(cookie);
			(*addr)[left] = (*addr)[0];
		}
	}

public:
	int left;
	int right;
	BaseStatement* caller;
};

class IfStatement : public BaseStatement {
public:
	IfStatement() {}
	IfStatement(std::vector<IValue> *as) : 
			BaseStatement(as), exprCaller(NULL),
			ifThenStat(NULL), elseifThenStat(NULL), elseThenStat(NULL)
			{}

	virtual int execute(void *cookie) override {
#ifdef RSI_DEBUG
		std::cout << "=====if state execute=====" << std::endl;
#endif
		int cond = 0;
		if(exprCaller == NULL) {
			cond = (int)(*addr)[exprVar];
		} else {
			exprCaller->execute(cookie);
			cond = (*addr)[0];
		}
		if(cond) {
			for(auto &elem : *ifThenStat) {
				elem->execute(cookie);
			}
		} else {
			if(elseifThenStat != NULL) {
				for(int i = 0; i < elseifThenStat->size(); i ++) {
					int flag = ((*elseifThenStat)[i])->execute(cookie);
					if(flag) return 0;
				}
			}
			if(elseThenStat != NULL) {
				for(int i = 0; i < elseThenStat->size(); i ++) {
					((*elseThenStat)[i])->execute(cookie);
				}
			}
		}
		return 0;
	}

public:
	int exprVar;
	BaseStatement* exprCaller;

	std::vector<BaseStatement*> *ifThenStat;
	std::vector<BaseStatement*> *elseifThenStat;
	std::vector<BaseStatement*> *elseThenStat;
};

class ElseifStatement : public BaseStatement {
public:
	ElseifStatement() {}
	ElseifStatement(std::vector<IValue> *as) : 
						BaseStatement(as), flag(0),
						exprCaller(NULL), Stat(NULL)
			 			{}

	virtual int execute(void *cookie) override {
		int cond = 0;
		if(exprCaller == NULL) {
			cond = (int)(*addr)[exprVar];
		} else {
			exprCaller->execute(cookie);
			cond = (*addr)[0];
		}
		if(cond) {
			flag = 1;
			for(auto &elem : *Stat) {
				elem->execute(cookie);
			}
		}
		return flag;
	}

public:
	int flag;
	int exprVar;
	BaseStatement* exprCaller;

	std::vector<BaseStatement*> *Stat;
};

class LoopStatement : public BaseStatement {
public:
	LoopStatement() {}
	LoopStatement(std::vector<IValue> *as) : BaseStatement(as) {}

	virtual int execute(void *cookie) override {
#ifdef RSI_DEBUG
		std::cout << "=====loop state execute=====" << std::endl;
#endif
		int times = (int)(*addr)[varIndex];
		times = times > 0 ? times : 0;
		for(int i = 0; i < times; i ++) {
			for(auto &elem : *Stat) {
				elem->execute(cookie);
			}
		}

	}

public:
	int varIndex;
	std::vector<BaseStatement*> *Stat;
};

class WhileStatement : public BaseStatement {
public:
	WhileStatement() {}
	WhileStatement(std::vector<IValue> *as) : 
									BaseStatement(as),exprCaller(NULL) {}

	virtual int execute(void *cookie) override {
#ifdef RSI_DEBUG
		std::cout << "=====while state execute=====" << std::endl;
#endif		
		int cond = 0;
		if(exprCaller == NULL) {
			while(cond = ((*addr)[exprVar] > 0 ? (*addr)[exprVar] : 0)) {
				for(auto &elem : *Stat) {
					elem->execute(cookie);
				}
			}
		} else {
			while(1) {
				exprCaller->execute(cookie);
				cond = (*addr)[0];
				if(cond == 0) break;
				for(auto &elem : *Stat) {
					elem->execute(cookie);
				}
			}
		}
	}

public:
	int exprVar;
	BaseStatement* exprCaller;
	std::vector<BaseStatement*> *Stat;
};

class CallStatement : public BaseStatement {
public:
	CallStatement() {}
	CallStatement(std::vector<IValue> *as) : BaseStatement(as) {}

	virtual int execute(void *cookie) override {
#ifdef RSI_DEBUG
		std::cout << "=====call state execute=====" << std::endl;
#endif		
		libEntry[index].pfun(params, config, *addr);
	}

public:
	int index;						// the index of library function
	std::vector<int> params;		// the index of function parameters
	void *config;					// the config of fb
};


typedef std::vector<BaseStatement*> CodeShadow;		// code model in memory

struct PouParam {									// pou parameter
	std::string pname;
	int type;
	double defvalue;
};

class SysPou {										// system library pou
public:
	std::string name;
	std::vector<PouParam> paramlist;
};



