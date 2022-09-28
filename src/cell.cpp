#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "cell.h"

using namespace std;

// Get the value of the cell
int Cell::getValue() {
    return Cell::value;
}
// Set the value of the cell
void Cell::setValue(int v) {
    Cell::value = v;
}
// Get the row
int Cell::getRow() {
    return Cell::row;
}
// Set the row
void Cell::setRow(int r) {
    Cell::row = r;
}
// Get the column
int Cell::getColumn() {
    return Cell::column;
}
// Set the column
void Cell::setColumn(int c) {
    Cell::column = c;
}
// Set the id of the cell
void Cell::setid(int i) {
    Cell::id = i;
}
// Get the id of the cell
int Cell::getid() {
    return Cell::id;
}
// Set the box value
void Cell::setBox() { // Set the box of the cell: from 1 to 9 (left to right and up to down)
    if (Cell::row < 3) {
        if (Cell::column < 3) { Cell::box = 1; Cell::colbox = {0, 1, 2}; Cell::rowbox = {0, 1, 2};}
        else if (2 < Cell::column && Cell::column < 6) { Cell::box = 2; Cell::colbox = {3, 4, 5}; Cell::rowbox = {0, 1, 2};}
        else if (Cell::column > 5) { Cell::box = 3; Cell::colbox = {6, 7, 8}; Cell::rowbox = {0, 1, 2};}
    }
    else if (2 < Cell::row && Cell::row < 6) {
        if (Cell::column < 3) { Cell::box = 4; Cell::colbox = {0, 1, 2}; Cell::rowbox = {3, 4, 5};}
        else if (2 < Cell::column && Cell::column < 6) { Cell::box = 5; Cell::colbox = {3, 4, 5}; Cell::rowbox = {3, 4, 5};}
        else if (Cell::column > 5) { Cell::box = 6; Cell::colbox = {6, 7, 8}; Cell::rowbox = {3, 4, 5};}
    }
    else if (Cell::row > 5) {
        if (Cell::column < 3) { Cell::box = 7; Cell::colbox = {0, 1, 2}; Cell::rowbox = {6, 7, 8};}
        else if (2 < Cell::column && Cell::column < 6) { Cell::box = 8; Cell::colbox = {3, 4, 5}; Cell::rowbox = {6, 7, 8};}
        else if (Cell::column > 5) { Cell::box = 9; Cell::colbox = {6, 7, 8}; Cell::rowbox = {6, 7, 8};}
    }
}
// Get the box value
int Cell::getBox() {
    return Cell::box;
}
// Check if the value n is in the row
bool Cell::inrows(int n, int grid[9][9]) {
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
bool Cell::incolumns(int n, int grid[9][9]) {
    bool checkcol = false;
    for (int i = 0; i < 9; i++) {
        if (grid[i][Cell::column] == n) {
            checkcol = true;
            break;
        }
    }
    return checkcol;
}
// Check if the value n is in the box
bool Cell::inbox(int n, int grid[9][9]) {
    bool checkbox = false;
    for (int v1 = 0; v1 < Cell::rowbox.size(); v1++) {
        for (int v2 = 0; v2 < Cell::colbox.size(); v2++) {
            if (grid[Cell::rowbox[v1]][Cell::colbox[v2]] == n) {
                checkbox = true;
            }
        }    
    }
    return checkbox;
}
// Add possible value to the possible values vector
void Cell::addPossible_value(int cellValue) {
    possible_values.push_back(cellValue);
}
// Remove the possible value from the vector of this cell
void Cell::removePossible_value(int position) {
    Cell::possible_values.erase(Cell::possible_values.begin() + position);
}
// Get the possible values vector size
int Cell::possible_values_size() {
    return Cell::possible_values.size();
}
// Get the possible value, based on its position in the vector
int Cell::getPossible_value(int position) {
    return Cell::possible_values[position];
}
// Remove value from the possible values vector of other cells
void Cell::removeValue(int value, Cell cell) {
    for (int i = 0; i < cell.possible_values_size(); i++) {
        if (cell.getPossible_value(i) == value) {
            cell.removePossible_value(i);
        }
    }
}
// Check if any of the neighbour cells has this value, if not, set this value
bool Cell::check_neighbour_cells(int value, vector<Cell> cells) {
    bool checkr = false; bool checkc = false; bool checkb = false;
    for (int i = 0; i < cells.size(); i++) {
        if (cells[i].getid() != id) {
            if (cells[i].getRow() == Cell::row) {
                for (int j = 0; j < cells[i].possible_values_size(); j++) {
                    if (cells[i].getPossible_value(j) == value) {
                        checkr = true;
                    }
                }
            }
            if (cells[i].getColumn() == Cell::column) {
                for (int j = 0; j < cells[i].possible_values_size(); j++) {
                    if (cells[i].getPossible_value(j) == value) {
                        checkc = true;
                    }
                }
            }
            if (cells[i].getBox() == Cell::box) {
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
// Remove the possible value of a cell based on new values set in neighbour cells
void Cell::quit_possiblevalue(int value, vector<Cell> cells) {
    for (int i = 0; i < cells.size(); i++) {
        if (cells[i].getid() == Cell::id) {
            if (cells[i].getRow() == Cell::row) {
                cells[i].removeValue(value, cells[i]);
                }
            if (cells[i].getColumn() == Cell::column) {
                cells[i].removeValue(value, cells[i]);
            }
            if (cells[i].getBox() == Cell::box) {
                cells[i].removeValue(value, cells[i]);
            }
        }
    }
}