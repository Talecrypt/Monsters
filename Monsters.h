// File: Monsters.h
// Author: Saif Abu Hananah
// Date: 22/May/2025
// Monstertale - A Monster-Taming Game

#ifndef MONSTERS_H
#define MONSTERS_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Monster (Abstract Base Class)
// Defines the common interface and data members for all monster types.
class Monster {
	protected:
		string name;
		int health;
        static int rollD20();
	public:
     // Pure-virtual interface methods—must be overridden
		Monster(const string& name, int health);
		virtual ~Monster()=default;
        string getName() const;
        virtual int input(int)=0;
		virtual int display() const=0;
		virtual bool attemptTame(int tamingToolQuality) = 0;
		virtual int feed(int foodAmount)=0;
        virtual int specialAction()=0;
};

// Dragon (Derived from Monster)
// A dragon with hibernation status and fire-breath power.
class Dragon : public Monster{
	protected:
		bool isHibernating;
		int firePower;

	public:
		Dragon();
        ~Dragon();
		int input(int);
		int display() const;
		bool attemptTame(int tamingToolQuality);
		int feed(int foodAmount);
		int specialAction();
};

// Unicorn (Derived from Monster)
// A unicorn with a healing aura and a growing horn.
class Unicorn : public Monster{
	protected:
		int hornLength;
		bool hasHealingAura;
	public:
		Unicorn();
        ~Unicorn();
		int input(int);
		int display() const;

		bool attemptTame(int tamingToolQuality);
		int feed(int foodAmount) ;
		int specialAction();

};

// Symbiote (Derived from Monster)
// A symbiotic creature with bond strength and synergy levels.
class Symbiote : public Monster{
	protected:
		int symbioteLevel;
		double bondStrength;
	public:
		Symbiote();
        ~Symbiote();

		int input(int);
        int display() const;

        bool attemptTame(int tamingToolQuality);
        int feed(int foodAmount);
        int specialAction();
		int mergeWithHost();
};	

#endif
