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
  assert(("The path to the file cannot be empty!", !path.empty()));

  try {
    ifstream input(path);
    string line;
    vector<string> lines;

    while (getline(input, line)) {
      lines.push_back(line);
    }

    input.close();

    return lines;
  } catch (int errorNumber) {
    throw runtime_error("The file you are tryng to open does not exist!");
  }
}

bool compare_word_frequency(pair<string, int> word1, pair<string, int> word2) {
  assert(("None of the words can be empty!", !word1.first.empty() || !word2.first.empty()));
  assert(("The word has to appear at least one time!", word1.second != 0 || word2.second != 0));

  if (word2.second == word1.second) {
    return word1.first < word2.first;
  }

  return word1.second > word2.second;
}
