#pragma once
#include <map>
#include <string>
#include <vector>

class XRef {
  size_t default_count_ = 1;
  std::map<std::string, std::map<size_t, size_t>> reference_ {};
  void logWord ( std::string const& word, size_t const lineno );
  void createEntry ( std::string const& word, size_t const lineno );
  void handleEntry ( std::map<std::string, std::map<unsigned, unsigned>>::iterator it, size_t const& lineno ) const;
public:
  XRef ();
  ~XRef ();
  void process( std::vector<std::string> const& data );
};

