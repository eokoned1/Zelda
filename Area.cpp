//Name: Area.cpp
//Author:  Mofe Okonedo
//Date:    11/16/23
//Desc: This file contains the source code details for area

#include "Area.h"

//Name: Area (Overloaded Constructor)
//Precondition: Must have valid input for each part of a area
// First int is the unique identifier for this particular area.
// The first string is the name of the area
// The second string is the description of the area
// The last four ints are the unique identifier for adjacent areas
//     (-1 = no path)
// North, East, South, and West
//Postcondition: Creates a new area
Area::Area(int ID, string name, string desc, int north, int east, int south, int west)
        : m_ID(ID), m_name(name), m_desc(desc) {
    // Setting all the directions for the area
    m_direction[N] = north;
    m_direction[E] = east;
    m_direction[S] = south;
    m_direction[W] = west;
}

//Name: GetName
//Precondition: Must have valid area
//Postcondition: Returns area name as string
string Area::GetName() {
    return m_name;
}

//Name: GetID
//Precondition: Must have valid area
//Postcondition: Returns area id as int
int Area::GetID() {
    return m_ID;
}

//Name: GetDesc
//Precondition: Must have valid area
//Postcondition: Returns area desc as string
string Area::GetDesc() {
    return m_desc;
}

//Name: CheckDirection
//Precondition: Must have valid area
//You pass it a char (N/n, E/e, S/s, or W/w) and if that is a valid exit it
//returns the ID of the area in that direction
//Postcondition: Returns id of area in that direction if the exit exists
//If there is no exit in that direction, returns -1
int Area::CheckDirection(char myDirection) {
    int directionID = -1; // Default to no exit in that direction

    switch (myDirection) {
        case 'N':
        case 'n': //check for upper and lower case to move in that direction
            directionID = m_direction[N];
            break;
        case 'E':
        case 'e':
            directionID = m_direction[E];
            break;
        case 'S':
        case 's':
            directionID = m_direction[S];
            break;
        case 'W':
        case 'w':
            directionID = m_direction[W];
            break;
    }

    return directionID;
}

//Name: PrintArea
//Precondition: Area must be complete
//Postcondition: Outputs the area name, area desc, then possible exits
void Area::PrintArea() {
    // Output area information and possible exits
    cout << "Area: " << m_name << "\nDescription: " << m_desc << "\nPossible Exits: ";

    for (int i = 0; i < 4; i++) { // loop over the directions
        if (m_direction[i] != -1) {
            switch (i) { // use enums to output navigation
                case N:
                    cout << "N ";
                    break;
                case E:
                    cout << "E ";
                    break;
                case S:
                    cout << "S ";
                    break;
                case W:
                    cout << "W ";
                    break;
            }
        }
    }

    cout << endl;
}
