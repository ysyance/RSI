
#pragma once

#include <vector>
#include <stack>
#include <unordered_map>
#include <exception>
#include <stdexcept>

#include "antlr4-runtime.h"
#include "RSIBaseVisitor.h"

#include "RSIRuntimeModel.h"


using namespace antlr4;



extern std::unordered_map<std::string, int> dataIndexMap;   // parser xml file and generator dataMap

extern std::unordered_map<std::string, int> constIndexMap;   // the index of all the constants in addr space 

extern std::unordered_set<std::string> fbMap;    		// parser xml file and generator functionblock map

extern std::unordered_map<std::string, int> funcMap;  	    // all library function map to check if designated function is existed


extern std::stack<std::vector<BaseStatement*>*> compileStack;


class RSICodeGenerator : public RSIBaseVisitor {
public:
	virtual antlrcpp::Any visitProgram(RSIParser::ProgramContext *ctx) override {
		std::cout << "program" << std::endl;
		compileStack.push(&CodeShadow);
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitStatBlock(RSIParser::StatBlockContext *ctx) override {
		std::cout << "statBlock" << std::endl;
		
		antlrcpp::Any result = defaultResult();
	    size_t n = ctx->children.size();
	    std::cout << "n : " << n << std::endl;
	    for (size_t i = 0; i < n; i++) {
	        if (!shouldVisitNextChild(ctx, result)) {
	          break;
        	}
	        antlrcpp::Any childResult = ctx->children[i]->accept(this);
	        result = aggregateResult(result, childResult);
	        std::vector<BaseStatement*>* cur = compileStack.top();
	        BaseStatement* tmp = result;
	        cur->push_back(tmp);
      	}

      	return result;
	}

	virtual antlrcpp::Any visitAssignStat(RSIParser::AssignStatContext *ctx) override {
		std::cout << "------assignStat-----" << std::endl;

		AssignStatement* tmpAssignStat = visitChildren(ctx);
		BaseStatement* tempBaseStat = tmpAssignStat;

		return tempBaseStat;
	}

	virtual antlrcpp::Any visitIfStat(RSIParser::IfStatContext *ctx) override {
		std::cout << "------ifStat------" << std::endl;

		IfStatement* tmpIfStat = visitChildren(ctx);
		BaseStatement* tempBaseStat = tmpIfStat;

		return tempBaseStat;
	}

	virtual antlrcpp::Any visitWhileStat(RSIParser::WhileStatContext *ctx) override {
		std::cout << "--------whileStat---------" << std::endl;

		WhileStatement* tmpWhileStat = visitChildren(ctx);
		BaseStatement* tempBaseStat = tmpWhileStat;

		return tempBaseStat;
	}

	virtual antlrcpp::Any visitLoopStat(RSIParser::LoopStatContext *ctx) override {
		std::cout << "--------loopStat---------" << std::endl;

		LoopStatement* tmpLoopStat = visitChildren(ctx);
		BaseStatement* tempBaseStat = tmpLoopStat;

		return tempBaseStat;
	}

	virtual antlrcpp::Any visitCallStat(RSIParser::CallStatContext *ctx) override {
		std::cout << "--------callStat------" << std::endl;

		CallStatement* tmpCallStat = visitChildren(ctx);
		BaseStatement* tempBaseStat = tmpCallStat;

		return tempBaseStat;
	}

	virtual antlrcpp::Any visitAssignExpr(RSIParser::AssignExprContext *ctx) override {
		std::cout << "assignExpr" << std::endl;
		AssignStatement *tempStat = new AssignStatement(&addrspace, &sys_ret_buffer);

		std::string id = ctx->ID()->getText();
		tempStat->left = dataIndexMap[id];

		antlrcpp::Any ret = visit(ctx->expr());
		if(ret.is<CallStatement*>()) {
			CallStatement* tempCallStat = ret;
			tempStat->caller = tempCallStat;
		} else {
			tempStat->right = ret;
		}

		return tempStat;
	}

	virtual antlrcpp::Any visitIfExpr(RSIParser::IfExprContext *ctx) override {
		std::cout << "ifExpr" << std::endl;
		IfStatement *tempStat = new IfStatement(&addrspace, &sys_ret_buffer);

		antlrcpp::Any ret = visit(ctx->expr());
		if(ret.is<CallStatement*>()) {
			CallStatement* tempCallStat = ret;
			tempStat->exprCaller = tempCallStat;
		} else {
			tempStat->exprVar = ret;
		}

		/* if section */
		std::vector<BaseStatement*> *thenStatBlock = new std::vector<BaseStatement*>();
		compileStack.push(thenStatBlock);
		visit(ctx->block());
		tempStat->ifThenStat = thenStatBlock;
		compileStack.pop();

		/* elseif section */
		std::vector<BaseStatement*> *elseifStatBlock = new std::vector<BaseStatement*>();
		int n = (ctx->elseif_stat()).size();
		std::cout << "else if : " << n << std::endl;
		for(int i = 0; i < n; i ++) {
			ElseifStatement *tmp = visit(ctx->elseif_stat(i));
			BaseStatement* base = tmp;
			elseifStatBlock->push_back(base);
		}
		tempStat->elseifThenStat = elseifStatBlock;

		/* else section */
		std::vector<BaseStatement*> *elseStatBlock = new std::vector<BaseStatement*>();
		compileStack.push(elseStatBlock);
		visit(ctx->else_stat());
		tempStat->elseThenStat = elseStatBlock;
		compileStack.pop();

		return tempStat;
	}

	virtual antlrcpp::Any visitElseifExpr(RSIParser::ElseifExprContext *ctx) override {
		std::cout << "elseifExpr" << std::endl;
		ElseifStatement *tempStat = new ElseifStatement(&addrspace, &sys_ret_buffer);

		antlrcpp::Any ret = visit(ctx->expr());
		if(ret.is<CallStatement*>()) {
			CallStatement* tempCallStat = ret;
			tempStat->exprCaller = tempCallStat;
		} else {
			tempStat->exprVar = ret;
		}

		std::vector<BaseStatement*> *thenStatBlock = new std::vector<BaseStatement*>();
		compileStack.push(thenStatBlock);
		visit(ctx->block());
		tempStat->Stat = thenStatBlock;
		compileStack.pop();

		return tempStat;
	}

	virtual antlrcpp::Any visitElseExpr(RSIParser::ElseExprContext *ctx) override {
		std::cout << "else" << std::endl;

		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitWhileExpr(RSIParser::WhileExprContext *ctx) override {
		std::cout << "whileExpr" << std::endl;
		WhileStatement *tempStat = new WhileStatement(&addrspace, &sys_ret_buffer);

		antlrcpp::Any ret = visit(ctx->expr());
		if(ret.is<CallStatement*>()) {
			CallStatement* tempCallStat = ret;
			tempStat->exprCaller = tempCallStat;
		} else {
			tempStat->exprVar = ret;
		}

		std::vector<BaseStatement*> *StatBlock = new std::vector<BaseStatement*>();
		compileStack.push(StatBlock);
		visit(ctx->block());
		tempStat->Stat = StatBlock;
		compileStack.pop();

		return tempStat;
	}

	virtual antlrcpp::Any visitLoopExpr(RSIParser::LoopExprContext *ctx) override {
		std::cout << "loopExpr" << std::endl;
		LoopStatement *tempStat = new LoopStatement(&addrspace, &sys_ret_buffer);

		tempStat->varIndex = visit(ctx->var());

		std::vector<BaseStatement*> *StatBlock = new std::vector<BaseStatement*>();
		compileStack.push(StatBlock);
		visit(ctx->block());
		tempStat->Stat = StatBlock;
		compileStack.pop();


		return tempStat;
	}

	virtual antlrcpp::Any visitCallExpr(RSIParser::CallExprContext *ctx) override {
		std::cout << "callExpr" << std::endl;
		CallStatement *tempStat = new CallStatement(&addrspace, &sys_ret_buffer);

		std::string call_id = ctx->ID()->getText();
		if(funcMap.find(call_id) != funcMap.end()) {
			tempStat->index = funcMap[call_id];
		}
		std::vector<int> *p = visit(ctx->params());
		tempStat->params = *p;

		return tempStat;
	}

	virtual antlrcpp::Any visitVariable(RSIParser::VariableContext *ctx) override {
		std::cout << "variable" << std::endl;

		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitCall(RSIParser::CallContext *ctx) override {
		std::cout << "call" << std::endl;

		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitParamlist(RSIParser::ParamlistContext *ctx) override {
		std::cout << "paramlist" << std::endl;

		std::vector<int> *tempParams = new std::vector<int>();

		antlrcpp::Any result = defaultResult();
	    size_t n = ctx->children.size();
	    for (size_t i = 0; i < n; i++) {
	        if (!shouldVisitNextChild(ctx, result)) {
	          break;
        	}
        	if(i%2 == 1) continue;  // skip ","
	        antlrcpp::Any childResult = ctx->children[i]->accept(this);
	        result = aggregateResult(result, childResult);
	        int index = result;
	        tempParams->push_back(index);
      	}

		return tempParams;
	}

	virtual antlrcpp::Any visitNum(RSIParser::NumContext *ctx) override {
		std::cout << "num" << std::endl;
		std::string strNum = ctx->NUM()->getText();
		return constIndexMap[strNum];
	}

	virtual antlrcpp::Any visitId(RSIParser::IdContext *ctx) override {
		std::cout << "id" << std::endl;
		std::string id = ctx->ID()->getText();

		return dataIndexMap[id];
	}
};


