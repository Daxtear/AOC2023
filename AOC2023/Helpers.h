#pragma once

#include <string>

using namespace std;

void Split(string str, char seperator, vector<string>& segments);
void ReadFile(const char* filename, vector<string>& lines);

void LTrim(std::string& s);
void RTrim(std::string& s);
void Trim(std::string& s);
std::string LTrimCopy(std::string s);
std::string RTrimCopy(std::string s);
std::string TrimCopy(std::string s);