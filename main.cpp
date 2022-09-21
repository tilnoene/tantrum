#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
#include "utils.cpp"

using namespace std;

vector<string> extract_words(string path_to_file) {
  assert(("I need a path to the file!", !path_to_file.empty()));

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
  assert(("I need a non-empty list of words!", !word_list.empty()));
  assert(("I need at least 25 words!", (int)word_list.size() >= 25));

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
  assert(("I need a non-empty list of words", !word_list.empty()));
  assert(("I need at least 25 non stop words!", (int)word_list.size() >= 25));
  
  map<string, int> word_freqs;

  for (auto word : word_list) {
    word_freqs[word]++;
  }

  return word_freqs;
}

vector<pair<string, int>> sort_by_frequency(map<string, int> word_frequency) {
  assert(("The word frequency dictionary cannot be empty!", !word_frequency.empty()));

  vector<pair<string, int>> frequencies;

  for (auto word_frequency : word_frequency) {
    frequencies.push_back(word_frequency);
  }

  sort(frequencies.begin(), frequencies.end(), compare_word_frequency); // falta ordenar pela frequencia

  return frequencies;
}

int main(int argc, char *argv[]) {
  assert(("Tantrum! I need a path to the file as an argument!", argc >= 2));
  assert(("Tantrum! I need only one argument - a path to a file", argc <= 2));
  
  auto word_list = remove_stop_words(extract_words(argv[1]));
  
  auto ans = sort_by_frequency(frequency(word_list));

  for (auto word : ans) {
    cout << word.first << " - " << word.second << '\n';
  }

  return 0;
}
