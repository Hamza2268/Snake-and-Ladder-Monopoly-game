#include "Card7.h"
#include "Grid.h"
#include "Player.h"

Card7::Card7(const CellPosition& pos) : Card(pos)
{
    cardNumber = 7;  // Set card number to 7
}

Card7::~Card7() 
{
}

void Card7::Apply(Grid* pGrid, Player* pPlayer) 
{
    // Call base class Apply() to print the card number and message
    Card::Apply(pGrid, pPlayer);

    //Give the player another dice roll
    if (pPlayer) 
    {
        pGrid->PrintErrorMessage("You get another dice roll! Click to continue...");
        pGrid->DecrementPlayer();
        pPlayer->SetTurnCount(pPlayer->GetTurnCount() - 1); // Decrease turn count to allow an extra roll
    }
}

void Card7::Save(ofstream& OutFile, ObjectType type)
{
    if (type == CardsType)
    {
        Card::Save(OutFile, type);
        OutFile << endl;
    }
}

void Card7::Load(ifstream& InFile)
{
    Card::Load(InFile);
}