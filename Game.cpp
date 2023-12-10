//Name: Game.cpp
//Author:  Mofe Okonedo
//Date:    11/16/23
//Desc: This file contains the source code for the Game class

#include "Game.h"

// Name: Game(string filename) - Overloaded Constructor
// Description: Creates a new Game
// Preconditions: None
// Postconditions: Initializes all game variables to defaults (constants)
// including m_myHero (null), m_curEnemy (null), filename (passed value),
// and starting area (START_AREA)
Game::Game(string filename) : m_myHero(nullptr), m_curArea(START_AREA) , m_curEnemy(nullptr), m_filename(filename) {
    srand(time(0)); // Seed to generate random number
    LoadMap();
}

// Name: ~Game
// Description: Destructor
// Preconditions: None
// Postconditions: Deallocates anything dynamically allocated
//                 in Game (weapons, enemies, and map)
Game::~Game() {

    for (Area* area : m_myMap) {
        delete area;
    }

    delete m_myHero;
    delete m_curEnemy;
}

// Name: LoadMap()
// Description: Dynamically creates areas and inserts them into
//              the m_myMap vector
// Note: the size of the map is not known - you should not use constants
//       Also, you can use stoi to convert strings to integers
// Precondition: m_filename is populated
// Postcondition: Map is populated with area objects.
void Game::LoadMap() {
    string name, description, ID, north, west, east, south;
    ifstream File(m_filename);
    if (File.is_open()) {
        while(getline(File, ID, DELIMITER)) {
            getline(File, name, DELIMITER);
            getline(File, description, DELIMITER);
            getline(File, north, DELIMITER);
            getline(File, east, DELIMITER);
            getline(File, south, DELIMITER);
            getline(File, west);
            int id = stoi(ID);
            int North = stoi(north);
            int West = stoi(west);
            int East = stoi(east);
            int South = stoi(south);
            Area * area = new Area(id, name, description, North, East, South, West);
            m_myMap.push_back(area);
        }
    }else{
        cout << "Could not open file" << endl;
    }


}

// Name: HeroCreation()
// Description: Populates m_myHero and asks name
// Preconditions: None
// Postconditions: m_myHero is populated (and m_name in m_myHero)
void Game::HeroCreation() {
    string heroName;
    cout << "Hero Name: ";
    cin >> heroName;

    m_myHero = new Hero(heroName, HERO_HEALTH);
}


// Name: Look()
// Description: Displays the current area's description and
//              the current enemy's desc (if there is one) otherwise, says
//              "It is peaceful here."
// Preconditions: None
// Postconditions: None
void Game::Look() {


    cout << m_myMap[m_curArea]->GetName() << endl
         << m_myMap[m_curArea]->GetDesc() << endl;

    if (m_curEnemy != nullptr) { // scan if there is an enemy in the area
        cout << m_curEnemy->GetDesc() << endl; // if there is give a descripton
    } else { // if there is not then print it is peaceful
        cout << "It is peaceful here." << endl;
    }

    cout << "Possible exits: "; // checks if there can be a move made to any of these directions and prints the exit
    if (m_myMap[m_curArea]->CheckDirection('N') != -1) cout << "N ";
    if (m_myMap[m_curArea]->CheckDirection('E') != -1) cout << "E ";
    if (m_myMap[m_curArea]->CheckDirection('S') != -1) cout << "S ";
    if (m_myMap[m_curArea]->CheckDirection('W') != -1) cout << "W ";
    cout << endl;

}


// Name: StartGame()
// Description: Welcomes the player to the game. Calls LoadMap, HeroCreation,
//              Randomizes an enemy, Look, and Action
// Preconditions: Input file must exist
// Postconditions: Map is loaded, User has chosen a hero to play with,
//                 prints the starting area, chooses a random enemy
//                 and calls action
void Game::StartGame() {
    cout << "Welcome to Legend Of Zelda!" << endl;
    LoadMap();
    HeroCreation();
    RandomEnemy();
    Look();
    Action();
}


// Name: Action()
// Description: Menu for game. Displays menu.
//              Player can look, move, attack, improve weapon, stats, or quit
//              Can only attack if there is actually a enemy in this area
// Preconditions: Everything in start has been completed
// Postconditions: Game continues until quit or player dies
void Game::Action() {
    char choice;
    do {
        cout << "What would you like to do?" << endl;
        cout << "1. Look\n2. Move\n3. Attack\n4. Improve Weapon\n5. Stats\n6. Quit\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case '1':
                Look();
                break;
            case '2':
                Move();
                break;
            case '3':
                Attack();
                break;
            case '4':
                ImproveWeapon();
                break;
            case '5':
                Stats();
                break;
            case '6':
                cout << "Thanks for playing! Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != '6' && m_myHero->GetHealth() > 0);
}


// Name: RandomEnemy()
// Description: Used to dynamically allocated a random enemy
//              (25% chance of nothing, 25% chance of Armos, 25% of Moblin, and
//               25% of Peahat.)
// Preconditions: None
// Postconditions: Populates m_curEnemy (sets to nullptr if nothing)
void Game::RandomEnemy() {
    int randNum = rand() % 4; //use rand to get a number between 0 and 3

    delete m_curEnemy; //deallocate memory of the other enemy since not in use

    switch (randNum) { // this the 25% chance of getting peaceful, armos, moblin or peahat
        case 0:
            m_curEnemy = nullptr;
            break;
        case 1:
            m_curEnemy = new Armos(ARMOS_NAME, ARMOS_HEALTH, ARMOS_DAMAGE, ARMOS_DESC);
            break;
        case 2:
            m_curEnemy = new Moblin(MOBLIN_NAME, MOBLIN_HEALTH, MOBLIN_DAMAGE, MOBLIN_DESC);
            break;
        case 3:
            m_curEnemy = new Peahat(PEAHAT_NAME, PEAHAT_HEALTH, PEAHAT_DAMAGE, PEAHAT_DESC);
            break;
    }
}

// Name: ImproveWeapon
// Description: Allows user to improve their weapon
// Preconditions: For each COST_IMPROVEMENT, damage in the weapon increases
//                by one.
// Postconditions: m_curHero's weapon is improved
void Game::ImproveWeapon() {
    if (m_myHero != nullptr) { //check if there is a hero
        int rupeesUsed = m_myHero->GetRupee() / COST_IMPROVEMENT;

        if (rupeesUsed > 0) { // see if there are rupees amount is adequate
            m_myHero->ImproveWeapon(rupeesUsed); // upgrade the weapon used by the hero
            cout << "Weapon improved! Damage increased by " << rupeesUsed << "." << endl;
        } else {
            cout << "You do not have enough rupees to upgrade your weapon." << endl;
        }
    } else {
        cout << "Error! \n";
    }
}


// Name: Move
// Description: Asks a player which direction they would like to move.
//              Moves player from one area to another (updates m_curArea)
//              Once successfully moved, chooses a new random enemy and
//              Calls Look
// Preconditions: Must be valid move (area must exist)
// Postconditions: Displays area information and new monster
void Game::Move() {
    char direction;
    bool validMove = false;

    while (!validMove) {
        cout << "Which direction? (N E S W) " << endl;
        cin >> direction;

        int nextAreaID = m_myMap[m_curArea]->CheckDirection(direction);

        if (nextAreaID != -1) {
            m_curArea = nextAreaID;
            RandomEnemy();
            Look();
            validMove = true;
        } else {
            // loops continues without condition so don't need to set to false
        }
    }
}


// Name: Attack
// Description: Allows player to attack an enemy.
// Preconditions: Must have enemy Enemy in current area
// Postconditions: Checks to make sure that there is an enemy to fight.
//                 Asks the user if they want to use a normal or special attack
//                 Updates health(hp) as battle continues.
//                 Both Hero and Enemy attack every round until
//                 one or more has <= 0 health
//                 May need to deallocate enemy Enemy to prevent memory leaks.
//                 When either Enemy or Hero <= 0 health, calls ProcessBattle
void Game::Attack() {
    if (m_curEnemy != nullptr) {
        cout << "Choose your attack:\n";
        cout << "1. Normal Attack\n";
        cout << "2. Special Attack\n";
        cout << "Enter your choice (1 or 2): ";

        char attackChoice;
        cin >> attackChoice;

        int heroDamage, enemyDamage;

        switch (attackChoice) { //chooses damage for hero and enemy depending on the ttack
            case '1':
                heroDamage = m_myHero->Attack();
                enemyDamage = m_curEnemy->Attack();
                break;
            case '2':
                heroDamage = m_myHero->SpecialAttack();
                enemyDamage = m_curEnemy->SpecialAttack();
                break;
            default:
                cout << "Invalid choice. Using Normal Attack.\n";
                heroDamage = m_myHero->Attack();
                enemyDamage = m_curEnemy->Attack();
                break;
        }

        while (m_myHero->GetHealth() > 0 && m_curEnemy->GetHealth() > 0) { //keep fighting until one dies

            m_myHero->SetHealth(m_myHero->GetHealth() - enemyDamage);
            m_curEnemy->SetHealth(m_curEnemy->GetHealth() - heroDamage); // Updating enemy's health

            cout << "You dealt " << heroDamage << " damage to the enemy." << endl;
            cout << "The enemy dealt " << enemyDamage << " damage to you." << endl;

            if (m_myHero->GetHealth() > 0 && m_curEnemy->GetHealth() > 0) { // if they are both alive display hp of both
                cout << m_myHero->GetName() << " Health: " << m_myHero->GetHealth();
                cout << "\tEnemy Health: " << m_curEnemy->GetHealth() << endl;
            }

            if (m_myHero->GetHealth() > 0 && m_curEnemy->GetHealth() > 0) {
                // Show menu of options of prompt for player while they are battling each other
                cout << "\nChoose your attack:\n";
                cout << "1. Normal Attack\n";
                cout << "2. Special Attack\n";
                cout << "Enter your choice (1 or 2): ";

                cin >> attackChoice;

                switch (attackChoice) {
                    case '1':
                        heroDamage = m_myHero->Attack(); // Hero's normal attack

                        if (rand() % 4 == 0) { // gives 25% chance of an enemy to use a special attack or normal
                            enemyDamage = m_curEnemy->SpecialAttack();
                        } else {
                            enemyDamage = m_curEnemy->Attack();
                        }
                        break;
                    case '2':
                        heroDamage = m_myHero->SpecialAttack(); // Hero special attack

                        if (rand() % 4 == 0) {
                            enemyDamage = m_curEnemy->SpecialAttack();
                        } else {
                            enemyDamage = m_curEnemy->Attack();
                        }
                        break;
                    default:
                        cout << "Invalid choice. Using Normal Attack.\n";
                        heroDamage = m_myHero->Attack();
                        if (rand() % 4 == 0) {
                            enemyDamage = m_curEnemy->SpecialAttack();
                            cout << "The enemy used a special attack!\n";
                        } else {
                            enemyDamage = m_curEnemy->Attack();
                        }
                        break;
                }
            }
        }

        ProcessBattle(m_curEnemy->GetHealth() > 0, m_myHero->GetHealth() > 0);
    } else {
        cout << "No enemy to attack.\n"; // print this if the area is peaceful
    }
}


// Name: Stats()
// Description: Displays the information about the hero (name, health, rupees)
// Preconditions: None
// Postconditions: None
void Game::Stats() {
    if (m_myHero != nullptr) {
        cout << "Hero Name: " << m_myHero->GetName() << "\nHealth: " << m_myHero->GetHealth() //call getters do display
             << "\nRupees: " << m_myHero->GetRupee() << "\nWeapon Damage: "
             << m_myHero->Attack() << endl;
    } else {
        cout << "Error: Hero does not exist.\n";
    }
}

// Name: ProcessBattle
// Description: Called when either the enemy or hero have no health left
//       Displays who won (Enemy, Hero, mutual destruction)
//       If hero wins, gives RUPEES_WIN and resets health to starting value
// Preconditions: Enemy or hero are <= 0 health
// Postconditions:
void Game::ProcessBattle(bool enemyAlive, bool alive) {
    if (!alive) {
        cout << "You have been defeated by the enemy!\n"; // print this when hero gets to 0 or negative health
        cout << "Game over. Thanks for playing!\n";
    } else if (!enemyAlive) {
        m_myHero->SetRupee(m_myHero->GetRupee() + RUPEES_WIN);
        m_myHero->SetHealth(HERO_HEALTH);
        cout << "You have defeated the enemy!\n";
        cout << "You have earned " << m_myHero->GetRupee()  << " rupees." << endl; //show the rupees that hero earned
    } else {
        cout << "It's a draw! Both you and the enemy have been defeated.\n";
        cout << "Game over. Thanks for playing!\n";
    }
}
