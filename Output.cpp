#include "Output.h"

#include "Input.h"

////////////////////////////////////////////////////////////////////////////////////////// 

Output::Output()
{
	// Initialize user interface parameters
	UI.InterfaceMode = MODE_DESIGN;

	// Widths and Heights

	UI.StatusBarHeight = 60;
	UI.ToolBarHeight = 55;
	UI.MenuItemWidth = 55;

	UI.width = 1210; // make it divisible by NumHorizontalCells
	UI.height = 610;
	UI.wx = 5;
	UI.wy = 5;

	UI.CellWidth = UI.width / NumHorizontalCells;
	UI.CellHeight = (UI.height - UI.ToolBarHeight - UI.StatusBarHeight) / NumVerticalCells;

	// Pen Colors of messages of status bar and players' info
	UI.MsgColor = DARKRED;
	UI.PlayerInfoColor = DARKSLATEBLUE;

	// Background Colors of toolbar and statusbar 
	UI.ToolBarColor = WHITE;
	UI.StatusBarColor = LIGHTGRAY;

	// Line Colors of the borders of each cell
	UI.GridLineColor = WHITE;

	// Cell Color if Empty & Cell Number Font & Color
	UI.CellColor_NoCard = LIGHTSLATEBLUE;
	UI.CellNumFont = 13;
	UI.CellNumColor = UI.GridLineColor;

	// Cell Color if Has Card & CARD Number Font & Color
	UI.CellColor_HasCard = SALMON;
	UI.CardNumFont = 35;
	UI.CardNumColor = WHITE;

	// Ladder Line Width and Color
	UI.LadderlineWidth = 6;
	UI.LadderColor = DARKSLATEBLUE;

	// The X and Y Offsets of the Space BEFORE Drawing the Ladder (offset from the start X and Y of the Cell)
	UI.LadderXOffset = (UI.CellWidth - 2 * UI.LadderlineWidth) / 5;
	UI.LadderYOffset = UI.CellHeight / 2;

	// Snake Line Width and Color
	UI.SnakelineWidth = 6;
	UI.SnakeColor = FIREBRICK;

	// Colors of the 4 Players
	UI.PlayerColors[0] = GOLD;
	UI.PlayerColors[1] = DARKSLATEBLUE;
	UI.PlayerColors[2] = KHAKI;
	UI.PlayerColors[3] = CHOCOLATE;

	// Create the output window
	pWind = CreateWind(UI.width + 15, UI.height, UI.wx, UI.wy);

	// Change the title
	pWind->ChangeTitle("Snakes & Ladders");

	// Create the toolbar, grid area and status bar
	CreateDesignModeToolBar();
	ClearGridArea();
	ClearStatusBar();

}

////////////////////////////////////////////////////////////////////////////////////////// 

window* Output::CreateWind(int w, int h, int x, int y) const
{
	// The Window Object is created inside the Ouput class
	window* pW = new window(w, h, x, y);
	return pW;
}

////////////////////////////////////////////////////////////////////////////////////////// 

Input* Output::CreateInput() const
{
	// The Input Object is created inside the Output class
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Some Utility Functions										//
//======================================================================================//

int Output::GetCellStartX(const CellPosition& cellPos) const
{
	int Num = cellPos.HCell();
	int cellwidth = UI.CellWidth;
	return cellwidth * Num;
	// this line should be changed with your implementation
}

//////////////////////////////////////////////////////////////////////////////////////////

int Output::GetCellStartY(const CellPosition& cellPos) const
{
	int Num = cellPos.VCell();
	int cellHeigth = UI.CellHeight;
	return (UI.ToolBarHeight + (cellHeigth * Num));
	// this line should be changed with your implementation
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawCardNumber(const CellPosition& cellPos, int cardNum) const
{
	// Get the X and Y of the upper left corner of the cell
	int cellStartX = GetCellStartX(cellPos);
	int cellStartY = GetCellStartY(cellPos);

	// Set the pen and font
	pWind->SetPen(UI.CardNumColor);
	pWind->SetFont(UI.CardNumFont, BOLD | ITALICIZED, BY_NAME, "Arial");

	int w = 0, h = 0;

	//       (Use GetIntegerSize() window function) and set the "w" and "h" variables with its width and height

	pWind->GetIntegerSize(w, h, cardNum);

	// Calculate where to write the integer of the cardNum
	int x = cellStartX + UI.CellWidth - UI.LadderXOffset - w - 5; // Before the End vertical line of a ladder 
	// (assuming the case where ladder is inside the cell)
	int y = cellStartY + (UI.CellHeight - h) / 2;    // in the vertical Middle of the cell


	pWind->DrawInteger(x, y, cardNum);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearToolBar() const
{
	// Clear by drawing a rectangle filled with toolbar background color
	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

void Output::ClearStatusBar() const
{
	// Clear drawing a rectangle filled with statusbar background color
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearGridArea() const
{
	// Draw each cell in the Grid: ( NumVerticalCells * NumberHorizontalCells )
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			CellPosition cellPos(i, j);
			DrawCell(cellPos); // Initially NO Cards in the cell
		}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateDesignModeToolBar() const
{
	UI.InterfaceMode = MODE_DESIGN;

	ClearToolBar(); // in order not to draw above the icons of the other mode when you switch

	// You can draw the tool bar icons in any way you want.
	// Below is one possible way

	// First prepare List of images for each menu item
	// To control the order of these images in the menu, 
	// reoder them in UI_Info.h ==> enum DESIGN_MODE_ITEMS
	// ** MAKE SURE THAT THE IMAGES ARE .JPG FILES **
	string MenuItemImages[DESIGN_ITM_COUNT];
	MenuItemImages[ITM_ADD_LADDER] = "images\\Menu_Ladder.jpg";
	MenuItemImages[ITM_ADD_SNAKE] = "images\\Menu_Snake.jpg";
	MenuItemImages[ITM_ADD_CARD] = "images\\Menu_Card.jpg";
	MenuItemImages[ITM_Copy_Card] = "images\\Menu_CopyCard.jpg";
	MenuItemImages[ITM_CUT_CARD] = "images\\Menu_CutCard.jpg";
	MenuItemImages[ITM_Paste_Card] = "images\\Menu_PasteCard.jpg";
	MenuItemImages[ITM_Edit_Card] = "images\\Menu_EditCard.jpg";
	MenuItemImages[ITM_Delete_Game_Object] = "images\\Menu_DeleteCard.jpg";
	MenuItemImages[ITM_Save_Grid] = "images\\Menu_SaveGrid.jpg";
	MenuItemImages[ITM_Open_Grid] = "images\\Menu_OpenGrid.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu_Exit.jpg";
	MenuItemImages[ITM_SWITCH_TO_PLAY_MODE] = "images\\Menu_SwitchToGame.jpg";



	// Draw menu item one image at a time
	for (int i = 0; i < DESIGN_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);


}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayModeToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;

	ClearToolBar(); // in order not to draw above the icons of the other mode when you switch

	// You can draw the tool bar icons in any way you want.
	// Below is one possible way

	// First prepare List of images for each menu item
	// To control the order of these images in the menu, 
	// reoder them in UI_Info.h ==> enum DESIGN_MODE_ITEMS
	// ** MAKE SURE THAT THE IMAGES ARE .JPG FILES **
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_ROLL_DICE] = "images\\Menu_Dice.jpg";
	MenuItemImages[ITM_Input_Dice_Value] = "images\\Menu_DiceValue.jpg";
	MenuItemImages[ITM_New_Game] = "images\\Menu_NewGame.jpg";
	MenuItemImages[ITM_SWITCH_TO_DESIGN_MODE] = "images\\Menu_SwitchToGrid.jpg";
	MenuItemImages[ITM_EXIT_PLAY_MODE] = "images\\Menu_Exit.jpg";



	// Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	// First clear the status bar from any previous writing

	// Set pen and font before drawing the string on the window
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(18, BOLD, BY_NAME, "Verdana");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.3), msg);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintPlayersInfo(string info)
{
	CreatePlayModeToolBar();

	// Set the pen and font before drawing the string on the window
	pWind->SetPen(UI.PlayerInfoColor);
	pWind->SetFont(20, BOLD, BY_NAME, "Verdana");

	int w = 0, h = 0;

	//       (Use GetStringSize() window function) and set the "w" and "h" variables with its width and height


	pWind->GetStringSize(w, h, info);

	// Set the start X & Y coordinate of drawing the string
	int x = UI.width - w - 20; // space 20 before the right-side of the window
	// ( - w ) because x is the coordinate of the start point of the string (upper left)
	int y = (UI.ToolBarHeight - h) / 2; // in the Middle of the toolbar height

	pWind->DrawString(x, y, info);
}

//======================================================================================//
//			         			Game Drawing Functions   								//
//======================================================================================//

void Output::DrawCell(const CellPosition& cellPos, int cardNum) const
{
	// Get the Cell Number (from 1 to NumVerticalCells*NumHorizontalCells) and the X & Y of its upper left corner
	int cellNum = cellPos.GetCellNum();
	int cellStartX = GetCellStartX(cellPos);
	int cellStartY = GetCellStartY(cellPos);

	// ----- 1- Draw the cell itself (background) --> Filled Rectangle -----
	pWind->SetPen(UI.GridLineColor, 1);
	if (cardNum == -1) // no card
		pWind->SetBrush(UI.CellColor_NoCard);
	else
		pWind->SetBrush(UI.CellColor_HasCard);
	pWind->DrawRectangle(cellStartX, cellStartY, cellStartX + UI.CellWidth, cellStartY + UI.CellHeight);



	// ----- 2- Draw the CELL number (the small number at the bottom right of the cell) -----
	pWind->SetPen(UI.CellNumColor);
	pWind->SetFont(UI.CellNumFont, BOLD, BY_NAME, "Verdana");

	int w = 0, h = 0;
	//       (Use GetIntegerSize() window function) and set the "w" and "h" variables with its width and height

	pWind->GetIntegerSize(w, h, cellNum);

	// Calculate X & Y coordinate of the start point of writing the card number (upper left point of the cell num)
	int x = cellStartX + (UI.CellWidth - w - 1);   // space 1 from the end of the cell width
	// ( - w ) because x is for the start point of cell num (num's left corner)
	int y = cellStartY + (UI.CellHeight - h - 1);  // space 1 from the end of the cell height
	// ( - w ) because y is for the start point of cell num (num's upper corner)

	pWind->DrawInteger(x, y, cellNum);

	// ----- 3- Draw card number (if any) -----
	if (cardNum != -1) // Note: cardNum -1 means no card
		DrawCardNumber(cellPos, cardNum);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawPlayer(const CellPosition& cellPos, int playerNum, color playerColor) const
{

	if (playerNum < 0 || playerNum>3)
		return;


	// Get the X & Y coordinates of the start point of the cell (its upper left corner)
	int cellStartX = GetCellStartX(cellPos);
	int cellStartY = GetCellStartY(cellPos);

	// Calculate the Radius of the Player's Circle
	int radius = UI.CellWidth / 14; // proportional to cell width

	// Calculate the horizontal space before drawing players circles (space from the left border of the cell)
	int ySpace = UI.CellHeight / 6; // proportional to cell height

	// Note: Players' Circles Locations depending on "playerNum" is as follows:
	// Player_0   Player_1
	// Player_2   Player_3

	// Calculate the Y coordinate of the center of the player's circle (based on playerNum)
	int y = cellStartY + ySpace + radius + 2;
	if (playerNum == 2 || playerNum == 3)
		y += radius + 2 + radius; // because playerNum 2 and 3 are drawn in the second row of circles

	// Calculate the Y coordinate of the center of the player's circle (based on playerNum)
	int x = cellStartX + UI.LadderXOffset + radius + 4; // UI.LadderXOffset is used to draw players' circles 
	// AFTER the ladder start vertical line (assuming there is a ladder)
	// for not overlapping with ladders
	if (playerNum == 1 || playerNum == 3)
		x += radius + 2 + radius; // because playerNum 1 and 3 are drawn in the second column of circles

	//playerColor = UI.PlayerColors[playerNum];
	pWind->SetBrush(playerColor);
	pWind->SetPen(playerColor);
	pWind->DrawCircle(x, y, radius, FILLED);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawLadder(const CellPosition& fromCell, const CellPosition& toCell) const
{
	if (fromCell.HCell() != toCell.HCell()) {
		PrintMessage("end cell and start cell are not in the same column, Click to continue");
	}

	if (fromCell.VCell() < toCell.VCell()) {
		PrintMessage("end cell cannot be smaller than start cell, Click to continue");
	}


	else {

		// Get the start X and Y coordinates of the upper left corner of the fromCell
		int cellStartX = GetCellStartX(fromCell);
		int fromStartY = GetCellStartY(fromCell);

		// Get the start Y coordinates of the upper left corner of the toCell (the X should be the same as fromCell .. Vertical)
		int toStartY = GetCellStartY(toCell);

		// ---- 1- Draw the First Vertical Line ---- 
		int x12 = cellStartX + UI.LadderXOffset; // the two points have the same x (vertical)
		int y1 = fromStartY + UI.LadderYOffset;  // the coordinate y of the first point of the First Vertical line
		int y2 = toStartY + UI.CellHeight - UI.LadderYOffset; // the coordinate y of the second point of the First Vertical line

		pWind->SetPen(UI.LadderColor, UI.LadderlineWidth);






		pWind->DrawLine(x12, y1, x12, y2, FRAME);


		// ---- 2- Draw the Second Vertical Line ---- 
		int x34 = cellStartX + UI.CellWidth - UI.LadderXOffset; // same x (vertical line)

		pWind->SetPen(UI.LadderColor, UI.LadderlineWidth);

		pWind->DrawLine(x34, y1, x34, y2, FRAME);

		// ---- 3- Draw the Cross Horizontal Lines ---- 



		for (fromStartY; fromStartY > toStartY; fromStartY -= UI.CellHeight) {
			pWind->DrawLine(x12, fromStartY, x34, fromStartY);
		}


		// The cross lines are drawn on the Horizontal Borders of the Cells between fromCell to toCell
		// Check the drawn ladders in the project document and imitate it

	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawSnake(const CellPosition& fromCell, const CellPosition& toCell) const
{

	if (fromCell.HCell() != toCell.HCell()) {
		PrintMessage("end cell and start cell are not in the same column, Click to continue");
	}




	else if (fromCell.VCell() > toCell.VCell()) {
		PrintMessage("end cell cannot be larger than start cell, Click to continue");
	}

	else {
		// Get the upper left corner coordinates of the fromCell and toCell
		int cellStartX = GetCellStartX(fromCell); // same for fromCell and toCell (vertical)
		int fromStartY = GetCellStartY(fromCell);
		int toStartY = GetCellStartY(toCell);

		// ---- 1- Draw Line representing the Snake Body ----

		// Set coordinates of start and end points of the Line of the Snake's Body
		int x12 = cellStartX + UI.LadderXOffset / 2; // same for the start and end point (vertical)
		int y1 = fromStartY + UI.CellHeight / 2;
		int y2 = toStartY + UI.CellHeight / 2;


		pWind->SetPen(UI.SnakeColor, UI.SnakelineWidth);



		pWind->DrawLine(x12, y1, x12, y2, FRAME);


		// ---- 2- Draw Polygon with Diamond Shape representing the Snake Head ----

		// Set Pen and Brush (background) of the Polygon
		pWind->SetPen(UI.SnakeColor, UI.SnakelineWidth);
		pWind->SetBrush(UI.SnakeColor);

		int yChange = UI.CellHeight / 4; // slight vertical difference to be used in the up and down polygon points
		int xChange = UI.CellWidth / 14; // slight horizontal difference to be used in the left and right polygon points


		//       Check the snakes drawn in the project document and draw it the same way
		int xcoords[4] = { x12,x12 - xChange,x12,x12 + xChange };
		int ycoords[4] = { (y1 + yChange) ,y1,(y1 - yChange),y1 };




		pWind->DrawPolygon(xcoords, ycoords, 4, FILLED);


		//       Check the snakes drawn in the project document and draw it the same way

	}
}

//////////////////////////////////////////////////////////////////////////////////////////

Output::~Output()
{
	// deallocating the window object
	delete pWind;
}

