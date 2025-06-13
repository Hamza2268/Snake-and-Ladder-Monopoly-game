
#pragma once
#include "Action.h"

class DeleteAction: public Action
{
private: 
	CellPosition targetCell;
public: 
	DeleteAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute(); 

	virtual ~DeleteAction();
};