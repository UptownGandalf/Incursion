#pragma once

extern int itemsInProduction;

class GameLogic
{
public:
	void StatusUpdate();
	void PrintMap();
	void TurnProcessor();
	void ShopHandler();
	void Combat();
	void Build();
	void BuildCheck();
	void SwarmCheck();
	void DepotCheck();
	void DefenseCheck();
};