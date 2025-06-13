#include "SwitchToPlayModeAction.h"
#include "Input.h"
#include "Output.h"
#include"GameObject.h"
#include "Player.h"

SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchToPlayModeAction::ReadActionParameters()
{
}

void SwitchToPlayModeAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    // Switch the UI to play mode
    pOut->CreatePlayModeToolBar();

    // Clear the status bar
    pOut->PrintMessage("Switched to Play Mode! All players have been reset to step 0 with full wallets.");
}

SwitchToPlayModeAction::~SwitchToPlayModeAction()
{
}
