#include "Input.h"

#include "Output.h"

//======================================================================================//
//								General Functions									    //
//======================================================================================//

Input::Input(window* pW)
{
	pWind = pW; // point to the passed window
}

////////////////////////////////////////////////////////////////////////////////////////// 

void Input::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y); // Note: x and y of WaitMouseClick are sent by reference
}

////////////////////////////////////////////////////////////////////////////////////////// 

string Input::GetSrting(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if (Key == 13)	// ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

////////////////////////////////////////////////////////////////////////////////////////// 

int Input::GetInteger(Output* pO) const
{

	///TODO: implement the GetInteger function as described in Input.h file 
	//       using function GetString() defined above and function stoi()

	string input = GetSrting(pO);
	// Checking if String is Numeric
	if (input.empty())
	{
		return -1;
	}
	for (int i = 0; i < input.length(); i++)
	{
		if (!isdigit(input.at(i)))
		{
			return -1;
		}
	}

	int num = (stoi(input) >= 0) ? stoi(input) : -1;

	return num;

}
//       using function GetString() defined above and function stoi()

//======================================================================================//
//								Game  Functions									        //
//======================================================================================//

ActionType Input::GetUserAction() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);

	//  ============ GUI in the Design mode ============
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// [1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_ADD_LADDER: return ADD_LADDER;
			case ITM_ADD_SNAKE: return ADD_SNAKE;
			case ITM_ADD_CARD: return ADD_CARD;
			case ITM_EXIT: return EXIT;
			case ITM_SWITCH_TO_PLAY_MODE: return TO_PLAY_MODE;
			case ITM_Copy_Card: return COPY_CARD;
			case ITM_CUT_CARD: return CUT_CARD;
			case ITM_Paste_Card: return PASTE_CARD;
			case ITM_Edit_Card: return EDIT_CARD;
			case ITM_Delete_Game_Object: return DELETE_GAME_OBJECT;
			case ITM_Save_Grid: return SAVE_GRID;
			case ITM_Open_Grid: return OPEN_GRID;




			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}

	// ============ GUI in the Play mode ============
	else
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int clickedItem = x / UI.MenuItemWidth;
			switch (clickedItem)
			{
			case ITM_ROLL_DICE: return ROLL_DICE;
			case ITM_Input_Dice_Value: return INPUT_DICE_VALUE;
			case ITM_New_Game: return NEW_GAME;
			case ITM_SWITCH_TO_DESIGN_MODE: return TO_DESIGN_MODE;
			case ITM_EXIT_PLAY_MODE: return EXIT;
			}
		}
		// perform checks similar to Design mode checks above for the Play Mode
		// and return the corresponding ActionType

	}

}

////////////////////////////////////////////////////////////////////////////////////////// 

CellPosition Input::GetCellClicked() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	// Get the coordinates of the user click

	CellPosition cellPos;

	if (UI.InterfaceMode == MODE_DESIGN)
	{
		if (y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight))
		{
			//       using the coordinates x, y and the appropriate variables of the UI_Info Object (UI)
			int hCell = x / UI.CellWidth;
			int vCell = (y - UI.ToolBarHeight) / UI.CellHeight;

			cellPos.SetHCell(hCell);
			cellPos.SetVCell(vCell);
			if (!cellPos.IsValidCell())
			{
				cellPos.SetHCell(-1);
				cellPos.SetVCell(-1);
			}
			return cellPos;
		}
	}

	return cellPos;
}

////////////////////////////////////////////////////////////////////////////////////////// 
