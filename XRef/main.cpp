// Project: XRef
// Name: Sam Terrazas
// File: main.cpp
// Created: 03/27/2019 6:21 PM
// Updated: 04/02/2019 8:36 PM
// 
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student, 
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class. 

#include "XRef.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <filesystem>

void Read( std::istream& is, std::vector<std::string>& vec );

// done so that std::copy can ignore carriage returns and keep going until the istream fails
struct Line final {
	std::string line_data;

	// ReSharper disable once CppNonExplicitConversionOperator
	operator std::string() const { return line_data; }
};

std::istream& operator>>( std::istream& str, Line& data ) {
	std::getline ( str, data.line_data );
	return str;
}

int main( int argc, char** argv ) {
	std::vector<std::string> data;

	if ( argc > 1 ) {
		auto file = std::ifstream ( argv[1] );
		if ( !file ) {
			std::cout << "File not found. Please check your spelling and try again." << std::endl;
			return 1;
		}
		Read ( file, data );
	} else {
		std::cout << "Since no file was supplied, please supply the text which should be cross referenced below."
				<< std::endl;
		std::cout << "Press [Ctrl + Z] then [Enter] to finish typing:" << std::endl;
		Read ( std::cin, data );
	}

	if ( data.empty () ) {
		std::cout << "No information was received. Exiting." << std::endl;
		return 1;
	}

	auto ref = XRef ();
	ref.process ( data );
	std::cout << std::endl << ref << std::endl;

	return 0;
}

void Read( std::istream& is, std::vector<std::string>& vec ) {
	std::copy ( std::istream_iterator<Line> ( is ), std::istream_iterator<Line> (), std::back_inserter ( vec ) );
	is.clear ();
}
