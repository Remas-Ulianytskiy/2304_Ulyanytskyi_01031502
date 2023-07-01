#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

template <typename type>
type get_user_input() {
    type input;
    cin >> input;
    return input;
}

void fill_game_field(vector<string>& field) {
    vector<char> char_for_field { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    short field_size = char_for_field.size();

    if (!field.empty())
        field.clear();

    for (short row = 0; row < field_size; ++row) {
        for (short column = 0; column < field_size; ++column) {
            field.push_back(string(1, char_for_field[column]) + to_string(field_size - row));
        }
    }
}

void display_game_field(vector<string>& field) {
    short field_size = field.size();

    for (short i = 0; i < field_size; ++i) {
        if (i % 8 == 0)
            cout << endl;
        cout << field[i] << ' ';
    }
    cout << endl << endl;
}

class Checker {
protected:
    virtual bool is_inside_board(char col, char row) const final {
        return col >= 'a' && col <= 'h' && row >= '1' && row <= '8';
    }

public:
    virtual bool check_move(const string& current_position, const string& new_position) const = 0;
};

class Checker_Normal : public Checker {
public:
    bool check_move(const string& current_position, const string& new_position) const override {
        bool current_col_and_row = is_inside_board(current_position[0], current_position[1]);
        bool new_col_and_row = is_inside_board(new_position[0], new_position[1]);

        if (!current_col_and_row || !new_col_and_row) {
            cout << "Position is out of game field!\n";
            return false;
        }

        int diff_row = new_position[1] - current_position[1];
        int diff_col = abs(new_position[0] - current_position[0]);        
        return diff_row == 1 && diff_col == 1;
    }
};

class Checker_King : public Checker {
public:
    bool check_move(const string& current_position, const string& new_position) const override {
        bool current_col_and_row = is_inside_board(current_position[0], current_position[1]);
        bool new_col_and_row = is_inside_board(new_position[0], new_position[1]);

        if (!current_col_and_row || !new_col_and_row) {
            cout << "Position is out of game field!\n";
            return false;
        }

        short diff_row = abs(new_position[1] - current_position[1]);
        short diff_col = abs(new_position[0] - current_position[0]);
        return diff_row == diff_col;
    }
};

int main() {
    string current_position, new_position;
    bool exit_status = false;
    vector<string> game_field;

    Checker_Normal checker_normal;
    Checker_King checker_king;

    fill_game_field(game_field);

    while (!exit_status) {
        cout << "1 - for display game field\n";
        cout << "2 - for chek Checker_Normal move\n";
        cout << "3 - for chek Checker_King move\n";
        cout << "0 - Exit\n";
        cout << "Enter: ";

        switch (get_user_input<int>())
        {
        case 0:
            exit_status = true;
            cout << "Exit!";
            break;
        case 1:
            cout << "\nGame field:";
            display_game_field(game_field);
            break;
        case 2:
            cout << "Set current position: ";
            current_position = get_user_input<string>();
            cout << "Set new position: ";
            new_position = get_user_input<string>();

            if (checker_normal.check_move(current_position, new_position)) {
                cout << "From " << current_position << " to ";
                cout << new_position << " is possible move for Checker_Normal.\n\n";
            }
            else {
                cout << "Invalid move.\n\n";
            }
            break;
        case 3:
            cout << "Set current position: ";
            current_position = get_user_input<string>();
            cout << "Set new position: ";
            new_position = get_user_input<string>();

            if (checker_king.check_move(current_position, new_position)) {
                cout << "From " << current_position << " to ";
                cout << new_position << " is possible move for Checker_King.\n\n";
            }
            else {
                cout << "Invalid move.\n\n";
            }
            break;
        default:
            cout << "Invalid input!\n\n";
            break;
        }
    }

    return 0;
}
