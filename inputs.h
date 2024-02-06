#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
inline vector<string> splitInput(const string& input, char separator = ' ');
inline vector<string> splitInput(const string& input, char separator) {
	vector<string> tokens;
	istringstream stream(input);
	string result;

	while (getline(stream, result, separator))
	{
		tokens.push_back(result);
	}

	return tokens;
}