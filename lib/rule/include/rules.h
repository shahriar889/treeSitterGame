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
private:
    virtual void executeImpl() = 0;
};

// Rule set
class ForEachLoopRule : public Rule{
    private:
        void executeImpl() override;
};

class WhileLoopRule : public Rule{
    private:
        void executeImpl() override;
};


class ParallelForLoopRule : public Rule{
    private:
        void executeImpl() override;
};

class MatchLoopRule : public Rule{
    private:
        void executeImpl() override;
};

class ExtendListRule : public Rule{
    private:
        void executeImpl() override;
};

class DiscardListRule : public Rule{
    private:
        void executeImpl() override;
};

class MessageOutputRule : public Rule{
    private:
        void executeImpl() override;
};

class AssignmentRule : public Rule{
    private:
        void executeImpl() override;
};
