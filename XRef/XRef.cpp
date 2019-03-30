#include "XRef.h"
#include <algorithm>
#include <regex>

using namespace std;

XRef::XRef () {}


XRef::~XRef () {}

void XRef::process( std::vector<std::string> const& data ) {
  regex pattern ( R"(\b[A-Za-z\-']\b)" );
  size_t lineno {1};
  for (auto const& item : data ) {
    auto begin = sregex_iterator ( item.begin (), item.end (), pattern );
    auto end = sregex_iterator ();
    for_each ( begin, end, [&]( string& word ) { this->logWord ( word, lineno ); } );
    ++lineno;
  }
}

void XRef::logWord( std::string const& word, size_t const lineno ) {
   auto entry = reference_.find ( word );
   if (entry != reference_.end ()) {
     //handleEntry ( entry, lineno );
   } else {
     createEntry ( word, lineno );
   }
}

void XRef::createEntry(std::string const& word, size_t const lineno) {
  //map<size_t, size_t> m;
  //m [lineno] = default_count_;
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
