// Project: XRef
// Name: Sam Terrazas
// File: main.cpp
// Created: 03/27/2019 6:21 PM
// Updated: 03/27/2019 6:21 PM
// 
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student, 
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class. 


#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include "XRef.h"
#include <fstream>
#include <algorithm>
#include <iterator>
#include <filesystem>

void Read ( std::istream& is, std::vector<std::string>& vec );
struct Line final {
  std::string line_data;

  operator std::string () const {
    return line_data;
  }
};
std::istream& operator>> (std::istream& str, Line& data) {
  std::getline ( str, data.line_data );
  return str;
}

int main (int argc, char** argv) {
  // process file giving by cin arguments
  // if no argument, process cin

  // process the input file 'Strings.txt' once.
  // for each line of the file, extract all word like tokens, which are words containing 
  // the following: only letters, hyphens, and apostrophes; no numerals.

  // tokens are sorted by alphabet and not by case
  // put output on cout and in a file

  // with using proper containers and algorithms the code could be as little as ~56 lines of code
  auto ref = XRef ();
  std::vector<std::string> data;

  if (argc > 1) {
    auto file = std::ifstream ( argv [1] );
    if (!file) {
      std::cout << "File not found. Please check your spelling and try again." << std::endl;
      return 1;
    }
    Read ( file, data );
  } else {
    std::cout << "Since no file was supplied, please supply the text which should be cross referenced below." << std::endl;
    std::cout << "Finish your entry by pressing `Ctrl+Z` and then 'Enter':" << std::endl;
    Read ( std::cin, data );
  }

  if ( data.empty () ) {
    std::cout << "No information was received. Exiting." << std::endl;
    return 1;
  }

  std::cout << std::endl << "Information received: " << std::endl;
  for( auto& item : data) {
    std::cout << item << std::endl;
  }

  ref.process ( data );

  return 0;
}

void Read ( std::istream& is, std::vector<std::string>& vec ) {
  // while (is) {
  //   std::string input;
  //   std::getline ( is, input );
  //   vec.push_back ( input );
  // }

  std::copy ( std::istream_iterator<Line> ( is ), std::istream_iterator<Line> ( ), std::back_inserter ( vec ) );
  is.clear ();
}