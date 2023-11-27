#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "stateManager.h"

struct Expression {
    Expression(std::string v) : value(v) {}
    std::string value;
};

std::vector<std::string> tokenizeExpression(Expression input);

class Rule {
public:
    void execute(std::shared_ptr<StateManager> states) {
        executeImpl(states);
    }
    bool isNested() {
        return isNestedImpl();
    }
    bool isDone() {
        return done;
    }
    void setDone() {
        done = true;
    }
    virtual ~Rule() = default;  

private: 
    virtual void executeImpl(std::shared_ptr<StateManager>) = 0;
    virtual bool isNestedImpl() = 0;
    bool done = false;
};

class PrimitiveRule : public Rule {
public:
    bool isNestedImpl() override {
        return false;
    }
private:
    void executeImpl(std::shared_ptr<StateManager>) override = 0;
};

class NestedRule: public Rule {
public:
    void setRules(std::vector<std::unique_ptr<Rule>> newRules) noexcept {
        rules = std::move(newRules);
    }
    bool isNestedImpl() override {
        return true;
    }
    
protected:
    std::vector<std::unique_ptr<Rule>> rules;
    
private:
    void executeImpl(std::shared_ptr<StateManager>) override = 0;
};

// Nested Rule set
class ForEachLoopRule final: public NestedRule{
public:
    ForEachLoopRule(std::vector<Expression> e) : expressions(e) { }   

private:
    void executeImpl(std::shared_ptr<StateManager>) override;
    std::vector<Expression> expressions;
};

class WhileLoopRule final: public NestedRule{
public:
    WhileLoopRule(std::vector<Expression> e) : expressions(e) { }   

private:
    void executeImpl(std::shared_ptr<StateManager>) override;
    std::vector<Expression> expressions;
};

class ParallelForLoopRule final: public NestedRule{
public:
    ParallelForLoopRule(std::vector<Expression> e) : expressions(e) { }   

private:
    void executeImpl(std::shared_ptr<StateManager>) override;
    std::vector<Expression> expressions;
};

class MatchLoopRule final: public PrimitiveRule{
public:
    MatchLoopRule(std::vector<Expression> e) : expressions(e) { }   

private:
    void executeImpl(std::shared_ptr<StateManager>) override;
    std::vector<Expression> expressions;
};

// Primitive Rule set
class ExtendListRule final: public PrimitiveRule{
public:
    ExtendListRule(std::vector<Expression> e) : expressions(e) { }   

private:
    void executeImpl(std::shared_ptr<StateManager>) override;
    std::vector<Expression> expressions;
};

class DiscardListRule final: public PrimitiveRule{
public:
    DiscardListRule(std::vector<Expression> e) : expressions(e) { }   

private:
    void executeImpl(std::shared_ptr<StateManager>) override;
    std::vector<Expression> expressions;
};

class MessageOutputRule final: public PrimitiveRule{
public:
    MessageOutputRule(std::vector<Expression> e) : expressions(e) { }   

private:
    void executeImpl(std::shared_ptr<StateManager>) override;
    std::vector<Expression> expressions;
};

class AssignmentRule final: public PrimitiveRule{
public:
    AssignmentRule(std::vector<Expression> e) : expressions(e) { }   

private:
    void executeImpl(std::shared_ptr<StateManager>) override;
    std::vector<Expression> expressions;
};
