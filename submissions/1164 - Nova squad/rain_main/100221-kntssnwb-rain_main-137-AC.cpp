#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>

using namespace std;

int main() {

    int testCases;
    scanf("%d", &testCases);

    while (testCases--) {

        int numberOfPoints;
        long long distanceLimit;

        scanf("%d %lld", &numberOfPoints, &distanceLimit);

        vector<pair<long long, long long>> eastboundPoints;
        vector<pair<long long, long long>> northboundPoints;

        eastboundPoints.reserve(numberOfPoints);
        northboundPoints.reserve(numberOfPoints);

        for (int pointIndex = 0;
             pointIndex < numberOfPoints;
             pointIndex++) {

            long long xCoordinate, yCoordinate, zCoordinate;
            char direction;

            scanf("%lld %lld %lld %c",
                  &xCoordinate,
                  &yCoordinate,
                  &zCoordinate,
                  &direction);

            if (direction == 'E') {

                eastboundPoints.push_back({
                    xCoordinate + yCoordinate,
                    xCoordinate
                });

            }
            else {

                northboundPoints.push_back({
                    xCoordinate + yCoordinate,
                    xCoordinate
                });
            }
        }

        sort(
            eastboundPoints.begin(),
            eastboundPoints.end()
        );

        long long intersectingPairs = 0;

        for (const auto& northboundPoint : northboundPoints) {

            long long coordinateSum = northboundPoint.first;
            long long northboundX = northboundPoint.second;

            auto firstMatchingEastbound = lower_bound(
                eastboundPoints.begin(),
                eastboundPoints.end(),
                make_pair(
                    coordinateSum,
                    northboundX - distanceLimit + 1
                )
            );

            auto pastLastMatchingEastbound = upper_bound(
                eastboundPoints.begin(),
                eastboundPoints.end(),
                make_pair(
                    coordinateSum,
                    northboundX
                )
            );

            intersectingPairs +=
                pastLastMatchingEastbound - firstMatchingEastbound;
        }
        printf(
            "%lld\n",
            (long long)numberOfPoints * distanceLimit
            - intersectingPairs
        );
    }

    return 0;
}
