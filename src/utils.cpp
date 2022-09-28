#include <iostream>
#include "utils.h"

using namespace std;

void print_grid(int grid[9][9]) { // To print the grid
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j)
        {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
}