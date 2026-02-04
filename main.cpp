// File: main.cpp
// Author: Saif Abu Hananah
// Date: 22/May/2025
// Monstertale - A Monster-Taming Game

#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include "tree.h"
#include "Monsters.h"

using namespace std;

//Exception handling
struct InputError {
    string msg;
};

// ——— Input validation helpers ———
char getYesNo(const string& prompt) {
    char c;
    while (true) {
        cout << prompt;
        if (!(cin >> c)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [Invalid input] Please enter 'y' or 'n'.\n";
            continue;
        }
        c = tolower(c);
        if (c=='y' || c=='n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return c;
        }
        cout << "  [Invalid] Please enter 'y' or 'n'.\n";
    }
}

int getIntInRange(const string& prompt, int min, int max) {
    int attempts = 0;
    while (true) {
        cout << prompt;
        int x;
        if (cin >> x && x >= min && x <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (++attempts >= 3) {
            throw InputError{"Too many invalid integer inputs."};
        }
        cout << "  [Invalid] Enter an integer between "
             << min << " and " << max << ".\n";
    }
}

int main() {
    // seed RNG
    srand(static_cast<unsigned>(time(nullptr)));

    Tree234   tree;           // holds all tamed monsters (sorted by name)
    int       userTamed = 0;  // how many the human has tamed
    int       encounterId = 0;

    cout << "=== Monstertale - A Monster-Taming Game ===\n\n";
    
    //Exception Handling
    try{
     // Game loop
     while (true) {
        encounterId++;
        unique_ptr<Monster> monster;
        int type = rand() % 3;  // 0=Dragon, 1=Unicorn, 2=Symbiote
        switch (type) {
            case 0: monster = make_unique<Dragon>();  
                break;
            case 1: monster = make_unique<Unicorn>(); 
                break;
            default: monster = make_unique<Symbiote>();
                break;
        }
        monster->input(encounterId);
        cout << "\nA wild monster appears:\n";
        monster->display();

        // Ask to attempt tame
        if (getYesNo("Attempt to tame this monster? (y/n): ") == 'y') {
            int quality = getIntInRange("  Taming tool quality (1–10): ", 1, 10);
            bool success = monster->attemptTame(quality);
            cout << (success ? "  >> You tamed it!\n" : "  >> Tame failed.\n");

            if(success){
                int foodAmt = getIntInRange("  How much to feed (1–10): ", 1, 10);
                monster->feed(foodAmt);
                monster->specialAction();
                Symbiote* sym = dynamic_cast<Symbiote*>(monster.get());
                if (sym) {
                    sym->mergeWithHost();
                } 
                tree.insert(move(monster));
                userTamed++;
                cout << "  [You’ve tamed " << userTamed << " monsters]\n";
                if (userTamed >= 10) {
                    cout << "\nYou’ve reached 10 tamed monsters! Game over.\n";
                    break;
                }
            }
        }

        // Continue or quit?
        if (getYesNo("Keep Venturing Forth? (y/n): ") == 'n') {
            cout << "\nYou chose to stop the adventure.\n";
            break;
        }
     }
    }
    catch (const InputError& e) {
        cerr << "[InputError] " << e.msg << "\nExiting game.\n";
        return 1;
    }
    // Generate NPC results (Players 2–5)
    const int numNPC = 4;
    vector<int> npcTamed(numNPC);
    for (int i = 0; i < numNPC; ++i) {
        npcTamed[i] = rand() % 11;  // 0–10
    }

    // Show final standings
    cout << "\n=== Final Standings ===\n";
    cout << "Player 1 (You): " << userTamed << "\n";
    for (int i = 0; i < numNPC; ++i) {
        cout << "Player " << (i + 2) << " (NPC): " << npcTamed[i] << "\n";
    }
    int bestNPC = *max_element(npcTamed.begin(), npcTamed.end());
    if      (userTamed >  bestNPC) cout << "\n!!You win!!\n";
    else if (userTamed == bestNPC) cout << "\nIt's a tie!\n";
    else                            cout << "\nSorry, you lose.\n";

    // Display the tree of YOUR tamed monsters
    cout << "\nYour Tamed Monsters (sorted by name):\n";
    tree.display();

    // Clean up
    tree.removeAll();
    cout << "\nThanks for playing!\n";
   
    return 0;
}
