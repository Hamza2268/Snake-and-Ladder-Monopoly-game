#pragma once
#include "Action.h"
#include <fstream>

class SaveGridAction : public Action {
    std::string fileName;

public:
    SaveGridAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();

    ~SaveGridAction();
};


