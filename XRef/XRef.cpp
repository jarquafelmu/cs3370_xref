// Project: XRef
// Name: Sam Terrazas
// File: XRef.cpp
// Created: 03/27/2019 6:22 PM
// Updated: 03/31/2019 8:21 AM
// 
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student, 
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class. 

#include "XRef.h"
#include <algorithm>
#include <regex>
#include <iostream>

using namespace std;

void XRef::process ( std::vector<std::string> const& data ) {
	regex const pattern ( R"([A-Za-z\-']+)" );
	// regex const pattern ( R"(\b[A-Za-z\-']+\b)" );
	size_t lineno { 1 };
	for ( auto const& item : data ) {
		for_each ( sregex_iterator ( item.begin (), item.end (), pattern ), sregex_iterator (), [&]( auto& match ) {
			auto word = match.str ();
			if ( word == "A" ) {
				cout << "'A' was found.";
			}
			if ( word == "a" ) {
				cout << "'a' was found.";
			}
			if ( word.length () > longest_key_ ) longest_key_ = word.length ();
			logWord ( word, lineno );
		} );
		++lineno;
	}
}

void XRef::logWord ( std::string const& word, size_t const lineno ) {
	auto const entry = references_.find ( word );
	if ( entry != references_.end () ) {
		handleEntry ( entry, lineno );
	}
	else {
		createEntry ( word, lineno );
	}
}

void XRef::createEntry ( std::string const& word, size_t const lineno ) { references_ [word] [lineno] = default_count_; }

void XRef::handleEntry ( std::map<string, map<size_t, size_t>>::iterator it, size_t const& lineno ) const {
	// second is a map, need to see if lineno is there, if so increment the value
	// if not insert a new start
	auto const entry_val = it->second.find ( lineno );
	if ( entry_val == it->second.end () ) { it->second [lineno] = default_count_; }
	else { entry_val->second++; }
}

auto XRef::display ( ostream& os ) -> void {
	for_each ( references_.begin (), references_.end (), [&]( auto& p ) {
		// os.width ( longest_key_ + 1 );
		// os << p.first;
		this->header(os, p.first, longest_key_ + 1);
		showReferences ( os, p.second );
	});
}

void XRef::showReferences ( ostream& os, map<size_t, size_t> map ) {
	auto const begin = map.begin ();
	auto const end = prev ( map.end (), 1 );
	auto count { 0 };
	for_each ( begin, end, [&]( auto &p ) {
		showReference ( os, p );
		os << ", ";
		if ( ++count % entity_wrap_ == 0 ) {
			os << endl;
			header(os, "", longest_key_ + 1);
		}
	});
	showReference ( os, *end );
	os << endl;
}

void XRef::showReference( ostream& os, pair<size_t, size_t> const& p ) { os << p.first << ":" << p.second; }

void XRef::header( ostream& os, string const& header, size_t const& width ) {
	os.width ( width );
	os.setf ( ios::left, ios::adjustfield );
	os << header << ": ";
}