#include "MinerOwnedStates.h"
#include "BankRobbersOwnedStates.h"
#include "BankRobbers.h"
#include "Locations.h"
#include "Common/Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

// this isn't defined with other colors in consoleapi2.h
// it has to be defined in every file we needed this color
#define FOREGROUND_YELLOW	 0x0006 // text color contains yellow.

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//-------------------------------------------------------------------------Lurk

Lurk* Lurk::Instance()
{
	static Lurk instance;

	return &instance;
}


void Lurk::Enter(BankRobbers* daltons)
{
	if (daltons->Location() != road)
	{
		daltons->ChangeLocation(road);
	}

	//send a delayed message to themselves to wait before going back to the bank
	Dispatch->DispatchMessage(4,                //time delay
		daltons->ID(),							//sender ID
		daltons->ID(),							//receiver ID
		Msg_TryAgain,							//msg
		NO_ADDITIONAL_INFO);

	SetTextColor(FOREGROUND_YELLOW|FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(daltons->ID()) << ": Let's plan our next heist!";
}


void Lurk::Execute(BankRobbers* daltons)
{
	switch (RandInt(0, 2))
	{
	case 0:

		cout << "\n" << GetNameOfEntity(daltons->ID()) << ": Joe, when do we eat?";

		break;

	case 1:

		cout << "\n" << GetNameOfEntity(daltons->ID()) << ": You sure we ain't lost?";

		break;

	case 2:

		cout << "\n" << GetNameOfEntity(daltons->ID()) << ": Shhh we're hidin'";

		break;
	}
}

void Lurk::Exit(BankRobbers* daltons)
{
	//the state is only exited through the receipt of a message
	//the text is thus defined in OnMessage rather than in Exit
}

bool Lurk::OnMessage(BankRobbers* daltons, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_TryAgain:
	{
		SetTextColor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(daltons->ID()) <<
			": Ok brothers, I got a new plan.";

		SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		
		cout << "\nMessage handled by " << GetNameOfEntity(daltons->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		daltons->GetFSM()->ChangeState(RobBank::Instance());
	}

	return true;

	}//end switch

	return false;
}

//------------------------------------------------------------------------RobBank

RobBank* RobBank::Instance()
{
	static RobBank instance;

	return &instance;
}


void RobBank::Enter(BankRobbers* daltons)
{
	if (daltons->Location() != bank)
	{
		daltons->ChangeLocation(bank);
	}

	SetTextColor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(daltons->ID()) << ": Hands up it's a robbery!";
}


void RobBank::Execute(BankRobbers* daltons)
{
	switch (RandInt(0, 2))
	{
	case 0:

		cout << "\n" << GetNameOfEntity(daltons->ID()) << ": Hehehe, this plan is the greatest";

		break;

	case 1:

		cout << "\n" << GetNameOfEntity(daltons->ID()) << ": Averell, hurry up and take the gold!";

		break;

	case 2:

		cout << "\n" << GetNameOfEntity(daltons->ID()) << ": Let's steal everythin' before Lucky Luke comes back";

		break;
	}

	//threaten people in the bank, waiting for Bob to arrive
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
		daltons->ID(),
		ent_Miner_Bob,
		Msg_GimmeYourGold,
		NO_ADDITIONAL_INFO);
}

void RobBank::Exit(BankRobbers* daltons)
{
}


bool RobBank::OnMessage(BankRobbers* daltons, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	//when Bob arrives at the bank, there's a fight
	case Msg_GetOut:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(daltons->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_YELLOW|FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(daltons->ID()) <<
			": Damn, it's Lucky Luke's cousin.";

		daltons->GetFSM()->ChangeState(FightBob::Instance());
	}

	return true;

	}//end switch

	return false;
}

//------------------------------------------------------------------------FightBob

FightBob* FightBob::Instance()
{
	static FightBob instance;

	return &instance;
}


void FightBob::Enter(BankRobbers* daltons)
{
	cout << "\n" << GetNameOfEntity(daltons->ID()) << ": You wanna fight?";
}


void FightBob::Execute(BankRobbers* daltons)
{
	cout << "\n" << GetNameOfEntity(daltons->ID()) << ": Jack, William, Averell, attack him!";

	//the Daltons have 15% chance to win the fight against Bob
	if (RandFloat() < 0.15)
	{
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
			daltons->ID(),
			ent_Miner_Bob,
			Msg_YouLose,
			NO_ADDITIONAL_INFO);

		SetTextColor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(daltons->ID()) <<
			": Woohoo, we finally got our revenge!";
	}

	else {
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
			daltons->ID(),
			ent_Miner_Bob,
			Msg_YouWin,
			NO_ADDITIONAL_INFO);

		SetTextColor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(daltons->ID()) <<
			": Aaaargh I hate that guy!!";
	}
	//It doesn't matter if they win or lose, they go back to lurking
	daltons->GetFSM()->ChangeState(Lurk::Instance());
}

void FightBob::Exit(BankRobbers* daltons)
{
	SetTextColor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(daltons->ID()) << ": Let's get outta here!";
}


bool FightBob::OnMessage(BankRobbers* daltons, const Telegram& msg)
{
	return false;
}