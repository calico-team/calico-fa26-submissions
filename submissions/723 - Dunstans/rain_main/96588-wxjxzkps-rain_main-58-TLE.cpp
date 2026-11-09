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
    long long numberOfNights;
    cin >> numberOfDrones >> numberOfNights;
    for (int drone = 0; drone < numberOfDrones; drone++) {
      cin >> X[drone] >> Y[drone] >> Z[drone] >> direction[drone];
    }

    long long totalRain = numberOfDrones * numberOfNights;

    for (int eastDrone = 0; eastDrone < numberOfDrones; eastDrone++) {
      if (direction[eastDrone] == 'E') {
        for (int northDrone = 0; northDrone < numberOfDrones; northDrone++) {
          if (direction[northDrone] == 'N') {
            int nightsToMeetX = X[northDrone] - X[eastDrone];
            int nightsToMeetY = Y[eastDrone] - Y[northDrone];
            if (nightsToMeetX == nightsToMeetY) {
              if (nightsToMeetX >= 1 && nightsToMeetX <= numberOfNights - 1) {
                totalRain = totalRain - 1;
              }
            }
          }
        }
      }
    }

    
    cout << totalRain << endl;
  }
  return 0;
}
