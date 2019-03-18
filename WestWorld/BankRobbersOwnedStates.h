#pragma once
#ifndef BANKROBBERS_OWNED_STATES_H
#define BANKROBBERS_OWNED_STATES_H

#include "Common/fsm/State.h"

class BankRobbers;



//------------------------------------------------------------------------
//
//	The bank robbers hide on the road to plan their next attack
//------------------------------------------------------------------------
class Lurk : public State<BankRobbers>
{
private:

	Lurk() {}

	//copy ctor and assignment should be private
	Lurk(const Lurk&);
	Lurk& operator=(const Lurk&);

public:

	//this is a singleton
	static Lurk* Instance();

	virtual void Enter(BankRobbers* daltons);

	virtual void Execute(BankRobbers* daltons);

	virtual void Exit(BankRobbers* daltons);

	virtual bool OnMessage(BankRobbers* daltons, const Telegram& msg);

};



//------------------------------------------------------------------------
//
// The bank robbers go to the bank and start stealing gold
// They will not leave until Bob arrives and fights them
//------------------------------------------------------------------------
class RobBank : public State<BankRobbers>
{
private:

	RobBank() {}

	//copy ctor and assignment should be private
	RobBank(const RobBank&);
	RobBank& operator=(const RobBank&);

public:

	//this is a singleton
	static RobBank* Instance();

	virtual void Enter(BankRobbers* daltons);

	virtual void Execute(BankRobbers* daltons);

	virtual void Exit(BankRobbers* daltons);

	virtual bool OnMessage(BankRobbers* daltons, const Telegram& msg);

};



//------------------------------------------------------------------------
//
// When Bob arrives at the bank, the bank robbers attack him
// The outcome is generated randomly, the bank robbers have 15% chance
// to win. If they do, Bob loses all the gold stored in the bank.
//------------------------------------------------------------------------
class FightBob : public State<BankRobbers>
{
private:

	FightBob() {}

	//copy ctor and assignment should be private
	FightBob(const FightBob&);
	FightBob& operator=(const FightBob&);

public:

	//this is a singleton
	static FightBob* Instance();

	virtual void Enter(BankRobbers* daltons);

	virtual void Execute(BankRobbers* daltons);

	virtual void Exit(BankRobbers* daltons);

	virtual bool OnMessage(BankRobbers* daltons, const Telegram& msg);

};



#endif