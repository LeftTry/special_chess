#include <iostream>
#include <vector>
#include <fstream>

#define vi vector<int>
#define vvi vector<vi>
#define pi pair<int, int>

using namespace std;

vvi field;
/*
    board is a chess board with custom size
    numbers from 1 - 5 are represents different figures
    number 0 represents empty cell
    Figures:
    1 - Zergling
        moves for 3 - 8 cells by the diagonal
        attacks only if enemy figure is 1 step forward or 1 step backward by the vertical
    2 - Ultralisk
        moves only forward for minimum 1 cell and maximum for the size of field
        attacks in the radius of 2 cells(2 cells forward and backward by vertical,
            2 left and right by horizontal, 2 cell by both diagonals
    3 -
 */
void print_field(){
    for(int i = 0;i < field.size();i++){
        for(int j = 0;j < field.size();j++){
            cout << field[i][j] << "\t";
        }
        cout << "\n";
    }
}

bool is_move_legitimate(int number_of_figure, pi cur_cell, pi cell_to_move){
    switch (number_of_figure) {
        case 1:
            if((abs(cell_to_move.first - cur_cell.first) == abs(cell_to_move.second - cur_cell.second)
            && abs(cell_to_move.first - cur_cell.first) < 9 && abs(cell_to_move.first - cur_cell.first) > 2)
            || (cell_to_move.first == cur_cell.first && abs(cell_to_move.second - cur_cell.second) == 1))
                return 1;
            else
                return 0;
        case 2:

    }
}

void move_figure(int number_of_figure, pi cur_cell, pi cell_to_move){
    field[cur_cell.first][cur_cell.second] = 0;
    field[cell_to_move.first][cell_to_move.second] = number_of_figure;
}

int main() {
    ifstream is("field.txt");
    if(is.is_open()){
        string s;
        getline(is, s);
        int n = stoi(s);
        field.resize(n, vi(n));
        for(int j = 0;j < n;j++){
            getline(is, s);
            for(int i = 0;i < s.size();i++){
                field[j][i] = s[i] - '0';
            }
        }
    } else {
        is.close();
        return 0;
    }
    is.close();

    return 0;
}
