#include "CopyCardAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "Card.h"

CopyCardAction::CopyCardAction(ApplicationManager* pApp) : Action(pApp)
{
}

void CopyCardAction::ReadActionParameters()
{
    // Get a Pointer to the Input / Output Interfaces and Grid
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // Ask user for the source cell
    pOut->PrintMessage("Copy Card: Click on the source cell ...");
    sourceCell = pIn->GetCellClicked();

    // Validate the selected cell
    if (!sourceCell.IsValidCell())
    {
        pOut->PrintMessage("Invalid cell! Operation cancelled.");
        sourceCell.SetVCell(-1); // Mark as invalid
    }

    pOut->ClearStatusBar();
}

void CopyCardAction::Execute()
{
    //Reads the Parameters
    ReadActionParameters();

    if (!sourceCell.IsValidCell())  //Checks if sourceCell is invalid
        return;

    Grid* pGrid = pManager->GetGrid();

    //Dynamic cast to check if the cell has an object or not
    GameObject* pGameObject = pGrid->GetGameObjectFromCell(sourceCell);
    if (!pGameObject)
    {
        pGrid->PrintErrorMessage("The selected cell does not contain a card. Operation cancelled.");
        return;
    }
    //Dynamic cast to check if the object is card or not
    Card* cardToCopy = dynamic_cast<Card*>(pGameObject);
    if (!cardToCopy)
    {
        pGrid->PrintErrorMessage("The selected cell does not contain a card. Operation cancelled.");
        return;
    }

    // Copy the card to the clipboard
    pGrid->SetClipboard(cardToCopy);

    pGrid->GetOutput()->PrintMessage("Card copied successfully to clipboard.");
}


CopyCardAction::~CopyCardAction()
{
}


