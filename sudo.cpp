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
        int id;
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

        void setid(int i) {
            id = i;
        }
        
        int getid() {
            return id;
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
        bool inbox(int n, int grid[9][9]) { // Checked 18/09/2022
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
        
        void removeValue(int value, Cell cell) {
            for (int i = 0; i < cell.possible_values_size(); i++) {
                if (cell.getPossible_value(i) == value) {
                    cell.removePossible_value(i);
                }
            }
        }
        
        bool check_neighbour_cells(int value, vector<Cell> cells) {
            bool checkr = false; bool checkc = false; bool checkb = false;
            for (int i = 0; i < cells.size(); i++) {
                if (cells[i].getid() != id) {
                    if (cells[i].getRow() == row) {
                        for (int j = 0; j < cells[i].possible_values_size(); j++) {
                            if (cells[i].getPossible_value(j) == value) {
                                checkr = true;
                            }
                        }
                    }
                    if (cells[i].getColumn() == column) {
                        for (int j = 0; j < cells[i].possible_values_size(); j++) {
                            if (cells[i].getPossible_value(j) == value) {
                                checkc = true;
                            }
                        }
                    }
                    if (cells[i].getBox() == box) {
                        for (int j = 0; j < cells[i].possible_values_size(); j++) {
                            if (cells[i].getPossible_value(j) == value) {
                                checkb = true;
                            }
                        }
                    }
                }
            }
            bool check;
            if (checkr == false or checkc == false or checkb == false) {
                check = false;
            } else {
                check = true;
            }
            return check;
        }

        void quit_possiblevalue(int value, vector<Cell> cells) {
            for (int i = 0; i < cells.size(); i++) {
                if (cells[i].getid() == id) {
                    if (cells[i].getRow() == row) {
                        cells[i].removeValue(value, cells[i]);
                        }
                    if (cells[i].getColumn() == column) {
                        cells[i].removeValue(value, cells[i]);
                    }
                    if (cells[i].getBox() == box) {
                        cells[i].removeValue(value, cells[i]);
                    }
                }
             }
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

    int id = 1;

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
                // cell.returnvalues(); // Parece que está bien, Check!!!! Borrar
                
            } else {
                continue;
            }
            id += 1;
        }
    }

    // Checked the code above 18/09/2022
    // Second part: Iterate 0 cells and fill with the correct values
    while (!cells.empty()) { // while there are cells with 0 value
        for (int i = 0; i < cells.size(); i++) { // Iterate thought the 0 cells.
            for (int j = 0; j < cells[i].possible_values_size(); j++) {
                bool inR = cells[i].inrows(cells[i].getPossible_value(j), grid);
                bool inC = cells[i].incolumns(cells[i].getPossible_value(j), grid);
                bool inB = cells[i].inbox(cells[i].getPossible_value(j), grid);
                if (inR == false && inC == false && inB == false) { // If the cell has only one possible value, set this value
                    if (cells[i].check_neighbour_cells(cells[i].getPossible_value(j), cells) == false) {
                        cells[i].setValue(cells[i].getPossible_value(j)); // It can be removed. If the next line is changed at the end as follows: cells[i].getPossible-value(j);
                        grid[cells[i].getRow()][cells[i].getColumn()] = cells[i].getValue();
                        cells.erase(cells.begin() + i);
                    }
                } else {
                    cells[i].removePossible_value(j);
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