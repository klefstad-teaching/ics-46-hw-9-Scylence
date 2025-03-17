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
    int length_distance = abs((int)word1.size() - (int)word2.size());
    if (length_distance > 1) return false;  // Case 1: Length distance > 1 implies word1 needs 2+ operation to connect to word2
    if (length_distance == 0) {             // Case 2: Equal length. Compares word by word,
        int n = word1.size(), diff = 0;     // return True if word difference = 1, False otherwise
        for (int i = 0; i < n; ++i)
            if (word1[i] != word2[i] && ++diff > 1) return false;
        return diff <= 1;  // Return true if word1 == word2 or differs by 1 letter
    }
    // Case 3: Length distance = 1. Call edit_distance_within to check insertion/deletion neighbors
    return edit_distance_within(word1, word2, 1);
}

set<string> generate_neighbors(const string& word, const set<string>& word_list) {
    // Find all possible neighbors of word
    set<string> neighbors;
    int word_length = word.length();

    // Case 1: substitution
    for (int i = 0; i < word_length; ++i) {
        string temp = word;
        for (char c = 'a'; c <= 'z'; ++c) {
            if (c == temp[i]) continue;
            temp[i] = c;
            if (word_list.count(temp)) neighbors.insert(temp);
        }
    }

    // Case 2: insertion
    for (int i = 0; i <= word_length; ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            string temp = word.substr(0, i) + c + word.substr(i);
            if (word_list.count(temp)) neighbors.insert(temp);
        }
    }

    // Case 3: deletion
    for (int i = 0; i < word_length; ++i) {
        string temp = word.substr(0, i) + word.substr(i + 1);
        if (word_list.count(temp)) neighbors.insert(temp);
    }
    return neighbors;
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

        set<string> neighbors = generate_neighbors(last_word, word_list);

        // Process neighbors narrowed down from word_list
        for (const string& word: neighbors) {
            if (!visited.count(word)) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) return new_ladder;
                visited.insert(word);
                ladder_queue.push(new_ladder);
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
