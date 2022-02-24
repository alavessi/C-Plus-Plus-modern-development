#pragma once

#include "date.h"

#include <string>
#include <memory>

enum class Comparison {Less, LessOrEqual, Greater, GreaterOrEqual, Equal, NotEqual};

class Node
{
public:
    virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

template<class T>
bool compare(const T& other, const Comparison& cmp, const T& item)
{
    switch (cmp)
    {
    case Comparison::Less:
        return other < item;
        break;
    case Comparison::LessOrEqual:
        return !(item < other);
        break;
    case Comparison::Greater:
        return item < other;
        break;
    case Comparison::GreaterOrEqual:
        return !(other < item);
        break;
    case Comparison::Equal:
        return other == item;
        break;
    case Comparison::NotEqual:
        return !(other == item);
        break;
    default:
        return false;
        break;
    }
}

class EmptyNode: public Node
{
public:
    bool Evaluate(const Date& date, const std::string& event) const override;
};

class DateComparisonNode: public Node
{
public:
    DateComparisonNode(const Comparison& cmp, const Date& date);
    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    Comparison cmp_;
    Date date_;
};
 
class EventComparisonNode: public Node
{
public:
    EventComparisonNode(const Comparison& cmp, const std::string& event);
    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    Comparison cmp_;
    std::string event_;
};

enum class LogicalOperation {Or, And};

class LogicalOperationNode: public Node
{
public:
    LogicalOperationNode(const LogicalOperation& op, const std::shared_ptr<const Node>& left, const std::shared_ptr<const Node>& right);
    bool Evaluate(const Date& date, const std::string& event) const override; 

private:
    LogicalOperation op_;
    std::shared_ptr<const Node> left_, right_;
};