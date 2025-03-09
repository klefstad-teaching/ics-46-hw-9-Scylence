#include "ladder.h"


void error(string word1, string word2, string msg);  // TODO

bool edit_distance_within(const std::string& str1, const std::string& str2, int d);  // TODO

bool is_adjacent(const string& word1, const string& word2);  // TODO

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);  // TODO

void load_words(set<string> & word_list, const string& file_name);  // TODO

void print_word_ladder(const vector<string>& ladder);  // TODO

void verify_word_ladder();  // TODO

