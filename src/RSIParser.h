
// Generated from RSI.g by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"


using namespace antlr4;



class RSIParser : public Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, ASSIGN = 4, IF = 5, THEN = 6, ELSE = 7, 
    END_IF = 8, WHILE = 9, DO = 10, END_WHILE = 11, LOOP = 12, END_LOOP = 13, 
    ID = 14, NUM = 15, COMMENT = 16, SPACE = 17, OTHER = 18
  };

  enum {
    RuleProg = 0, RuleBlock = 1, RuleStat = 2, RuleAssignment = 3, RuleIf_stat = 4, 
    RuleElseif_stat = 5, RuleElse_stat = 6, RuleWhile_stat = 7, RuleLoop_stat = 8, 
    RuleCall_stat = 9, RuleExpr = 10, RuleParams = 11, RuleVar = 12
  };

  RSIParser(TokenStream *input);
  ~RSIParser();

  virtual std::string getGrammarFileName() const override;
  virtual const atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual dfa::Vocabulary& getVocabulary() const override;


  class ProgContext;
  class BlockContext;
  class StatContext;
  class AssignmentContext;
  class If_statContext;
  class Elseif_statContext;
  class Else_statContext;
  class While_statContext;
  class Loop_statContext;
  class Call_statContext;
  class ExprContext;
  class ParamsContext;
  class VarContext; 

  class ProgContext : public ParserRuleContext {
  public:
    ProgContext(ParserRuleContext *parent, size_t invokingState);
   
    ProgContext() : ParserRuleContext() { }
    void copyFrom(ProgContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class ProgramContext : public ProgContext {
  public:
    ProgramContext(ProgContext *ctx);

    BlockContext *block();
    tree::TerminalNode *EOF();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  ProgContext* prog();

  class BlockContext : public ParserRuleContext {
  public:
    BlockContext(ParserRuleContext *parent, size_t invokingState);
   
    BlockContext() : ParserRuleContext() { }
    void copyFrom(BlockContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class StatBlockContext : public BlockContext {
  public:
    StatBlockContext(BlockContext *ctx);

    std::vector<StatContext *> stat();
    StatContext* stat(size_t i);
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  BlockContext* block();

  class StatContext : public ParserRuleContext {
  public:
    StatContext(ParserRuleContext *parent, size_t invokingState);
   
    StatContext() : ParserRuleContext() { }
    void copyFrom(StatContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class IfStatContext : public StatContext {
  public:
    IfStatContext(StatContext *ctx);

    If_statContext *if_stat();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  class LoopStatContext : public StatContext {
  public:
    LoopStatContext(StatContext *ctx);

    Loop_statContext *loop_stat();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  class CallStatContext : public StatContext {
  public:
    CallStatContext(StatContext *ctx);

    Call_statContext *call_stat();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  class AssignStatContext : public StatContext {
  public:
    AssignStatContext(StatContext *ctx);

    AssignmentContext *assignment();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  class WhileStatContext : public StatContext {
  public:
    WhileStatContext(StatContext *ctx);

    While_statContext *while_stat();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  StatContext* stat();

  class AssignmentContext : public ParserRuleContext {
  public:
    AssignmentContext(ParserRuleContext *parent, size_t invokingState);
   
    AssignmentContext() : ParserRuleContext() { }
    void copyFrom(AssignmentContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class AssignExprContext : public AssignmentContext {
  public:
    AssignExprContext(AssignmentContext *ctx);

    tree::TerminalNode *ID();
    tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  AssignmentContext* assignment();

  class If_statContext : public ParserRuleContext {
  public:
    If_statContext(ParserRuleContext *parent, size_t invokingState);
   
    If_statContext() : ParserRuleContext() { }
    void copyFrom(If_statContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class IfExprContext : public If_statContext {
  public:
    IfExprContext(If_statContext *ctx);

    tree::TerminalNode *IF();
    ExprContext *expr();
    tree::TerminalNode *THEN();
    BlockContext *block();
    tree::TerminalNode *END_IF();
    std::vector<Elseif_statContext *> elseif_stat();
    Elseif_statContext* elseif_stat(size_t i);
    Else_statContext *else_stat();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  If_statContext* if_stat();

  class Elseif_statContext : public ParserRuleContext {
  public:
    Elseif_statContext(ParserRuleContext *parent, size_t invokingState);
   
    Elseif_statContext() : ParserRuleContext() { }
    void copyFrom(Elseif_statContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class ElseifExprContext : public Elseif_statContext {
  public:
    ElseifExprContext(Elseif_statContext *ctx);

    tree::TerminalNode *ELSE();
    tree::TerminalNode *IF();
    ExprContext *expr();
    tree::TerminalNode *THEN();
    BlockContext *block();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  Elseif_statContext* elseif_stat();

  class Else_statContext : public ParserRuleContext {
  public:
    Else_statContext(ParserRuleContext *parent, size_t invokingState);
   
    Else_statContext() : ParserRuleContext() { }
    void copyFrom(Else_statContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class ElseExprContext : public Else_statContext {
  public:
    ElseExprContext(Else_statContext *ctx);

    tree::TerminalNode *ELSE();
    BlockContext *block();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  Else_statContext* else_stat();

  class While_statContext : public ParserRuleContext {
  public:
    While_statContext(ParserRuleContext *parent, size_t invokingState);
   
    While_statContext() : ParserRuleContext() { }
    void copyFrom(While_statContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class WhileExprContext : public While_statContext {
  public:
    WhileExprContext(While_statContext *ctx);

    tree::TerminalNode *WHILE();
    ExprContext *expr();
    tree::TerminalNode *DO();
    BlockContext *block();
    tree::TerminalNode *END_WHILE();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  While_statContext* while_stat();

  class Loop_statContext : public ParserRuleContext {
  public:
    Loop_statContext(ParserRuleContext *parent, size_t invokingState);
   
    Loop_statContext() : ParserRuleContext() { }
    void copyFrom(Loop_statContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class LoopExprContext : public Loop_statContext {
  public:
    LoopExprContext(Loop_statContext *ctx);

    tree::TerminalNode *LOOP();
    VarContext *var();
    tree::TerminalNode *DO();
    BlockContext *block();
    tree::TerminalNode *END_LOOP();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  Loop_statContext* loop_stat();

  class Call_statContext : public ParserRuleContext {
  public:
    Call_statContext(ParserRuleContext *parent, size_t invokingState);
   
    Call_statContext() : ParserRuleContext() { }
    void copyFrom(Call_statContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class CallExprContext : public Call_statContext {
  public:
    CallExprContext(Call_statContext *ctx);

    tree::TerminalNode *ID();
    ParamsContext *params();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  Call_statContext* call_stat();

  class ExprContext : public ParserRuleContext {
  public:
    ExprContext(ParserRuleContext *parent, size_t invokingState);
   
    ExprContext() : ParserRuleContext() { }
    void copyFrom(ExprContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class CallContext : public ExprContext {
  public:
    CallContext(ExprContext *ctx);

    Call_statContext *call_stat();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  class VariableContext : public ExprContext {
  public:
    VariableContext(ExprContext *ctx);

    VarContext *var();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  ExprContext* expr();

  class ParamsContext : public ParserRuleContext {
  public:
    ParamsContext(ParserRuleContext *parent, size_t invokingState);
   
    ParamsContext() : ParserRuleContext() { }
    void copyFrom(ParamsContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class ParamlistContext : public ParamsContext {
  public:
    ParamlistContext(ParamsContext *ctx);

    std::vector<VarContext *> var();
    VarContext* var(size_t i);
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  ParamsContext* params();

  class VarContext : public ParserRuleContext {
  public:
    VarContext(ParserRuleContext *parent, size_t invokingState);
   
    VarContext() : ParserRuleContext() { }
    void copyFrom(VarContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class NumContext : public VarContext {
  public:
    NumContext(VarContext *ctx);

    tree::TerminalNode *NUM();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  class IdContext : public VarContext {
  public:
    IdContext(VarContext *ctx);

    tree::TerminalNode *ID();
    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  VarContext* var();


private:
  static std::vector<dfa::DFA> _decisionToDFA;
  static atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static dfa::Vocabulary _vocabulary;
  static atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

