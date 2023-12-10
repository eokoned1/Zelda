//Name: Hero.cpp
//Author:  Mofe Okonedo
//Date:    11/16/23
//Desc: This file contains the source code for the Hero!

#include "Hero.h"

// Name: Hero(string name, int health) - Overloaded Constructor
// Description: Used for hero. Provides random weapon using RandomWeapon.
// Preconditions: None
// Postconditions: Used to populate hero (Link)
Hero::Hero(string name, int health) : m_name(name), m_health(health), m_rupees(0), m_weapon(nullptr) {
    RandomWeapon(); // Randomly assign a starting weapon
}

// Name: ~Hero Destructor
// Description: Deallocates the weapon
// Preconditions: None
// Postconditions: Used to deallocate anything dynamically allocated
Hero::~Hero() {
    delete m_weapon; // Deallocate the weapon
}

// Name: Attack()
// Description: Calls the weapon's attack
// Preconditions: None
// Postconditions: Returns damage
int Hero::Attack() {
    if (m_weapon != nullptr) {
        return m_weapon->Attack();
    } else {
        // If the hero has no weapon, use a default base damage
        return WEAPON_BASE;
    }
}

// Name: GetName()
// Description: Returns the current name
// Preconditions: None
// Postconditions: Returns the current name
string Hero::GetName() {
    return m_name;
}

// Name: SetName()
// Description: Updates m_name with a new name
// Preconditions: None
// Postconditions: Updates m_name
void Hero::SetName(string name) {
    m_name = name;
}

// Name: GetHealth()
// Description: Returns the health of the hero
// Preconditions: None
// Postconditions: Returns the health of the hero
int Hero::GetHealth() {
    return m_health;
}

// Name: SetHealth(int)
// Description: Updates m_health of the hero
// Preconditions: None
// Postconditions: Updates m_health of the hero
void Hero::SetHealth(int health) {
    m_health = health;
}

// Name: GetRupee()
// Description: Returns the rupee of the hero
// Preconditions: None
// Postconditions: Returns the rupee of the hero
int Hero::GetRupee() {
    return m_rupees;
}

// Name: SetRupee(int)
// Description: Updates m_rupee of the hero
// Preconditions: None
// Postconditions: Updates m_rupee of the hero
void Hero::SetRupee(int rupees) {
    m_rupees = rupees;
}

// Name: RandomWeapon
// Description: Dynamically allocates random weapon (sword, bomb, or boomerang)
//              Indicates which weapon the hero starts with.
// Preconditions: Called when hero is instantiated
// Postconditions: Updates m_weapon to point at random weapon
void Hero::RandomWeapon() {
    // Dynamically allocate a random weapon (sword, bomb, or boomerang)
    int randNum = rand() % 3; // 0 to 2
    std::string weaponName;

    switch (randNum) {
        case 0:
            weaponName = "swords";
            m_weapon = new Sword(WEAPON_BASE);
            break;
        case 1:
            weaponName = "bombs";
            m_weapon = new Bomb(WEAPON_BASE);
            break;
        case 2:
            weaponName = "boomerangs";
            m_weapon = new Boomerang(WEAPON_BASE);
            break;
    }

    cout << "You start with " << weaponName << "!" << endl;
}

// Name: ImproveWeapon()
// Description: Improves m_weapon (1 damage for each 3 rupees) by calling
//              the weapon's ImproveWeapon
// Preconditions: None
// Postconditions: Increases m_weapon and decreases m_rupees
void Hero::ImproveWeapon(int rupeesSpent) {
    // Improve m_weapon (1 damage for each 3 rupees) by calling the weapon's ImproveWeapon
    if (m_weapon != nullptr) {
        m_weapon->ImproveWeapon(rupeesSpent);
    }
    // Decrease the hero's rupees
    m_rupees -= rupeesSpent;
}

// Name: SpecialAttack()
// Description: Calls the weapon's special attack
// Preconditions: None
// Postconditions: Used to attack an enemy using the weapon's special attack
int Hero::SpecialAttack() {
    if (m_weapon != nullptr) {
        return m_weapon->SpecialAttack();
    } else {
        // If the hero has no weapon, return the base value for special attack
        return WEAPON_BASE;
    }
}

// Name: Overloaded <<
// Description: Prints the details of the hero (just name and health)
// Preconditions: None
// Postconditions: Returns an ostream with output of hero
ostream& operator<<(ostream& os, Hero& hero) {
    os << "Name: " << hero.m_name << "\nHP: " << hero.m_health;
    return os;
}
