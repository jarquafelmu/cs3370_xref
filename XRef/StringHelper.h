// Project: Analyze
// Name: Sam Terrazas
// File: StringHelper.h
// Created: 03/17/2019 9:36 PM
// Updated: 03/17/2019 10:07 PM
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

  static bool isSame( std::string str1, std::string str2 ) {
    // first makes sure that the two strings are of equal size. if not then they're not a match automatically
    // next uses the the std::equal to walk through each character of both strings and ensures that they are equal.
    return str1.size () == str2.size () && std::equal ( str1.begin (), str1.end (), str2.begin (), str2.end (),
      []( char& c1, char& c2 ) {
        return c1 == c2 || std::toupper (
          c1, std::locale ( "en_US.UTF8" ) ) == std::toupper (
          c2, std::locale ( "en_US.UTF8" ) );
      } );
  }

  static void lower( std::string& s ) { std::transform ( s.begin (), s.end (), s.begin (), tolower ); }

  static void upper( std::string& s ) { std::transform ( s.begin (), s.end (), s.begin (), toupper ); }
} STRING_HELPER {};
#endif // STRING_HELPER_H

/**
 * REFLECTION:
 *
 * So this project really stressed by understanding of using the stl. For a while now I
 * have been trying to use the STL as much as possible and modern programming practices
 * so it was nice to have a project that actually required those uses.
 *
 * I learned a ton about lambdas in c++ and how I can use them to my favor. Going forward
 * I will try to use the STL more often as it is really helpful in compressing a lot of
 * code.
 */
