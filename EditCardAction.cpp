#include "EditCardAction.h"

#include "Input.h"
#include "Output.h"
#include "Card.h"

EditCardAction::EditCardAction(ApplicationManager* pApp) : Action(pApp)
{
}

void EditCardAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Click on the source to edit");
    targetCell = pIn->GetCellClicked();

    if (!targetCell.IsValidCell())
    {
        pOut->PrintMessage("Invalid cell clicked. Action cancelled.");
        return;
    }

    pOut->ClearStatusBar();
}

void EditCardAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // Ask the user to select a cell containing a card
    pOut->PrintMessage("Select the cell of the card to edit...");
    targetCell = pIn->GetCellClicked();

    // Get the game object at the selected cell
    GameObject* pGameObject = pGrid->GetGameObjectFromCell(targetCell);

    // Check if the object is a card
    Card* pCard = dynamic_cast<Card*>(pGameObject);
    if (pCard)
    {
        pCard->EditParameters(pGrid);
    }
    else
    {
        pOut->PrintMessage("No card found at the selected cell. Operation cancelled.");
    }
}

EditCardAction::~EditCardAction()
{
}
