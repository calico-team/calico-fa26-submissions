#include <iostream>
using namespace std;

int X[100005];
int Y[100005];
int Z[100005];
char direction[100005];

int main() {
  int totalTests;
  cin >> totalTests;
  for (int testNumber = 0; testNumber < totalTests; testNumber++) {
    int numberOfDrones;
    int numberOfNights;
    cin >> numberOfDrones >> numberOfNights;
    for (int drone = 0; drone < numberOfDrones; drone++) {
      cin >> X[drone] >> Y[drone] >> Z[drone] >> direction[drone];
    }

    int totalRain = 0;

    for (int night = 1; night <= numberOfNights; night++) {
      for (int drone = 0; drone < numberOfDrones; drone++) {
        int somebodyAbove = 0;
        for (int other = 0; other < numberOfDrones; other++) {
          if (other != drone) {
            if (X[other] == X[drone] && Y[other] == Y[drone]) {
              if (Z[other] > Z[drone]) {
                somebodyAbove = 1;
              }
            }
          }
        }
        if (somebodyAbove == 0) {
          totalRain = totalRain + 1;
        }
      }

      for (int drone = 0; drone < numberOfDrones; drone++) {
        if (direction[drone] == 'E') {
          X[drone] = X[drone] + 1;
        } else {
          Y[drone] = Y[drone] + 1;
        }
      }
    }

    cout << totalRain << endl;
  }
  return 0;
}
