#include "SwitchToDesignModeAction.h"
#include "Grid.h"
#include "Output.h"

SwitchToDesignModeAction::SwitchToDesignModeAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchToDesignModeAction::ReadActionParameters()
{
}

void SwitchToDesignModeAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();

    // Switch the UI to design mode
    pOut->CreateDesignModeToolBar();
    pGrid->ResetGame();
    // Clear the status bar
    pOut->PrintMessage("Switched to Design Mode. The current grid is now editable.");
}

SwitchToDesignModeAction::~SwitchToDesignModeAction()
{
}

