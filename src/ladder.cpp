#include "ladder.h"
#include <algorithm>
#include <fstream>
#include <set>
#include <vector>


void error(string word1, string word2, string msg) {
    cout << msg << "\'" << word1 << "\' and \'" << word2 << '\'' << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    // Tabulation approach on edit distance dynamic programming problem
    // Implementation learned from this vid: https://www.youtube.com/watch?v=fJaKO8FbDdo
    int n = str1.size(), m = str2.size();
    vector<int> previous(m+1, 0), current(m+1, 0);

    // Initialize base case: if str1 is empty, then edit distance to str2 is j, j = 0..m
    for (int j = 0; j <= m; ++j)
        previous[j] = j;

    for (int i = 1; i <= n; ++i) {
        current[0] = i;
        for (int j = 1; j <= m; ++j) {
            if (str1[i-1] == str2[j-1]) current[j] = previous[j-1];
            else current[j] = 1 + min(previous[j], min(current[j-1], previous[j-1]));
        }
        previous = current;
    }
    return previous[m] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    int length_distance = word1.size() - word2.size();
    length_distance = abs(length_distance);
    // Length distance > 1 implies word1 needs 2+ operation to connect to word2
    // so return false immediately;
    // else call edit_distance_within()
    return length_distance <= 1 ? edit_distance_within(word1, word2, 1) : false;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // Return empty ladder if start word == end word
    // or else an infinite loop might occur
    if (begin_word == end_word) {
        error(begin_word, end_word, "generate_word_ladder: Cannot perform word ladder search on ");
        return vector<string>();
    }
    vector<string> ladder, begin_ladder{begin_word};
    queue<vector<string>> ladder_queue;
    ladder_queue.push(begin_ladder);
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        ladder = ladder_queue.front();
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
    return vector<string>();  // Returns empty ladder if ladder from start to end word not found
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    for (string word; in >> word; )
        word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
        return;
    }
    cout << "Word ladder found: ";
    for (string word: ladder)
        cout << word << ' ';
    cout << '\n';
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
