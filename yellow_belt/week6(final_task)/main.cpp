#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>

std::string ParseEvent(std::istream& is)
{
  std::string event;
  is >> std::ws;
  std::getline(is, event);
  return event;
}

template <typename K, typename V>
std::ostream& operator<< (std::ostream& os, std::pair<K, V> item)
{
  os << item.first << " " << item.second;
  return os;
}

void TestAll();

int main()
{
  TestAll();

  Database db;

  for (std::string line; std::getline(std::cin, line); )
  {
    std::istringstream is(line);

    std::string command;
    is >> command;
    if (command == "Add")
    {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    }
    else if (command == "Print")
    {
      db.Print(std::cout);
    }
    else if (command == "Del")
    {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const std::string& event) {return condition->Evaluate(date, event);};
      int count = db.RemoveIf(predicate);
      std::cout << "Removed " << count << " entries" << std::endl;
    }
    else if (command == "Find")
    {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const std::string& event) {return condition->Evaluate(date, event);};

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries)
      {
        std::cout << entry << std::endl;
      }
      std::cout << "Found " << entries.size() << " entries" << std::endl;
    }
    else if (command == "Last")
    {
      try
      {
        std::cout << db.Last(ParseDate(is)) << std::endl;
      }
      catch (std::invalid_argument&)
      {
        std::cout << "No entries" << std::endl;
      }
    }
    else if (command.empty())
    {
      continue;
    }
    else
    {
      throw std::logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

void TestParseEvent()
{
  {
    std::istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    std::istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    std::istringstream is("  first event  \n  second event");
    std::vector<std::string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, std::vector<std::string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll()
{
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}
