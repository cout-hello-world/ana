/* This anagram-solving program is placed in the public domain
 * by its author, Henry Elliott. */
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <cctype>

#include "enable.hpp"

std::multimap<std::string, std::string> get_words();
void clean(std::string &line);
void to_lower(std::string &line);
void semiclean(std::string &line);
void process(const std::string &line,
             const std::multimap<std::string, std::string> &words);
void print_intro();
void print_prompt();

int main()
{
	auto words = get_words();
	print_intro();
	print_prompt();
	for (std::string line; std::getline(std::cin, line);) {
		process(line, words);
		print_prompt();
	}
}

std::multimap<std::string, std::string> get_words()
{
	decltype(get_words()) words;
	for (int i = 0; i != ENABLE_SIZE; ++i) {
		std::string entry(enable[i]);
		std::string original(entry);
		clean(entry);
		words.insert(std::make_pair(entry, original));
	}
	return words;
}

void clean(std::string &line)
{
	semiclean(line);
	std::sort(line.begin(), line.end());
}

void semiclean(std::string &line)
{
	std::string::size_type line_number;
	while ((line_number = line.find_first_of("' -")) != std::string::npos) {
		line.erase(line_number, 1);
	}
	to_lower(line);
}

void to_lower(std::string &line)
{
	for (auto &ch : line) {
		ch = std::tolower(ch);
	}
}

void process(const std::string &line,
             const std::multimap<std::string, std::string> &words)
{
	std::string semiclean_copy(line);
	semiclean(semiclean_copy);
	std::string clean_copy(line);
	clean(clean_copy);
	bool displayed = false;
	auto range = words.equal_range(clean_copy);
	for (auto iter = range.first; iter != range.second; ++iter) {
		std::string anagram = iter->second;
		if (anagram != semiclean_copy) {
			if (!displayed) {
				std::cout << "Anagram(s) for \"" << line << "\":" << std::endl;
				displayed = true;
			}
			std::cout << anagram << std::endl;
		}

	}
	if (!displayed) {
		std::cout << "No anagrams found for \"" << line
				  << "\"." << std::endl;
	}
}

void print_prompt()
{
	std::cout << "Enter string: " << std::flush;
}
	

void print_intro()
{
	std::cout << "Anagram finder placed in the public domain by Henry Elliott."
	          << std::endl;
	std::cout << "This program uses the public domain ENABLE word list from:"
	          << std::endl;
	std::cout << "http://www.puzzlers.org/pub/wordlists/enable1.txt\n"
	          << std::endl;
}
