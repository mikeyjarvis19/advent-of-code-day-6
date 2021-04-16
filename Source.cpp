#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <algorithm>

std::string remove_char_from_string(std::string string_to_clean, char character_to_remove) {
	string_to_clean.erase(std::remove(string_to_clean.begin(), string_to_clean.end(), character_to_remove), string_to_clean.end());
	return string_to_clean;
}

std::vector<std::string> split_passports(std::string const& input_string)
{
	std::vector<std::string> group_strings;
	std::regex re("[\r\n]{2,}");

	std::sregex_token_iterator
		begin(input_string.begin(), input_string.end(), re, -1),
		end;

	std::copy(begin, end, std::back_inserter(group_strings));

	// Cleanup the newlines and replace with space character for consistency
	for (int i = 0; i < group_strings.size(); i++) {
		group_strings[i] = remove_char_from_string(group_strings[i], '\n');
		group_strings[i] = remove_char_from_string(group_strings[i], ' ');
	}
	return group_strings;
}

int count_distinct_characters(std::string const& input_string) {
	return 1;
}

int main() {
	std::ifstream fileContents("input.txt");
	std::stringstream buffer;
	buffer << fileContents.rdbuf();
	std::string fileString = buffer.str();
	auto groupStrings = split_passports(fileString);
	int i;
}