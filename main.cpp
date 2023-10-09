#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#define vi vector<int>
#define vvpi vector<vector<pair<int, int>>>
#define pi pair<int, int>
#define vpi vector<pi>

using namespace std;

vvpi field;
/*
    board is a chess board with custom size
    numbers from 1 to 5 are represents different figures
    number 0 represents empty cell
    Figures:
    1 - Zergling
        moves for 3 - 8 cells by the diagonal
        attacks only if enemy figure is 1 step forward or 1 step backward by the vertical
    2 - Ultralisk
        moves only forward or backward for minimum 1 cell and maximum for the size of field
        attacks in the radius of 2 cells(2 cells forward and backward by vertical,
            2 left and right by horizontal, 2 cell by both diagonals
    3 -
 */
void print_field(){
    for(int i = 0;i < field.size();i++){
        for(int j = 0;j < field.size();j++){
            cout << field[i][j].first << "\t";
        }
        cout << "\n";
    }
}

bool is_move_legitimate(int number_of_figure, int number_of_player, pi cur_cell, pi cell_to_move){
    if(field[cur_cell.first][cur_cell.second].second != number_of_player) return false;
    switch (number_of_figure) {
        case 1:
            if(abs(cell_to_move.first - cur_cell.first) == abs(cell_to_move.second - cur_cell.second)
            && abs(cell_to_move.first - cur_cell.first) < 9 && abs(cell_to_move.first - cur_cell.first) > 2) {
                if (field[cell_to_move.first][cell_to_move.second].first == 0)
                    return true;
                else
                    return false;
            }
            else if (cell_to_move.first == cur_cell.first && abs(cell_to_move.second - cur_cell.second) == 1)
                return true;
        case 2:
            if(cell_to_move.first == cur_cell.first){
                if(field[cell_to_move.first][cell_to_move.second].first == 0)
                    return true;
                else{
                    if(abs(cell_to_move.second - cur_cell.second) < 3)
                        return true;
                    else
                        return false;
                }
            }
            else{
                if(abs(cell_to_move.first - cur_cell.first) < 3 &&
                abs(cell_to_move.second - cur_cell.second) < 3)
                    return true;
                else
                    return false;
            }
        default:
            return false;
    }
}

void move_figure(int number_of_figure, int number_of_player, pi cur_cell, pi cell_to_move){
    if(is_move_legitimate(number_of_figure, number_of_player, cur_cell, cell_to_move)) {
        field[cur_cell.first][cur_cell.second].first = 0;
        field[cur_cell.first][cur_cell.second].second = -1;
        field[cell_to_move.first][cell_to_move.second].first = number_of_figure;
        field[cell_to_move.first][cell_to_move.second].second = number_of_player;
    } else {
        cout << "Move is not legitimate" << "\n";
    }
}

int main() {
    ifstream is;
    is.open("../field.txt");
    int n;
    if(is.is_open()){
        string s;
        getline(is, s);
        n = stoi(s);
        field.resize(n, vpi(n));
        for(int j = 0;j < n;j++){
            getline(is, s);
            s.erase(remove(s.begin(), s.end(), ' '), s.end());
            for(int i = 0;i < s.size();i++){
                field[j][i].first = s[i] - '0';
                if(j < 2) field[j][i].second = 0;
                else if(j <= n - 2) field[j][i].second = 1;
                else field[j][i].second = -1;
            }
        }
    } else {
        is.close();
        return 0;
    }
    is.close();
    print_field();
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    int i = 0;
    while(x1 != -1 || x2 != -1){
        b:;
        cin >> x1 >> y1;
        if(x1 == -1) break;
        if(x1 < n && y1 < n){
            a:;
            cin >> x2 >> y2;
            if (x2 == -1) break;
            if(x2 < n && y2 < n){
                pi cur_cell = {x1, y1};
                pi cell_to_move = {x2, y2};
                int number_of_figure = field[x1][y1].first;
                int number_of_player = i % 2;
                if(i == 0) cout << "Player's 1 move:\n";
                else cout << "Player's 2 move:\n";
                move_figure(number_of_figure, number_of_player, cur_cell, cell_to_move);
                i++;
            } else{
                cout << "Input is incorrect" << "\n";
                goto a;
            }
        } else {
            cout << "Input is incorrect" << "\n";
            goto b;
        }
        print_field();
    }
    return 0;
}
