#include "BankRobbers.h"

// this isn't defined with other colors in consoleapi2.h
// it has to be defined in every file we needed this color
#define FOREGROUND_YELLOW	 0x0006 // text color contains yellow.

bool BankRobbers::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void BankRobbers::Update()
{
	//set text color to yellow
	SetTextColor(FOREGROUND_YELLOW|FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}