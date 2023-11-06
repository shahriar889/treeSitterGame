#include "ruleFactories.h"

std::unique_ptr<Rule> ForEachLoopFactory::createImpl()
{
  return std::make_unique<ForEachLoopRule>();
}

std::unique_ptr<Rule> WhileLoopFactory::createImpl()
{
  return std::make_unique<WhileLoopRule>();
}

std::unique_ptr<Rule> ParallelForLoopFactory::createImpl()
{
  return std::make_unique<ParallelForLoopRule>();
}

std::unique_ptr<Rule> MatchLoopFactory::createImpl()
{
  return std::make_unique<MatchLoopRule>();
}

std::unique_ptr<Rule> ExtendListFactory::createImpl()
{
  return std::make_unique<ExtendListRule>();
}

std::unique_ptr<Rule> DiscardListFactory::createImpl()
{
  return std::make_unique<DiscardListRule>();
}

std::unique_ptr<Rule> MessageOutputRuleFactory::createImpl()
{
  return std::make_unique<MessageOutputRule>();
}

std::unique_ptr<Rule> AssignmentRuleFactory::createImpl()
{
  return std::make_unique<AssignmentRule>();
}
