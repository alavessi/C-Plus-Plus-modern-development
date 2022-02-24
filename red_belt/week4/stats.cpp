#include "stats.h"

Stats::Stats()
{
  MethodStats["GET"] = MethodStats["POST"] = MethodStats["PUT"] = MethodStats["DELETE"] = MethodStats["UNKNOWN"] = 0;
  UriStats["/"] = UriStats["/order"] = UriStats["/product"] = UriStats["/basket"] = UriStats["/help"] = UriStats["unknown"] = 0;
}

void Stats::AddMethod(std::string_view method)
{
  if (method == "GET" || method == "POST" || method == "PUT" || method == "DELETE")
  {
    MethodStats[method]++;
  }
  else
  {
    MethodStats["UNKNOWN"]++;
  }
}

void Stats::AddUri(std::string_view uri)
{
  if (uri == "/" || uri == "/order" || uri == "/product" || uri == "/basket" || uri == "/help")
  {
    UriStats[uri]++;
  }
  else
  {
    UriStats["unknown"]++;
  }
}

const std::map<std::string_view, int>& Stats::GetMethodStats() const
{
  return MethodStats;
}

const std::map<std::string_view, int>& Stats::GetUriStats() const
{
  return UriStats;
}

HttpRequest ParseRequest(std::string_view line)
{
  size_t space = line.find(' ');
  while (line[space] == line.front())
  {
    line.remove_prefix(space + 1);
    space = line.find(' ');
  }
  std::string_view method = line.substr(0, space);
  line.remove_prefix(space + 1);
  space = line.find(' ');
  std::string_view uri = line.substr(0, space);
  line.remove_prefix(space + 1);
  std::string_view protocol = line;
  return {method, uri, protocol};
}
