#include "rules.h"

class RuleFactory {
public:
    std::unique_ptr<Rule> create() {
        return createImpl();
    };
private:
    virtual std::unique_ptr<Rule> createImpl() = 0;
};