#include "rules.h"

class ForEachLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing For-Each loop...\n";
    }
};

class WhileLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing While loop...\n";
    }
};

class ParallelForLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Parallel-For loop...\n";
    }
};


class MatchLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Match loop...\n";
    }
};

class ExtendListRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Extend list...\n";
    }
};

class DiscardListRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Discard list...\n";
    }
};


class MessageOutputRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Message output...\n";
    }
};


class AssignmentRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Assignment...\n";
    }
};