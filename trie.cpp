//katya raman: 4803987

#include "trie.hpp"
#include <algorithm>
#include <cctype>
#include <stack>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;


Trie::Trie():end_of_word(false){
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    this->roots[i] = NULL;

  }
}


Trie::Trie(Trie const& other):end_of_word(other.end_of_word){
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (other.roots[i] != nullptr) {
      this->roots[i] = new Trie(*other.roots[i]);
    }
    else {
      this->roots[i] = nullptr; 

    }

  }

}


Trie::~Trie(){

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    delete this->roots[i];
   
  }
}



Trie& Trie::operator=(Trie const& other){
  if (this == &other) {
    return *this; 

  }

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    delete this->roots[i];

  }

  this->end_of_word = other.end_of_word;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (other.roots[i] != nullptr) {
      this->roots[i] = new Trie(*other.roots[i]);

    }
    else {
      this->roots[i] == nullptr; 
    }

  }
  return *this;
}



void Trie::insert(char const* const str){
  char currentChar = *str;
 
  if (str == NULL){ 
    return;
  }
  
  if (currentChar == '\0') { 
    this->end_of_word = true;
    return;

  }


  if (isalpha(currentChar)) {
    int currentIndex = tolower(currentChar) - 'a';
    if (this->roots[currentIndex] == nullptr) {
      this->roots[currentIndex] = new Trie();
      this->roots[currentIndex]->insert(str+1);
    }
    else {
      this->roots[currentIndex]->insert(str+1);
    }

  }
  else {
    this->insert(str+1);
  }

}


bool Trie::check(char const* const str) const{
  
  if (str == nullptr) {
    return false;
  }

  char currentChar = *str;
  
  if (currentChar == '\0') {
    return this->end_of_word; 
  }

  if (isalpha(currentChar)) {
    int currentIndex = tolower(currentChar) - 'a';
    if (this->roots[currentIndex] != nullptr) {
      return this->roots[currentIndex]->check(str+1);
    }
    else {
      return false;
    }

  }
  else {
    return this->check(str+1);
  }

}



char* Trie::firstWithPrefix(char const* const str,unsigned depth) const{
  char currentChar;                                                                                                                                                                                               
  string cleanedPrefix = "";
  string finalWord = "";
  Trie* current = const_cast<Trie*>(this);
  char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  if (str == NULL) {
    return NULL;
  }
  
  for (int i = 0; i < strlen(str); i++) {
    if (isalpha(str[i]) != 0) {                                                                                        
      cleanedPrefix += tolower(str[i]);
    }
  }
  

  if (cleanedPrefix.length() == 0 || strlen(str) == 0) {
    bool notEmpty = false; 

    for (int i = 0; i < ALPHABET_SIZE; i++) {
      if (current->roots[i] != nullptr) {
	notEmpty = true; 
        finalWord += letters[i];
        current = current->roots[i];
        i = -1;
        continue;

      }
      if (current->end_of_word == true && notEmpty == true) {
        char * cStringPointer = new char[finalWord.length()+1];

        for (int i = 0; i < finalWord.length(); i++) {
          cStringPointer[i] = finalWord[i];
        }
        cStringPointer[finalWord.length()] = '\0';
        return cStringPointer;

      }

    }
    return nullptr; 
  }
  
  for (int currentIndex = 0; currentIndex < cleanedPrefix.length(); currentIndex++) {
    currentChar = cleanedPrefix[currentIndex];
    int indexTrie = currentChar - 'a';

    if (current->roots[indexTrie] == nullptr) {
      return NULL;

    }

    if (cleanedPrefix[currentIndex+1] == '\0' || currentIndex == cleanedPrefix.length()-1) {
      finalWord += currentChar;
      current = current->roots[indexTrie];
      break;

    }

    else {
      finalWord += currentChar; 
      current = current->roots[indexTrie];

      continue;
    }
  }


  while (current->end_of_word != true ) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {

      currentChar = letters[i];
      int indexTrie = i;
    
      if (current->roots[i] != nullptr) {
	finalWord += currentChar;
	current = current->roots[indexTrie];
	if (current->end_of_word != true) {
	  break;
	}

      }	
      if (current->end_of_word == true) {
	break; 

      }
    
    }
  
  }
  
  char * cStringPointer = new char[finalWord.length()+1];

  for (int i = 0; i < finalWord.length(); i++) {
    cStringPointer[i] = finalWord[i]; 
  }
  cStringPointer[finalWord.length()] = '\0';
  return cStringPointer;
   
}




Trie load_trie(std::istream& is){
  Trie current;
  string input;
  string cleanedWord = ""; 


  while (getline(is, input)) {
    while (input.length() == 0) {
      getline(is,input);
    }
    
    for (int i = 0; i < input.length(); i++) {
      if (isalpha(input[i]) != 0) {
	cleanedWord += tolower(input[i]); 
      }

    }
    if (cleanedWord.length() != 0) {
      current.insert(cleanedWord.c_str());
      cleanedWord = "";
    }

  }
  return current; 
}



Trie load_trie(std::string filename){
  ifstream file;
  file.open(filename);

  Trie current = load_trie(file);

  file.close();
   
  return current;
}
