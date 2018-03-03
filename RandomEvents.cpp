#include "stdafx.h"
#include "Globals.h"
#include "GameLogic.h"
#include "RandomEvents.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

int eventChance = rand() % 100 + 1;
int eventType = rand() % 5 + 1;
int luck = rand() % 100 + 1;
string confirm;

RandomEvents randomEvents;


void RandomEvents::RandomHandler()
{
	if (eventChance >= 50)
	{
		randomEvents.EventPicker();
	}
	else
	{
		return;
	}
}

void RandomEvents::EventPicker()
{
	switch (eventType)
	{
	case (1):
		cout << "+10 to Swarm (RANDOM EVENT)" << endl;
		swarm = swarm + 10;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		break;
	case (2):
		cout << "+15 to Marines (RANDOM EVENT)" << endl;
		marines = marines + 15;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		break;
	case (3):
		cout << "Explosion in Engineering. -100 to Facility HP (RANDOM EVENT)" << endl;
		facilityHP = facilityHP - 100;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		break;
	}

}