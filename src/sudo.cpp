#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "cell.h"
#include "utils.h"

using namespace std;

int main() {
    // Example sudoku matrix
    int grid[9][9] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    cout << "########################################\n";
    cout << "############ INITIAL SUDOKU ############\n";
    cout << "########################################\n";

    print_grid(grid); // Print grid

    vector<Cell> cells; // vector for all the 0 cell

    int id = 1; // id of the cell

    // First part: Iterate cells and keep the possible values
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {
            Cell cell; // Create the object cell for all cells
            cell.setRow(row); // Add row to the object
            cell.setColumn(column); // Add column to the object
            cell.setBox(); // Set the box
            cell.setValue(grid[row][column]); // Add cell value to the object
            cell.setid(id);
            if (cell.getValue() == 0) { // If the value is 0, check if there is any possible values
                for (int value = 1; value < 10; value++) {
                    bool inR = cell.inrows(value, grid); bool inC = cell.incolumns(value, grid); bool inB = cell.inbox(value, grid);
                    if (inR == false && inC == false && inB == false) {  // If all are false: add possible value to a vector
                        cell.addPossible_value(value);
                    }
                }
                cells.push_back(cell); // Add each 0 cell to the cells vector
                
            } else {
                continue;
            }
            id += 1;
        }
    }

    // Second part: Iterate 0 cells and fill with the correct values
    while (!cells.empty()) { // while there are cells with 0 value
        for (int i = 0; i < cells.size(); i++) { // Iterate thought the 0 cells.
            for (int j = 0; j < cells[i].possible_values_size(); j++) {
                bool inR = cells[i].inrows(cells[i].getPossible_value(j), grid);
                bool inC = cells[i].incolumns(cells[i].getPossible_value(j), grid);
                bool inB = cells[i].inbox(cells[i].getPossible_value(j), grid);
                if (inR == false && inC == false && inB == false) { // If the cell has only one possible value, set this value
                    if (cells[i].check_neighbour_cells(cells[i].getPossible_value(j), cells) == false) {
                        grid[cells[i].getRow()][cells[i].getColumn()] = cells[i].getPossible_value(j);
                        cells.erase(cells.begin() + i);
                    }
                } else {
                    cells[i].removePossible_value(j);
                }
            }
        }
    }

    cout << "########################################\n";
    cout << "############## FINAL SUDOKU ############\n";
    cout << "########################################\n";

    print_grid(grid); // Print grid
    cout << "\n";

    return 0;
}