#include "Ladder.h"
#include"Snake.h"


Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	///TODO: Do the needed validation (DONE)
	if (!startCellPos.IsValidCell() || !endCellPos.IsValidCell())
	{
		this->endCellPos = CellPosition(0,0);
		return;
	}
	this->endCellPos = endCellPos;
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below (DONE)


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that 
	pGrid->GetOutput()->PrintMessage("You have reached a ladder. Click to continue ...");
	pGrid->GetInput()->GetCellClicked();
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

Ladder::~Ladder()
{
}
void Ladder::Save(std::ofstream& outfile, ObjectType type) 
{
	// Checks if type is ladder
	if (type == LaddersType)
	{
		outfile << position.GetCellNum() << " " << endCellPos.GetCellNum() << std::endl;
	}
}

void Ladder::Load(ifstream& Infile)	// Loads and Reads the GameObject parameters from the file
{
	//TODO (DONE)
		int startCellNum, endCellNum;
		Infile >> startCellNum >> endCellNum;
		position = CellPosition::GetCellPositionFromNum(startCellNum);
		endCellPos = CellPosition::GetCellPositionFromNum(endCellNum);
}

bool Ladder::IsOverlapping(GameObject* newObj) const
{
	Ladder* pLadder = dynamic_cast<Ladder*>(newObj);
	// Checks if object is ladder
	if (pLadder)
	{
		if ((position.VCell() >= pLadder->endCellPos.VCell()) && (endCellPos.VCell() <= pLadder->position.VCell()) &&
			(position.HCell() == pLadder->position.HCell()))
		{
			return true; // Overlap
		}
		return false; // No overlap
	}
	//Checks if object is Snake
	Snake* pSnake = dynamic_cast<Snake*>(newObj);
	if (pSnake)
	{
		if (GetEndPosition().VCell() == pSnake->GetPosition().VCell() && GetEndPosition().HCell() == pSnake->GetPosition().HCell())
		{
			return true;
		}
	}

	return false; // No overlap
}

CellPosition Ladder::GetStartPosition() const
{
	return position; 
}
ObjectType Ladder::GetType() const 
{
	return LaddersType;
}