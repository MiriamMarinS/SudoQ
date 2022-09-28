#ifndef CELL_H
#define CELL_H
#include <vector>

using namespace std;

class Cell {
    private:
        int value;
        int row;
        int column;
        int box;
        int id;
        vector<int> possible_values;
        vector<int> colbox;
        vector<int> rowbox;
    public:
        // Get the value of the cell
        int getValue();
        // Set the value of the cell
        void setValue(int v);
        // Get the row
        int getRow();
        // Set the row
        void setRow(int r);
        // Get the column
        int getColumn();
        // Set the column
        void setColumn(int c);
        // Set the id of the cell
        void setid(int i);
        // Get the id of the cell
        int getid();
        // Set the box value
        void setBox();
        // Get the box value
        int getBox();
        // Check if the value n is in the row
        bool inrows(int n, int grid[9][9]);
        // Check if the value n is in the column
        bool incolumns(int n, int grid[9][9]);
        // Check if the value n is in the box
        bool inbox(int n, int grid[9][9]);
        // Add possible value to the possible values vector
        void addPossible_value(int cellValue);
        // Remove the possible value from the vector of this cell
        void removePossible_value(int position);
        // Get the possible values vector size
        int possible_values_size();
        // Get the possible value, based on its position in the vector
        int getPossible_value(int position);
        // Remove value from the possible values vector of other cells
        void removeValue(int value, Cell cell);
        // Check if any of the neighbour cells has this value, if not, set this value
        bool check_neighbour_cells(int value, vector<Cell> cells);
        // Remove the possible value of a cell based on new values set in neighbour cells
        void quit_possiblevalue(int value, vector<Cell> cells);
};

#endif