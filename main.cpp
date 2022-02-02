/* A bare-bones imitation of a 1970s-era interactive fiction game written 
 * for an introductory programming course, inspired by the the 1979 Infocom game "Zork".
 * Author: Kevin Jin
 * Date: 11-09-2021
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

// Global constants
const int STEPS_TO_FOREST = 50;         // Distance to forest
const int STEPS_TO_DUNGEON = 100;       // Distance to dungeon
const int STEPS_TO_HOUSE = 4000;        // Distance to house
const int STEPS_TO_MAZE = 6000;         // Distance to maze
const int MIN_VALUE = 0;                // Min value of random numbers for playerPickup
const int MAX_VALUE = 5;                // Max value of random numbers for playerPickup

int main() {
    srand(time(NULL));

    char action; // Stores the action performed by the user in the main menu
    char repeat; // Repeats main menu

    char direction; // Stores the direction the user wishes to move
    int numSteps = 0; // Stores the number of steps the user wishes to move

    vector<string> knapsack;    // Player knapsack
    vector<string> items = {"apple", "knife", "pebble", "lantern", "potion", "ring"}; // Possible items to pick up

    int randIndex; // Selects random item between index 1-5 inclusive
    char input; // Repeats pickup

    int minIndex; // Minimum index for selection sort of knapsack
    string minValue; // Minimum string for selection sort of knapsack

    do {
        cout << "What would you like to do? Please select an option:" << endl;
        cout << "\tA: Move\n\tB: Attack\n\tC: Pick Up Item\n\tD: Display Knapsack Contents\n\tE: Quit\n";
        cout << ">> ";
        cin >> action;

        if (islower(action)) {
            action = toupper(action);
        }

        switch (action) {
            // Move
            case 'A': {
                // Get the number of steps from the user.
                cout << "Please enter the number of steps you would like to travel:" << endl;
                cout << ">> ";
                cin >> numSteps;

                // Prevent user from entering negative steps.
                while (numSteps < 0) {
                    cout << "You can't travel a negative number of steps! Please try again." << endl;
                    cout << "Please enter the number of steps you would like to travel:" << endl;
                    cout << ">> ";
                    cin >> numSteps;
                }

                // Get the compass direction from the user.
                cout << "Please enter the compass direction in which you would like to travel (N, S, W, E):" << endl;
                cout << ">> ";
                cin >> direction;

                // Prevent user from entering an invalid direction.
                while (direction != 'N' && direction != 'S' && direction != 'E' && direction != 'W') {
                    cout << "You can't travel in a direction that's not on the compass! Please try again." << endl;
                    cout << "Please enter the compass direction in which you would like to travel (N, S, W, E):" << endl;
                    cout << ">> ";
                    cin >> direction;
                }

                // Determine which location the user ends up at.
                if (numSteps >= STEPS_TO_FOREST && direction == 'N') {
                    cout << "You have entered the forest." << endl;
                } else if (numSteps >= STEPS_TO_DUNGEON && direction == 'S') {
                    cout << "You have entered the dungeon." << endl;
                } else if (numSteps >= STEPS_TO_HOUSE && direction == 'E') {
                    cout << "You have entered the house." << endl;
                } else if (numSteps >= STEPS_TO_MAZE && direction == 'W') {
                    cout << "You have entered the maze." << endl;
                } else {
                    cout << "You don't see anything around you." << endl;
                }
                break;
            }

            // Attack
            case 'B': {
                cout << "You chose to attack!" << endl;
                break;
            }

            // Pick up item
            case 'C': {
                do {
                    if (knapsack.size() <= 6) { // If the knapsack isn't full (6 items) yet
                        randIndex = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
                        knapsack.push_back(items[randIndex]);
                        cout << "Picked up the " << items[randIndex] << ". ";
                        cout << "Enter P to pick up another item. "
                                "Enter any other key to return to the main menu." << endl;
                        cout << ">> ";
                        cin >> input;
                    } else { // If the knapsack is full
                        cout << "Your knapsack's full!" << endl;
                        break;
                    }
                } while (input == 'P'); // Pick up another item if directed, unless the knapsack is full
                break;
            }

            // Display sorted list of knapsack contents
            case 'D': {
                if (knapsack.empty()) {
                    cout << "Your knapsack is empty!" << endl;
                } else if (knapsack.size() >= 2) {
                    // Selection sort
                    for (int startScan = 0; startScan < (knapsack.size() - 1); startScan++) {
                        minIndex = startScan;
                        minValue = knapsack[startScan];
                        for (int index = startScan + 1; index < knapsack.size(); index++) {
                            if (knapsack[index] < minValue) {
                                minValue = knapsack[index];
                                minIndex = index;
                            }
                        }
                        knapsack[minIndex] = knapsack[startScan];
                        knapsack[startScan] = minValue;
                    }

                    cout << "Your knapsack contains: " << endl;
                    for (int index = 0; index < (knapsack.size() - 1); index++) {
                        cout << knapsack[index] << " ";
                        cout << endl;
                    }
                }
                break;
            }

            // Terminate the program
            case 'E': {
                cout << "Quitting..." << endl;
                return 0;
            }

            // Detects invalid input
            default: {
                cout << "That's not a valid option. Please try again.\n";
            }
        }
        cout << "Would you like to return to the main menu? [Y/N]" << endl;
        cout << ">> ";
        cin >> repeat;
    } while (repeat == 'Y'); // Repeats main menu on 'Y' input

    return 0;
}