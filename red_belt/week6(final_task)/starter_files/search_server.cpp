#include "search_server.h"
#include "iterator_range.h"

#include <iterator>
#include <sstream>

std::vector<std::string> SplitIntoWords(const std::string& line)
{
  std::istringstream words_input(line);
  return {std::istream_iterator<std::string>(words_input), std::istream_iterator<std::string>()};
}

void SearchServer::UpdateDocumentSingleThread(std::istream& document_input)
{
  InvertedIndex new_index;

  for (std::string current_document; std::getline(document_input, current_document); )
  {
    new_index.Add(std::move(current_document));
  }

  std::unique_lock<std::shared_mutex> lock(shm);
  std::swap(index, new_index);
}

SearchServer::SearchServer(std::istream& document_input)
{
  //UpdateDocumentBase(document_input);
  UpdateDocumentSingleThread(document_input);
}

void SearchServer::UpdateDocumentBase(std::istream& document_input)
{
  futures_update.push_back(std::async(&SearchServer::UpdateDocumentSingleThread, this, std::ref(document_input)));
}

void SearchServer::AddQueriesSingleThread(std::istream &query_input, std::ostream &search_results_output)
{
  const size_t docs_size = docs_size();
  std::vector<std::pair<size_t, size_t>> docid_count(docs_size);
  for (std::string current_query; std::getline(query_input, current_query); )
  {
    {
      std::shared_lock<std::shared_mutex> lock(shm);
      std::fill(docid_count.begin(), docid_count.end(), std::make_pair(0, 0));
      {
        for (const std::string& word : SplitIntoWords(current_query))
        {
          for (const auto& [docid, freq] : index.Lookup(word))
          {
            docid_count[docid].first = docid;
            docid_count[docid].second += freq;
          }
        }
      }
    }

    auto middle = (docid_count.size() < 5) ? docid_count.end() : docid_count.begin() + 5;
    std::partial_sort(docid_count.begin(), middle, docid_count.end(), [] (std::pair<size_t, size_t> lhs, std::pair<size_t, size_t> rhs)
      {
        int64_t lhs_docid = lhs.first;
        auto lhs_hit_count = lhs.second;
        int64_t rhs_docid = rhs.first;
        auto rhs_hit_count = rhs.second;
        return std::make_pair(lhs_hit_count, -lhs_docid) > std::make_pair(rhs_hit_count, -rhs_docid);
      });

    search_results_output << current_query << ':';
    for (const auto& [docid, hitcount] : Head(docid_count, 5))
    {
      if (hitcount)
      {
        search_results_output << " {" << "docid: " << docid << ", " << "hitcount: " << hitcount << '}';
      }
    }
    search_results_output << "\n";
  }
}

void SearchServer::AddQueriesStream(std::istream& query_input, std::ostream& search_results_output)
{
  futures_add.push_back(std::async(&SearchServer::AddQueriesSingleThread, this, std::ref(query_input), std::ref(search_results_output)));
}

void InvertedIndex::Add(const std::string& document)
{
  std::unordered_map<std::string, size_t> words;
  for (const std::string& word : SplitIntoWords(document))
  {
    words[word]++;
  }
  for (const auto& [word, freq] : words)
  {
    index[word].push_back({IdxDocument, freq});
  }
  IdxDocument++;
}

const std::vector<std::pair<size_t, size_t>>& InvertedIndex::Lookup(const std::string& word) const
{
  auto it = index.find(word);
  if (it != index.end())
  {
    return it->second;
  }
  return empty;
}
