#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
#include <cstdint>
#include "../models/Fighter.h"
#include "Animation.h"

namespace UI {

    // Enums for menu context and attacks
    enum class FormContext {
        MAIN_MENU = 1,
        ONLY_BACK = 2,
        PICK_FIGHTER = 3,
        BATTLE = 4
    };

    enum class AttackType {
        LIGHT = 1,
        SPECIAL = 2,
        CRITICAL = 3
    };

    // ---[ HELPERS ]---
    void clearScreen();
    void clearLines(int count);
    void moveDown(int count);
    void hideCursor();
    void showCursor();
    void errorMessage();

    // ---[ LOADING & LOGOS ]---
    void loadingCSV(bool loaded);
    void loadingBattle(const std::string& f1,  const std::string& f2);
    void fighterThinking(const std::string& f);
    void appearLogo();
    void printLogo();

    // ---[ MENUS ]---
    void firstMenu();
    void mainMenu();
    void aboutUs();

    // ---[ INPUT & CREATION ]---
    std::string inputName();
    int inputPositiveInt(const std::string& msg, Animation::Color c);
    uint8_t inputCritChance();
    Fighter createFighterUI();

    // ---[ FIGHTER LIST ]---
    void fightersInfo(const std::vector<Fighter>& list);

    // ---[ 'choose your fighter' LIST ]---
    void chooseFighter(const std::vector<Fighter>& f, int fightersPerRow = 3, int option = -1);

    // ---[BATTLE HUD]---
    void fightInfoBar(const Fighter& f1, const Fighter& f2);
    void fightTurnBar(const Fighter& f);
    void fightOptionBar(const Fighter& f);

    // ---[ATTACK COMPONENT]---
    void fightAttackBar(const Fighter& f1, const Fighter& f2, AttackType a);

    // ---[WINNDR BAR]---
    void fightWinnerBar(const Fighter& winner);

    // ---[MAIN INPUT HANDLER]---
    uint8_t optionBox(FormContext m, int limit = 255);

}
#endif