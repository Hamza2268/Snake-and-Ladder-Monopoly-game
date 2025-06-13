#include"Card.h"

// TODO Add more includes as needed for other card types

Card::Card(const CellPosition& pos) : GameObject(pos) // sets the cell position of the GameObject
{
}

void Card::SetCardNumber(int cnum)
{
	if (cnum > 0 && cnum <= 13) {
		cardNumber = cnum;
	}
	else cardNumber = -1;
}
void Card::setPosition(CellPosition pos) {
	if (pos.IsValidCell()) position = pos;

}
int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{
	pOut->DrawCell(position, cardNumber);

	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"


}

void Card::ReadCardParameters(Grid* pGrid)
{

}

void Card::Apply(Grid* pGrid, Player* pPlayer)
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}

Card::~Card()
{
}

void Card::EditParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("This card does not have editable parameters.");
}

void Card::Save(std::ofstream& outfile, ObjectType type)
{
	if (type == CardsType)
	{
		outfile << cardNumber << " " << position.GetCellNum();
	}
}


void Card::Load(ifstream& Infile)
{


}

bool Card::IsOverlapping(GameObject* newObj) const
{
	return false;
}
ObjectType Card::GetType() const
{
	return CardsType;
}

void Card::Reset()
{

}