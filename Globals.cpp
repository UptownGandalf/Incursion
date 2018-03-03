#include "stdafx.h"
#include "Globals.h"
#include "GameLogic.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

int fuel = 0;
int marines = 0;
int cash = 500;
int facilityHP = 3000;
int swarm = 1;
int generators = 0;
int sentries;
int depots;
bool marinesDefending = false;
int turnspassed = 0;
int marineLifeLeft = 50;

string command;
GameLogic gameLogic;
GlobalFunctions globalFunctionsActual;

void GlobalFunctions::CheckSave()
{
	ifstream save_file("saveGame.txt");
	if (save_file.good())
	{
		cout << "Save file found. Would you like to load it?" << endl;
		cin >> command;
		if (command == "yes" || "Yes" || "y")
		{

		}
		else
		{
			cout << "Starting a new game..." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			gameLogic.StatusUpdate();
		}
	}
	else
	{
		cout << "No save files found. Launching a new game..." << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		gameLogic.StatusUpdate();
	}
}

void GlobalFunctions::Help()
{
	system("CLS");
	cout << "Opening your Game Manual file now." << endl;
	cout << "When you're done, enter any value to start the game." << endl;
	ifstream helpFile("help.txt");
	cin >> command;
	if (command == "" || "input")
	{
		globalFunctionsActual.CheckSave();
	}
}