//
//  main.cpp
//  antlr4-cpp-demo
//
//  Created by Mike Lischke on 13.03.16.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

#include "antlr4-runtime.h"
#include "RSILexer.h"
#include "RSIParser.h"
#include "RSIVisitor.h"
#include "RSIBaseVisitor.h"
#include "RSICodeGenerator.h"
#include "RSIExecutor.h"

using namespace antlr4;
using namespace antlr4::tree;


std::unordered_map<std::string, int> dataIndexMap;   // parser xml file and generator dataMap; var --> index
std::unordered_map<int, std::string> rdataIndexMap;   // index --> var

std::unordered_map<std::string, int> constIndexMap;   // the index of all the constants in addr space 

std::unordered_set<std::string> fbMap;       // parser xml file and generator functionblock map

std::unordered_map<std::string, int> funcMap;       // all library function map to check if designated function is existed

std::vector<IValue> addrspace;     // RSI address space --- simple version

IValue sys_ret_buffer;         // return value buffer of all the sys function


void init(){
  addrspace.push_back(1);
  addrspace.push_back(2);

  dataIndexMap.insert(std::pair<std::string, int>("A", 0));
  dataIndexMap.insert(std::pair<std::string, int>("B", 1));

  for(int i = 0; i < RSI_LIB_SIZE; i ++) {
    funcMap.insert(std::pair<std::string, int>(libEntry[i].name, i));
  }

  for(auto elem : dataIndexMap) {
    rdataIndexMap.insert(std::pair<int, std::string>(elem.second, elem.first));
  }

}


int main(int , const char **) {
  std::ifstream infile("rsi.code");

  init();                     // parse xml file, build symbol table
  for(auto elem : dataIndexMap) {
    std::cout << elem.first << " : " << addrspace[elem.second] << std::endl;
  }

  ANTLRInputStream input(infile);
  RSILexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  RSIParser parser(&tokens);
  ParseTree *tree = parser.prog();

  RSIBaseVisitor vi;          // first time, build constant table
  vi.visit(tree);

  RSICodeGenerator CG;        // second time, generate execute model
  CG.visit(tree);

  std::cout << tree->toStringTree(&parser) << std::endl;

  RSIExecutor app(CodeShadow);
  app.execute();

  // for(auto elem : dataIndexMap) {
  //   std::cout << elem.first << " : " << addrspace[elem.second] << std::endl;
  // }

  // for(auto e : addrspace) {
  //   std::cout << e << std::endl;
  // }


  return 0;
}
