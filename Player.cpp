#include "Player.h"

#include "GameObject.h"

Player::Player(Cell* pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	this->usedFireAttack = 0;
	this->usedIceAttack = 0;
	this->usedPoisonAttack = 0;
	this->usedLightningAttack = 0;
	this->specialAttackCount = 0;
	this->justRolledDiceNum = 1;
	this->Poison = 0;
	this->Fire = 0;
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell* cell)
{
	pCell = cell;
}
void Player::SetTurnCount(int T)
{
	turnCount = T;
}
Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	if (wallet >= 0)
		this->wallet = wallet;
	else
		this->wallet = 0;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

void Player::SetjustRolledDiceNum(int RolledDice)
{
	justRolledDiceNum = RolledDice;
}

int Player::GetjustRolledDiceNum()
{
	return justRolledDiceNum;
}

void Player::IncrementTurnCount()
{
	turnCount = (turnCount + 1) % 4;
}

void Player::ResetTurnCount()
{
	turnCount = 0;  // Reset the turn count (For New Game)
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);

	///TODO: use the appropriate output function to draw the player with "playerColor"

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);

	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)

}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	IncrementTurnCount();

	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	if (!GetjustRolledDiceNum())   // In Case of Preventing the Player From Playing his Turn
	{
		pGrid->PrintErrorMessage("You are not allowed to Play this Turn ,Click to continue.");
		SetjustRolledDiceNum(1);

		if (turnCount == 3)
			ResetTurnCount();
	}
	else if (turnCount == 3)   // Recharge turn if the player is not prevented from his turn
	{

		string decision;

		int addwallet = diceNumber * 10;
		if (specialAttackCount < 2)    // Check that Player not out of Attacks
		{
			pGrid->GetOutput()->PrintMessage(" Special attack instead of Reacharging Wallet ? (y/n)");
			decision = pGrid->GetInput()->GetSrting(pGrid->GetOutput());
			while (!(decision == "y" || decision == "Y" || decision == "N" || decision == "n"))  // If Player entered invalid answer
			{
				pGrid->GetOutput()->PrintMessage("Invalid answer ,Special attack instead of Reacharging Wallet ? (y/n)");
				decision = pGrid->GetInput()->GetSrting(pGrid->GetOutput());
			}
			if (decision == "y" || decision == "Y" )
			{
				string attack;
				pGrid->GetOutput()->PrintMessage("Choose from your attack: Ice (i), Fire (f), Poison (p), Lightning (l). (type b to go back)");
				attack = pGrid->GetInput()->GetSrting(pGrid->GetOutput()); 

				// If Player entered invalid answer  
				while (!(attack == "i" || attack == "I" || attack == "f" || attack == "F" || attack == "l" || attack == "L" || attack == "p" || attack == "P" || attack == "b" || attack == "B"))
				{
					pGrid->GetOutput()->PrintMessage("Invalid ,Choose from your attack: Ice (i), Fire (f), Poison (p), Lightning (l). (type b to go back)");
					attack = pGrid->GetInput()->GetSrting(pGrid->GetOutput());
				}

				// If the player is out of the chosen attack 
				// Or Entered invalid Attack
				while (!CanUseSpecialAttack(attack) && attack != "b" && attack != "B")  
				{
					pGrid->GetOutput()->PrintMessage("You are out of that Attack Choose another One: Ice (i), Fire (f), Poison (p), Lightning (l).(type b to go back)");
					attack = pGrid->GetInput()->GetSrting(pGrid->GetOutput());
				}

				// Applying the attack
				if (attack != "b"&& attack != "B" && CanUseSpecialAttack(attack) && (attack == "i" || attack == "I" || attack == "f" || attack == "F" || attack == "l" || attack == "L" || attack == "p" || attack == "P"))
				{
					pGrid->ApplySpecialAttack(*this, attack, playerNum);
				}

				else if (attack == "b" || attack == "B")  // In Case the Player Wants to Cancel the Attack
				{
					
					pGrid->PrintErrorMessage("Special attack is cancelled ,Now your wallet will be recharged ,Click to continue");

					if (!Poison)   // To Notify the Player of his Applied Punishment
					{
						pGrid->GetOutput()->PrintMessage("Your Dice Value is " + to_string(diceNumber));
						justRolledDiceNum = diceNumber ;
					}
					else
					{
						pGrid->GetOutput()->PrintMessage("Your Dice Value is " + to_string(diceNumber + 1) + " ,Applying Poison to be " + to_string(diceNumber));
						justRolledDiceNum = diceNumber + 1;
					}
					wallet += 10 * diceNumber;
					
				}
				ResetTurnCount();
			}
			else  // In case the Player Press No
			{
				pGrid->PrintErrorMessage("Now your wallet will be recharged, Click to continue");

				if (!Poison)
				{
					pGrid->GetOutput()->PrintMessage("Your Dice Value is " + to_string(diceNumber));
					justRolledDiceNum = diceNumber ;
				}
				else
				{
					pGrid->GetOutput()->PrintMessage("Your Dice Value is " + to_string(diceNumber + 1) + " ,Applying Poison to be " + to_string(diceNumber));
					justRolledDiceNum = diceNumber + 1;
				}
				wallet += 10 * diceNumber;
				ResetTurnCount();
			}
		}
		else			  // If the Player is out of attacks 
		{				  // Recharge the Player Wallet Directly

			pGrid->PrintErrorMessage("Now your wallet will be recharged, Click to continue");

			if (!Poison)
			{
				pGrid->GetOutput()->PrintMessage("Your Dice Value is " + to_string(diceNumber));
				justRolledDiceNum = diceNumber ;
			}
			else
			{
				pGrid->GetOutput()->PrintMessage("Your Dice Value is " + to_string(diceNumber + 1) + " ,Applying Poison to be " + to_string(diceNumber));
				justRolledDiceNum = diceNumber + 1;
			}
			wallet += 10 * diceNumber;
			ResetTurnCount();
		}
	}
	else   // If not Recharge Turn 
	{      // Updating the Player Position if not prevented from his turn

		CellPosition Pos = pCell->GetCellPosition();
		Pos.AddCellNum(diceNumber);
		if (Pos.VCell() == -1)  //incremented more than cell no.99
		{
			pGrid->SetEndGame(true);
			pGrid->PrintErrorMessage("congratulations ,Player " + to_string(playerNum) + " Has Won.");
			ClearDrawing(pGrid->GetOutput());
		}
		else
		{
			if (Poison)
			{
				Poison--;
				justRolledDiceNum = diceNumber + 1;
			}
			else
				justRolledDiceNum = diceNumber ;
			pGrid->UpdatePlayerCell(this, Pos);
		
		}
		
		if (pCell->HasLadder() || pCell->HasSnake())   // Taking Ladders & Snakes 
		{
			GameObject* CellObj = pCell->GetGameObject();
			CellObj->Apply(pGrid, this);
		}
		
		if (pCell->HasCard())						  // Applying the Card Command
		{
			GameObject* CellObj = pCell->GetGameObject();
			CellObj->Apply(pGrid, this);
		}
	}
	if (Fire)   // After Applying the Attack Fire Deduct 20 Coins from the Player Wallet
	{
		wallet -= 20;
		Fire--;			// Decrement the Done Attack (Turn from the 3)
	}
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)

	// 3- Set the justRolledDiceNum with the passed diceNumber

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"

	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position

	// 6- Apply() the game object of the reached cell (if any)

	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
}



void Player::AppendPlayerInfo(string& playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}

bool Player::CanUseSpecialAttack(const string& attack)
{
	if (specialAttackCount >= 2)
	{
		return false; // Already used two unique special attacks
	}
	if ((attack == "i" || attack == "I") && !usedIceAttack)
		return true;
	if ((attack == "f" || attack == "F") && !usedFireAttack)
		return true;
	if ((attack == "p" || attack == "P") && !usedPoisonAttack)
		return true;
	if ((attack == "l" || attack == "L") && !usedLightningAttack)
		return true;
	return false;
}
void Player::UseSpecialAttack(const string& attack)
{
	if (attack == "i" || attack == "I")
	{
		usedIceAttack = true;
		specialAttackCount++;
	}
	if (attack == "f" || attack == "F")
	{
		usedFireAttack = true;
		specialAttackCount++;
	}
	if (attack == "p" || attack == "P")
	{
		usedPoisonAttack = true;
		specialAttackCount++;
	}
	if (attack == "l" || attack == "L")
	{
		usedLightningAttack = true;
		specialAttackCount++;
	}
}

// Setters & Getters of the Special Attacks

void Player::SetPoison()
{
	Poison += 5;
}

int Player::GetPoison()
{
	return Poison;
}

void Player::SetFire()
{
	Fire += 3;
}

void Player::ResetFire() {
	Fire = 0;
}
void Player::ResetPoison() {
	Poison = 0;
}

void Player::SetUsedIceAttack(bool IceAttack)
{
	usedIceAttack = IceAttack;
}

bool Player::GetUsedIceAttack()
{
	return usedIceAttack;
}

void Player::SetUsedFireAttack(bool FireAttack)
{
	usedFireAttack = FireAttack;
}



bool Player::GetUsedFireAttack()
{
	return usedFireAttack;
}

void Player::SetUsedLightningAttack(bool LightningAttack)
{
	usedLightningAttack = LightningAttack;
}

bool Player::GetUsedLightningAttack()
{
	return usedLightningAttack;
}

void Player::SetspecialAttackCount(int AttackCount)
{
	specialAttackCount = AttackCount;
}

int Player::GetSpecialAttackCount()
{
	return specialAttackCount;
}

void Player::SetUsedPoisonAttack(bool PoisonAttack)
{
	usedPoisonAttack = PoisonAttack;
}

bool Player::GetUsedPoisonAttack()
{
	return usedPoisonAttack;
}
