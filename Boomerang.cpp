//Name: Boomerang.cpp
//Author:  Mofe Okonedo
//Date:    11/16/23
//Desc: This file contains the source code for the Boomerang weapon

#include "Boomerang.h"

// Name: Boomerang(int damage)
// Description: Creates a new Boomerang
// Preconditions: None
// Postconditions: Can create a Boomerang
Boomerang::Boomerang(int damage) : Weapon(damage) { // use of initialization list

}

// Name: SpecialAttack
// Description: Defines the Boomerang's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Boomerang::SpecialAttack() {
    // Chooses a random number between 1 and m_damage twice (once out and once back)

    int hit = (rand() % GetDamage() + 1);

    cout << "You throw a boomerang and it does " << hit << " damage on the way out and " << hit << " damage on the way back!" << endl;

    // return the hit doubled
    return hit * 2;
}
