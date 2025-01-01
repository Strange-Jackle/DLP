#include <iostream>
#include <string>
using namespace std;

int NextState(int currentState, char input) {
    if (currentState == 1) {
        if (input == '1') return 1;
        if (input == '0') return 2;
    } else if (currentState == 2) {
        if (input == '1') return 3;
        if (input == '0') return 5;
    } else if (currentState == 3) {
        if (input == '1') return 4;
        if (input == '0') return 5;
    } else if (currentState == 4) {
        if (input == '1') return 4;
        if (input == '0') return 2;
    }
    else if (currentState == 5) {
        if (input == '1') return -2;
        if (input == '0') return -2;
    }
    return -1; // Invalid state
}

int main() {
    string input;
    cout << "Enter the input string: ";
    cin >> input;

    int currentState = 1; // Initial state
    int acceptingState = 4; // Accepting state

    for (char c : input) {
        currentState = NextState(currentState, c);
        if (currentState == -1) {
            cout << "Invalid input character encountered!\n";
            return 1;
        }
    }

    if (currentState == acceptingState) {
        cout << "The input string is accepted (ends in state " << currentState << ").\n";
    } 
    else{
        cout << "The input string is rejected (ends in state " << currentState << ").\n";
    } 

    return 0;
}