#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <pthread.h>

using namespace std;

#define NUMTHREADS 4
#define NUMOFFILES 2
#define NUMOFSCHAR 14
string targetWordG;


vector<char> specialCharacters = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '=', '+', '_'};


void checkWord(string* s1, string* s2) {
  //cout << *s1 << endl;
  if (*s1 == *s2) {

    cout << "Found Password!";
    ofstream outfile;
    outfile.open("Results.txt", std::ios_base::app);
    outfile << "Found!\n";
    outfile.close();
    exit(0);
  }
}

void checkSpecialChar(string* workingString, string* targetWord) {
  string workingTemp;
  for(char specialCharacter : specialCharacters){
            workingTemp = *workingString + specialCharacter;
            checkWord(&workingTemp, targetWord);
          }
}


void *pThreadEvaluateMask(void *mask) {
  string workingString;
  string targetWord = targetWordG;
  string getLineTemp = *(string*)mask;

  checkWord(&getLineTemp, &targetWord);
  for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++) {
        //run check here -- guesing ages
          workingString = getLineTemp + to_string(i) + to_string(j);
          checkWord(&workingString, &targetWord);
          checkSpecialChar(&workingString, &targetWord);
          workingString[0] = toupper(workingString[0]);
          checkWord(&workingString, &targetWord);
          checkSpecialChar(&workingString, &targetWord);
          for(int k = 0; k < 10; k++){
           for(int g = 0; g < 10; g++){
             //run check here -- guesing dates
              workingString = getLineTemp + to_string(i) + to_string(j) + to_string(k) + to_string(g);
              checkWord(&workingString, &targetWord);
              checkSpecialChar(&workingString, &targetWord);
              workingString[0] = tolower(workingString[0]);
              checkWord(&workingString, &targetWord);
              checkSpecialChar(&workingString, &targetWord);
            }
          }
        }
      }
}

int main(int argc, char *argv[]){
  pthread_t threadArray[NUMTHREADS];
  string FileNames[NUMOFFILES+1];
  FileNames[0] ="names.txt";
  FileNames[1] = "common.txt";
  FileNames[2] = "MostCommonPasswords.txt";
  string getLineTemp[4];
  ifstream fileDictionary;

  string test = argv[1];
  targetWordG = test;
  if (targetWordG.back() == '\n'){
      targetWordG.pop_back();
  }
  cout << "looking for: " << targetWordG << endl;
  //rainbow attack
  fileDictionary.open(FileNames[2]);
  while(getline(fileDictionary, getLineTemp[0])){
    checkWord(&getLineTemp[0], &targetWordG);
  }

  //uses common names and then common words
  for (auto & FileName : FileNames){
    fileDictionary.open(FileName);
    while(getline(fileDictionary, getLineTemp[0])) {
      pthread_create(&threadArray[0], nullptr, pThreadEvaluateMask, &getLineTemp[0]);
      for (int j= 1; j < NUMTHREADS; j++){
        if (getline(fileDictionary, getLineTemp[j])){
          getline(fileDictionary, getLineTemp[j]);
          pthread_create(&threadArray[j], nullptr, pThreadEvaluateMask, &getLineTemp[j]);
        }
      }
      for (unsigned long j : threadArray){
        pthread_join(j, nullptr);
      }
    }
    fileDictionary.close();
  }

  cout << "Falled";

return 0;
}
