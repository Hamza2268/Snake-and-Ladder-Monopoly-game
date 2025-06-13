#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "Player.h"
#include"CardOne.h"
#include"CardTwo.h"
#include"CardThree.h"
#include"CardFour.h"
#include"CardFive.h"
#include"CardSix.h"
#include"Card7.h"
#include"CardEight.h"
#include"Card9.h"
#include"CardTen.h"
#include"Card11.h"
#include"Card12.h"
#include"Card13.h"



Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Check for overlap before adding
	if (IsOverlapping(pNewObject))
	{
		delete pNewObject; // Prevent memory leak
		return false;  // Do not add overlapping object
	}
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition& pos)
{

	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========

Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


void Grid::ResetPlayer()
{
	currPlayerNumber = 0;
}

void Grid::ResetTurnCount()
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->ResetTurnCount();
	}
}

Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder* Grid::GetNextLadder(const CellPosition& position)
{
	int startH = position.HCell(); // Start horizontal position
	int startV = position.VCell(); // Start vertical position (row)

	// Search from the current position upwards through all rows
	for (int i = startV; i >= 0; i--) // From the starting row to the top row
	{
		for (int j = startH; j < NumHorizontalCells; j++) // From current column to the last column
		{
			// Get the GameObject in the current cell
			GameObject* pObject = CellList[i][j]->GetGameObject();

			// Check if the GameObject is a Ladder
			if (pObject)
			{
				Ladder* pLadder = dynamic_cast<Ladder*>(pObject);
				if (pLadder) // Found a ladder
				{
					return pLadder; // Return the ladder object
				}
			}
		}
		startH = 0; // Reset to search from the first column in subsequent rows
	}

	// If no ladder is found, return NULL
	return NULL;
}

Snake* Grid::GetNextSnake(const CellPosition& position)
{
	int startH = position.HCell();
	int startV = position.VCell();


	for (int i = startV; i >= 0; i--)
	{
		for (int j = startH; j < NumHorizontalCells; j++)
		{

			GameObject* pObject = CellList[i][j]->GetGameObject();


			if (pObject)
			{
				Snake* pLadder = dynamic_cast<Snake*>(pObject);
				if (pLadder)
				{
					return pLadder;
				}
			}
		}
		startH = 0;
	}

	return NULL;
}
bool Grid::SetGameObjectInCell(const CellPosition& pos, GameObject* pGameObject)
{
	if (!pos.IsValidCell())
	{
		return false; // Invalid position, return false
	}
	Cell* pCell = CellList[pos.VCell()][pos.HCell()];

	if (pCell->GetGameObject() != nullptr)
	{
		return false; // The cell is occupied, return false
	}

	// If the cell is empty, set the new GameObject in the cell
	pCell->SetGameObject(pGameObject);

	return true;
}


GameObject* Grid::GetGameObjectFromCell(const CellPosition& position) const
{
	if (!position.IsValidCell())
		return NULL;

	Cell* cell = CellList[position.VCell()][position.HCell()];
	return cell ? cell->GetGameObject() : NULL;
}



// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
	if (Clipboard)
		delete Clipboard;
}


bool Grid::IsCellValidForStart(const CellPosition & startPos) const
{
	if (CellList[startPos.VCell()][startPos.HCell()]->GetGameObject() != NULL)
		return false;
	return true;
}

bool Grid::IsEndCellStartOfAnotherObject(const CellPosition & endPos) const {
	Cell* cell = CellList[endPos.VCell()][endPos.HCell()];
	if (cell->HasLadder() || cell->HasSnake())
		return true;
	return false;
}

void Grid::SaveAll(ofstream& OutFile, ObjectType type)
{
	
	int count = 0;

	// First pass: Count objects of the specified type
	OutFile << CountGameObjects(type) << std::endl;

	// Second pass: Save objects of the specified type
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			Cell* pCell = CellList[i][j];
			if (pCell)
			{
				GameObject* pGameObject = pCell->GetGameObject();
				if (pGameObject && pGameObject->GetType() == type)
				{
					pGameObject->Save(OutFile, type);
				}
			}
		}
	}
	// Sets all savedonce of this cards to false to be able to be saved again in another file if we want
	CardTen::setSavedOnce(false);
	Card11::setSavedOnce(false);
	Card12::setSavedOnce(false);
	Card13::setSavedOnce(false);
}


void Grid::LoadAll(std::ifstream& infile, ObjectType type)
{
	int count;
	infile >> count; // Read the number of objects to load

	for (int i = 0; i < count; i++)
	{
		GameObject* pGameObject = nullptr;
		// to check the type and load according to it
		switch (type)
		{
		case LaddersType:
			pGameObject = new Ladder(CellPosition(0, 0), CellPosition(0, 0)); // Create with dummy positions
			break;

		case SnakesType:
			pGameObject = new Snake(CellPosition(0, 0), CellPosition(0, 0)); // Create with dummy positions
			break;

		case CardsType: // if case card it reads from file card number to create new card and gets it's position for constructor 
			int cardnum;
			infile >> cardnum;
			int cellpos;
			infile >> cellpos;
			// to check the type and load according to it
			switch (cardnum)
			{
			case 1:
				pGameObject = new CardOne(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 2:
				pGameObject = new CardTwo(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 3:
				pGameObject = new CardThree(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 4:
				pGameObject = new CardFour(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 5:
				pGameObject = new CardFive(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 6:
				pGameObject = new CardSix(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 7:
				pGameObject = new Card7(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 8:
				pGameObject = new CardEight(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 9:
				pGameObject = new Card9(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 10:
				pGameObject = new CardTen(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 11:
				pGameObject = new Card11(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 12:
				pGameObject = new Card12(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			case 13:
				pGameObject = new Card13(CellPosition::GetCellPositionFromNum(cellpos));
				break;
			}

		}

		if (pGameObject)//calls each item's load function 
		{
			pGameObject->Load(infile); // Load the actual data
			AddObjectToCell(pGameObject); // Add the object to the grid
		}
	}

	CardTen::setSavedOnce(false);
	Card11::setSavedOnce(false);
	Card12::setSavedOnce(false);
	Card13::setSavedOnce(false);
}




int Grid::CountGameObjects(ObjectType type) const //to count number of objects of a specified type
{
	int count = 0;

	for (int i = 0; i < NumVerticalCells; i++) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			Cell* pCell = CellList[i][j];
			if (pCell) 
			{
				GameObject* pGameObject = pCell->GetGameObject();
				if (pGameObject && pGameObject->GetType()==type) 
				{
					count++;
				}
			}
		}
	}
	return count;
}

void Grid::ClearGrid() // to clear the grid before loading a saved grid
{
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetGameObject())
			{
				delete CellList[i][j]->GetGameObject();
				CellList[i][j]->SetGameObject(NULL);
			}
		}
	}
}


bool Grid::IsOverlapping(GameObject* newObj) const // to loop on all cells to check the overlapping
{
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			GameObject* pGameObject = CellList[i][j]->GetGameObject();
			if (pGameObject && pGameObject->IsOverlapping(newObj))
			{
				return true;
			}
		}
	}
	return false;
}

void Grid::ResetPosition()
{
	CellPosition StartCellPosition(NumVerticalCells - 1, 0);
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		UpdatePlayerCell(PlayerList[i], StartCellPosition);
	}
}

void Grid::ResetWallet()
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->SetWallet(100);
	}
}

void Grid::ResetGame()
{
	ResetPosition();
	ResetWallet();
	ResetPlayer();
	ResetTurnCount();
	ResetSpecialAttack();

	for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // left to right
		{
			if (CellList[i][j]->HasCard())
			{
				GameObject* TempObj = CellList[i][j]->GetGameObject();
				Card* Tempcard = dynamic_cast<Card*>(TempObj);
				if (Tempcard->GetCardNumber() >= 10 && Tempcard->GetCardNumber() <= 13)
					Tempcard->Reset();

			}
		}
	}

}

void Grid::DecrementPlayer()
{
	if (currPlayerNumber == 0)
		currPlayerNumber = 3;
	else
		currPlayerNumber--;
}
int Grid::SelectTargetPlayer(int CurrentPlayer)
{
	// Display a list of players to choose from
	pOut->PrintMessage("Select a player to target:");
	int TargetPlayer = pIn->GetInteger(pOut);

	// Validate the selection
	while (TargetPlayer < 0 || TargetPlayer >= MaxPlayerCount || TargetPlayer == CurrentPlayer)
	{
		pOut->PrintMessage("Invalid selection. Select a different player:");
		TargetPlayer = pIn->GetInteger(pOut);
	}
	pOut->ClearStatusBar();
	return TargetPlayer;
}

void Grid::ApplySpecialAttack(Player& player, const string& attack, int CurrentPlayer) // to Apply the special attacks
{
	if (player.CanUseSpecialAttack(attack))
	{
		if (attack == "i" || attack == "I") {
			// Ice attack logic: prevent the chosen player from rolling the next turn
			int targetPlayerIndex = SelectTargetPlayer(CurrentPlayer);
			PlayerList[targetPlayerIndex]->SetjustRolledDiceNum(0);
		}
		else if (attack == "f" || attack == "F") {
			// Fire attack logic: deduct 20 coins from the chosen player's wallet for the next 3 turns
			int targetPlayerIndex = SelectTargetPlayer(CurrentPlayer);
			PlayerList[targetPlayerIndex]->SetFire(); // Deduct 60 coins over 3 turns
		}
		else if (attack == "p" || attack == "P") {
			// Poison attack logic: deduct 1 number from the chosen player's dice roll for 5 turns
			int targetPlayerIndex = SelectTargetPlayer(CurrentPlayer);
			PlayerList[targetPlayerIndex]->SetPoison();
			// Implement the effect as needed
		}
		else if (attack == "l" || attack == "L") {
			// Lightning attack logic: deduct 20 coins from all other players
			for (int i = 0; i < MaxPlayerCount; ++i) {
				if (i != CurrentPlayer) {
					PlayerList[i]->SetWallet(PlayerList[i]->GetWallet() - 20);
				}
			}
			pOut->PrintMessage("Player " + to_string(CurrentPlayer) + " Has Deduced 20 Coins from all other Players.^_^");
		}

		// Mark the special attack as used by the player
		player.UseSpecialAttack(attack);
	}
	else
		pOut->PrintMessage("You are Out of that attack ,Choose another one..!");
}

void Grid::ResetSpecialAttack()// Resets special attacks counts & plag of each player for a new game
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{

		PlayerList[i]->SetjustRolledDiceNum(1);
		PlayerList[i]->SetUsedFireAttack (false);
		PlayerList[i]->SetUsedIceAttack(false);
		PlayerList[i]->SetUsedPoisonAttack(false);
		PlayerList[i]->SetUsedLightningAttack(false);
		PlayerList[i]->SetspecialAttackCount(0);
		PlayerList[i]->ResetPoison();
		PlayerList[i]->ResetFire();
	}

}
