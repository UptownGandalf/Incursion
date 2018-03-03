#include "stdafx.h"
#include "Globals.h"
#include "GameLogic.h"
#include "RandomEvents.h"
#include "Outcomes.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

Outcomes outcomesActual;

void Outcomes::OutcomeCheck()
{
	if (facilityHP <= 0)
	{
		outcomesActual.OutcomeBad();
	}
	if (turnspassed == 100)
	{
		outcomesActual.OutcomeGood();
	}
}

void Outcomes::OutcomeBad()
{
	system("CLS");
	cout << "The Swarm has overrun the facility." << endl;
	cout << "Those unlucky enough to not already be dead will soon be consumed." << endl;
	cout << "As the last few bursts of static come through the radio, all communication is lost." << endl;
	cout << "From your Command Center, you watch as the lights and computers gradually shut off." << endl;
	cout << "You sit and wait in a dark room as their hungry maws draw closer and closer..." << endl;
	cout << " " << endl;
	cout << "G A M E  O V E R" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(60000));
}

void Outcomes::OutcomeGood()
{
	system("CLS");
	cout << "Help has arrived!" << endl;
	cout << "You've survived the Swarm's onslaught. Our reinforcements will handle the rest." << endl;
	cout << "Well done, commander." << endl;
	cout << "G A M E  O V E R" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(60000));
}