#include <iostream>
#include <string>
using namespace std;

int totalTests, stringLength, numberOfLetters;
char possibleLetters[100];
string knownAnswer;
string myGuess;
string judgeReply;
int position, letterNumber;

int main() {
  cin >> totalTests;
  int currentTest = 1;
  while (currentTest <= totalTests) {
    cin >> stringLength >> numberOfLetters;
    for (position = 0; position < numberOfLetters; position++) {
      cin >> possibleLetters[position];
    }

    knownAnswer = "";
    for (position = 0; position < stringLength; position++) {
      knownAnswer = knownAnswer + "_";
    }

    letterNumber = 0;
    int finished = 0;
    while (finished == 0) {
      myGuess = "";
      for (position = 0; position < stringLength; position++) {
        if (knownAnswer[position] == '_') {
          myGuess = myGuess + possibleLetters[letterNumber];
        } else {
          myGuess = myGuess + knownAnswer[position];
        }
      }

      cout << myGuess << endl;

      cin >> judgeReply;
      if (judgeReply == "CORRECT") {
        finished = 1;
      } else {
        for (position = 0; position < stringLength; position++) {
          if (judgeReply[position] == '_') {
          } else {
            knownAnswer[position] = judgeReply[position];
          }
        }
        letterNumber = letterNumber + 1;
      }
    }
    currentTest = currentTest + 1;
  }
  return 0;
}
