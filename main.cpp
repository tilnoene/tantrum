#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool is_alpha(char c){
  return !isalpha(c);
}

string remove_non_alpha(string text) {
  replace_if (text.begin(), text.end(), is_alpha, ' ');
  return text;
}

string lower(string text) {
  for (auto &c : text) {
    c = tolower(c);
  }

  return text;
}

vector<string> split(string text, char key) {
  vector<string> splitted_text;
  string word = "";
  for (auto &c : text+key) {
    if (c == key) {
      if (word != "") {
        splitted_text.push_back(word);
      }

      word = "";
      continue;
    }
    
    word += c;
  }

  return splitted_text;
}

vector<string> read_file(string path) {
  ifstream input(path);
  string line;
  vector<string> lines;

  while (getline(input, line)) {
    lines.push_back(line);
  }

  input.close();

  return lines;
}

vector<string> extract_words(string path_to_file) {
  vector<string> file_lines = read_file(path_to_file);
  vector<string> word_list;

  for (auto line : file_lines) {
    auto splitted_line = split(remove_non_alpha(line), ' ');
    word_list.insert(word_list.end(), splitted_line.begin(), splitted_line.end());
  }

  for (auto &word : word_list) {
    word = lower(word);
  }

  return word_list;
}

vector<string> remove_stop_words(vector<string> word_list) {
  vector<string> file_lines = read_file("stop_words.txt");
  vector<string> stop_words;
  vector<string> cleaned_word_list;

  for (auto line : file_lines) {
    auto splitted_line = split(line, ',');
    stop_words.insert(stop_words.end(), splitted_line.begin(), splitted_line.end());
  }

  sort(stop_words.begin(), stop_words.end());
  
  for (auto &word : word_list) {
    bool is_stop_word = binary_search(stop_words.begin(), stop_words.end(), word);

    if (!is_stop_word) {
      cleaned_word_list.push_back(word);
    }

  }

  return cleaned_word_list;
}

map<string, int> frequency(vector<string> word_list) {
  map<string, int> word_freqs;

  for (auto word : word_list) {
    word_freqs[word]++;
  }

  return word_freqs;
}

bool compare_word_frequency(pair<string, int> word1, pair<string, int> word2) {
  if (word2.second == word1.second) {
    return word1.first < word2.first;
  }

  return word1.second > word2.second;
}

vector<pair<string, int>> sort_by_frequency(map<string, int> word_frequency) {
  vector<pair<string, int>> frequencies;

  for (auto word_frequency : word_frequency) {
    frequencies.push_back(word_frequency);
  }

  sort(frequencies.begin(), frequencies.end(), compare_word_frequency); // falta ordenar pela frequencia

  return frequencies;
}

int main() {
  auto word_list = remove_stop_words(extract_words("pride_and_prejudice.txt"));
  
  auto ans = sort_by_frequency(frequency(word_list));

  for (auto word : ans) {
    cout << word.first << " - " << word.second << '\n';
  }

  return 0;
}
