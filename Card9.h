#pragma once

#include "Card.h"

class Card9 : public Card
{
private:
    CellPosition targetCell; // The cell the player will be moved to

public:
    Card9(const CellPosition& pos);  // Constructor
    virtual void ReadCardParameters(Grid* pGrid);  // Reads the target cell during design mode
    virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of moving the player
    virtual void Save(ofstream& OutFile, ObjectType type);   // Saves Card9 details
    virtual void Load(ifstream& InFile);             // Loads Card9 details
    virtual ~Card9();  // Destructor
    void SetCell(CellPosition cell); //Sets targetcell
    CellPosition GetCell(); // gets targetcell
};

