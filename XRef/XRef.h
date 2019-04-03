// Project: XRef
// Name: Sam Terrazas
// File: XRef.h
// Created: 03/27/2019 6:22 PM
// Updated: 04/02/2019 8:36 PM
// 
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student, 
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class. 

#ifndef XREF_H
#define XREF_H

#include <map>
#include <string>
#include <vector>
#include <ostream>
#include "StringHelper.h"

class XRef final {
	struct Comp final {
		bool operator()( const std::string& lhs, const std::string& rhs ) const {
			if ( STRING_HELPER.iequal ( lhs, rhs ) ) { return lhs < rhs; }
			return STRING_HELPER.lower ( lhs ) < STRING_HELPER.lower ( rhs );
		}
	};

	std::map<std::string, std::map<size_t, size_t>, Comp> references_ {};

	size_t starting_lineno_ { 1 };
	size_t default_count_ { 1 };
	size_t longest_key_ {};
	size_t entity_wrap_ { 9 };

	void logWord( std::string const& word, size_t lineno );
	void createEntry( std::string const& word, size_t lineno );
	void updateEntry( std::map<std::string, std::map<unsigned, unsigned>>::iterator it, size_t const& lineno ) const;

	void showReferences( std::ostream& os, std::map<size_t, size_t> map );
	static void showReference( std::ostream& os, std::pair<unsigned, unsigned> const& p );
	static void header( std::ostream& os, std::string const& header, size_t const& width );
public:
	auto display( std::ostream& os ) -> void;
	void process( std::vector<std::string> const& data );

	friend auto operator<<( std::ostream& os, XRef& obj ) -> std::ostream& {
		obj.display ( os );
		return os;
	}
};
#endif // XREF_H
