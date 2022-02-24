#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const std::string& event) const
{
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const
{
    return compare(date, cmp_, date_);
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const std::string& event) :cmp_(cmp), event_(event) {} 

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const
{
    return compare(event, cmp_, event_);
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op, const std::shared_ptr<const Node>& left, const std::shared_ptr<const Node>& right) : op_(op), left_(left), right_(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const
{
    if (op_ == LogicalOperation::And)
    {
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    }
    else
    {
        return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    }
    
}