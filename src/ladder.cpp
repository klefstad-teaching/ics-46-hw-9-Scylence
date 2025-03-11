#include "ladder.h"
#include <fstream>
#include <set>
#include <vector>


void error(string word1, string word2, string msg) {
    cout << msg << "\'" << word1 << "\' and \'" << word2 << '\'' << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d);  // TODO

bool is_adjacent(const string& word1, const string& word2);  // TODO

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // TODO
    vector<string> ladder, begin_ladder{begin_word};
    if (begin_word == end_word) {
        error(begin_word, end_word, "generate_word_ladder: Cannot perform word ladder search on ");
        return ladder;
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push(begin_ladder);
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        ladder.push_back(ladder_queue.front());
        ladder_queue.pop();
        string last_word = ladder.back();
        for (string word: word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.count(word) == 0) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    error(begin_word, end_word, "generate_word_ladder: No ladder found for ");
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

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}

