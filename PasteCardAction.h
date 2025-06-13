#pragma once
#include "Action.h"
#include "CellPosition.h"

class PasteCardAction : public Action
{
private:
    CellPosition destinationCell; 

public:
   
    PasteCardAction(ApplicationManager* pApp);
    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual ~PasteCardAction();
};


