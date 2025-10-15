// File: Monsters.cpp
// Author: Saif Abu Hananah
// Date: 22/May/2025
// Program 3: Monstertale - A Monster-Taming Game
// Class: CS302

#include "Monsters.h"

// Initializes the Monster’s name and health.
Monster::Monster(const string &name, int health) : name(name), health(health){}

// Accessor for this monster’s name to use in the tree.
string Monster::getName() const { return name; }

// Utility to roll a 20-sided die, returning 1–20.
int Monster::rollD20(){return rand() % 20 + 1;}

//Dragon Class
// default constructor
Dragon::Dragon() : Monster("", 0),isHibernating(false),firePower(0){}

// Dragon: destructor
Dragon::~Dragon(){}

// Randomly assigns a dragon name from a preset list (plus “#id” for uniqueness),
// random health (50–100), hibernation status, and fire power (10–100).
int Dragon::input(int id){
    static const vector<string> dragonNames = {
    "Igris", "Stormfly", "Kaisel", "Kamish", "Toothless"
    };
    // pick a random name
    name = dragonNames[rand() % dragonNames.size()] + "#" + to_string(id);
    // random health & unique stats
    health = rand() % 51 + 50;   // 50–100
    isHibernating= rand() % 2;         // true/false
    firePower = rand() % 91 + 10;   // 10–100
    return 1;
}

// Prints the dragon’s current stats
int Dragon::display()const{
     cout << "Dragon [" << name << "] HP:" << health << " Hibernation: " << isHibernating << " FirePower: "<< firePower << endl;
    return 1;
}

// Rolls a d20 plus the taming tool quality and compares against a threshold.
bool Dragon::attemptTame(int tamingToolQuality) {
    cout << "You need to roll atleast 20 if its hibernating or 15 otherwise!" << endl;
    int roll = rollD20();
    int total = roll + tamingToolQuality;
    cout << name << " You Rolled: " << roll << ", Quality: " << tamingToolQuality << ", Total: " << total << endl;
    int threshold = isHibernating ? 20 : 15;
    return total >= threshold;
}

// Increases health by food amount plus a fraction of firePower.
int Dragon::feed(int foodAmount) {
    health += foodAmount + firePower / 10;
    cout << name << " eats " << foodAmount << ", new HP: " << health << endl;
    return 1;
}

// Prints the dragon’s unique action (breathing fire).
int Dragon::specialAction() {
    cout << name << " breathes fire with power " << firePower << "!" << endl;
    return 1;
}

//Unicorn Class
// Unicorn: default constructor
Unicorn::Unicorn() :Monster("", 0), hornLength(0), hasHealingAura(false) {}

// Unicorn: destructor
Unicorn::~Unicorn() {}

// Randomly assigns a unicorn name from a preset list (plus “#id” for uniqueness),
// random health (50–100), horn length (1–10), and healing aura flag.
int Unicorn::input(int id) {
    static const vector<string> unicornNames = {
    "Celestia","Luna","Twilight","Sunset","Cadence"
    };
    name = unicornNames[rand() % unicornNames.size()]+ "#" + to_string(id);
    health = rand() % 51 + 50;  // 50–100
    hornLength = rand() % 10 + 1;   // 1–10
    hasHealingAura = rand() % 2;
    return 1;
}

// Prints the unicorn’s current stats (name, HP, horn length, aura).
int Unicorn::display() const {
    cout << "Unicorn [" << name << "], HP: " << health << ", Horn: " << hornLength << ", Healing Aura: " << hasHealingAura << endl;
    return 1;
}

// Rolls a d20 plus the taming tool quality and compares against a threshold.
bool Unicorn::attemptTame(int tamingToolQuality) {
    cout << "You need to roll atleast 10 if it has healing aura or 5 otherwise!:" <<endl;
    int roll = rollD20();
    int total = roll + tamingToolQuality;
    cout << name << " You Rolled: " << roll << ", Quality: " << tamingToolQuality << ", Total Roll: " << total << endl;
    int threshold = hasHealingAura ? 10 : 5;
    return total >= threshold;
}

// Increases health by food amount plus a fraction of horn length, and
// grows the horn slightly based on food.
int Unicorn::feed(int foodAmount) {
    health += foodAmount + (hornLength / 5);
    hornLength += foodAmount * 0.1;
    cout << name << " eats " << foodAmount << ", New HP: " << health << ", New Horn: " << hornLength << endl; 
    return 1;
}

// Prints the unicorn’s unique action (healing).
int Unicorn::specialAction() {
    cout << name << " heals for: " << hornLength << " points!" << endl;
    return 1;
}

//Symbiote Class

Symbiote::Symbiote() : Monster("",0), symbioteLevel(0), bondStrength(0.0) {}

//Destructor
Symbiote::~Symbiote() {}

// Randomly pick a name and stats for this Symbiote
int Symbiote::input(int id){
    static const vector<string> symbioteNames = {
    "Venom", "Carnage", "Scream", "Mayhem", "Knull"
    };
    name = symbioteNames[rand() % symbioteNames.size()]+ "#" + to_string(id);
    health = rand() % 51 + 50;      // 50–100
    symbioteLevel = rand() % 5 + 1;        // 1–5
    bondStrength = (rand() % 26 + 5) / 10.0; // 0.5–3.0
    return 0;
}

//Displays monster
int Symbiote::display() const {
    cout << "Symbiote [" << name << "] HP:" << health << " Level:" << symbioteLevel << " Possible Bond:" << bondStrength << endl;
    return 0;
}
//Roll a d20 + tool quality and compare against dynamic threshold
bool Symbiote::attemptTame( int tamingToolQuality){
    cout << "The Mininum roll u need is: " << symbioteLevel*bondStrength << endl;
    int roll = rollD20();
    int total = roll + tamingToolQuality;
    cout << name << " You Rolled: " << roll << ", Quality: " << tamingToolQuality << ", Total Roll: " << total << endl;
    double dynamicThreshold = (symbioteLevel * bondStrength) +5;
    return total >= static_cast<int>(dynamicThreshold);
}
// Increase HP by foodAmount plus symbioteLevel bonus
int Symbiote::feed(int foodAmount) {
    health += foodAmount + symbioteLevel;
    cout << name << " absorbs " << foodAmount << ", new HP: " << health << endl;
  return 0;
}
// Show this Symbiote’s unique action
int Symbiote::specialAction() {
    cout << name << " shifts forms and smiles evilly! " << endl;
  return 0;
}
// RTTI-only method for downcasting
int Symbiote::mergeWithHost() {
    cout << name << " merges with you as its host at level " << symbioteLevel << "!" << endl;
  return 0;
}
