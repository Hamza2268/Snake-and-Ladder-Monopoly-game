#pragma once
#include "Action.h"

class CutCardAction : public Action
{
private:
    CellPosition sourceCell; 
public:
    CutCardAction(ApplicationManager* pApp); 

    virtual void ReadActionParameters(); 
    virtual void Execute();            

    virtual ~CutCardAction();
};


