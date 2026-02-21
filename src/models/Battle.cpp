#include "../../include/models/Battle.h"
#include "../../include/views/UI.h"
#include "../../include/utils/Tools.h"
#include "../../include/views/Animation.h" // Animation::delay

using namespace UI;  // too much UI:: ...
using namespace Tools; // for randomInt

Battle::Battle(const Fighter& f1, const Fighter& f2) 
    : _turnFlag(false) 
{
    // make_unique is RAII method
    _player1 = std::make_unique<Fighter>(f1);
    _player2 = std::make_unique<Fighter>(f2);
}

Fighter& Battle::attacker() {
    return _turnFlag ? *_player2 : *_player1;
}

Fighter& Battle::defender() {
    return _turnFlag ? *_player1 : *_player2;
}

void Battle::switchTurn() {
    _turnFlag = !_turnFlag;
}

void Battle::executeTurn(int choice) {
    Fighter& att = attacker();
    Fighter& def = defender();
    
    clearScreen();

    
    if (choice == 1) {
        int chance = randomInt(1, 100);
        
        // Critical Logic
        if (chance <= att.Critical()) {
            att.cAttack(def); // 2x damage
            fightAttackBar(att, def, AttackType::CRITICAL);
        } else {
            att.lAttack(def); // Normal damage
            fightAttackBar(att, def, AttackType::LIGHT);
        }
    }
    // 2 = Special Attack (if not used)
    else if (choice == 2) {
        // Provjera flag-a
        if (!att.FlagSpecial()) {
            att.sAttack(def);
            att.setFlag(true); // after using set flagSpecial as true
            fightAttackBar(att, def, AttackType::SPECIAL);
        } else {
            
            att.lAttack(def); //only LightAttack
            fightAttackBar(att, def, AttackType::LIGHT);
        }
    }
    
    // UI pause
    Animation::wait(2);
    clearScreen();
    switchTurn();

}

int Battle::aiDecideMove() {
    Fighter& bot = attacker();
    
    // AI Thinking animation
    fighterThinking(bot.Name());
    
    // Logic: if AI has Special, 40% chance he wil use
    if (!bot.FlagSpecial() && randomInt(1, 100) > 60) {
        return 2; // Special
    }
    
    return 1; // Light (default)
}

void Battle::startPvP() {
    // Loading animation
    loadingBattle(_player1->Name(), _player2->Name());
    clearScreen();

    // Main BAttle loop
    while (_player1->isAlive() && _player2->isAlive()) {
        
        fightInfoBar(*_player1, *_player2);
        fightTurnBar(attacker());
        fightOptionBar(attacker());

        // Input handler (UI)
        // Limited options, only 1 and 2 (Light, Special)
        uint8_t choice = optionBox(FormContext::BATTLE);

        // Validation for option 2
        if (choice == 2 && attacker().FlagSpecial()) {
            errorMessage(); // "Used!"
            continue; // Vrati na pocetak petlje
        }

        executeTurn(choice);
    }
    
    // ending, winner
    clearScreen();
    Fighter& winner = _player1->isAlive() ? *_player1 : *_player2;
    fightWinnerBar(winner);
}

void Battle::startPvE() {
    loadingBattle(_player1->Name(), _player2->Name());
    clearScreen();

    while (_player1->isAlive() && _player2->isAlive()) {
        
        fightInfoBar(*_player1, *_player2);
        fightTurnBar(attacker());

        int choice;

        // if it's AI's turn (Player 2)
        if (_turnFlag) {
            choice = aiDecideMove();
        } 
        // if it's player's turn (Player 1)
        else {
            fightOptionBar(attacker());
            choice = optionBox(FormContext::BATTLE);

            if (choice == 2 && attacker().FlagSpecial()) {
                errorMessage();
                continue;
            }
        }

        executeTurn(choice);
    }

    clearScreen();
    Fighter& winner = _player1->isAlive() ? *_player1 : *_player2;
    fightWinnerBar(winner);
}