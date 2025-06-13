#pragma once

#include "Card.h"

class Card7 : public Card
{
public:
    Card7(const CellPosition& pos);  // Constructor
    virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of Card7
    virtual void Save(ofstream& OutFile, ObjectType type);   // Saves Card7 details
    virtual void Load(ifstream& InFile);             // Loads Card7 details
    virtual ~Card7();  // Destructor
};
