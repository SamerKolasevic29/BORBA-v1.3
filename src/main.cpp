#include "../include/models/Fighter.h"
#include "../include/utils/Tools.h"
#include "../include/views/UI.h"
#include "../include/controllers/Forms.h"
#include "../include/views/Animation.h"


#include <vector>
#include <memory>
#include <iostream>


using std::cout;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using namespace UI;
using namespace Tools;
using namespace Forms;
using namespace Animation;

int main() {
    // 1. Roster inicialisation (base of all fighers on Heap)
    #ifdef _WIN32  
        enableAnsi(); 
    #endif
    vector<unique_ptr<Fighter>> Roster;

    // 2. load data from CSV
    // helper func
    vector<Fighter> tempRoster;
    bool loaded = loadCSV(tempRoster, "data/fighters.csv");
    
    // if it fails from data folder, try from root (fallback)
    if (!loaded) {
        loaded = loadCSV(tempRoster, "fighters.csv");
    }

    // move classic objects to unique_ptr (Modern C++ way)
    for (const auto& f : tempRoster) {
        Roster.push_back(make_unique<Fighter>(f));
    }

  
    loadingCSV(loaded);
    
    // if roster is empty, we cant play
    if (Roster.empty()) {
        cout << "Fatal Error: No fighters loaded! check fighters.csv\n";
        return 1;
    }

    // 3. main game loop
    bool running = true;
    bool firstRun = true;

    while (running) {
        // Show Menu and wait desicion
        int choice = showMainMenu(firstRun);
        firstRun = false; // next time it will show second version of menu

        switch (choice) {
            case 1: // VS Computer
                if (Roster.size() < 2) {
                    errorMessage(); // Requires 2 Fighters
                } else {
                    clearScreen();
                    runPvEScene(Roster);
                }
                break;

            case 2: // PvP
                if (Roster.size() < 2) {
                    errorMessage();
                } else {
                    runPvPScene(Roster);
                }
                break;

            case 3: // Fighters Info
                showFightersInfoScene(Roster);
                break;

            case 4: // Create Fighter
                if (runCreateFighterScene(Roster)) {
                    // success
                }
                break;

            case 5: // About Us
                showAboutUsScene();
                break;

            case 0: // Exit
                clearScreen();
                writeLine("Thanks for playing BORBA v1.3!\n", BRIGHT_CYAN, 50);
                wait(2);
                running = false;
                break;

            default:
                break;
        }
    }

    return 0;
}
