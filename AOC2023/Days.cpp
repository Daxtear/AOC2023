#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "Days.h"
#include "Helpers.h"

using namespace std;

#pragma region day1

int Day1_1(vector<string>& lines) {
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

const string digits = "0123456789";
const string digitstrings[]{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int Day1_2(vector<string>& lines) {
	int sum = 0;
	for (string line : lines) {

		size_t firstindex = line.find_first_of(digits, 0);
		size_t firstnum = -1;

		if (firstindex != string::npos)
			firstnum = line[firstindex] - 48;

		size_t lastindex = line.find_last_of(digits, line.length() - 1);
		size_t lastnum = -1;

		if (lastindex == string::npos)
			lastindex = 0;
		else
			lastnum = line[lastindex] - 48;

		for (size_t a = 1; a < 10; ++a) {
			size_t s = line.find(digitstrings[a]);
			if (s < firstindex) {
				firstindex = s;
				firstnum = a;
			}

			s = line.rfind(digitstrings[a]);
			if (s != string::npos && s > lastindex) {
				lastindex = s;
				lastnum = a;
			}
		}
		string str = to_string(firstnum) + to_string(lastnum);
		cout << line + " - " + to_string(firstnum) + " " + to_string(lastnum) + "\r\n";
		sum += stoi(str);
	}
	return sum;
}

#pragma endregion day1
#pragma region day2
map<string, int> cubecounts = {
	{ "red", 12 },
	{ "green", 13 },
	{ "blue", 14 }
};

int Day2_1(vector<string>& lines) {
	int score = 0;
	for (string line : lines) {
		vector<string> segments;
		Split(line, ':', segments);
		vector<string> sets;
		Split(segments[1], ';', sets);
		vector<string> game;
		Split(segments[0], ' ', game);
		int gameID = stoi(game[1]);
		bool over = false;
		for (string set : sets) {
			if (over)
				break;
			vector<string> hands;
			Split(set, ',', hands);
			for (string hand : hands) {
				vector<string> seg2;
				Split(TrimCopy(hand), ' ', seg2);
				int count = stoi(seg2[0]);
				if (count > cubecounts[seg2[1]]) {
					over = true;
					break;
				}
			}
		}
		if (!over)
			score += gameID;
	}
	return score;
}

int Day2_2(vector<string>& lines) {
	int score = 0;
	for (string line : lines) {
		vector<string> segments;
		Split(line, ':', segments);
		vector<string> sets;
		Split(segments[1], ';', sets);
		map<string, int> counts = {
			{ "red", 0 },
			{ "green", 0 },
			{ "blue", 0 }
		};
		for (string set : sets) {
			vector<string> hands;
			Split(set, ',', hands);
			for (string hand : hands) {
				vector<string> seg2;
				Split(TrimCopy(hand), ' ', seg2);
				int count = stoi(seg2[0]);
				if (count > counts[seg2[1]])
					counts[seg2[1]] = count;
			}
		}
		score += counts["red"] * counts["green"] * counts["blue"];
	}
	return score;
}
#pragma endregion day2
#pragma region day3
int Day3_1(vector<string>& lines) {
	int sum = 0;
	for (int a = 0; a < lines.size(); ++a) {
		string prev;
		if (a > 0)
			prev = lines[a - 1];
		else {
			prev = "";
			for (char cha : lines[a]) {
				prev += '.';
			}
		}
		string line = lines[a];
		string next;
		if (a < lines.size() - 1)
			next = lines[a + 1];
		else {
			next = "";
			for (char cha : lines[a]) {
				next += '.';
			}
		}

		string currentnumber = "";
		bool adjacentToSymbol = false;

		for (int b = 0; b < line.length(); ++b) {
			char c = line[b];
			if (isdigit(c)) {
				currentnumber += c;
				if (b > 0) {
					if (!(isdigit(prev[b - 1]) || prev[b - 1] == '.') ||
						!(isdigit(line[b - 1]) || line[b - 1] == '.') ||
						!(isdigit(next[b - 1]) || next[b - 1] == '.')
						)
						adjacentToSymbol = true;
				}
				if (!(isdigit(prev[b]) || prev[b] == '.') ||
					!(isdigit(next[b]) || next[b] == '.')
					)
					adjacentToSymbol = true;
				if (b < line.length() - 1) {
					if (!(isdigit(prev[b + 1]) || prev[b + 1] == '.') ||
						!(isdigit(line[b + 1]) || line[b + 1] == '.') ||
						!(isdigit(next[b + 1]) || next[b + 1] == '.')
						)
						adjacentToSymbol = true;
				}
			}
			else {
				if (!currentnumber.empty()) {
					if (adjacentToSymbol)
						sum += stoi(currentnumber);
					adjacentToSymbol = false;
					currentnumber = "";
				}
			}
		}
		if (!currentnumber.empty() && adjacentToSymbol)
			sum += stoi(currentnumber);
	}
	return sum;
}

class day3gear {

public:

	int number1 = 0;
	int number2 = 0;

	bool over = false;

	bool operator==(const day3gear& other) const {
		return this == &other;
	}

	bool operator<(const day3gear& other) const {
		return this < &other;
	}

	bool operator>(const day3gear& other) const {
		return this > &other;
	}
};

struct ivec2 {

public:

	ivec2(int x, int y) {
		X = x;
		Y = y;
	}

	int X;
	int Y;

	bool operator==(const ivec2& other) const {
		return X == other.X && Y == other.Y;
	}

	bool operator<(const ivec2& other) const {
		if (Y < other.Y)
			return true;
		else if (Y == other.Y && X < other.X)
			return true;
		return false;
	}

	bool operator>(const ivec2& other) const {
		if (Y > other.Y)
			return true;
		else if (Y == other.Y && X > other.X)
			return true;
		return false;
	}

};

int Day3_2(vector<string>& lines) {
	int sum = 0;

	map<ivec2, day3gear> gears;

	auto addgear = [&](ivec2 vec, string value) {
		if (gears.count(vec) <= 0) {
			gears[vec] = day3gear();
		}

		int val = stoi(value);

		if (gears[vec].over)
			return;

		if (gears[vec].number1 > 0) {
			if (gears[vec].number2 > 0) {
				gears[vec].over = true;
			}
			else {
				gears[vec].number2 = stoi(value);
			}
		}
		else {
			gears[vec].number1 = stoi(value);
		}

		};

	for (int a = 0; a < lines.size(); ++a) {
		string prev;
		if (a > 0)
			prev = lines[a - 1];
		else {
			prev = "";
			for (char cha : lines[a]) {
				prev += '.';
			}
		}
		string line = lines[a];
		string next;
		if (a < lines.size() - 1)
			next = lines[a + 1];
		else {
			next = "";
			for (char cha : lines[a]) {
				next += '.';
			}
		}

		string currentnumber = "";
		vector<ivec2> gearlocations;

		auto checkAndAddLocation = [&](string& line, int x, int y) {
			if (line[x] == '*' && (gearlocations.empty() || find(gearlocations.begin(), gearlocations.end(), ivec2(x, y)) == gearlocations.end()))
				gearlocations.push_back(ivec2(x, y));
			};

		for (int b = 0; b < line.length(); ++b) {
			char c = line[b];
			if (isdigit(c)) {
				currentnumber += c;
				if (b > 0) {
					checkAndAddLocation(prev, b - 1, a - 1);
					checkAndAddLocation(line, b - 1, a);
					checkAndAddLocation(next, b - 1, a + 1);
				}

				checkAndAddLocation(prev, b, a - 1);
				checkAndAddLocation(next, b, a + 1);

				if (b < line.length() - 1) {
					checkAndAddLocation(prev, b + 1, a - 1);
					checkAndAddLocation(line, b + 1, a);
					checkAndAddLocation(next, b + 1, a + 1);
				}
			}
			else {
				if (!currentnumber.empty()) {

					for (auto loc : gearlocations) {
						addgear(loc, currentnumber);
					}

					currentnumber = "";
					gearlocations.clear();
				}
			}
		}
		if (!currentnumber.empty()) {

			for (auto loc : gearlocations) {
				addgear(loc, currentnumber);
			}
		}
	}
	for (auto gear : gears) {
		if (gear.second.number1 > 0 && gear.second.number2 > 0 && !gear.second.over)
			sum += gear.second.number1 * gear.second.number2;
	}

	return sum;
}

#pragma endregion day3
#pragma region day4
int Day4_1(vector<string>& lines) {
	int sum = 0;
	for (auto line : lines) {
		int linescore = 0;
		vector<string> segments;
		Split(line, ':', segments);

		vector<string> lists;
		Split(segments[1], '|', lists);

		vector<string> winning;
		Split(TrimCopy(lists[0]), ' ', winning);

		vector<string> numbers;
		Split(TrimCopy(lists[1]), ' ', numbers);

		for (auto number : numbers) {
			if (number.empty())
				continue;

			if (find(winning.begin(), winning.end(), number) != winning.end()) {
				if (linescore == 0)
					linescore = 1;
				else
					linescore *= 2;
			}
		}
		sum += linescore;
	}
	return sum;
}

int Day4_2(vector<string>& lines) {
	vector<int> counts(lines.size(), 1);
	for (int a = 0; a < lines.size(); ++a) {
		string line = lines[a];

		int wins = 0;
		vector<string> segments;
		Split(line, ':', segments);

		vector<string> lists;
		Split(segments[1], '|', lists);

		vector<string> winning;
		Split(TrimCopy(lists[0]), ' ', winning);

		vector<string> numbers;
		Split(TrimCopy(lists[1]), ' ', numbers);

		for (auto number : numbers) {
			if (number.empty())
				continue;

			if (find(winning.begin(), winning.end(), number) != winning.end()) {
				wins++;
				counts[a + wins] += counts[a];
			}
		}
	}
	return Sum(counts);
}
#pragma endregion day4
#pragma region day5

struct mapping {
public:
	long long SourceRangeStart;
	long long DestRangeStart;
	long long RangeLength;
	long long DestRangeEnd() {
		return DestRangeStart + RangeLength - 1;
	}
	long long SourceRangeEnd() {
		//cout << to_string(SourceRangeStart) + " " + to_string(SourceRangeStart + RangeLength - 1) + "\n";
		return SourceRangeStart + RangeLength - 1;
	}

	long long GetDest(long long in) {
		if (in <= SourceRangeStart || in > SourceRangeEnd())
			return in;
		return in - SourceRangeStart + DestRangeStart;
	}

	mapping(string input) {
		vector<string> segments;
		Split(TrimCopy(input), ' ', segments);
		SourceRangeStart = stoll(segments[1]);
		DestRangeStart = stoll(segments[0]);
		RangeLength = stoll(segments[2]);
	}

	bool operator<(const mapping& other) const {
		return SourceRangeStart < other.SourceRangeStart;
	}

	bool operator>(const mapping& other) const {
		return SourceRangeStart > other.SourceRangeStart;
	}

	bool operator==(const mapping& other) const {
		return SourceRangeStart == other.SourceRangeStart && RangeLength == other.RangeLength;
	}
};

class almanac {
public:

	vector<long long> Seeds;
	vector<mapping> Mappings[7];

	long long GetMapping(int level, long long source) {
		vector<mapping>::reverse_iterator mi = find_if(Mappings[level].rbegin(), Mappings[level].rend(), [&](mapping m) { return m.SourceRangeStart <= source; });
		if (mi == Mappings[level].rend()) {
			return source;
		}
		else {
			return mi->GetDest(source);
		}
	}

	almanac(vector<string>& input) {
		int mode = 0; // 0 = seed2soil; 1 = soil2fert; 2 = fert2water; 3 = water2light; 4 = light2temp; 5 = temp2hum; 6 = hum2loc
		for (int a = 0; a < input.size(); ++a) {
			if (a == 0) {
				vector<string> segments;
				Split(TrimCopy(input[a]), ':', segments);
				vector<string> seedstrings;
				Split(TrimCopy(segments[1]), ' ', seedstrings);
				for (string seed : seedstrings) {
					Seeds.push_back(stoll(seed));
				}
				a += 2;
				continue;
			}
			if (input[a].empty()) {
				sort(Mappings[mode].begin(), Mappings[mode].end());
				mode++;
				a++;
				continue;
			}
			mapping m = mapping(input[a]);
			Mappings[mode].push_back(m);
		}
		sort(Mappings[mode].begin(), Mappings[mode].end());
	}

};

long long Day5_1(vector<string>& lines) {
	almanac al = almanac(lines);
	vector<long long> seedLocs;

	for (long long seed : al.Seeds) {
		seedLocs.push_back(al.GetMapping(6, al.GetMapping(5, al.GetMapping(4, al.GetMapping(3, al.GetMapping(2, al.GetMapping(1, al.GetMapping(0, seed))))))));
	}

	return *min_element(seedLocs.begin(), seedLocs.end());
}

long long Day5_2(vector<string>& lines) {
	almanac al = almanac(lines);
	long long lowestloc = LLONG_MAX;

	for (long long a = 0; a < al.Seeds.size() / 2; ++a) {
		long long seedpos = a * 2;
		for (long long b = 0; b < al.Seeds[seedpos + 1]; ++b) {
			long long newloc = al.GetMapping(6, al.GetMapping(5, al.GetMapping(4, al.GetMapping(3, al.GetMapping(2, al.GetMapping(1, al.GetMapping(0, al.Seeds[seedpos] + b)))))));
			if (newloc < lowestloc)
				lowestloc = newloc;
		}
		cout << "seedloc: " + to_string(lowestloc) + "\n";
	}

	return lowestloc;
}

#pragma endregion day5

int Day6_1(vector<string>& lines) {

}

int Day6_2(vector<string>& lines) {

}