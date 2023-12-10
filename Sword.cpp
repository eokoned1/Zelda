//Name: Sword.cpp
//Author:  Mofe Okonedo
//Date:    11/16/23
//Desc: This file contains the source code for the Sword weapon

#include "Sword.h"

// Name: Sword(int damage)
// Description: Creates a new Sword
// Preconditions: None
// Postconditions: Can create a Sword
Sword::Sword(int damage) : Weapon(damage) {
}

// Name: SpecialAttack
// Description: Defines the Sword's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Sword::SpecialAttack() {
    // The special attack slashes and does between 1 and m_damage (twice)
    // For example, if m_damage is 4, it could do between 2 and 8 for a total of 10

    int specialDamage = (rand() % (GetDamage()) + 1)*2; // Random value between 1 and m_damage * 2
    cout << "You slash twice with a sword!" << endl;
    return specialDamage;
}
