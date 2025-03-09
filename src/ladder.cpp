#include "ladder.h"
#include <fstream>
#include <set>
#include <vector>


void error(string word1, string word2, string msg) {
    cout << "Cannot perform word ladder search on \'" << word1 << "\' and \'" << word2 << '\'' << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d);  // TODO

bool is_adjacent(const string& word1, const string& word2);  // TODO

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // TODO
    queue<string, vector<string>> ladder_queue;
    ladder_queue.push([begin_word]);
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (string word: word_list) {
            if is_adjacent(last_word, word) {
                if (word not in visited) {
                    visited.insert(word);
                    new_ladder = ladder;
                    new_ladder.push(word);
                    if (word == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return "no ladder found";
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    for (string word; in >> word; )
        word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (string word: ladder)
        cout << word << "->";
}

void verify_word_ladder();  // TODO

