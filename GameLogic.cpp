#include "stdafx.h"
#include "Globals.h"
#include "RandomEvents.h"
#include "GameLogic.h"
#include "Outcomes.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

string terminalInput;
GameLogic gameLogicActual;
RandomEvents randomEventsActual;
Outcomes outcomes;
int buildTurnsLeft = 3;
int itemsInProduction;
int itemType;

void GameLogic::StatusUpdate()
{
	system("CLS");
	cout << "FUEL: " << fuel << endl;
	cout << "MARINES: " << marines << endl;
	cout << "SWARM SIZE: " << swarm << endl;
	cout << "FACILITY HP: " << facilityHP << endl;
	cout << "CASH: " << cash << endl;
	cout << "GENERATORS: " << generators << endl;
	cout << "SENTRIES: " << sentries << endl;
	cout << "MINING DEPOTS: " << depots << endl;
	cout << " " << endl;
	cout << "Please enter a command." << endl;
	cin >> terminalInput;
	if (terminalInput == "map")
	{
		gameLogicActual.PrintMap();
		cin >> terminalInput;
	}
	if (terminalInput == "endturn")
	{
		gameLogicActual.TurnProcessor();
	}
	if (terminalInput == "buy")
	{
		gameLogicActual.ShopHandler();
	}
	if (terminalInput == "combat")
	{
		gameLogicActual.Combat();
	}
	if (terminalInput == "build")
	{
		gameLogicActual.Build();
	}
	else
	{
		cout << "Unrecognized command. Restarting interface." << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		gameLogicActual.StatusUpdate();
	}
}

void GameLogic::PrintMap()
{
	cout << "###############################" << endl;
	cout << "#                             #" << endl;
	cout << "#########       O             #" << endl;
	cout << "#       #       O              " << endl;
	cout << "# CORE  #       O              " << endl;
	cout << "#       #       O             #" << endl;
	cout << "#########                     #" << endl;
	cout << "###############################" << endl;
}

void GameLogic::TurnProcessor()
{
	cout << "Processing AI turn..." << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	if (generators >= 1)
	{
		fuel = fuel + 100;
	}
	swarm = swarm + 10;
	turnspassed++;
	gameLogicActual.BuildCheck();
	gameLogicActual.SwarmCheck();
	outcomes.OutcomeCheck();
	gameLogicActual.DepotCheck();
	randomEventsActual.RandomHandler();
	gameLogicActual.DefenseCheck();
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	gameLogicActual.StatusUpdate();

}

void GameLogic::ShopHandler()
{
	system("CLS");
	int shopInput;
	cout << "SHOP" << endl;
	cout << "Your Cash:" << cash << endl;
	cout << "1. Buy Generator (500 Cash)" << endl;
	cout << "2. Recruit Marine (50 Cash)" << endl;
	cout << "3. Repair Facility [100 HP] (100 Cash)" << endl;
	cout << "4. Exit Shop" << endl;
	cin >> shopInput;
	if (shopInput == 1)
	{
		if (cash >= 500)
		{
			cout << "You've purchased one Generator." << endl;
			generators++;
			cash = cash - 500;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			gameLogicActual.ShopHandler();
		}
		else
		{
			cout << "You don't have enough cash to buy this." << endl;
			cout << "Returning to the shop." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			gameLogicActual.ShopHandler();
		}
	}
	if (shopInput == 2)
	{
		if (cash >= 50)
		{
			cout << "You've recruited one Marine." << endl;
			marines++;
			cash = cash - 50;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			gameLogicActual.ShopHandler();
		}
		else
		{
			cout << "You don't have enough cash to buy this." << endl;
			cout << "Returning to the shop." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			gameLogicActual.ShopHandler();
		}
	}
	if (shopInput == 4)
	{
		gameLogicActual.StatusUpdate();
	}
}

void GameLogic::Combat()
{
	int combatChoice;
	system("CLS");
	cout << "Combat Interface" << endl;
	cout << "Marines Reporting for Duty: " << marines << endl;
	cout << "Swarm: " << swarm << endl;
	cout << "What should we do, sir?" << endl;
	cout << "1. Attack the Swarm" << endl;
	cout << "2. Prepare Defenses" << endl;
	cin >> combatChoice;
	if (combatChoice == 1)
	{
		if (marines >= 1)
		{
			cout << "Calculating battle outcome..." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			if (swarm > marines)
			{
				int marineDamageDealt = marines * 5;
				swarm = swarm - marineDamageDealt;
				if (swarm < 0)
				{
					swarm = 0;
				}
				if (luck >= 50)
				{
					marines = 0;
				}
				else
				{
					marines = marines - swarm / 5;
				}
				cout << "New Swarm Size: " << swarm << endl;
				cout << "Marines Lost: " << marines << endl;
				cout << "Returning to main interface..." << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
				gameLogicActual.StatusUpdate();
			}
			else
			{
				cout << "The Marines outnumber the Swarm!" << endl;
				cout << "Swarm reduced to 0." << endl;
				swarm = 0;
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
				gameLogicActual.StatusUpdate();
			}
		}
		else
		{
			cout << "Not enough Marines." << endl;
			gameLogicActual.StatusUpdate();
		}
	}
	if (combatChoice == 2)
	{
		if (marines >= 1)
		{
			marinesDefending = true;
			cout << "All available Marines have been ordered to defend." << endl;
			cout << "The Swarm will not grow, but your garrison will slowly deplete." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			gameLogicActual.StatusUpdate();
		}
		else
		{
			cout << "Not enough Marines." << endl;
			gameLogicActual.StatusUpdate();
		}

	}
	else
	{
		cout << "Invalid command." << endl;
		gameLogicActual.Combat();
	}
}

void GameLogic::Build()
{
	system("CLS");
	cout << "FUEL: " << fuel << endl;
	cout << "What would you like to build?" << endl;
	cout << "1. Sentry Turret [100 Fuel]" << endl;
	cout << "2. Medical Station [350 Fuel]" << endl;
	cout << "3. Docking Platform [1500 Fuel]" << endl;
	cout << "4. Combat Robot Production Facility [5000 Fuel]" << endl;
	cout << "5. Mining Depot [500 Fuel]" << endl;
	cout << "6. Exit" << endl;
	cin >> terminalInput;
	if (terminalInput == "1")
	{
		if (fuel >= 100)
		{
			cout << "Sentry Turret production started." << endl;
			cout << "It will be ready in three turns." << endl;
			itemsInProduction++;
			buildTurnsLeft = 3;
			itemType = 1;
			fuel = fuel - 100;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			gameLogicActual.Build();
		}
		else
		{
			cout << "Not enough fuel." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			gameLogicActual.Build();
		}
	}
	if (terminalInput == "5")
	{
		if (fuel >= 500)
		{
			cout << "Mining Depot production started." << endl;
			cout << "It will be ready in three turns." << endl;
			itemsInProduction++;
			buildTurnsLeft = 3;
			itemType = 2;
			fuel = fuel - 500;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			gameLogicActual.Build();
		}
		else
		{
			cout << "Not enough fuel." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			gameLogicActual.Build();
		}
	}
	if (terminalInput == "6")
	{
		gameLogicActual.StatusUpdate();
	}
}

void GameLogic::BuildCheck()
{
	if (itemsInProduction >= 1)
	{
		buildTurnsLeft--;
		if (buildTurnsLeft == 0)
		{
			cout << "An item has finished production!" << endl;
			cout << "Check the map to see where it was deployed." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			if (itemType == 1)
			{
				sentries++;
			}
			if (itemType == 2)
			{
				depots++;
			}
		}
		else
		{
			cout << "Production Turns Left: " << buildTurnsLeft << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		}
	}
	else
	{
		return;
	}
}

void GameLogic::SwarmCheck()
{
	if (swarm > 50)
	{
		cout << "The Swarm is too large!" << endl;
		cout << "-500 to Facility HP" << endl;
		facilityHP = facilityHP - 500;
		if (swarm > 250)
		{
			cout << "The Swarm is massive!" << endl;
			cout << "-1000 to Facility HP!" << endl;
			facilityHP = facilityHP - 1000;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	}
	else
	{
		return;
	}
}

void GameLogic::DepotCheck()
{
	int depotProduction = depots * 100;
	cash = cash + depotProduction;
	cout << "Cash Produced by Mining Depots: " << depotProduction << endl;
}

void GameLogic::DefenseCheck()
{
	if (marinesDefending == true)
	{
		if (marines = 0)
		{
			cout << "You don't have enough Marines to defend!" << endl;
			marinesDefending = false;
		}
		else
		{
			cout << "Your Marines are in defensive formation!" << endl;
			cout << "The Swarm has not grown this turn." << endl;
			cout << "You've lost one Marine in combat." << endl;
			swarm = swarm - 10;
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		}
	}
	else
	{
		return;
	}
}