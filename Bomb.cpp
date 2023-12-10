//Name: Bomb.cpp
//Author:  Mofe Okonedo
//Date:    11/16/23
//Desc: This file contains the source code for the Bomb weapon

#include "Bomb.h"

// Name: Bomb(int damage)
// Description: Creates a new Bomb
// Preconditions: None
// Postconditions: Can create a Bomb
Bomb::Bomb(int damage) : Weapon(damage) {

}

// Name: SpecialAttack
// Description: Defines the Bomb's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Bomb::SpecialAttack() {
    // Chooses a random number between 1/2 m_damage and 2 * m_damage

    int specialDamage = rand() % (2*GetDamage() - GetDamage()/2 + 1) + GetDamage()/2; // Random value between 1/2
    // m_damage and 2 * m_damage
    cout << "You throw a bomb and it explodes!" << endl;

    return specialDamage;
}
