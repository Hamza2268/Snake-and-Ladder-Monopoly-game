#pragma once
#include "Card.h"
class Card13 :
	public Card
{

	static int Price;
	static int Fees;
	static bool Initialized;
	static Player* Owner;
	static bool SavedOnce;
	static bool OpenOnce;

public:
	Card13(const CellPosition& pos);

	void setPrice(int x);
	void EditParameters(Grid* pGrid);
	void setFees(int y);
	int GetPrice();
	int GetFees();
	virtual bool IsOverlapping(GameObject* newObj) const;

	virtual void ReadCardParameters(Grid* pGrid); // Reads card parameters once

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies card effect
	virtual void Save(std::ofstream& outfile, ObjectType type);
	virtual void Load(ifstream& InFile); // Loads card data

	virtual ~Card13(); // Destructor
	void Reset();

	static void setSavedOnce(bool s);
	static void setOpenOnce(bool s);
};