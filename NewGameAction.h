#pragma once

#include "Action.h"

class NewGameAction : public Action
{

	// No parameters for this action

public:
	NewGameAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~NewGameAction();
};
