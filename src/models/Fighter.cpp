#include "Fighter.h"

using std::string;
using std::to_string;

// Default Constructor
Fighter::Fighter()
    : _name("Unknown"), _health(0), _lightAttack(0), _specialAttack(0),  
      _critical(0), _flagSpecial(false) {}

// Parameterized Constructor
Fighter::Fighter(string n, int h, int la, int sa, uint8_t c)
    : _name(n), _health(h), _lightAttack(la), _specialAttack(sa),
    _critical(c), _flagSpecial(false) {}

// Copy Constructor
Fighter::Fighter(const Fighter& f) 
    : _name(f._name), _health(f._health), _lightAttack(f._lightAttack),
      _specialAttack(f._specialAttack), _critical(f._critical), _flagSpecial(false) {}


// ---[ GETTERS ]---
string Fighter::Name() const       { return _name; }
int Fighter::Health() const        { return _health; }
int Fighter::LightAttack() const   { return _lightAttack; }     
int Fighter::SpecialAttack() const { return _specialAttack; }
uint8_t Fighter::Critical() const  { return _critical; }
bool Fighter::FlagSpecial() const  { return _flagSpecial; }
bool Fighter::isAlive() const      { return _health > 0; }

// ---[ SETTERS ]---
void Fighter::setName(const string& n) { _name = n; }
void Fighter::setHealth(int h)         { _health = h; }
void Fighter::setLightAttack(int la)   { _lightAttack = la; }
void Fighter::setSpecialAttack(int sa) { _specialAttack = sa; }
void Fighter::setCritical(uint8_t c)   { _critical = c; }
void Fighter::setFlag(bool f)          { _flagSpecial = f; }

// ---[ STRING FORMATTERS ]---
string Fighter::HealthStr() const        { return to_string(_health) + "HP"; }
string Fighter::LightAttackStr() const   { return to_string(_lightAttack) + "ATK"; }
string Fighter::SpecialAttackStr() const { return to_string(_specialAttack) + "ATK"; }
string Fighter::CriticalStr() const      { return to_string(_critical) + "%"; }

// ---[ COMBAT LOGIC ]---
void Fighter::lAttack(Fighter& b) {
    b.setHealth(b.Health() - this->LightAttack());
}

void Fighter::sAttack(Fighter& b) {
    b.setHealth(b.Health() - this->SpecialAttack());
}

void Fighter::cAttack(Fighter& b) {
    //Critical is 2x Light Attack
    b.setHealth(b.Health() - 2 * this->LightAttack());
}