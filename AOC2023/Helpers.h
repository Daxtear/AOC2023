#pragma once

#include <string>
#include <vector>

using namespace std;

void Split(string str, char seperator, vector<string>& segments);
void ReadFile(const char* filename, vector<string>& lines);

int Sum(vector<int> ints);
int Product(vector<int> ints);

void LTrim(std::string& s);
void RTrim(std::string& s);
void Trim(std::string& s);
std::string LTrimCopy(std::string s);
std::string RTrimCopy(std::string s);
std::string TrimCopy(std::string s);
std::string RemoveAll(std::string s, char c);