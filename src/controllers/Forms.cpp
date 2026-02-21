#include "../../include/controllers/Forms.h"
#include "../../include/views/UI.h"
#include "../../include/models/Battle.h"
#include "../../include/utils/Tools.h"
#include "../../include/views/Animation.h"


#include <iostream>

using namespace UI;
using namespace Tools;
using namespace Animation;

namespace Forms {

    // Local helper for fast stats voiew of choesn Fighter
    void displayFighterPreview(const std::vector<std::unique_ptr<Fighter>>& roster, int index) {
        if (index < 0 || index >= (int)roster.size()) return;

        // receiving the stats from the chosen one
        const auto& f = *roster[index];

        writeLine("\n\t[PREVIEW] ", BRIGHT_CYAN, 30);
        writeLine(f.Name(), BRIGHT_WHITE, 30);
        writeLine("  HP:", BRIGHT_GREEN, 30);
        writeLine(f.HealthStr(), BRIGHT_GREEN, 30);
        writeLine("  ATK:", BRIGHT_RED, 30);
        writeLine(f.LightAttackStr(), BRIGHT_RED, 30);
        writeLine("  SPEC:", RED, 30);
        writeLine(f.SpecialAttackStr(), RED, 30);
        writeLine("  CRIT:", BRIGHT_YELLOW, 30);
        writeLine(f.CriticalStr(), BRIGHT_YELLOW, 30);
        std::cout << "\n";
    }

    int showMainMenu(bool isFirstRun) {
        clearScreen();
        if (isFirstRun) {
            firstMenu();
        } else {
            mainMenu();
        }
        return optionBox(FormContext::MAIN_MENU);
    }

    void runPvEScene(const std::vector<std::unique_ptr<Fighter>>& roster) {
        clearScreen();
        
        // 1. Show List
        chooseFighter(roster, 3);

        // 2. Choosing Fighter (Human)
        uint8_t p1_idx = optionBox(FormContext::PICK_FIGHTER, roster.size());
        displayFighterPreview(roster, p1_idx - 1);
        wait(2);
        
        clearScreen();

        // 3. Choosing Fighter (AI)
        chooseFighter(roster, 3, p1_idx);
        uint8_t p2_idx = optionBox(FormContext::PICK_FIGHTER, roster.size());
        displayFighterPreview(roster, p2_idx - 1);
        wait(2);

        // 4. Create Battle instance w/ selected Fighters 
        auto battle = std::make_unique<Battle>(*roster[p1_idx - 1], *roster[p2_idx - 1]);
        
        clearScreen();
        battle->startPvE(); // Run PvE game loop
        
        wait(3);
    }

    void runPvPScene(const std::vector<std::unique_ptr<Fighter>>& roster) {
        clearScreen();
        
        chooseFighter(roster, 3);

        uint8_t p1_idx = optionBox(FormContext::PICK_FIGHTER, roster.size());
        displayFighterPreview(roster, p1_idx - 1);
        wait(2);
        
        clearScreen();

        chooseFighter(roster, 3, p1_idx);
        uint8_t p2_idx = optionBox(FormContext::PICK_FIGHTER, roster.size());
        displayFighterPreview(roster, p2_idx - 1);
        wait(2);

        auto battle = std::make_unique<Battle>(*roster[p1_idx - 1], *roster[p2_idx - 1]);
        
        clearScreen();
        battle->startPvP(); // Run PvP game loop
        
        wait(3);
    }

    void showFightersInfoScene(const std::vector<std::unique_ptr<Fighter>>& roster) {
        clearScreen();
        fightersInfo(roster); // UI func works directly w/ unique_ptr
        optionBox(FormContext::ONLY_BACK);
    }

    bool runCreateFighterScene(std::vector<std::unique_ptr<Fighter>>& roster) {
        clearScreen();
        
        // 1. UI creates temporary object on stack
        Fighter nf = createFighterUI();

        // 2. Adding that object in Roster (on heap like unique_ptr)
        // std::move switches property (optimisation)
        roster.push_back(std::make_unique<Fighter>(std::move(nf)));

        // 3. Save in CSV
        // Using last element form roster (the one we just added)
        bool saved = writeCSV(*roster.back(), "data/fighters.csv");
        
        // Fallback: if data folder does not exist, save to root
        if (!saved) {
            writeCSV(*roster.back(), "fighters.csv");
        }

         wait(2);
        return true;
    }

}