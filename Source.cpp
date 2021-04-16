#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <sstream>

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
		for (size_t j = 0; j < group_strings[i].length(); j++)
		{
			if (group_strings[i][j] == '\n')
			{
				group_strings[i][j] = ' ';
			}
		}
	}
	return group_strings;
}

int main() {
	std::ifstream fileContents("input.txt");
	std::stringstream buffer;
	buffer << fileContents.rdbuf();
	std::string fileString = buffer.str();
	auto groupStrings = split_passports(fileString);
	int i;
}