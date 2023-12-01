#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "Days.h"

using namespace std;

int Day1_1(list<string>& lines) {
    int sum = 0;
    for (string line : lines) {
        string str = "";
        char ctemp = 'a';
        for (char c : line) {
            if (isdigit(c)) {
                if (ctemp == 'a')
                    str += c;
                ctemp = c;
            }
        }
        str += ctemp;
        sum += stoi(str);
    }
    return sum;
}