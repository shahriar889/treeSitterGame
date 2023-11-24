#include "ruleFactories.h"

std::unique_ptr<Rule> ForEachLoopFactory::createImpl(std::vector<Expression> expressions)
{
  return std::make_unique<ForEachLoopRule>(expressions);
}

std::unique_ptr<Rule> WhileLoopFactory::createImpl(std::vector<Expression> expressions)
{
  return std::make_unique<WhileLoopRule>(expressions);
}

std::unique_ptr<Rule> ParallelForLoopFactory::createImpl(std::vector<Expression> expressions)
{
  return std::make_unique<ParallelForLoopRule>(expressions);
}

std::unique_ptr<Rule> MatchLoopFactory::createImpl(std::vector<Expression> expressions)
{
  return std::make_unique<MatchLoopRule>(expressions);
}

std::unique_ptr<Rule> ExtendListFactory::createImpl(std::vector<Expression> expressions)
{
  return std::make_unique<ExtendListRule>(expressions);
}

std::unique_ptr<Rule> DiscardListFactory::createImpl(std::vector<Expression> expressions)
{
  return std::make_unique<DiscardListRule>(expressions);
}

std::unique_ptr<Rule> MessageOutputRuleFactory::createImpl(std::vector<Expression> expressions)
{
  return std::make_unique<MessageOutputRule>(expressions);
}

std::unique_ptr<Rule> AssignmentRuleFactory::createImpl(std::vector<Expression> expressions)
{
  return std::make_unique<AssignmentRule>(expressions);
}
