
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "IValue.h"

#define MAX_SPOU_NAME_SIZE  50

#define RSI_DEBUG_PRINT

#ifdef RSI_DEBUG_PRINT
extern std::unordered_map<int, std::string> rdataIndexMap;   // index --> var
#endif

class EntityBase;

typedef struct {
    char name[MAX_SPOU_NAME_SIZE];
    int param_count;
    int (*pfun)(std::vector<int>&, EntityBase*, std::vector<IValue>&);
} RSILibEntry; /* System-level POU(Library) descriptor */

typedef enum{
	RSI_SUM = 0,
	RSI_SUB,
	RSI_MULTI,
	RSI_DIV,

	RSI_ABS,
	RSI_NORM,
	RSI_EXP,
	RSI_LOG,
	RSI_CEIL,
	RSI_FLOOR,
	RSI_ROUND,
	RSI_POW,

	RSI_SIN,
	RSI_COS,
	RSI_TAN,
	RSI_ASIN,
	RSI_ACOS,
	RSI_ATAN,
	RSI_ATAN2,

	RSI_INC,
	RSI_DEC,

	RSI_PRINT,

	RSI_EQ,
	RSI_GT,
	RSI_GE,
	RSI_LT,
	RSI_LE,

	RSI_AND,
	RSI_OR,
	RSI_XOR,
	RSI_NOT,

	RSI_P,
	RSI_PD,
	RSI_I,
	RSI_D,
	RSI_PI,
	RSI_PID,

	RSI_AXISCORR,
	RSI_POSCORR,
	RSI_TRANSFRAME,
	RSI_POSACT,
	RSI_AXISACT,
	RSI_GEARTORQUE,
	RSI_MOTORCURRENT,

	RSI_COMM_INTERFACE,

}POUId;


inline int rsi_sum(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = 0;
	for(int i = 0; i < params.size(); i ++) {
		addrspace[0] += addrspace[params[i]];
	}
	return 0;
}

inline int rsi_sub(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] - addrspace[params[1]];
	return 0;
}

inline int rsi_multi(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] * addrspace[params[1]];
	return 0;
}
inline int rsi_div(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] / addrspace[params[1]];
	return 0;
}

inline int rsi_abs(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_norm(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_exp(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_log(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_ceil(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_floor(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_pow(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}

inline int rsi_sin(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_cos(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_tan(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_asin(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_acos(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_atan(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_atan2(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}

inline int rsi_inc(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[params[0]] += 1;
	return 0;
}
inline int rsi_dec(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[params[0]] -= 1;
	return 0;
}

inline int rsi_print(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
#ifdef RSI_DEBUG_PRINT
	std::cout << "[DEBUG: " << rdataIndexMap[params[0]] << " --> " << addrspace[params[0]] << " ]" << std::endl;
#else
	std::cout << "Macro RSI_DEBUG_PRINT not defined" << std::endl;
#endif
	return 0;
}


inline int rsi_eq(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] == addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_gt(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] > addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_ge(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] >= addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_lt(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] < addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_le(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] <= addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_and(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	int cond1 = addrspace[params[0]];
	int cond2 = addrspace[params[1]];
	addrspace[0] = cond1 && cond2;

	return 0;
}

inline int rsi_or(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	int cond1 = addrspace[params[0]];
	int cond2 = addrspace[params[1]];
	addrspace[0] = cond1 || cond2;

	return 0;
}

inline int rsi_xor(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	int cond1 = addrspace[params[0]];
	int cond2 = addrspace[params[1]];
	if(cond1 == 0 && cond2 != 0 || cond1 != 0 && cond2 == 0){
		addrspace[0] = 1;
	} else {
		addrspace[0] = 0;
	}
	
	return 0;
}

inline int rsi_not(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	int cond1 = addrspace[params[0]];
	addrspace[0] = (cond1 == 0 ? 1 : 0);
	return 0;
}

inline int rsi_p(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_pd(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_i(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_d(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_pi(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}

inline int rsi_pid(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) ;

inline int rsi_timer(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_limit(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}

inline int rsi_min(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]];
	for(int i = 0; i < params.size(); i ++) {
		addrspace[0] = addrspace[params[i]] < addrspace[0] ? addrspace[params[i]] : addrspace[0];
	}
	return 0;
}

inline int rsi_max(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]];
	for(int i = 0; i < params.size(); i ++) {
		addrspace[0] = addrspace[params[i]] > addrspace[0] ? addrspace[params[i]] : addrspace[0];
	}
	return 0;
}

inline int rsi_delay(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_monitor(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_stop(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}


inline int rsi_axiscorr(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_poscorr(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_transfame(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_posact(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_axisact(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_geartorque(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_motorcurrent(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}

inline int rsi_comm_interface(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace);



#define VARIABLE_LEN 0

#define RSI_LIB_SIZE  51

/* ORDER SENSITIVE */
static const RSILibEntry libEntry[RSI_LIB_SIZE] = {
	{"SUM", VARIABLE_LEN, rsi_sum},
	{"SUB", 2, rsi_sub},
	{"MULTI", 2, rsi_multi},
	{"DIV", 2, rsi_div},

	{"ABS", 1, rsi_abs},
	{"NORM", VARIABLE_LEN, rsi_norm},
	{"EXP", 2, rsi_exp},
	{"LOG", 2, rsi_log},
	{"CEIL", 1, rsi_ceil},
	{"FLOOR", 1, rsi_floor},
	{"POW", 2, rsi_pow},

	{"SIN", 1, rsi_sin},
	{"COS", 1, rsi_cos},
	{"TAN", 1, rsi_tan},
	{"ASIN", 1, rsi_asin},
	{"ACOS", 1, rsi_acos},
	{"ATAN", 1, rsi_atan},
	{"ATAN2", 1, rsi_atan2},

	{"INC", 1, rsi_inc},
	{"DEC", 1, rsi_dec},

	{"PRINT", 1, rsi_print},

	{"EQ", 2, rsi_eq},
	{"GT", 2, rsi_gt},
	{"GE", 2, rsi_ge},
	{"LT", 2, rsi_lt},
	{"LE", 2, rsi_le},

	{"AND", 2, rsi_and},
	{"OR", 2, rsi_or},
	{"XOR", 2, rsi_xor},
	{"NOT", 1, rsi_not},

	{"P", 1, rsi_p},
	{"PD", 1, rsi_pd},
	{"I", 1, rsi_i},
	{"D", 1, rsi_d},
	{"PI", 1, rsi_pi},
	{"PID", 1, rsi_pid},

	{"TIMER", 1, rsi_timer},
	{"LIMIT", 3, rsi_limit},
	{"MIN", VARIABLE_LEN, rsi_min},
	{"MAX", VARIABLE_LEN, rsi_max},
	{"DELAY", 1, rsi_delay},
	{"MONITOR", VARIABLE_LEN, rsi_monitor},
	{"STOP", 1, rsi_stop},

	{"AXISCORR", VARIABLE_LEN, rsi_axiscorr},
	{"POSCORR", VARIABLE_LEN, rsi_poscorr},
	{"TRANSFRAME", VARIABLE_LEN, rsi_transfame},
	{"POSACT", VARIABLE_LEN, rsi_posact},
	{"AXISACT", VARIABLE_LEN, rsi_axisact},
	{"GEARTORQUE", VARIABLE_LEN, rsi_geartorque},
	{"MOTORCURRENT", VARIABLE_LEN, rsi_motorcurrent},

	{"COMM_INTERFACE", VARIABLE_LEN, rsi_comm_interface},
};


/* ************** the Entity type of function block ***************** */
class EntityBase {
public:
	EntityBase(std::string f) : funcName(f) {}

	virtual int setConfig(std::string key, std::string value) = 0;

	virtual int printInfo() { std::cout << "[> EntityBase <]" << std::endl; }

public:
	std::string funcName;
};

class EntityPID : public EntityBase{
public:
	EntityPID() : EntityBase("PID"), kp(0), ki(0), kd(0), Ts(10), prev(0) {}

	virtual int setConfig(std::string key, std::string value) override {
		if(key == "Kp")  {
			kp = std::stod(value);
		} else if(key == "Ki") {
			ki = std::stod(value);
		} else if(key == "Kd") {
			kd = std::stod(value);
		} else if(key == "Ts") {
			Ts = std::stod(value);
		} else {
			return -1;
		}
		return 0;
	}

	virtual int printInfo() override {
		std::cout << "Type: " << funcName << " --> ";
		std::cout << "Kp=" << kp << " Ki=" << ki << " Kd=" << kd << " Ts=" << Ts << std::endl;
	}

public:
	IValue kp;
	IValue ki;
	IValue kd;

	IValue Ts;

	IValue prev;
};


class EntityDELAY : public EntityBase{
public:
	EntityDELAY() : EntityBase("DELAY"), T(0) {}

	virtual int setConfig(std::string key, std::string value) override {
		if(key == "T")  {
			T = std::stod(value);
		} else {
			return -1;
		}
		return 0;
	}

	virtual int printInfo() override {
		std::cout << "Type: " << funcName << " --> ";
		std::cout << "T=" << T << std::endl;
	}

public:
	IValue T;
};



class EntityFactory {
public:
	static EntityBase* getEntity(std::string name) {
		if(name == "PID") {
			return new EntityPID();
		} else if(name == "DELAY") {
			return new EntityDELAY();
		} else {
			return NULL;
		}
	}
};





