#pragma once
#ifndef BANKROBBERS_H
#define BANKROBBERS_H

#include <string>

#include "Common/fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "BankRobbersOwnedStates.h"
#include "Common/misc/ConsoleUtils.h"
#include "Miner.h"
#include "Common/fsm/StateMachine.h"
#include "Common/misc/Utils.h"



class BankRobbers : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<BankRobbers>* m_pStateMachine;

	location_type   m_Location;
	

public:

	BankRobbers(int id) :m_Location(bank),
		BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<BankRobbers>(this);

		//the bank robbers start at the bank
		m_pStateMachine->SetCurrentState(RobBank::Instance());

		//BankRobbers don't have a global state
	}

	~BankRobbers() { delete m_pStateMachine; }


	//this must be implemented
	void          Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<BankRobbers>* GetFSM()const { return m_pStateMachine; }

	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }
	
};

#endif
