#include <iostream>
#include <string>
using namespace std;

// Function to determine the next state based on current state and input character
int NextState(int currentState, char input) {
    if (currentState == 1) {
        if (input == 'a') return 2;
        if (input == 'b') return 4;
        if (input == 'c') return 6;
    } else if (currentState == 2) {
        if (input == 'a') return 3;
        if (input == 'b') return 2;
        if (input == 'c') return 2;
    } else if (currentState == 3) {
        if (input == 'a') return 3;
        if (input == 'b') return 2;
        if (input == 'c') return 2;
    } else if (currentState == 4) {
        if (input == 'a') return 4;
        if (input == 'b') return 5;
        if (input == 'c') return 4;
    } 
     else if (currentState == 5) {
        if (input == 'a') return 4;
        if (input == 'b') return 5;
        if (input == 'c') return 4;
    }
     else if (currentState == 6) {
        if (input == 'a') return 6;
        if (input == 'b') return 6;
        if (input == 'c') return 7;
    }
     else if (currentState == 7) {
        if (input == 'a') return 6;
        if (input == 'b') return 6;
        if (input == 'c') return 7;
    }
    return -1; // Invalid state
}

int main() {
    string input;
    cout << "Enter the input string (over a, b, c): ";
    cin >> input;

    int currentState = 1; // Initial state
    int acceptingState1 = 3; // Accepting state for 'a'
    int acceptingState2 = 5; // Accepting state for 'b'
    int acceptingState3 = 7; // Accepting state for 'c'

    for (char c : input) {
        currentState = NextState(currentState, c);
        if (currentState == -1) {
            cout << "Invalid input character encountered!\n";
            return 1;
        }
    }

    if (currentState == acceptingState1 || currentState == acceptingState2 || currentState == acceptingState3) {
        cout << "The input string is accepted (starts and ends with the same letter).\n";
    } else {
        cout << "The input string is rejected (does not start and end with the same letter).\n";
    }

    return 0;
}