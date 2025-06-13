#include "CutCardAction.h"
#include "Grid.h"
#include "Cell.h"
#include "Card.h"
#include "Input.h"
#include "Output.h"

CutCardAction::CutCardAction(ApplicationManager* pApp) : Action(pApp)
{
}

void CutCardAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // Ask user to select the source cell
    pOut->PrintMessage("Cut Card: Click on the source cell ...");
    sourceCell = pIn->GetCellClicked();

    // Validate the selected cell
    if (!sourceCell.IsValidCell())
    {
        pOut->PrintMessage("Invalid cell! Operation cancelled.");
        sourceCell.SetVCell(-1); // Mark as invalid
    }
    else
    {
        pOut->ClearStatusBar();
    }
}

void CutCardAction::Execute()
{
    ReadActionParameters();

    if (!sourceCell.IsValidCell()) //Checks if valid
        return;

    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();

    //Dynamic cast to check if the cell has an object or not
    GameObject* pGameObject = pGrid->GetGameObjectFromCell(sourceCell);

    if (!pGameObject)
    {
        pOut->PrintMessage("The selected cell does not contain a card. Operation cancelled.");
        return;
    }
    //Dynamic cast to check if the object is card or not
    Card* cardToCut = dynamic_cast<Card*>(pGameObject);
    if (!cardToCut)
    {
        pOut->PrintMessage("The selected object is not a card. Operation cancelled.");
        return;
    }

    // Copy the card to the clipboard and remove it
    pGrid->SetClipboard(cardToCut);    // Copy the card to the clipboard
    pGrid->RemoveObjectFromCell(sourceCell); // Remove the card from the cell (handles deallocation)

    pGrid->UpdateInterface();
    pOut->PrintMessage("Card cut successfully to clipboard.");
}

CutCardAction::~CutCardAction()
{
}

