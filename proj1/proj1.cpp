////////////////////////////////////////////
//  HW01: Word, Char, Num usage stats     //
//  Name: Simon Aizpurua                  //
//  Date: 5/27/16                         //
//  Prof: Bob Myers                       //
//  Term: Summer 2016                     //
////////////////////////////////////////////


#include <iostream>

#include <string>
#include <cctype>
#include <sstream>

#include <vector>
#include <map>
#include <algorithm>
#include <utility>

// Aliases
typedef std::pair<int, int> intpair;
typedef std::pair< std::string, intpair> str_intpair;

typedef std::map< std::string, intpair> mapSPi;
typedef std::map< std::string, int> mapSI;

// Functions to handle maps
void insertString1( mapSPi& map, const std::string& str );
int topN( const mapSPi& map );
void printMap(const mapSPi& map);

// void insertString( mapSI& map, const std::string& str );
bool cmp(const str_intpair& p1, const str_intpair& p2) {
  if (p1.second.second == p2.second.second)
    return p1.second < p2. second;
  else
    return p1.second.second > p2.second.second;
}

int main()
{
  // Creating map of characters, words, and number STRINGS
  // mapSI wordMap, numbMap, charMap;
  mapSPi wordMap1, numbMap1, charMap1;

  // Temporary char variable to hold char from stream
  char c;
  // int counter = 0;

  // Temporary string variables before they are pushed
  std::string word_str = "";
  std::string num_str = "";
  std::string temp = "";

  while(std::cin.get(c)) {
   /*  Map Loading Method 
        1. load char into a string we will 'push'
        2. send loaded string to map
        3. reset string
   */

   // Character Map
    temp += c;
    insertString1(charMap1, temp);
    temp.clear();

   // Word Map //
    // If true then put lowercase version of char into a 'loading' string
    if (isalpha(c)) {
      word_str.push_back(tolower(c));

     // If the next char in stream returns false then send our 'loaded' 
     // string to be inserted into our Map. Then clear string
      if (!isalpha(std::cin.peek())) {
        insertString1(wordMap1, word_str);
        word_str.clear();
      }
    }

   // Number Map -- Near identical implementation as wordMap
    if(c >= '0' && c <= '9') {
      num_str.push_back(c);
      if (std::cin.peek() < '0' || std::cin.peek() > '9') {
        // cout << num_str <<"\n";
        insertString1(numbMap1, num_str);
        num_str.clear();
      }
    }
  } // end of stream

  std::cout << "Total " << charMap1.size() << " different characters, " 
        << topN(charMap1) << " most used characters:\n";
  printMap(charMap1);

  std::cout << "Total " << wordMap1.size() << " different words, " 
        << topN(wordMap1) << " most used words:\n";
  printMap(wordMap1);

  std::cout << "Total " << numbMap1.size() << " different numbers, " 
        << topN(numbMap1) << " most used numbers:\n";
  printMap(numbMap1);



  return 0;
}

int topN( const mapSPi& map ) {
  return map.size() > 10? 10 : map.size();
}

// Sends a string to be inserted into a map
void insertString1( mapSPi & map, const std::string& str ) {
  if(map.find(str) != map.end())
    ++map[str].second;
  else {
    map.emplace(std::piecewise_construct,
                std::forward_as_tuple(str),
                std::forward_as_tuple(map.size(), 1));
  }
}
void printMap(const mapSPi& map) {
  unsigned counter = 0;
  std::vector<str_intpair> v;
  copy(map.begin(), map.end(), back_inserter(v));
  sort(v.begin(), v.end(), cmp);

  for (int i = 0; i < topN(map); ++i)
  {
    std::cout << "No. " << counter << ": " << v[i].first << "\t\t" 
                              << v[i].second.second << "\n";
      ++counter;
  }
  std::cout << "\n";

}


	






