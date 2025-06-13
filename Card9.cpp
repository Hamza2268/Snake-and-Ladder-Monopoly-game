#include "Card9.h"
#include "Grid.h"
#include "Player.h"

Card9::Card9(const CellPosition& pos) : Card(pos) 
{
    cardNumber = 9;  // Set the card number to 9
}

Card9::~Card9() 
{
}

void Card9::ReadCardParameters(Grid* pGrid) 
{
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("New Card 9: Enter the cell to move the player to...");
    targetCell = pIn->GetCellClicked(); // Read the target cell position

    while (!targetCell.IsValidCell()) {
        pOut->PrintMessage("Invalid cell! Click again...");
        targetCell = pIn->GetCellClicked();
    }

    pOut->ClearStatusBar();
}

void Card9::Apply(Grid* pGrid, Player* pPlayer) 
{
    // Call the base class Apply() to print the card's effect
    Card::Apply(pGrid, pPlayer);

    if (pPlayer) {
        pGrid->PrintErrorMessage("Player will be moved to the specified cell. Click to continue...");
        pGrid->UpdatePlayerCell(pPlayer, targetCell); // Move player to the target cell

        // Apply the effect of the cell where the player landed (if any)
        if (pPlayer->GetCell()->GetGameObject())
        {
            pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
        }
    }
}

void Card9::Save(ofstream& OutFile, ObjectType type)
{
    if (type == CardsType)
    {
        Card::Save(OutFile, type);
        OutFile << " " << targetCell.GetCellNum(); // Save target cell position
        OutFile << endl;
    }
}

void Card9::Load(ifstream& InFile)
{
    int targetCellNum;
    InFile >> targetCellNum; // Read target cell number
    targetCell = CellPosition::GetCellPositionFromNum(targetCellNum);
}
void Card9::SetCell(CellPosition cell)
{
    targetCell = cell;
}
CellPosition Card9::GetCell()
{
    return targetCell;
}