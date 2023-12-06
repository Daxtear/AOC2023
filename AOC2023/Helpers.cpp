#include <vector>
#include <fstream>

#include "Helpers.h"

void Split(string str, char separator, vector<string>& strings) {
	int startIndex = 0, endIndex = 0;
	for (int i = 0; i <= str.size(); i++) {

		// If we reached the end of the word or the end of the input.
		if (str[i] == separator || i == str.size()) {
			endIndex = i;
			if (endIndex != startIndex) {
				string temp;
				temp.append(str, startIndex, endIndex - startIndex);
				strings.push_back(temp);
			}
			startIndex = endIndex + 1;
		}
	}
	
}

void ReadFile(const char* filename, vector<string>& lines)
{
	lines.clear();
	ifstream file(filename);
	string s;
	while (getline(file, s))
		lines.push_back(s);
}

int Sum(vector<int> ints) {
	int sum = 0;
	for (int num : ints)
		sum += num;
	return sum;
}

int Product(vector<int> ints) {
	int pro = 1;
	for (int num : ints)
		pro *= num;
	return pro;
}

// trim from start (in place)
void LTrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
void RTrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
void Trim(std::string& s) {
	RTrim(s);
	LTrim(s);
}

// trim from start (copying)
std::string LTrimCopy(std::string s) {
	LTrim(s);
	return s;
}

// trim from end (copying)
std::string RTrimCopy(std::string s) {
	RTrim(s);
	return s;
}

// trim from both ends (copying)
std::string TrimCopy(std::string s) {
	Trim(s);
	return s;
}

std::string RemoveAll(std::string s, char c) {
	string str = "";
	for (char ch : s) {
		if (ch != c)
			str += ch;
	}
	return str;
}