#include <iostream>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <time.h>

//Enumeration type, gives names to the built-in colours
enum concol
{
	black = 0, dark_blue = 1, dark_green = 2, dark_cyan = 3, dark_red = 4,
	dark_purple = 5, dark_yellow = 6, light_gray = 7, gray = 8, blue = 9,
	green = 10, cyan = 11, red = 12, purple = 13, yellow = 14, white = 15
};

//Function to set the text and background colours
void setColours(concol textCol, concol backCol)
{
	unsigned short colours = (backCol << 4) | textCol;

	//Set the attributes for the console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colours);
}

//Function to return how much of the board the player can see
int furthestVisibility(std::vector<char> supporting)
{
	int visibility = 0;
	for (int i = 0; i < supporting.size(); i++)
	{
		if (supporting[i] == 'F')
		{
			visibility = i;
		}
	}

	//Returns the value of the furthest piece on the board plus two
	return visibility + 2;
}

//Function to return how much of the board the player can see
int nearestVisibility(std::vector<char> supporting)
{
	for (int i = 0; i < supporting.size(); i++)
	{
		if (supporting[i] == 'F')
		{
			//Returns the value of the nearest piece on the board minus two
			return i - 2;
		}
	}
}

//Function that is to be called when the program starts up
//It initialises the values of boardSize and playerTokens which will influence the printing of the grid
void startUp(int& boardSize, int& playerTokens)
{
	//Make user input value into boardSize
	std::cout << "   The board can be of any size between 3 and 30\n";
	std::cout << "   Enter the size of the board : ";
	std::cin >> boardSize;

	//Data Validation for boardSize
	while (std::cin.fail() || boardSize > 30 || boardSize < 3)
	{
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "   Invalid value entered. Please try again\n" << std::endl;
		std::cout << "   The board can be of any size between 3 and 30\n";
		std::cout << "   Enter the size of the grid : ";
		std::cin >> boardSize;
	}

	//If boardSize is an even number
	if (boardSize % 2 == 0)
	{
		//Value set to 1 as the player has no choice
		if ((boardSize / 2) - 1 == 1)
		{
			playerTokens = 1;
		}
		else
		{
			//Make user input value into playerTokens
			std::cout << "\n   Both players can have tokens ranging between 1 and " << (boardSize / 2) - 1 << "\n";
			std::cout << "   Enter the number of player tokens : ";
			std::cin >> playerTokens;

			//Data Validation for playerTokens
			while (std::cin.fail() || playerTokens<1 || playerTokens>(boardSize / 2) - 1)
			{
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "   Invalid value entered. Please try again\n" << std::endl;
				std::cout << "   Both players can have tokens ranging between 1 and " << (boardSize / 2) - 1 << "\n";
				std::cout << "   Enter the number of player tokens : ";
				std::cin >> playerTokens;
			}
		}		
	}
	//If boardSize is an odd number
	else
	{
		//Value set to 1 as the player has no choice
		if (((boardSize + 1) / 2) - 1 == 1)
		{
			playerTokens = 1;
		}
		else
		{
			//Make user input value into playerTokens
			std::cout << "\n   Both players can have tokens ranging between 1 and " << ((boardSize + 1) / 2) - 1 << "\n";
			std::cout << "   Enter the number of player tokens : ";
			std::cin >> playerTokens;

			//Data Validation for playerTokens
			while (std::cin.fail() || playerTokens<1 || playerTokens>((boardSize + 1) / 2) - 1)
			{
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "   Invalid value entered. Please try again\n" << std::endl;
				std::cout << "   Both players can have tokens ranging between 1 and " << ((boardSize + 1) / 2) - 1 << "\n";
				std::cout << "   Enter the number of player tokens : ";
				std::cin >> playerTokens;
			}
		}	
	}

	if (boardSize >= 25)
	{
		std::cout << "\n   Since you have opted for a larger board, it would be recommended to maximise your console window, if not already maximised.\n";
	}
}

//Function that is to be called to set up the game pieces
//It assigns positions on the board for the Frogs and Toads
void setUp(std::vector<char>& gameBoard, std::vector<char>& supporting, int boardSize, int playerTokens)
{
	//Assigning values for Frogs
	for (int i = 0; i < playerTokens; i++)
	{
		gameBoard.at(i) = char(254);
		supporting.at(i) = 'F';
	}

	//Assigning values for Toads
	for (int i = boardSize - 1; i > (boardSize - 1) - playerTokens; i--)
	{
		gameBoard.at(i) = char(254);
		supporting.at(i) = 'T';
	}
}

//Function to Print Board
//Takes two one-dimensional vectors as parameters
void printBoard(std::vector<char> gameBoard, std::vector<char> supporting)
{
	bool visible = true;
	//Printing Column Numbers
	std::cout << "\n   ";
	for (int i = 0; i < gameBoard.size(); i++)
	{
		if (i >= 8)
		{
			std::cout << " " << i + 1 << " ";
		}
		else
		{
			std::cout << " " << i + 1 << "  ";
		}
	}
	std::cout << std::endl;

	//Printing Board Top
	std::cout << "  " << char(218);
	for (int i = 0; i < gameBoard.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << char(196);
		}

		if (i == gameBoard.size() - 1)
		{
			std::cout << char(191);
		}
		else
		{
			std::cout << char(194);
		}
	}
	std::cout << std::endl;

	//Printing Board
	//Prints the elements in different colours depending upon the content they hold
	std::cout << "  ";
	std::cout << char(179);
	for (int i = 0; i < gameBoard.size(); i++)
	{
		if (i <= furthestVisibility(supporting) && i>=nearestVisibility(supporting))
		{
			visible = true;
		}
		else
		{
			visible = false;
		}

		if (!visible)
		{
			setColours(gray, gray);
		}
		//Printing Vector Elements
		std::cout << ' ';

		if (supporting[i] == 'F' && visible)
		{
			setColours(green, black);
		}
		else if (supporting[i] == 'T' && visible)
		{
			setColours(red, black);
		}
		std::cout << gameBoard[i];

		if (visible)
		{
			setColours(white, black);
		}

		std::cout << ' ';
		setColours(white, black);
		std::cout << char(179);

	}
	std::cout << std::endl;

	//Printing Board Bottom
	std::cout << "  ";
	std::cout << char(192);
	for (int i = 0; i < gameBoard.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << char(196);
		}

		if (i == gameBoard.size() - 1)
		{
			std::cout << char(217);
		}
		else
		{
			std::cout << char(193);
		}
	}
	std::cout << std::endl;
}

//Function to Print Board without the Fog
//Takes two one-dimensional vectors as parameters
void finalPrint(std::vector<char> gameBoard, std::vector<char> supporting)
{
	//Printing Board Top
	std::cout << "  " << char(218);
	for (int i = 0; i < gameBoard.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << char(196);
		}

		if (i == gameBoard.size() - 1)
		{
			std::cout << char(191);
		}
		else
		{
			std::cout << char(194);
		}
	}
	std::cout << std::endl;

	//Printing Board
	//Prints the elements in different colours depending upon the content they hold
	std::cout << "  ";
	std::cout << char(179);
	for (int i = 0; i < gameBoard.size(); i++)
	{
		//Printing Vector Elements
		std::cout << ' ';

		if (supporting[i] == 'F')
		{
			setColours(green, black);
		}
		else if (supporting[i] == 'T')
		{
			setColours(red, black);
		}
		std::cout << gameBoard[i];

		std::cout << ' ';
		setColours(white, black);
		std::cout << char(179);

	}
	std::cout << std::endl;

	//Printing Board Bottom
	std::cout << "  ";
	std::cout << char(192);
	for (int i = 0; i < gameBoard.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << char(196);
		}

		if (i == gameBoard.size() - 1)
		{
			std::cout << char(217);
		}
		else
		{
			std::cout << char(193);
		}
	}
	std::cout << std::endl;
}

//Function to handle the Player 1 Move
void player1Move(std::vector<char>& gameBoard, std::vector<char>& supporting)
{
	int column;
	bool error = false;
	bool jump = false;
	std::cout << "\n   Player 1's Move (Frogs/Green)\n" << std::endl;

	//Inputting values for column
	//Checking if the values entered are valid
	//Checking and making sure the move is valid before making the move
	do
	{
		std::cout << "   Enter the column number of the piece you want to move : ";
		std::cin >> column;

		while (column<1 || column>supporting.size() || std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "   Invalid value entered. Please try again\n" << std::endl;
			std::cout << "   Enter the column number of the piece you want to move : ";
			std::cin >> column;
		}
		column--;

		//If the current element is F, and the next element is occupied, but the element after is free, jump will be set to true
		//Indicating the player token must jump over the character
		if (supporting[column] == 'F' && ((column != supporting.size() - 1 && column != supporting.size() - 2) && supporting[column + 1] != ' ' && supporting[column + 2] == ' '))
		{
			jump = true;
			error = false;
		}
		else if (supporting[column] != 'F' || (column == supporting.size() - 1 || supporting[column + 1] != ' '))
		{
			error = true;
			std::cout << "   Invalid value entered. Please try again\n" << std::endl;
		}
		else
		{
			error = false;
		}
	} while (error);

	//Making the move
	//If jump is true, move the piece 2 columns
	//If not, move the piece 1 column
	if (jump)
	{
		gameBoard.at(column) = ' ';
		gameBoard.at(column + 2) = char(254);
		supporting.at(column) = ' ';
		supporting.at(column + 2) = 'F';

		std::cout << "   You have moved the Frog from " << column + 1 << " to " << column + 3 << std::endl;
	}
	else
	{
		gameBoard.at(column) = ' ';
		gameBoard.at(column + 1) = char(254);
		supporting.at(column) = ' ';
		supporting.at(column + 1) = 'F';

		std::cout << "   You have moved the Frog from " << column + 1 << " to " << column + 2 << std::endl;
	}

	//Printing updated board
	printBoard(gameBoard, supporting);
}

//Function to handle the CPU Move
void cpuMove(std::vector<char>& gameBoard, std::vector<char>& supporting)
{
	std::cout << "\n   Player 2's Move - CPU (Toads/Red)\n" << std::endl;

	srand(time(nullptr));

	std::vector<int> movable;
	int choice;

	//Iterating through the vector and checking if the piece is movable or not
	//If movable, push back the index (i) to the vector
	for (int i = 0; i < supporting.size(); i++)
	{
		if (i == 1 && supporting[i] == 'T' && supporting[i - 1] == ' ')
		{
			movable.push_back(i);
		}
		else if (i > 1 && supporting[i] == 'T' && (supporting[i - 1] == ' ' || supporting[i - 2] == ' '))
		{
			movable.push_back(i);
		}
	}

	//Returns random index between 0 and size of the vector movable
	//This index will give the column of the piece to be moved
	choice = rand() % movable.size();

	//If jump criteria are met, the token will jump over the next piece
	if ((movable[choice] != 0 && movable[choice] != 1) && supporting[movable[choice] - 1] != ' ' && supporting[movable[choice] - 2 == ' '])
	{
		gameBoard.at(movable[choice]) = ' ';
		gameBoard.at(movable[choice] - 2) = char(254);
		supporting.at(movable[choice]) = ' ';
		supporting.at(movable[choice] - 2) = 'T';
	}
	//If not, the piece will move normally
	else
	{
		gameBoard.at(movable[choice]) = ' ';
		gameBoard.at(movable[choice] - 1) = char(254);
		supporting.at(movable[choice]) = ' ';
		supporting.at(movable[choice] - 1) = 'T';
	}
	
	//Printing updated board
	printBoard(gameBoard, supporting);
}

//Function to check if Player 1 has any moves left
//Returns a Boolean accordingly
bool checkP1Moves(std::vector<char> supporting)
{
	for (int i = 0; i < supporting.size(); i++)
	{
		//If the current element is the second last element and
		//If it is a frog and
		//If the next element is empty
		//Return true
		if (i == supporting.size() - 2 && supporting[i] == 'F' && supporting[i + 1] == ' ')
		{
			return true;
		}
		//If the current element is not any of the last two elements and
		//If it is a frog and
		//If either the next element or the element after is empty
		//Return true
		else if (i < supporting.size() - 2 && supporting[i] == 'F' && (supporting[i + 1] == ' ' || supporting[i + 2] == ' '))
		{
			return true;
		}
	}
	return false;
}

//Function to check if Player 2 has any moves left
//Returns a Boolean accordingly
bool checkP2Moves(std::vector<char> supporting)
{
	for (int i = supporting.size() - 1; i >= 0; i--)
	{
		//If the current element is the second element and
		//If it is a toad and
		//If the next element is empty
		//Return true
		if (i == 1 && supporting[i] == 'T' && supporting[i - 1] == ' ')
		{
			return true;
		}
		//If the current element is not any of the first two elements and
		//If it is a toad and
		//If either the next element or the element after is empty
		//Return true
		else if (i > 1 && supporting[i] == 'T' && (supporting[i - 1] == ' ' || supporting[i - 2] == ' '))
		{
			return true;
		}
	}
	return false;
}

//Function for the main game loop
void mainGame(std::vector<char>& gameBoard, std::vector<char>& supporting)
{
	printBoard(gameBoard, supporting);

	while (true)
	{
		//Move 1 - Player
		//Calling the function for Player 1 Move
		player1Move(gameBoard, supporting);

		//Checking if P2 has any valid moves
		if (!checkP2Moves(supporting))
		{
			std::cout << "\n   You Win!\n";
			std::cout << "   P2 (CPU) has no valid moves left. P1 (You) is the winner!";
			break;
		}

		//Move 2 - CPU
		//Calling the function for Player 2 Move
		cpuMove(gameBoard, supporting);

		//Checking if P1 has any valid moves
		if (!checkP1Moves(supporting))
		{
			std::cout << "\n   Game Over!\n";
			std::cout << "   P1 (You) has no valid moves left. P2 (CPU) is the winner!";
			break;
		}
	}

	//Calling finalPrint to print the board without the fog
	if (gameBoard.size() > 3)
	{
		std::cout << "\n\n\n   The full board will be printed below without the fog" << std::endl;
		finalPrint(gameBoard, supporting);
	}
	else
	{
		std::cout << std::endl;
	}

	std::cout << "\n   Thank you for playing Frogs and Toads!" << std::endl;
}

int main()
{
	int boardSize = 0;
	int playerTokens = 0;

	//Calling function startUp to initialise values of boardSize and playerTokens
	startUp(boardSize, playerTokens);

	//Create two blank vector with boardSize element
	//board will contain the tokens
	//supporting is a vector that will support the main board by telling if token is a Frog or a Toad
	std::vector<char> board(boardSize, ' ');
	std::vector<char> supporting(boardSize, ' ');

	//Calling function setUp to allocate positions for both players
	setUp(board, supporting, boardSize, playerTokens);

	//Calling function for main game loop
	mainGame(board, supporting);	

	return 1;
}

