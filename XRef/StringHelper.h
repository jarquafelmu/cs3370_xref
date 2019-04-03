// Project: XRef
// Name: Sam Terrazas
// File: StringHelper.h
// Created: 03/31/2019 8:03 AM
// Updated: 03/31/2019 8:21 AM
// 
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student, 
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class. 

#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <string>
#include <algorithm>
#include <locale>
#include <regex>

inline class StringHelper final {

public:
	static std::string trim( const std::string str, const std::string& matcher, const std::string& replacer ) {
		std::regex const r ( matcher );
		std::string result;
		std::regex_replace ( std::back_inserter ( result ), str.begin (), str.end (), r, replacer );
		return result;
	}

	static std::string trim( std::string s ) {
		// start at the beginning and keep iterating until a location that is not a whitespace character is found
		auto const wsfront {
			std::find_if_not ( s.begin (), s.end (), []( int const c ) {
				return std::isspace ( c, std::locale ( "en_US.UTF8" ) );
			} )
		};

		// start at the end and keep iterating until a location that is not a whitespace character is found
		auto const wsback {
			std::find_if_not ( s.rbegin (), s.rend (), []( int const c ) {
				return std::isspace ( c, std::locale ( "en_US.UTF8" ) );
			} ).base ()
		};

		// create a new string with the new beginning and new end that doesn't include the whitespace characters
		// otherwise create a blank string
		auto result { wsback <= wsfront ? std::string () : std::string ( wsfront, wsback ) };

		return result;
	}

	static bool iequal( std::string str1, std::string str2 ) {
		// first makes sure that the two strings are of equal size. if not then they're not a match automatically
		// next uses the the std::equal to walk through each character of both strings and ensures that they are equal.
		return str1.size () == str2.size () && std::equal ( str1.begin (), str1.end (), str2.begin (), str2.end (),
			[]( char& c1, char& c2 ) {
				return c1 == c2 || std::tolower (
					c1, std::locale ( "en_US.UTF8" ) ) == std::tolower (
					c2, std::locale ( "en_US.UTF8" ) );
			} );
	}

	static std::string lower ( std::string s ) {
		std::transform ( s.begin (), s.end (), s.begin (), tolower ); 
		return s;
	}

	static std::string upper( std::string s ) { 
		std::transform ( s.begin (), s.end (), s.begin (), toupper ); 
		return s;
	}
} STRING_HELPER {};
#endif // STRING_HELPER_H
