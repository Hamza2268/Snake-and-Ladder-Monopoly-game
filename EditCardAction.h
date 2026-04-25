#pragma once

#include "Action.h"
#include "Card.h"

class EditCardAction : public Action
{
private:
    CellPosition targetCell;

public:
    EditCardAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();

    virtual ~EditCardAction();
};