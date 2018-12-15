#pragma once
#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>      /* std::transform */
#include <string>         /* not needed for Mac OSX */


class TextAnalysis { 
public:
  TextAnalysis() = default;  
  void add_word(const std::string&, size_t); // IMPLEMENT BELOW
  size_t countWord(const std::string&); // IMPLEMENT BELOW
  size_t countTwoWords(const std::string&, const std::string&); // IMPLEMENT BELOW
  
  void read_text(std::istream&, const std::string&); // ALREADY DONE
  
private:  
  std::unordered_map<std::string, std::vector<size_t> > wordtable; // hash table with key=word and value=vector of page numbers
};

// ALREADY DONE: BREAK A LINE INTO A LIST OF WORDS
// Courtesy of Martin Broadhurst -- http://www.martinbroadhurst.com/how-to-split-a-string-in-c.html
template <class Container>
void split(const std::string& str, Container& cont, const std::string& delims = " ") {
  std::size_t curr, prev = 0;
  curr = str.find_first_of(delims);
  
  while (curr != std::string::npos) {                   // largest possible unsigned number
    cont.push_back(str.substr(prev, curr - prev));
    prev = curr + 1;
    curr = str.find_first_of(delims, prev);
  }
  
  cont.push_back(str.substr(prev, curr - prev));
}

// ALREADY DONE: READ FROM A TEXT FILE LINE BY LINE
void TextAnalysis::read_text(std::istream& in, const std::string& ignore) {
  std::string line;
  
  for (size_t i = 1; getline(in, line, '\n'); i++) {
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    
    typedef std::list<std::string> container;
    container words;                          // split into container, dump ignore chars
    split<container>(line, words, ignore);
    
    typename container::const_iterator cit;
    for (cit = words.cbegin(); cit != words.cend(); ++cit) { add_word(*cit, i); }
  }
}

// TO DO
void TextAnalysis::add_word(const std::string& word, size_t line) {
  //try to find the word first. 
  std::unordered_map<std::string, std::vector<size_t>>::iterator search = wordtable.find(word);
  //if word does not exist, Initialize new key(word) in hashtable as null vector
  if(search == wordtable.end()){
    wordtable[word]= std::vector<size_t>();
  }
  //push line into the vector of key(word)
  wordtable[word].push_back(line);
}

// TO DO
size_t TextAnalysis::countWord(const std::string& word) {
  //find word
  std::unordered_map<std::string, std::vector<size_t>>::iterator search = wordtable.find(word);
  //return the size of the vector of the key (word) if word exists. Otherwise return 0 because there are 0 occurances
  if(search != wordtable.end())
    return search->second.size();
  return 0;
}

// TO DO
size_t TextAnalysis::countTwoWords(const std::string& word1, const std::string& word2) {
  // set up iterators to find both words
  std::unordered_map<std::string, std::vector<size_t>>::iterator word1It = wordtable.find(word1);
  std::unordered_map<std::string, std::vector<size_t>>::iterator word2It = wordtable.find(word2);
  // if either word does not exist, return the sum of their sizes. 
  if(word1It == wordtable.end() || word2It == wordtable.end())
    return countWord(word1)+countWord(word2);
  return 0;
}

