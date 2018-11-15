
// Author: Gerardo Torres
// an implementation of Conway's Game of Life using vectors, basic file i/o, and strings

// compile: `$ g++ rec01.cpp -o rec01`
// run:     `$ ./rec01`

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void print_vector (vector<string> vec, int generation) {
    cout << "printing generation " << generation << "..." << endl;
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j];
        } 
        cout << endl; // new line character for row
    } 
    cout << endl; // new line character between generations
}

int main () {
    ifstream life("life.txt");
    
    if (!life) {
        cerr << "failed to open life.txt";
        exit(1);
    } else {
        cout << "file.txt successfully opened" << endl;
    }

    vector<string> vectorOfCells; // initial 2D world
    string line;
	
    while ((getline(life, line))) {
		vectorOfCells.push_back(line); // pushing into vector string by string
	}

    // printing generation 0
    print_vector (vectorOfCells, 0);

    for (int generation = 1; generation < 11; ++generation) { // iterating through generations
        vector<string> newVectorOfCells;
        for (size_t row = 1; row < vectorOfCells.size() + 1; ++row) { // iterating through rows
            string currRow = vectorOfCells[row - 1];
            string newRow = "";
            for (size_t col = 1; col < currRow.size() + 1; ++col) { // iterating through cells
                char currCell = currRow[col - 1];
                int livingNeighbors = 0;

                int rowIndex = row - 1;
                int colIndex = col - 1;

                // cell schema: 
                // nw | n | ne
                // w  | * | e
                // sw | s | se

                if (row > 1) { // has north         
                    if (vectorOfCells[rowIndex - 1][colIndex] == '*') { // north
                        ++livingNeighbors;
                    }
                    if (col > 1) { // northwest
                        if (vectorOfCells[rowIndex - 1][colIndex - 1] == '*') {
                            ++livingNeighbors;
                        }
                    }
                    if (col < 20) { // northeast
                        if (vectorOfCells[rowIndex - 1][colIndex + 1] == '*') {
                            ++livingNeighbors;
                        }
                    }
                }

                if (col > 1) { // west
                    if (vectorOfCells[rowIndex][colIndex - 1] == '*') {
                        ++livingNeighbors;
                    }
                }

                if (col < 20) { // east
                    if (vectorOfCells[rowIndex][colIndex + 1] == '*') {
                        ++livingNeighbors;
                    }
                }

                if (row < 8) { // has south
                    if (vectorOfCells[rowIndex + 1][colIndex] == '*') { // south
                        ++livingNeighbors;
                    }
                    if (col > 1) { // southwest
                        if (vectorOfCells[rowIndex + 1][colIndex - 1] == '*') {
                            ++livingNeighbors;
                        }
                    }
                    if (col < 20) { // southeast
                        if (vectorOfCells[rowIndex + 1][colIndex + 1 ] == '*') {
                            ++livingNeighbors;
                        }
                    }
                }
                char newCellValue;
                if (currCell == '*') {
                    newCellValue = '*';
                    if (livingNeighbors < 2 || livingNeighbors > 3) {
                        newCellValue = '-';
                    }
                } else {
                    newCellValue = '-';
                    if (livingNeighbors == 3) {
                        newCellValue = '*';
                    }
                }
                newRow = newRow + newCellValue;
            }
            newVectorOfCells.push_back(newRow);
        }
        print_vector(newVectorOfCells, generation); // output to the terminal
        vectorOfCells = newVectorOfCells;
    }
    life.close();
}
