////////////////////////////////////////////
//  HW01: Word, Char, Num usage stats   //
//  Name: Simon Aizpurua          //
//  Date: 5/27/16             //
//  Prof: Bob Myers             //
//  Term: Summer 2016           //
////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>
#include <utility>

using namespace std;

// Everything that works so far ////////////////////////

// Aliases
typedef pair<string, int> pair_strint;
typedef vector<pair_strint> vector_pair_strint;
typedef map<string, int> mapSI;
// typedef map<char, int> mapCI;

// Functions to work with maps
void insertString( mapSI& map, const string& str );
void insertChar( mapSI& map, const string& ch );


int topN( const mapSI & map );
void printMap( const mapSI& map);

////////////////////////////////////////////////////////
// Creating a functor
struct IntCmp {
    bool operator()(const pair_strint &lhs, const pair_strint &rhs) {
        return lhs.second > rhs.second;
    }
};


int main () {

  // Working
  mapSI wordMap, numbMap, charMap;

  // Temporary variables to handle input stream.
  char c;

  // Temporary string variables to hold word and number strings
  string word_str = ""; 
  string num_str = "";
  string temp = "";

  // While loop to read entire input
  while(cin.get(c)) {
    temp += c;
    insertChar(charMap, temp);
    temp.clear();

    if(isalpha(tolower(c))) {

      word_str.push_back(tolower(c));
      if(!isalpha(cin.peek())) {
        // cout << word_str <<"\n";
        insertString(wordMap, word_str);
        word_str.clear();
      }       
    }

    if(c >= '0' && c <= '9') {
      num_str.push_back(c);
      if (cin.peek() < '0' || cin.peek() > '9') {
        // cout << num_str <<"\n";
        insertString(numbMap, num_str);
        num_str.clear();
      }
    }
  }

  cout << "Total " << charMap.size() << " different characters, " << topN(charMap)
      << " most used characters:\n";

  printMap(charMap);


  cout << "Total " << wordMap.size() << " different words, " << topN(wordMap)
      << " most used words:\n";
  
  printMap(wordMap);
  cout << "Total " << numbMap.size() << " different numbers, " << topN(numbMap)
      << " most used numbers:\n";
  printMap(numbMap);


  cout << "\n";

  return 0;
}

int topN( const mapSI& map ) {
  return map.size() > 10? 10 : map.size();
}

void printMap( const mapSI& map) {
  unsigned counter = 0;
  vector< pair <string, int>> vpair;
  for(auto& it : map) {
    vpair.push_back(pair_strint (it.first, it.second));
  }

  // for(auto& it : vpair) {
  //  cout << it.first << "\t" << it.second << "\n";
  // }
  sort(vpair.begin(), vpair.end(), IntCmp());

  for (int i = 0; i < topN(map); ++i)
  {
    cout << "No. " << counter << ": " << vpair[i].first << "\t\t" << vpair[i].second << "\n";
      ++counter;
  }
  cout << "\n";
}


void insertString( mapSI& map, const string& str ) {
  if(map.find(str) != map.end())
    ++map[str];
  else
    map.insert ( pair_strint (str, 1));
}
void insertChar(mapSI & map, const string& ch) {
  if(map.find(ch) != map.end())
    ++map[ch];
  else
    map.insert ( pair_strint (ch, 1) );
}