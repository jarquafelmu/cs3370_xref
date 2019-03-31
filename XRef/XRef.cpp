#include "XRef.h"
#include <algorithm>
#include <regex>
#include <iostream>
#include <iomanip>

using namespace std;

void XRef::print(ostream& os, map<size_t, size_t>::iterator const it) {
	os << it->first << ":" << it->second;
}

void XRef::print ( ostream& os, map<size_t, size_t> map ) {
	auto const begin = map.begin ();
	auto const end = prev ( map.end (), 1 );
	auto count {0};
	for_each ( begin, end, [&]( const auto p ) {
		print ( os );
		os << ", ";
		if ( ++count % entity_wrap_ == 0 ) {
			os << endl;
			os.width ( longest_key_ + 1 );
			os << " ";
		};
	});
	print ( os, end );
}

auto XRef::print(ostream& os ) -> void {
	for_each ( reference_.begin (), reference_.end(), [&](const auto& p) {
		os.width ( longest_key_ + 1 );
		os << p->first;
		print ( os, p->second );
	});
}

void XRef::process( std::vector<std::string> const& data ) {
  regex const pattern ( R"(\b[A-Za-z\-']+\b)" );
  size_t lineno {1};
  for (auto const& item : data ) {
    for_each ( sregex_iterator ( item.begin (), item.end (), pattern ), sregex_iterator (), [&]( auto& match ) {
			auto word = match.str ();
			if ( word.length () > longest_key_ ) longest_key_ = word.length ();
      logWord ( word, lineno );
    });
    ++lineno;
  }
}

void XRef::logWord ( std::string const& word, size_t const lineno ) {
	auto const entry = reference_.find ( word );
	cout << "word: " << word << endl;
	if ( entry != reference_.end () ) {
		handleEntry ( entry, lineno );
		print ( cout, entry->second );
	}
	else {
		createEntry ( word, lineno );
		std::cout << "{" << lineno << ": " << default_count_ << "}" << endl;
	}
	cout << endl;
}

void XRef::createEntry(std::string const& word, size_t const lineno) {
  reference_ [word] [lineno] = default_count_;
}

void XRef::handleEntry( std::map<string, map<size_t, size_t>>::iterator it, size_t const& lineno ) const {
  // second is a map, need to see if lineno is there, if so increment the value
  // if not insert a new start
  auto const entry_val = it->second.find ( lineno );
  if ( entry_val == it->second.end () ) {
    it->second [lineno] = default_count_;
  }
  else {
    entry_val->second++;
  }
}

