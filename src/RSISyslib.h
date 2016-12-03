
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "IValue.h"

#define MAX_SPOU_NAME_SIZE  50

extern std::unordered_map<int, std::string> rdataIndexMap;   // index --> var

extern std::vector<IValue> addrspace;			// RSI address space --- simple version

extern IValue sys_ret_buffer;					// return value buffer of all the sys function

typedef struct {
    char name[MAX_SPOU_NAME_SIZE];
    int param_count;
    int (*pfun)(std::vector<int>&, void*);
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

}POUId;


inline int rsi_sum(std::vector<int>& params, void* config) {
	sys_ret_buffer = 0;
	for(int i = 0; i < params.size(); i ++) {
		sys_ret_buffer += addrspace[params[i]];
	}
	return 0;
}

inline int rsi_sub(std::vector<int>& params, void* config) {
	sys_ret_buffer = addrspace[params[0]] - addrspace[params[1]];
	return 0;
}

inline int rsi_multi(std::vector<int>& params, void* config) {
	sys_ret_buffer = addrspace[params[0]] * addrspace[params[1]];
	return 0;
}
inline int rsi_div(std::vector<int>& params, void* config) {
	sys_ret_buffer = addrspace[params[0]] / addrspace[params[1]];
	return 0;
}

inline int rsi_abs(std::vector<int>& params, void* config) {}
inline int rsi_norm(std::vector<int>& params, void* config) {}
inline int rsi_exp(std::vector<int>& params, void* config) {}
inline int rsi_log(std::vector<int>& params, void* config) {}
inline int rsi_ceil(std::vector<int>& params, void* config) {}
inline int rsi_floor(std::vector<int>& params, void* config) {}
inline int rsi_pow(std::vector<int>& params, void* config) {}

inline int rsi_sin(std::vector<int>& params, void* config) {}
inline int rsi_cos(std::vector<int>& params, void* config) {}
inline int rsi_tan(std::vector<int>& params, void* config) {}
inline int rsi_asin(std::vector<int>& params, void* config) {}
inline int rsi_acos(std::vector<int>& params, void* config) {}
inline int rsi_atan(std::vector<int>& params, void* config) {}
inline int rsi_atan2(std::vector<int>& params, void* config) {}

inline int rsi_inc(std::vector<int>& params, void* config) {
	addrspace[params[0]] += 1;
	return 0;
}
inline int rsi_dec(std::vector<int>& params, void* config) {
	addrspace[params[0]] -= 1;
	return 0;
}

inline int rsi_print(std::vector<int>& params, void* config) {
	std::cout << "[DEBUG: " << rdataIndexMap[params[0]] << " --> " << addrspace[params[0]] << " ]" << std::endl;
	return 0;
}


inline int rsi_eq(std::vector<int>& params, void* config) {
	sys_ret_buffer = addrspace[params[0]] == addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_gt(std::vector<int>& params, void* config) {
	sys_ret_buffer = addrspace[params[0]] > addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_ge(std::vector<int>& params, void* config) {
	sys_ret_buffer = addrspace[params[0]] >= addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_lt(std::vector<int>& params, void* config) {
	sys_ret_buffer = addrspace[params[0]] < addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_le(std::vector<int>& params, void* config) {
	sys_ret_buffer = addrspace[params[0]] <= addrspace[params[1]] ? 1 : 0;
	return 0;
}


#define VARIABLE_LEN 0

#define RSI_LIB_SIZE  26

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
	{"LE", 2, rsi_le}

};


