#include <iostream>
#include <string>
using namespace std;

int NextState(int currentState, char input) {
    if (currentState == 1) {
        if (input == 'a') return 2;
        if (input == 'b') return 3;
    } else if (currentState == 2) {
        if (input == 'a') return 1;
        if (input == 'b') return 4;
    } else if (currentState == 3) {
        if (input == 'a') return 4;
        if (input == 'b') return 1;
    } else if (currentState == 4) {
        if (input == 'a') return 3;
        if (input == 'b') return 2;
    }
    return -1; // Invalid state
}

int main() {
    string input;
    cout << "Enter the input string: ";
    cin >> input;

    int currentState = 1; // Initial state
    int acceptingState = 2; // Accepting state

    for (char c : input) {
        currentState = NextState(currentState, c);
        if (currentState == -1) {
            cout << "Invalid input character encountered!\n";
            return 1;
        }
    }

    if (currentState == acceptingState) {
        cout << "The input string is accepted (ends in state " << currentState << ").\n";
    } else {
        cout << "The input string is rejected (ends in state " << currentState << ").\n";
    }

    return 0;
}