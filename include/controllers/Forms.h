#ifndef FORMS_H
#define FORMS_H

#include <vector>
#include <memory>
#include "../models/Fighter.h"

namespace Forms {

    // Main menu (returns user's choice)
    int showMainMenu(bool isFirstRun);

    // PvP scene: choosing two fighters -> running Battle PvP
    void runPvPScene(const std::vector<std::unique_ptr<Fighter>>& roster); 

    // PvE scene: choosing two fighters (cs AI) -> running Battle PvE
    void runPvEScene(const std::vector<std::unique_ptr<Fighter>>& roster);

    // Creating fighter scene: Input -> validate -> Adding in Roster -> Save CSV
    // Returns true if its everything okay
    bool runCreateFighterScene(std::vector<std::unique_ptr<Fighter>>& roster);

    //Info scene: listing the roster (read-only)
    void showFightersInfoScene(const std::vector<std::unique_ptr<Fighter>>& roster);

    // About Us scene
    void showAboutUsScene();
}
#endif