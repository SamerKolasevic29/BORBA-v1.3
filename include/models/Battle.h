#ifndef BATTLE_H
#define BATTLE_H

#include <memory>  // std::unique_ptr
#include "Fighter.h"

class Battle {
private:
    std::unique_ptr<Fighter> _player1;
    std::unique_ptr<Fighter> _player2;

    bool _turnFlag; // false = player1, true = player2

    // Helpers
    Fighter& attacker();
    Fighter& defender();
    void switchTurn();

public:
    Battle(const Fighter& f1, const Fighter& f2);
    ~Battle() = default;

    void startPvP();
    void startPvE();

private: 
    void executeTurn(int choice);
    int aiDecideMove();
}; 

#endif
