#include "XRef.h"


XRef::XRef () {}


XRef::~XRef () {}

void XRef::process( std::vector<std::string> const& data ) {
  
}

void XRef::note( std::string const& word, size_t const lineno ) {
  auto entry = reference_.find ( word );
  if (entry != reference_.end ()) {
    // second is a map, need to see if lineno is there, if so increment the value
    // if not insert a new start
    auto const entry_val = entry->second.find ( lineno );
    if (entry_val == entry->second.end ()) {
      entry->second [lineno] = default_count_;
    }
    else {
      entry_val->second++;
    }
  }
}
