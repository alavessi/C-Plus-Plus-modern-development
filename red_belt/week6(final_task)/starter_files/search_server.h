#pragma once

#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <shared_mutex>
#include <future>

class InvertedIndex
{
public:
  void Add(const std::string& document);
  const std::vector<std::pair<size_t, size_t>>& Lookup(const std::string& word) const;
  size_t IdxDocument = 0;

private:
  std::unordered_map<std::string, std::vector<std::pair<size_t, size_t>>> index;
  std::vector<std::pair<size_t, size_t>> empty;
};

class SearchServer
{
public:
  SearchServer() = default;
  explicit SearchServer(std::istream& document_input);
  void UpdateDocumentBase(std::istream& document_input);
  void AddQueriesStream(std::istream& query_input, std::ostream& search_results_output);

private:
  void UpdateDocumentSingleThread(std::istream& document_input);
  void AddQueriesSingleThread(std::istream &query_input, std::ostream &search_results_output);
  inline size_t docs_size() const
  {
    return index.IdxDocument;
  }

  std::shared_mutex shm;
  InvertedIndex index;
  std::vector<std::future<void>> futures_add, futures_update;
};
