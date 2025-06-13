#pragma once

#include "GameObject.h"
#include "Player.h"


// Base Class of All Types of Cards (CardOne, CardTwo, CardThree, ...etc.)
// Note: We will make each type of Card in a separate class because:
// it may have additional data members and functions like: Apply(), ...etc. which have different implementation depending on Card Number
class Card : public GameObject
{
protected:
	int cardNumber; // an integer representing the card number
public:
	Card(const CellPosition& pos); // A Constructor for card that takes the cell position of it

	virtual void Reset();

	void SetCardNumber(int cnum);   // The setter of card number
	int GetCardNumber();            // The getter of card number
	void setPosition(CellPosition pos);
	void Draw(Output* pOut) const;  // Draws the card number in the cell position of the card
	// It has the same implementation for all Card Types (Non-Virtual)

	virtual void ReadCardParameters(Grid* pGrid); // It reads the parameters specific for each Card Type
	// It is a virtual function (implementation depends on Card Type)

	virtual void Apply(Grid* pGrid, Player* pPlayer);  // It applies the effect of the Card Type on the passed player
	// It is a virtual function (implementation depends on Card Type)

	virtual void Save(ofstream& outfile, ObjectType type);	// Saves the GameObject parameters to the file
	virtual void Load(ifstream& Infile);	// Loads and Reads the GameObject parameters from the file
	virtual ObjectType GetType() const;

	virtual ~Card(); // A Virtual Destructor

	virtual bool IsOverlapping(GameObject* newObj) const;

	virtual void EditParameters(Grid* pGrid);
};