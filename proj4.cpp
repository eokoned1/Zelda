//Name: proj4.cpp
//Author:  Mofe Okonedo
//Date:    11/16/23
//Desc: This file contains the main function for project 4

#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
    if( argc != 2) {
        cout << "This requires a map file to be loaded." << endl;
        cout << "Usage: ./proj4 proj4_map1.txt" << endl;
    }

    cout << "Loading file: " << argv[1] << endl << endl;

    string mapName = argv[1];
    srand (time(NULL));
    Game g(mapName);
    g.StartGame();
    return 0;
}

