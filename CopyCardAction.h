#pragma once
#include "Action.h"

class CopyCardAction : public Action
{
private:
    CellPosition sourceCell;
public:
    CopyCardAction(ApplicationManager* pApp); // A Constructor
    virtual void ReadActionParameters(); //Reads CopyCardAction parameter 
    virtual void Execute(); // copy the card
    virtual ~CopyCardAction(); //A Destructor
};

