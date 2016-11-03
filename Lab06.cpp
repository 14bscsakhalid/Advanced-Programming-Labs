#include <conio.h>
#include <iostream>
using namespace std;


#define STATIONS 4

int shortest_path(int a, int b) {
    if (a < b)
        return a;
    else
        return b;
}

int iterative(int time[][STATIONS], int swtime[][STATIONS], int *entry, int *exit) {
    int new1[STATIONS] = {0};
    int new2[STATIONS] = {0};

    new1[0] = entry[0] + time[0][0];
    new2[0] = entry[1] + time[1][0];

    for (int i = 1; i < STATIONS; ++i) {
        new1[i] = shortest_path(new1[i - 1] + time[0][i], new2[i - 1] + swtime[1][i] + time[0][i]);
        new2[i] = shortest_path(new2[i - 1] + time[1][i], new1[i - 1] + swtime[0][i] + time[1][i]);
    }


    return shortest_path(new1[STATIONS - 1] + exit[0], new2[STATIONS - 1] + exit[1]);
}

int T0 = 0;
int T1 = 0;

int recursive(int time[][STATIONS], int swtime[][STATIONS], int *entry, int *exit, int n, int inst) {
    if (n == 0) {
        return entry[inst] + time[inst][0];
    }

    
    if (inst == 0) {
		T0 = shortest_path(recursive(time, swtime, entry, exit, n - 1, 0) + time[0][n],
                recursive(time, swtime, entry, exit, n - 1, 1) + swtime[1][n] + time[0][n]);
    } else if (inst == 1) {
       T1 = shortest_path(recursive(time, swtime, entry, exit, n - 1, 1) + time[1][n],
                recursive(time, swtime, entry, exit, n - 1, 0) + swtime[0][n] + time[1][n]);
    }

    return shortest_path(T0, T1);
}

void main() {
    int time[][STATIONS] = {
        {7, 3, 6, 5},
        {0, 6, 6, 6}
    };
    int swtime[][STATIONS] = {
        {10, 10, 6, 5},
        {2, 9, 2, 6}
    };
    int entry[] = {12, 15};
    int exit[] = {16, 9};

    int path = iterative(time, swtime, entry, exit);
    cout << "Shortest path by Iterative Method: " << path << "\n";

	int path1 = recursive(time, swtime, entry, exit, STATIONS, 0);
    cout << "Shortest path by Recursive Method: " << path1 << "\n";


    _getch();
}