#pragma once

extern int fuel;
extern int marines;
extern int swarm;
extern int facilityHP;
extern int generators;
extern int cash;
extern int marineLifeLeft;
extern int sentries;
extern int depots;
extern bool marinesDefending;
extern int turnspassed;
extern const char* map;
class GlobalFunctions {
public:
	void CheckSave();
	void Help();
};

