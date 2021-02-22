#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/// Split the text into the sentences using '.' as a delimiter
vector <string> split_text(const string& input) {
    vector <string> sentences;
    int start = 0, finish;
    finish = input.find('.', start);
    while (finish != -1) {
        string new_sentence;
        new_sentence = input.substr(start, (finish - start + 1));
        sentences.push_back(new_sentence);
        start = finish + 2;
        finish = input.find('.', start);
    }
    return sentences;
}

/// Uppercase the given word in the sentence
string word_to_upper(string sentence, const string& word) {
    int len = word.length();
    int start, finish;
    start = sentence.find(word);
    finish = start + len;
    while (start != -1) {
        for (int i = start; i <= finish; i++) {
            sentence[i] = toupper(sentence[i]);
        }
        start = sentence.find(word);
        finish = start + len;
    }
    return sentence;
}

/// Find vector of given words in the text, uppercase, and return the vector of edited sentences for every given word
vector <vector <string>> find_word(vector <string> &sentences, vector <string> &word_list) {
    vector <string> contain_word;
    vector <vector <string>> edited_sentences;

    for (const auto& word : word_list) {
        for (auto &sentence : sentences) {
            int marked = sentence.find(word);
            if (marked != -1) {
                string new_sentence = word_to_upper(sentence, word);
                contain_word.push_back(new_sentence);
            }
        }
        edited_sentences.push_back(contain_word);
        contain_word.clear();
    }

    return edited_sentences;
}

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("in.txt");
    fout.open("out.txt");

    string text;
    getline(fin, text);

    vector <string> sentences;
    sentences = split_text(text);

    int number;
    fin >> number;
    vector <string> word_list(number);
    for (int i = 0; i < number; i++) {
        fin >> word_list[i];
    }

    vector <vector <string>> edit_sentences = find_word(sentences, word_list);

    for (int i = 0; i < edit_sentences.size(); i++) {
        fout << edit_sentences[i].size() << '\n';
        for (int j = 0; j < edit_sentences[i].size(); j++) {
            fout << edit_sentences[i][j] << '\n';
        }
    }

    fin.close();
    fout.close();
}
