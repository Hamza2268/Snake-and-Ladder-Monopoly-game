#pragma once

#include "Grid.h"
#include "Cell.h"

class Player
{
	Cell* pCell;		   // pointer to the current Cell of the player

	const int playerNum;   // the player number (from 0 to MaxPlayerCount-1)
	// player number does NOT change after construction (const.)

	int stepCount;		   // step count which is the same as his cellNum: from 1 to NumVerticalCells*NumHorizontalCells
	int wallet;		       // player's wallet (how many coins he has -- integer)
	int justRolledDiceNum; // the current dice number which is just rolled by the player
	int turnCount;         // a counter that starts with 0, is incremented with each dice roll
	// and reset again when reached 3
	// it is used to indicate when to move and when to add to your wallet

	int Poison;  //  Turns to apply Poison on the chosen Player
	int Fire;   //  Turns to apply Fire on the chosen Player

	// Validation of the player usage not to use the same attack twice
	bool usedIceAttack;
	bool usedFireAttack;
	bool usedPoisonAttack;
	bool usedLightningAttack;

	// Special Attack Counters
	int specialAttackCount;

public:

	Player(Cell* pCell, int playerNum); // Constructor making any needed initializations

	// ====== Setters and Getters ======

	void SetCell(Cell* cell);		// A setter for the pCell
	Cell* GetCell() const;			// A getter for the pCell

	void SetWallet(int wallet);		// A setter for the wallet
	int GetWallet() const;			// a getter for the wallet
	void SetTurnCount(int T);
	int GetTurnCount() const;		// A getter for the turnCount

	///TODO: You can add setters and getters for data members here (if needed)
	void SetjustRolledDiceNum(int RolledDice);
	int GetjustRolledDiceNum();
	void IncrementTurnCount();
	void ResetTurnCount();
	// ====== Drawing Functions ======

	void Draw(Output* pOut) const;			// Draws the Player's Circle on its current cell

	void ClearDrawing(Output* pOut) const;	// Clears the Player's Circle from its current cell

	// ====== Game Functions ======

	void Move(Grid* pGrid, int diceNumber);	// Moves the Player with the passed diceNumber 
	// and Applies the Game Object's effect (if any) of the end reached cell 
	// for example, if the end cell contains a ladder, take it

	void AppendPlayerInfo(string& playersInfo) const; // Appends player's info to the input string, 
	// for example: P0(wallet, turnCount)

	bool CanUseSpecialAttack(const string& attack);
	void UseSpecialAttack(const string& attack);

	void SetPoison();  // Apply Poison
	int GetPoison();

	void SetFire();  // Apply Fire

	// For New Game Reset
	void ResetFire();
	void ResetPoison();

	// Setters and Getters For the Special Attack
	void SetUsedIceAttack(bool IceAttack);
	bool GetUsedIceAttack();

	
	void SetUsedFireAttack(bool FireAttack);
	bool GetUsedFireAttack();

	
	void SetUsedPoisonAttack(bool PoisonAttack);
	bool GetUsedPoisonAttack();

	
	void SetUsedLightningAttack(bool LightningAttack);
	bool GetUsedLightningAttack();

	
	void SetspecialAttackCount(int AttackCount);
	int GetSpecialAttackCount();
};
