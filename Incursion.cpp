// Incursion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Globals.h"
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <iomanip>
#include <thread>
#include <iostream>
#include <string>
using namespace std;

string input;
GlobalFunctions globalFunctions;

void Boot()
{
	cout << setw(130) << "I N C U R S I O N" << endl;
	cout << " " << endl;
	cout << "V.0.1 [Alpha] [Public]" << endl;
	cout << "Copyright (C) 2018 Brandon Byrne. All rights reserved." << endl;
	cout << "Performing Boot Procedure..." << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	cout << "Boot done." << endl;
	cout << "Please enter a command." << endl;
	cin >> input;
	if (input == "newgame")
	{
		globalFunctions.CheckSave();
	}
	else if (input == "help" && "Help")
	{
		cout << "Launching help interface..." << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		globalFunctions.Help();
	}
	else
	{
		cout << "Unknown command." << endl;
		cout << "Rebooting." << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		system("CLS");
		Boot();
	}
}

int main()
{
	Boot();
	HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 300, 150, 300, 300, TRUE);
    return 0;
}

