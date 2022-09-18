#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;


class Cell {
    private:
        int value;
        int row;
        int column;
        int box;
        vector< int > possible_values;
        vector<int> colbox;
        vector<int> rowbox;
    public:
        int getValue() {
            return value;
        };
        void setValue(int v) {
            value = v;
        };
        
        int getRow() {
            return row;
        }
        void setRow(int r) {
            row = r;
        }
        int getColumn() {
            return column;
        }
        void setColumn(int c) {
            column = c;
        }

        void setBox() { // Set the box of the cell: from 1 to 9 (left to right and up to down)
            if (row < 3) {
                if (column < 3) { box = 1; colbox = {0, 1, 2}; rowbox = {0, 1, 2};}
                else if (2 < column && column < 6) { box = 2; colbox = {3, 4, 5}; rowbox = {0, 1, 2};}
                else if (column > 5) { box = 3; colbox = {6, 7, 8}; rowbox = {0, 1, 2};}
            }
            else if (2 < row && row < 6) {
                if (column < 3) { box = 4; colbox = {0, 1, 2}; rowbox = {3, 4, 5};}
                else if (2 < column && column < 6) { box = 5; colbox = {3, 4, 5}; rowbox = {3, 4, 5};}
                else if (column > 5) { box = 6; colbox = {6, 7, 8}; rowbox = {3, 4, 5};}
            }
            else if (row > 5) {
                if (column < 3) { box = 7; colbox = {0, 1, 2}; rowbox = {6, 7, 8};}
                else if (2 < column && column < 6) { box = 8; colbox = {3, 4, 5}; rowbox = {6, 7, 8};}
                else if (column > 5) { box = 9; colbox = {6, 7, 8}; rowbox = {6, 7, 8};}
            }
        }

        void returnvaluesrowcol() { // Borrar
            for (int i=0; i < rowbox.size(); i++) {
                cout << "row" << rowbox[i] << ",";
                cout << "col" << colbox[i] << ",";
            }
            cout << endl;
        }

        int getBox() {
            return box;
        }
    
        // Check if the value n is in the row
        bool inrows(int n, int grid[9][9]) { // Checked 11/09/2022
            bool checkrow = false;
            for (int i = 0; i < 9; i++) {
                if (grid[row][i] == n) {
                    checkrow = true;
                    break;
                }
            }
            return checkrow;
        }

        // Check if the value n is in the column
        bool incolumns(int n, int grid[9][9]) { // Checked 11/09/2022
            bool checkcol = false;
            for (int i = 0; i < 9; i++) {
                if (grid[i][column] == n) {
                    checkcol = true;
                    break;
                }
            }
            return checkcol;
        }

        // Check if the value n is in the box
        bool inbox(int n, int grid[9][9]) {
            bool checkbox = false;
            for (int v1 = 0; v1 < rowbox.size(); v1++) { // Substitute 2 by rowbox.size()
                for (int v2 = 0; v2 < colbox.size(); v2++) { // Substitute 2 by colbox.size()
                    // cout << rowbox[v1] << ";;" << colbox[v2] << "\n"; // Borrar
                    if (grid[rowbox[v1]][colbox[v2]] == n) {
                        checkbox = true;
                    }
                }    
            }
            return checkbox;
        }

        void addPossible_value(int cellValue) { // Add possible value to the vector of possible values
            possible_values.push_back(cellValue);
        }
        void removePossible_value(int position) { // Remove possible value from the vector of possible values
            possible_values.erase(possible_values.begin() + position);
        }
        int possible_values_size() { // Return the size of possible_values
            return possible_values.size();
        }
        int getPossible_value(int position) { // Get the possible value in position n of the vector of possible values
            return possible_values[position];
        }
        void returnvalues() { // Borrar
            for (int i=0; i < possible_values.size(); i++) {
                cout << possible_values[i] << ",";
            }
            cout << endl;
        }
        bool check_neighbour_cells(vector <Cell> cells, int val) {
            bool check = false;
            for (int i = 0; i < cells.size(); i++) {
                // Check in rows
                if ((cells[i].getRow()) == (row && cells[i].getColumn() != column)) {
                    if (find(cells[i].possible_values.begin(), cells[i].possible_values.end(), val) == cells[i].possible_values.end()) {
                        bool check = true;
                    }
                }
                // Check in columns
                if ((cells[i].getColumn() == column) && (cells[i].getRow() != row)) {
                    if (find(cells[i].possible_values.begin(), cells[i].possible_values.end(), val) == cells[i].possible_values.end()) {
                        bool check = true;
                    }
                }
                // Check in box
                if ((cells[i].getBox() == box) && (cells[i].getRow() != row) && (cells[i].getColumn() != column)) {
                    if (find(cells[i].possible_values.begin(), cells[i].possible_values.end(), val) == cells[i].possible_values.end()) {
                        bool check = true;
                    }
                }
            }
            return check;
        }
};

void print_grid(int grid[9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j)
        {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
}

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

    // First part: Iterate cells and keep the possible values
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {
            Cell cell; // Create the object cell for all cells
            cell.setRow(row); // Add row to the object
            cell.setColumn(column); // Add column to the object
            cell.setBox(); // Set the box
            cell.setValue(grid[row][column]); // Add cell value to the object
            if (cell.getValue() == 0) { // If the value is 0, check if there is any possible values
                // cell.returnvaluesrowcol(); // Borrar
                for (int value = 1; value < 10; value++) {
                    bool inR = cell.inrows(value, grid); bool inC = cell.incolumns(value, grid); bool inB = cell.inbox(value, grid);
                    // cout << inR << inC << inB; // Borrar
                    // cout << "\n"; // Borrar
                    if (inR == false && inC == false && inB == false) {        // If all are false: add possible value to a vector
                        cell.addPossible_value(value);
                    }
                }
                cells.push_back(cell); // Add each 0 cell to the cells vector
                // cell.returnvalues();
                
            } else {
                continue;
            }
        }
    }

    // Second part: Iterate 0 cells and fill with the correct values
    while (!cells.empty()) { // while there are cells with 0 value
    // for (int count = 0; count < 4; count++) { // Borrar
        // cout << cells.size() << "\n"; // Borrar
        for (int i = 0; i < cells.size(); i++) { // Iterate thought the 0 cells.
            // cout << "RCB: " << cells[i].getRow() << ";" << cells[i].getColumn() << ";" << cells[i].getBox() << "\n"; // Borrar
            // cells[i].returnvalues(); // Borrar
            if (cells[i].possible_values_size() == 1) { // If the cell has only one possible value, set this value
                    cells[i].setValue(cells[i].getPossible_value(0));
                    // cout << "Unique value: " << cells[i].getPossible_value(0) << "\n"; // Borrar
                    // cout << cells[i].getPossible_value(1); // Borrar
                    grid[cells[i].getRow()][cells[i].getColumn()] = cells[i].getValue(); // Add new value to grid
                    // cout << cells[i].getValue();
                    cells.erase(cells.begin() + i); // remove from cells vector the object cell which a value !=  0
            } else { // If the cell has more than one possible value, check which is more suitable
                for (int n = 0; n < cells[i].possible_values_size(); n++) { // Iterate through the possible values
                    int val = cells[i].getPossible_value(n); // Take the possible value in each iteration
                    // cout << "Val: " << val << "\n";
                    bool inR = cells[i].inrows(val, grid); bool inC = cells[i].incolumns(val, grid); bool inB = cells[i].inbox(val, grid); // Check if the possible value is suitable for this position
                    // cout << "Checking, is in row/column/box? " << inR << inC << inB << "\n";
                    if ((inR == false) && (inC == false) && (inB == false)) {
                        // cout << "Checking if is the possible value of other cell" << "\n";
                        if (cells[i].check_neighbour_cells(cells, val) == false) { // Can it be in another part of the row/column/box? If not: set this value
                            // cout << "It is not the possible value of other cell\n";
                            cells[i].setValue(val);
                            grid[cells[i].getRow()][cells[i].getColumn()] = cells[i].getValue(); // Add new value to grid
                            cells.erase(cells.begin() + i); // remove from cells vector de object cell which a value !=  0
                            break;
                        }
                    } else {
                        // cout << "YES arriba\n";
                        cells[i].removePossible_value(n); // If it is not suitable now, remove from the possible values
                    }
                }
            }
        }
    // cout << "_____________________________\n";    
    }

    cout << "########################################\n";
    cout << "############## FINAL SUDOKU ############\n";
    cout << "########################################\n";

    print_grid(grid); // Print grid
    cout << "\n";

    return 0;
}