#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>

int count_unique_characters(std::string input_string) {
	char* str = const_cast<char*>(input_string.c_str());
	int count = 0;

	for (int i = 0; i < strlen(str); i++) {
		bool appears = false;
		for (int j = 0; j < i; j++) {
			if (str[j] == str[i]) {
				appears = true;
				break;
			}
		}

		if (!appears) {
			count++;
		}
	}

	return count;
}

std::string remove_char_from_string(std::string string_to_clean, char character_to_remove) {
	string_to_clean.erase(std::remove(string_to_clean.begin(), string_to_clean.end(), character_to_remove), string_to_clean.end());
	return string_to_clean;
}

std::vector<std::string> split_groups(std::string const& input_string)
{
	std::vector<std::string> group_strings;
	std::regex re("[\r\n]{2,}");

	std::sregex_token_iterator
		begin(input_string.begin(), input_string.end(), re, -1),
		end;

	std::copy(begin, end, std::back_inserter(group_strings));
	return group_strings;
}

std::vector<std::string> parse_member_answers(std::string const& group_string) {
	std::vector<std::string> output_vector;
	boost::split(output_vector, group_string, boost::is_any_of("\n"));
	return output_vector;
}

int calculate_common_answers(std::vector<std::string> const& group_strings) {
	int count = 0;
	for (auto const& character : group_strings[0]) {
		int n = 1;
		for (auto const& member_string : group_strings) {
			auto character_position = member_string.find_first_of(character);
			if (character_position == std::string::npos) {
				n = 0;
				break;
			}
		}
		count += n;
		}
	return count;
}

int main() {
	int sumOfGroupCounts = 0;
	int part2sum = 0;
	std::ifstream fileContents("input.txt");
	std::stringstream buffer;
	buffer << fileContents.rdbuf();
	std::string fileString = buffer.str();
	auto groupStrings1 = split_groups(fileString);
	auto groupStrings2 = split_groups(fileString);
	// Cleanup the newline and space characters
	for (int i = 0; i < groupStrings1.size(); i++) {
		groupStrings1[i] = remove_char_from_string(groupStrings1[i], '\n');
		groupStrings1[i] = remove_char_from_string(groupStrings1[i], ' ');
	}
	for (int i = 0; i < groupStrings1.size(); i++) {
		sumOfGroupCounts += count_unique_characters(groupStrings1[i]);
	}
	std::cout << "Total count: " << sumOfGroupCounts << "\n";
	for (const auto& group : groupStrings2) {
		auto groupMembers = parse_member_answers(group);
		part2sum += calculate_common_answers(groupMembers);
	}
	std::cout << "Part 2 total: " << part2sum;

}