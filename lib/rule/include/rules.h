#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <iostream>

// Abstract Definition
class Rule {
    public:
        void execute() {
            executeImpl();
        }
        bool isNested() {
            return isNestedImpl();
        }
        virtual ~Rule() = default;  
    private: 
        virtual void executeImpl() = 0;
        virtual bool isNestedImpl() = 0;
};

class PrimitiveRule : public Rule {
    public:
        bool isNestedImpl() override {
            return false;
        }
    private:
        void executeImpl() override = 0;
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
    void executeImpl() override = 0;
};

// Nested Rule set
class ForEachLoopRule final: public NestedRule{
    void executeImpl() override;
};

class WhileLoopRule final: public NestedRule{
    void executeImpl() override;
};


class ParallelForLoopRule final: public NestedRule{
    void executeImpl() override;
};

class MatchLoopRule final: public PrimitiveRule{
    private:
        void executeImpl() override;
};

// Primitive Rule set
class ExtendListRule final: public PrimitiveRule{
    private:
        void executeImpl() override;
};

class DiscardListRule final: public PrimitiveRule{
    private:
        void executeImpl() override;
};

class MessageOutputRule final: public PrimitiveRule{
    private:
        void executeImpl() override;
};

class AssignmentRule final: public PrimitiveRule{
    private:
        void executeImpl() override;
};