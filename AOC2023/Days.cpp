#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

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

	ivec2() {
		X = 0;
		Y = 0;
	}

	ivec2(int x, int y) {
		X = x;
		Y = y;
	}

	int X;
	int Y;

	bool operator==(const ivec2& other) const {
		return X == other.X && Y == other.Y;
	}

	bool operator!=(const ivec2& other) const {
		return X != other.X || Y != other.Y;
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

	static ivec2 Left;
	static ivec2 Right;
	static ivec2 Up;
	static ivec2 Down;
};

ivec2 ivec2::Left = ivec2(-1, 0);
ivec2 ivec2::Right = ivec2(1, 0);
ivec2 ivec2::Up = ivec2(0, -1);
ivec2 ivec2::Down = ivec2(0, 1);

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
#pragma region day6

int Day6_1(vector<string>& lines) {
	vector<string> timesegments;
	vector<string> distsegments;
	Split(lines[0], ':', timesegments);
	Split(lines[1], ':', distsegments);
	vector<string> timestrings;
	vector<string> diststrings;
	Split(TrimCopy(timesegments[1]), ' ', timestrings);
	Split(TrimCopy(distsegments[1]), ' ', diststrings);

	vector<int> winningGames;
	for (int a = 0; a < timestrings.size(); ++a) {
		int time = stoi(timestrings[a]);
		int dist = stoi(diststrings[a]);

		int winstart = 0;
		int winend = time;

		for (int b = 0; b < time; ++b) {
			if (winstart == 0) {
				if ((time - b) * b > dist)
					winstart = b;
			}
			else {
				if ((time - b) * b <= dist) {
					winend = b;
					break;
				}
			}
		}
		winningGames.push_back(winend - winstart);
	}

	return Product(winningGames);
}

long long Day6_2(vector<string>& lines) {
	vector<string> timesegments;
	vector<string> distsegments;
	Split(lines[0], ':', timesegments);
	Split(lines[1], ':', distsegments);

	long long time = stoll(RemoveAll(timesegments[1], ' '));
	long long dist = stoll(RemoveAll(distsegments[1], ' '));

	long long winstart = 0;
	long long winend = time;

	for (long long b = 0; b < time; ++b) {
		if (winstart == 0) {
			if ((time - b) * b > dist)
				winstart = b;
		}
		else {
			if ((time - b) * b <= dist) {
				winend = b;
				break;
			}
		}
	}

	return winend - winstart;
}

#pragma endregion day6
#pragma region day7
vector<char> cardvalues {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
vector<char> cardvaluesJ {'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A' };

class hand {
public:
	int type = 0;
	int bid;
	string cards;
	int values[5];

	hand(string input, bool Jmode) {
		vector<string> segments;
		Split(input, ' ', segments);
		cards = segments[0];
		bid = stoi(segments[1]);
		map<char, int> chars;
		int maxcardcount = 0;
		int jCount = 0;

		for (int a = 0; a < 5; ++a) {
			if (chars.find(cards[a]) == chars.end())
				chars[cards[a]] = 1;
			else
				chars[cards[a]] += 1;

			if (chars[cards[a]] > maxcardcount)
				maxcardcount = chars[cards[a]];

			if (Jmode && cards[a] == 'J')
				jCount++;

			if (Jmode)
				values[a] = find(cardvaluesJ.begin(), cardvaluesJ.end(), cards[a]) - cardvaluesJ.begin();
			else
				values[a] = find(cardvalues.begin(), cardvalues.end(), cards[a]) - cardvalues.begin();
		}

		switch (chars.size()) {
		case 1:
			type = 6;
			break;
		case 2:
			if (jCount > 0)
				type = 6;
			else if (maxcardcount == 4)
				type = 5;
			else
				type = 4;
			break;
		case 3:
			if (jCount > 1 || (maxcardcount == 3 && jCount == 1))
				type = 5;
			else if (jCount == 1)
				type = 4;
			else if (maxcardcount == 3)
				type = 3;
			else
				type = 2;
			break;
		case 4:
			if (jCount > 0)
				type = 3;
			else
				type = 1;
			break;
		case 5:
			if (jCount > 0)
				type = 1;
			else
				type = 0;
			break;
		}

	}

	bool operator<(const hand& other) const {
		if (type != other.type)
			return type < other.type;

		for (int a = 0; a < 5; ++a) {
			if (values[a] == other.values[a])
				continue;
			return values[a] < other.values[a];
		}
		return false;
	}

	bool operator>(const hand& other) const {
		return !(*this < other) && !(*this == other);
	}

	bool operator==(const hand& other) const {
		return cards == other.cards;
	}
};


int Day7_1(vector<string>& lines) {
	vector<hand> hands;
	for (string line : lines) {
		hands.push_back(hand(line, false));
	}
	sort(hands.begin(), hands.end());
	int sum = 0;
	for (int a = 0; a < hands.size(); ++a) {
		sum += hands[a].bid * (a + 1);
	}
	return sum;
}

int Day7_2(vector<string>& lines) {
	vector<hand> hands;
	for (string line : lines) {
		hands.push_back(hand(line, true));
	}
	sort(hands.begin(), hands.end());
	int sum = 0;
	for (int a = 0; a < hands.size(); ++a) {
		cout << hands[a].cards + " " << hands[a].type << "\n";
		sum += hands[a].bid * (a + 1);
	}
	return sum;
}
#pragma endregion day7
#pragma region day8
int Day8_1(vector<string>& lines) {
	map<string, vector<string>> Maps;
	vector<int> directions;
	for (int a = 0; a < lines.size(); ++a) {
		if (a == 0) {
			for (char c : lines[a]) {
				if (c == 'L')
					directions.push_back(0);
				else
					directions.push_back(1);
			}
			a++;
			continue;
		}
		string line = RemoveAll(lines[a], ' ');
		line = RemoveAll(line, '(');
		line = RemoveAll(line, ')');
		vector<string> segments;
		Split(line, '=', segments);
		vector<string> destinations;
		Split(segments[1], ',', destinations);
		Maps[segments[0]] = destinations;
	}
	int step = 0;
	for (string source = "AAA"; source != "ZZZ"; ) {
		source = Maps[source][directions[step % directions.size()]];
		++step;
	}
	return step;
}

long long Day8_2(vector<string>& lines) {
	map<string, vector<string>> Maps;
	vector<int> directions;
	vector<string> sources;
	for (int a = 0; a < lines.size(); ++a) {
		if (a == 0) {
			for (char c : lines[a]) {
				if (c == 'L')
					directions.push_back(0);
				else
					directions.push_back(1);
			}
			a++;
			continue;
		}
		string line = RemoveAll(lines[a], ' ');
		line = RemoveAll(line, '(');
		line = RemoveAll(line, ')');
		vector<string> segments;
		Split(line, '=', segments);
		vector<string> destinations;
		Split(segments[1], ',', destinations);
		Maps[segments[0]] = destinations;
		if (segments[0][2] == 'A')
			sources.push_back(segments[0]);
	}
	long long step = 0;
	int steptest = -1;
	bool nonZ = false;
	bool dotest = step % directions.size() == steptest;
	vector<string> steptestdata;
	vector<long long> steptestrepeatstepdiff;
	vector<long long> steptestzloc;
	int steptestrepeatstepdiffcount = 0;
	long long maxinterval = -1;
	long long maxstart = -1;
	while (true) {

		dotest = step % directions.size() == steptest;

		if (step == directions.size()) {
			steptest = step % directions.size();
			cout << "steptest:";
			for (int a = 0; a < sources.size(); ++a) {
				cout << " " + sources[a];
			}
			cout << "\n";
		}
		else if (dotest) {
			for (int a = 0; a < sources.size(); ++a) {
				if (sources[a] == steptestdata[a] && steptestrepeatstepdiff[a] < 0) {
					steptestrepeatstepdiff[a] = step - directions.size();
					if (steptestrepeatstepdiff[a] > maxinterval) {
						maxinterval = steptestrepeatstepdiff[a];
						maxstart = steptestzloc[a] + directions.size();
					}
					steptestrepeatstepdiffcount++;
					cout << "source " + to_string(a) + " steptest repeat at step " + to_string(step) + " with offset " + to_string(steptestrepeatstepdiff[a]) + ". that is now " + to_string(steptestrepeatstepdiffcount) + "/" + to_string(steptestrepeatstepdiff.size()) + "\n";
					cout << "z loc inside: " + to_string(steptestzloc[a]) + "\n";
				}
			}
		}

		int zcount = 0;
		for (int a = 0; a < sources.size(); ++a) {
			if (step == directions.size()) {
				steptestdata.push_back(sources[a]);
				steptestrepeatstepdiff.push_back(-1);
				steptestzloc.push_back(-1);
			}

			sources[a] = Maps[sources[a]][directions[step % directions.size()]];
			if (sources[a][2] == 'Z') {
				zcount++;
				if (steptest >= 0 && steptestrepeatstepdiff[a] < 0) {
					steptestzloc[a] = step - directions.size();
				}
			}
		}

		if (steptestrepeatstepdiffcount == sources.size())
			break;

		++step;
	}

	step = maxstart;
	bool noZ = true;
	while (noZ) {
		step += maxinterval;
		noZ = false;
		long long internalstep = step - directions.size();
		for (int a = 0; a < steptestrepeatstepdiff.size(); ++a) {
			if (internalstep % steptestrepeatstepdiff[a] != steptestzloc[a]) {
				noZ = true;
				break;
			}
		}
	}

	return step + 1;
}
#pragma endregion day8
#pragma region day9
int Day9AddNextValue(vector<int>& values) {
	if (Sum(values) == 0) {
		values.push_back(0);
		return 0;
	}
	else {
		vector<int> nextvalues;
		for (int a = 1; a < values.size(); ++a) {
			nextvalues.push_back(values[a] - values[a - 1]);
		}
		return values[values.size() - 1] + Day9AddNextValue(nextvalues);
	}
}

int Day9AddPrevValue(vector<int>& values) {
	if (Sum(values) == 0) {
		values.push_back(0);
		return 0;
	}
	else {
		vector<int> nextvalues;
		for (int a = 1; a < values.size(); ++a) {
			nextvalues.push_back(values[a] - values[a - 1]);
		}
		return values[0] - Day9AddPrevValue(nextvalues);
	}
}

int Day9_1(vector<string>& lines) {
	int sum = 0;
	for (string line : lines) {
		vector<int> values;
		SplitToInt(line, ' ', values);
		sum += Day9AddNextValue(values);
	}
	return sum;
}

int Day9_2(vector<string>& lines) {
	int sum = 0;
	for (string line : lines) {
		vector<int> values;
		SplitToInt(line, ' ', values);
		sum += Day9AddPrevValue(values);
	}
	return sum;
}
#pragma endregion day9
#pragma region day10
ivec2 Day10GetOutDir(char c, ivec2 inDir) {
	switch (c) {
	case '|':
		if (inDir.Y < 0)
			return ivec2::Up;
		if (inDir.Y > 0)
			return ivec2::Down;
		break;
	case '-':
		if (inDir.X < 0)
			return ivec2::Left;
		if (inDir.X > 0)
			return ivec2::Right;
		break;
	case 'L':
		if (inDir.Y > 0)
			return ivec2::Right;
		if (inDir.X < 0)
			return ivec2::Up;
		break;
	case 'J':
		if (inDir.Y > 0)
			return ivec2::Left;
		if (inDir.X > 0)
			return ivec2::Up;
		break;
	case 'F':
		if (inDir.Y < 0)
			return ivec2::Right;
		if (inDir.X < 0)
			return ivec2::Down;
		break;
	case '7':
		if (inDir.Y < 0)
			return ivec2::Left;
		if (inDir.X > 0)
			return ivec2::Down;
		break;
	}
	return ivec2(0, 0);
}

int Day10_1(vector<string>& lines) {
	const int height = lines.size();
	const int width = lines[0].length();
	string pipemap = Combine(lines);
	const int totallength = pipemap.length();
	vector<int> distancemap = vector<int>(totallength, 0);
	const int startpos = find(pipemap.begin(), pipemap.end(), 'S') - pipemap.begin();
	distancemap[startpos] = -1;
	const int startx = startpos % width;
	const int starty = startpos / width;
	bool startl = startx > 0 && Day10GetOutDir(pipemap[startpos - 1], ivec2::Left) != ivec2(0, 0);
	bool startr = startx < width - 1 && Day10GetOutDir(pipemap[startpos + 1], ivec2::Right) != ivec2(0, 0);
	bool startu = starty > 0 && Day10GetOutDir(pipemap[startpos - width], ivec2::Up) != ivec2(0, 0);
	bool startd = starty < height - 1 && Day10GetOutDir(pipemap[startpos + width], ivec2::Down) != ivec2(0, 0);

	ivec2 next1;
	ivec2 next2;
	if (startl && startr) {
		pipemap[startpos] = '-';
		next1 = ivec2::Left;
		next2 = ivec2::Right;
	}
	else if (startu && startd) {
		pipemap[startpos] = '|';
		next1 = ivec2::Up;
		next2 = ivec2::Down;
	}
	else if (startl && startu) {
		pipemap[startpos] = 'J';
		next1 = ivec2::Left;
		next2 = ivec2::Up;
	}
	else if (startl && startd) {
		pipemap[startpos] = '7';
		next1 = ivec2::Left;
		next2 = ivec2::Down;
	}
	else if (startr && startu) {
		pipemap[startpos] = 'L';
		next1 = ivec2::Up;
		next2 = ivec2::Right;
	}
	else if (startr && startd) {
		pipemap[startpos] = 'F';
		next1 = ivec2::Down;
		next2 = ivec2::Right;
	}

	int a = 0;
	int pos1 = startpos;
	int pos2 = startpos;
	bool active1 = true;
	bool active2 = true;
	while (active1 || active2) {
		a++;
		if (active1) {
			pos1 = pos1 + width * next1.Y + next1.X;
			distancemap[pos1] = a;
			next1 = Day10GetOutDir(pipemap[pos1], next1);
		}
		if (active2) {
			pos2 = pos2 + width * next2.Y + next2.X;
			distancemap[pos2] = a;
			next2 = Day10GetOutDir(pipemap[pos2], next2);
		}

		active1 = distancemap[pos1 + width * next1.Y + next1.X] == 0;
		active2 = distancemap[pos2 + width * next2.Y + next2.X] == 0;
	}

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (x + y * width == startpos)
				cout << 'O';
			else if (distancemap[x + y * width] == a)
				cout << 'X';
			else if (distancemap[x + y * width] != 0)
				cout << pipemap[x + y * width];
			else
				cout << ' ';
		}
		cout << "\n";
	}

	return a;
}

int Day10_2(vector<string>& lines) {
	const int height = lines.size();
	const int width = lines[0].length();
	string pipemap = Combine(lines);
	const int totallength = pipemap.length();
	vector<int> distancemap = vector<int>(totallength, 0);
	const int startpos = find(pipemap.begin(), pipemap.end(), 'S') - pipemap.begin();
	distancemap[startpos] = -1;
	const int startx = startpos % width;
	const int starty = startpos / width;
	bool startl = startx > 0 && Day10GetOutDir(pipemap[startpos - 1], ivec2::Left) != ivec2(0, 0);
	bool startr = startx < width - 1 && Day10GetOutDir(pipemap[startpos + 1], ivec2::Right) != ivec2(0, 0);
	bool startu = starty > 0 && Day10GetOutDir(pipemap[startpos - width], ivec2::Up) != ivec2(0, 0);
	bool startd = starty < height - 1 && Day10GetOutDir(pipemap[startpos + width], ivec2::Down) != ivec2(0, 0);

	ivec2 next1;
	ivec2 next2;
	if (startl && startr) {
		pipemap[startpos] = '-';
		next1 = ivec2::Left;
		next2 = ivec2::Right;
	}
	else if (startu && startd) {
		pipemap[startpos] = '|';
		next1 = ivec2::Up;
		next2 = ivec2::Down;
	}
	else if (startl && startu) {
		pipemap[startpos] = 'J';
		next1 = ivec2::Left;
		next2 = ivec2::Up;
	}
	else if (startl && startd) {
		pipemap[startpos] = '7';
		next1 = ivec2::Left;
		next2 = ivec2::Down;
	}
	else if (startr && startu) {
		pipemap[startpos] = 'L';
		next1 = ivec2::Up;
		next2 = ivec2::Right;
	}
	else if (startr && startd) {
		pipemap[startpos] = 'F';
		next1 = ivec2::Down;
		next2 = ivec2::Right;
	}

	int a = 0;
	int pos1 = startpos;
	int pos2 = startpos;
	bool active1 = true;
	bool active2 = true;
	while (active1 || active2) {
		a++;
		if (active1) {
			pos1 = pos1 + width * next1.Y + next1.X;
			distancemap[pos1] = a;
			next1 = Day10GetOutDir(pipemap[pos1], next1);
		}
		if (active2) {
			pos2 = pos2 + width * next2.Y + next2.X;
			distancemap[pos2] = a;
			next2 = Day10GetOutDir(pipemap[pos2], next2);
		}

		active1 = distancemap[pos1 + width * next1.Y + next1.X] == 0;
		active2 = distancemap[pos2 + width * next2.Y + next2.X] == 0;
	}

	// 0 = free; 1 = blocked; 2 = starter; 3 = possibly enclosed; 4 = outside
	vector<int> gapmap = vector<int>(totallength * 9, 0);

	vector<ivec2> fieldsToDo;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (distancemap[x + y * width] > 0 || (startx == x && y == starty)) {
				switch (pipemap[x + y * width]) {
				case '|':
					gapmap[x * 3 + 1 + (y * 3 + 0) * width * 3] = 1;
					gapmap[x * 3 + 1 + (y * 3 + 1) * width * 3] = 1;
					gapmap[x * 3 + 1 + (y * 3 + 2) * width * 3] = 1;
					break;
				case '-':
					gapmap[x * 3 + 0 + (y * 3 + 1) * width * 3] = 1;
					gapmap[x * 3 + 1 + (y * 3 + 1) * width * 3] = 1;
					gapmap[x * 3 + 2 + (y * 3 + 1) * width * 3] = 1;
					break;
				case 'L':
					gapmap[x * 3 + 1 + (y * 3 + 0) * width * 3] = 1;
					gapmap[x * 3 + 1 + (y * 3 + 1) * width * 3] = 1;
					gapmap[x * 3 + 2 + (y * 3 + 1) * width * 3] = 1;
					break;
				case 'J':
					gapmap[x * 3 + 1 + (y * 3 + 0) * width * 3] = 1;
					gapmap[x * 3 + 1 + (y * 3 + 1) * width * 3] = 1;
					gapmap[x * 3 + 0 + (y * 3 + 1) * width * 3] = 1;
					break;
				case 'F':
					gapmap[x * 3 + 1 + (y * 3 + 2) * width * 3] = 1;
					gapmap[x * 3 + 1 + (y * 3 + 1) * width * 3] = 1;
					gapmap[x * 3 + 2 + (y * 3 + 1) * width * 3] = 1;
					break;
				case '7':
					gapmap[x * 3 + 1 + (y * 3 + 2) * width * 3] = 1;
					gapmap[x * 3 + 1 + (y * 3 + 1) * width * 3] = 1;
					gapmap[x * 3 + 0 + (y * 3 + 1) * width * 3] = 1;
					break;
				}
			}
			else {
				gapmap[x * 3 + 1 + (y * 3 + 1) * width * 3] = 3;
			}

			auto addStart = [&](int sx, int sy) {
				if (gapmap[sx + sy * width * 3] == 0) {
					gapmap[sx + sy * width * 3] = 2;
					fieldsToDo.push_back(ivec2(sx, sy));
				}
			};

			if (x == 0) {
				addStart(x * 3 + 0, y * 3 + 0);
				addStart(x * 3 + 0, y * 3 + 1);
				addStart(x * 3 + 0, y * 3 + 2);
			}
			if (x == width - 1) {
				addStart(x * 3 + 2, y * 3 + 0);
				addStart(x * 3 + 2, y * 3 + 1);
				addStart(x * 3 + 2, y * 3 + 2);
			}
			if (y == 0) {
				addStart(x * 3 + 0, y * 3 + 0);
				addStart(x * 3 + 1, y * 3 + 0);
				addStart(x * 3 + 2, y * 3 + 0);
			}
			if (y == height - 1) {
				addStart(x * 3 + 0, y * 3 + 2);
				addStart(x * 3 + 1, y * 3 + 2);
				addStart(x * 3 + 2, y * 3 + 2);
			}
		}
	}

	for (int y = 0; y < height * 3; ++y) {
		for (int x = 0; x < width * 3; ++x) {
			switch (gapmap[x + y * width * 3]) {
			case 0:
				cout << ' ';
				break;
			case 1:
				cout << 'X';
				break;
			case 4:
				cout << '.';
				break;
			default:
				cout << to_string(gapmap[x + y * width * 3]);
				break;
			}
		}
		cout << '\n';
	}

	while (fieldsToDo.size() > 0) {
		ivec2 field = fieldsToDo.back();
		fieldsToDo.pop_back();

		switch (gapmap[field.X + field.Y * width * 3]) {
		case 4:
		case 1:
			break;
		default:
			gapmap[field.X + field.Y * width * 3] = 4;
			if (field.X > 0)
				fieldsToDo.push_back(ivec2(field.X - 1, field.Y));
			if (field.X < width * 3 - 1)
				fieldsToDo.push_back(ivec2(field.X + 1, field.Y));
			if (field.Y > 0)
				fieldsToDo.push_back(ivec2(field.X, field.Y - 1));
			if (field.Y < height * 3 - 1)
				fieldsToDo.push_back(ivec2(field.X, field.Y + 1));
			break;
		}
	}

	for (int y = 0; y < height * 3; ++y) {
		for (int x = 0; x < width * 3; ++x) {
			switch (gapmap[x + y * width * 3]) {
			case 0:
				cout << ' ';
				break;
			case 1:
				cout << 'X';
				break;
			case 4:
				cout << '.';
				break;
			default:
				cout << to_string(gapmap[x + y * width * 3]);
				break;
			}
		}
		cout << '\n';
	}

	return count(gapmap.begin(),gapmap.end(),3);
}
#pragma endregion day10
#pragma region day11
template <typename T>
struct NonspecificPair {
public:
	T Value1;
	T Value2;

	NonspecificPair(T value1, T value2) {
		Value1 = value1;
		Value2 = value2;
	}

	bool operator==(const NonspecificPair& other) const {
		return (Value1 == other.Value1 && Value2 == other.Value2) || (Value1 == other.Value2 && Value2 == other.Value1);
	}

	bool operator<(const NonspecificPair& other) const {
		T minvalue = min(Value1, Value2);
		T otherminvalue = min(other.Value1, other.Value2);

		if (minvalue < otherminvalue)
			return true;
		else if (minvalue == otherminvalue) {
			T maxvalue = max(Value1, Value2);
			T othermaxvalue = max(other.Value1, other.Value2);
			if (maxvalue < othermaxvalue)
				return true;
		}

		return false;
	}

	bool operator<=(const NonspecificPair& other) const {
		return *this < other || *this == other;
	}

	bool operator>(const NonspecificPair& other) const {
		return !(*this <= other);
	}

	bool operator>=(const NonspecificPair& other) const {
		return *this > other || *this == other;
	}
};

class Chart {
public:

	string Data;

	long long Height;
	long long Width;

	Chart(vector<string> rows) {
		Data = Combine(rows);
		Height = rows.size();
		Width = rows[0].length();
	}

	string GetRow(long long row) {
		return Data.substr(row * Width, Width);
	}

	string GetColumn(long long column) {
		string str = "";
		for (long long a = 0; a < Height; ++a) {
			str += Data[column + a * Width];
		}
		return str;
	}

	void InsertRow(long long index, char initializer, int count = 1) {
		Data.insert(index * Width, Width * count, '.');
	}

	void InsertRow(long long index, string values, int count = 1) {
		for(int a = 0; a < count; ++a)
			Data = Data.insert(index * Width, values);
		Height += count;
	}

	void InsertColumn(long long index, char initializer, int count = 1) {
		string str = "";
		for (long long a = 0; a < Height; ++a) {
			str += initializer;
		}
		InsertColumn(index, str, count);
	}

	void InsertColumn(long long index, string values, int count = 1) {
		Width += count;
		for (long long a = 0; a < values.length(); ++a) {
			Data = Data.insert(index + a * Width, count, values[a]);
		}
	}

	char GetValue(long long x, long long y) {
		return Data[x + y * Width];
	}
};

ostream& operator<<(ostream& os, Chart& obj) {
	for (long long a = 0; a < obj.Height; ++a) {
		os << obj.GetRow(a) + '\n';
	}
	return os;
}

long long Day11_1(vector<string>& lines) {
	map<NonspecificPair<ivec2>, int> Distances;
	vector<ivec2> Galaxies;
	Chart chart = Chart(lines);

	for (int a = 0; a < chart.Height; ++a) {
		string row = chart.GetRow(a);
		if (row.find('#') == string::npos) {
			chart.InsertRow(a, '.');
			++a;
		}
	}

	for (int a = 0; a < chart.Width; ++a) {
		string col = chart.GetColumn(a);
		if (col.find('#') == string::npos) {
			chart.InsertColumn(a, '.');
			++a;
		}
		else {
			int gxid = col.find('#');
			while (gxid != string::npos) {
				Galaxies.push_back(ivec2(a,gxid));
				gxid = col.find('#',gxid + 1);
			}
		}
	}

	long long sum = 0;

	for (ivec2 galaxy : Galaxies) {
		for (ivec2 galaxy2 : Galaxies) {
			if (galaxy == galaxy2)
				continue;

			NonspecificPair<ivec2> pair = NonspecificPair<ivec2>(galaxy, galaxy2);

			if (Distances.find(pair) == Distances.end()) {
				int dist = abs(galaxy.X - galaxy2.X) + abs(galaxy.Y - galaxy2.Y);
				Distances[pair] == dist;
				sum += dist;
			}
		}
	}

	cout << chart;
	return sum;
}

long long Day11_2(vector<string>& lines) {
	map<NonspecificPair<ivec2>, int> Distances;
	vector<ivec2> Galaxies;
	Chart chart = Chart(lines);
	vector<int> emptycol;
	vector<int> emptyrow;

	for (int a = 0; a < chart.Height; ++a) {
		string row = chart.GetRow(a);
		if (row.find('#') == string::npos) {
			emptyrow.push_back(a);
		}
	}

	for (int a = 0; a < chart.Width; ++a) {
		string col = chart.GetColumn(a);
		if (col.find('#') == string::npos) {
			emptycol.push_back(a);
		}
		else {
			int gxid = col.find('#');
			while (gxid != string::npos) {
				Galaxies.push_back(ivec2(a + emptycol.size() * 999999, gxid + (emptyrow.size() - (find_if(emptyrow.rbegin(), emptyrow.rend(), [gxid](int i) { return i < gxid; }) - emptyrow.rbegin())) * 999999));
				gxid = col.find('#', gxid + 1);
			}
		}
	}

	long long sum = 0;

	for (ivec2 galaxy : Galaxies) {
		for (ivec2 galaxy2 : Galaxies) {
			if (galaxy == galaxy2)
				continue;

			NonspecificPair<ivec2> pair = NonspecificPair<ivec2>(galaxy, galaxy2);

			if (Distances.find(pair) == Distances.end()) {
				int dist = abs(galaxy.X - galaxy2.X) + abs(galaxy.Y - galaxy2.Y);
				Distances[pair] == dist;
				sum += dist;
			}
		}
	}

	cout << chart;
	return sum;
}
#pragma endregion day11

bool Day12Recurse(int& sum, vector<int>& numbers, int* numberend, int* numberp, string& line, int pos, char* c) {

	bool Last = numberp == numberend;
	int number = *numberp;
	int linesize = line.length();

	if (pos + number > linesize)
		return false;

	for (int a = 0; a < number; ++a) {
		if (*(c + a) == '.') {
			return true;
		}
	}

	if (!Last && (pos + number == linesize))
		return false;

	int nextdam = string::npos;
	char* nd = c + number;
	for (int a = pos + number; a < linesize; ++a, ++nd) {
		if (*nd == '#') {
			nextdam = a;
			break;
		}
	}

	if (nextdam == pos + number)
		return true;

	if (Last) {
		if(nextdam == string::npos)
			sum++;

		return true;
	}

	for (int a = number + 1; a < linesize - pos; ++a) {
		if (!Day12Recurse(sum, numbers, numberend, numberp + 1, line, a + pos, c+a))
			break;
		if (nextdam == a)
			break;
	}

	return true;
}

int Day12_1(vector<string>& lines) {
	int sum = 0;

	for (string line : lines) {
		vector<string> segments;
		Split(line, ' ', segments);
		vector<string> numberstrings;
		Split(segments[1], ',', numberstrings);
		vector<int> numbers;
		for (string str : numberstrings)
			numbers.push_back(stoi(str));
		
		int numbercount = numbers.size();

		for (int a = 0; a < segments[0].length(); ++a) {
			Day12Recurse(sum, numbers, &numbers.back(), &numbers.front(), segments[0], a, &segments[0][0]);
			if (segments[0][a] == '#')
				break;
		}
	}

	return sum;
}

int Day12_2(vector<string>& lines) {
	int sum = 0;

	for (string line : lines) {
		vector<string> segments;
		Split(line, ' ', segments);
		vector<string> numberstrings;
		Split(segments[1], ',', numberstrings);
		vector<int> numbers;
		string input = "";
		for (int a = 0; a < 5; ++a) {
			for (string str : numberstrings)
				numbers.push_back(stoi(str));
			input += segments[0];
			if (a != 4)
				input += '?';
		}

		int numbercount = numbers.size();

		char* c = &input[0];

		for (int a = 0; a < input.length(); ++a) {
			Day12Recurse(sum, numbers, &numbers.back(), &numbers.front(), input, a, c + a);
			if (*(c + a) == '#')
				break;
		}
		cout << input << " " << numbercount << "\n";
	}

	return sum;
}