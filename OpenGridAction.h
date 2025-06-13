#pragma once
#include "Action.h"

class OpenGridAction : public Action
{
private:
    std::string fileName; // File name to open the grid
public:
    OpenGridAction(ApplicationManager* pApp); // Constructor
    virtual void ReadActionParameters();      // Reads the file name
    virtual void Execute();                   // Opens and loads the grid
    virtual ~OpenGridAction();                // Destructor
};



