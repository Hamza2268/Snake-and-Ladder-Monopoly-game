#include "Card11.h"



int Card11::Price = 0;
int Card11::Fees = 0;
bool Card11::Initialized = false;
Player* Card11::Owner = nullptr;
bool Card11::SavedOnce = false;
bool Card11::OpenOnce=false;
Card11::Card11(const CellPosition& pos) : Card(pos) {

    cardNumber = 11;
}
Card11::~Card11()
{

}
int Card11::GetPrice()
{
    return Price;
}

int Card11::GetFees()
{
    return Fees;
}
void Card11::setPrice(int x) {
    if (x >= 0) Price = x;
}

void Card11::setFees(int x) {
    if (x >= 0) Fees = x;
}

void Card11::ReadCardParameters(Grid* pGrid)// Reads from user Valid price and fees for card
{
    if (!Initialized) {
        Input* piN = pGrid->GetInput();
        Output* pouT = pGrid->GetOutput();


        pouT->PrintMessage("New Card11, Enter the station price: ");
        int cprice = piN->GetInteger(pouT);

        while (cprice <= 0)
        {
            pouT->PrintMessage("Invalid :New Card11, Enter the station price: ");
             cprice = piN->GetInteger(pouT);
        }
        setPrice(cprice);

        pouT->PrintMessage("New Card11, Enter the station fees: ");
        int cfees = piN->GetInteger(pouT);

        while (cfees <= 0)
        {
            pouT->PrintMessage("Invalid :New Card11, Enter the station fees: ");
             cfees = piN->GetInteger(pouT);
        }
        setFees(cfees);

        Initialized = true;
        pouT->ClearStatusBar();
    }

}

void Card11::Apply(Grid* pGrid, Player* pPlayer)//Applys during the game to give option to buy card if not owned 
//and deducts fees if owned and adds it to the owner
{

    Card::Apply(pGrid, pPlayer);

    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    if (Owner == nullptr)
    {
        pOut->PrintMessage("Do you want to buy Card11? (Price: " + to_string(Price) + ") (Y/N)");
        string choice = pIn->GetSrting(pOut);

        while (!(choice == "Y" || choice == "y" || choice == "N" || choice == "n")) {

            pOut->PrintMessage("Please enter valid Answer ,Do you want to buy Card11? (Price: " + to_string(Price) + ") (Y/N)");
            choice = pIn->GetSrting(pOut);
        }

        if (choice == "Y" || choice == "y")
        {
            if (pPlayer->GetWallet() >= Price)
            {
                pPlayer->SetWallet(pPlayer->GetWallet() - Price);
                Owner = pPlayer;
                pOut->PrintMessage("You bought all Card11 stations!");
            }
            else
            {
                pOut->PrintMessage("Insufficient wallet amount to buy the station.");
            }
        }
        else if (choice == "N" || choice == "n") {
            pOut->PrintMessage("Didn't buy station");
        }

  
    }
    else if (Owner != pPlayer)
    {
        pOut->PrintMessage("This station is owned. You must pay fees!");
        if (pPlayer->GetWallet() - Fees > 0)
            Owner->SetWallet(Owner->GetWallet() + Fees);
        else
            Owner->SetWallet(Owner->GetWallet() + pPlayer->GetWallet());
        pPlayer->SetWallet(pPlayer->GetWallet() - Fees);
    }
    else
    {
        pOut->PrintMessage("You already own this station.");
    }
}


void Card11::Save(std::ofstream& outfile, ObjectType type)//saves special parameters as price and fees if first time saving
{

    if (!SavedOnce)
    {
        Card::Save(outfile, type);
        outfile << " " << Price << " " << Fees << endl;
        SavedOnce = true;
    }
    else
    {
        Card::Save(outfile, type);
        outfile << endl;
    }
}

void Card11::Load(ifstream& InFile)//loads special parameters as price and fees if not opened before
{
    Card::Load(InFile);
    if (!OpenOnce)
    {
        int p, f;
        InFile >> p >> f;
        setPrice(p);
        setFees(f);
        OpenOnce = true;
    }
}

bool Card11::IsOverlapping(GameObject* newObj) const
{
    return false;
}

void Card11::EditParameters(Grid* pGrid)//rereads parameters for editimg card
{
    // Get pointers to Input and Output interfaces
    Input* pInput = pGrid->GetInput();
    Output* pOutput = pGrid->GetOutput();

    // Print a message to inform the user about the edit action
    pOutput->PrintMessage("Editing Card11: Enter new card price...");

    // Read the new price from the user
    int newPrice = pInput->GetInteger(pOutput);
    while (newPrice < 0) // Ensure the price is positive
    {
        pOutput->PrintMessage("Invalid price. Please enter a positive value:");
        newPrice = pInput->GetInteger(pOutput);
    }

    // Print a message to enter the new fees
    pOutput->PrintMessage("Enter new fees for Card11...");
    int newFees = pInput->GetInteger(pOutput);
    while (newFees < 0) // Ensure the fees are positive
    {
        pOutput->PrintMessage("Invalid fees. Please enter a positive value:");
        newFees = pInput->GetInteger(pOutput);
    }

    // Update the card's data members
    setPrice(newPrice);
    setFees(newFees);

    // Clear the status bar
    pOutput->ClearStatusBar();
}
void Card11::Reset()// resets owner to none for new game
{
    Owner = nullptr;
    Initialized = false;
}

void Card11::setSavedOnce(bool s)//so it doesn't save price amd fees for allcards
{
    SavedOnce = s;
}

void Card11::setOpenOnce(bool s)//so it doesn't load price and fees more than once
{
    OpenOnce = s;
}
