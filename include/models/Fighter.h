#ifndef FIGHTER_H
#define FIGHTER_H

#include <string>
#include <cstdint>

class Fighter {
private:
    std::string _name;
    int _health;
    int _lightAttack;
    int _specialAttack;
    uint8_t _critical;
    bool _flagSpecial;

public:
    // Constructors
    Fighter();
    Fighter(std::string n, int h, int la, int sa, uint8_t c);
    Fighter(const Fighter& f);

    // Getters 
    std::string Name() const;
    int Health() const;
    int LightAttack() const;
    int SpecialAttack() const;
    uint8_t Critical() const;
    bool FlagSpecial() const;
    bool isAlive() const;

    // Setters
    void setName(const std::string& n);
    void setHealth(int h);
    void setLightAttack(int la);
    void setSpecialAttack(int sa);
    void setCritical(uint8_t c);
    void setFlag(bool f);

    // String formatters (UI helpers)
    std::string HealthStr() const;
    std::string LightAttackStr() const;
    std::string SpecialAttackStr() const;
    std::string CriticalStr() const;
    

    // Combat Logic
    void lAttack(Fighter& b); // Light Attack
    void sAttack(Fighter& b); // Special Attack
    void cAttack(Fighter& b); // Critical Attack

};

#endif //FIGHTER_H