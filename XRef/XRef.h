#pragma once
#include <map>
#include <string>
#include <vector>
#include <ostream>

class XRef {
	auto filter = []( auto const& key1, auto const& key2 ) {
		if 
	}

	std::map < std::string, std::map<size_t, size_t>,  > reference_ {};

  size_t default_count_ = 1;
	size_t longest_key_ {};
	size_t entity_wrap_ { 9 };

	static void print ( std::ostream& os, std::map<size_t, size_t>::iterator it );
	void print ( std::ostream& os, std::map<size_t, size_t> map );

  void logWord ( std::string const& word, size_t lineno );
  void createEntry ( std::string const& word, size_t lineno );
  void handleEntry ( std::map<std::string, std::map<unsigned, unsigned>>::iterator it, size_t const& lineno ) const;
public:
	auto print ( std::ostream& os ) -> void;
  void process( std::vector<std::string> const& data );

  friend auto operator<<( std::ostream& os, XRef const& obj ) -> std::ostream& {
    return os
      << "default_count_: " << obj.default_count_ << std::endl
      << "reference_: " << std::endl
      << "size: " << obj.reference_.size () << std::endl;
      
  }
};

