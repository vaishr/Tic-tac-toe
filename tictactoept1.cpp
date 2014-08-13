#include <iostream>

using namespace std;

void displayboard(char board[][3]);
int checkforwinplayer1(char board[][3], const char play1);
int checkforwinplayer2(char board[][3], const char play2);
void inputcheckandmove(int row, int column, char board[][3], char player);

int main() 

{

	int row, column;
	char board[3][3];
	const char play1= 'X', play2= 'O';
	char player;
	int movecount=0;
	int i,j;

	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
			board[i][j]=' ';


	displayboard(board);

	cout << "Player 1: Please enter a row and column number and press Enter" << endl;
	cin >> row >> column; 
	cin.sync();
	cin.clear();

	player= play1;
	inputcheckandmove(row, column, board, player);// marks move after checking that it's valid and available

	system("CLS");
	displayboard(board);
	++movecount;

	while (movecount < 9)// repeats loop as long as there is no tie

	{

		cout << "Player 2: Please enter a row and column number and press Enter." << endl;
		cin >> row >> column;
		cin.sync();
		cin.clear();

		player=play2;
		inputcheckandmove(row, column, board, player);

		system("CLS");
		displayboard(board);
		++movecount;
		

		if (checkforwinplayer2(board, play2)==1)// ends loop if player 2 wins
		{
			cout << "Congratulations Player 2!  You won the game!";
			break;
		}

			cout << "Player 1: Please enter a row and column number and press Enter" << endl;
			cin >> row >> column; 
			cin.sync();
			cin.clear();

			player= play1;
			inputcheckandmove(row, column, board, player);// marks move after checking that it's valid and available

			system("CLS");
			displayboard(board);
			++movecount;

			if (checkforwinplayer1(board, play1)==1)// ends loop if player 1 wins
			{
				cout << "Congratulations Player 1!  You won the game!";
				break;
			}

	}


	if (!((checkforwinplayer1(board, play1)==1 || checkforwinplayer2(board, play2)==1)))
		cout << "Game Over. It's a tie!"; 


	cin.get();
	return 0;
}


void displayboard(char board [][3])

{
	cout << "Tic Tac Toe game" << endl << endl;
	cout << "  1   2    3" << endl; 
	cout << "1 " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " " << endl;
	cout << "____|___|____" <<endl;
	cout << "2 " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " " << endl;
	cout << "____|___|____" <<endl;
	cout << "3 " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " " << endl;
	cout << "    |   | " <<endl << endl;
}

int checkforwinplayer1(char board[][3], const char play1)
{

	if (board[0][0]== play1 && board[1][0]== play1 && board[2][0]== play1) //win by column:
		return 1;
	if 
		(board[0][1]== play1 && board[1][1]== play1 && board[2][1]== play1)
		return 1;
	if
		(board[0][2]== play1 && board[1][2]== play1 && board[2][2]== play1)
		return 1;
	if
		(board[0][0]== play1 && board[0][1]== play1 && board[0][2]== play1)//win by row:
		return 1;
	if
		(board[1][0]== play1 && board[1][1]== play1 && board[1][2]== play1)
		return 1;
	if
		(board[2][0]== play1 && board[2][1]== play1 && board[2][2]== play1)
		return 1;
	if
		(board[0][0]== play1 && board[1][1]== play1 && board[2][2]== play1)//win by diagonal:
		return 1;
	if
		(board[2][0]== play1 && board[1][1]== play1 && board[0][2]== play1)
		return 1;
	else 
		return -1;
}

int checkforwinplayer2 (char board[][3], const char play2)
{

	if ((board[0][0] == play2 && board[1][0] == play2 && board[2][0] == play2) || 
		(board[0][1]== play2 && board[1][1]== play2 && board[2][1]== play2) ||
		(board[0][2]== play2 && board[1][2]== play2 && board[2][2]== play2) ||
		(board[0][0]== play2 && board[0][1]== play2 && board[0][2]== play2) ||
		(board[1][0]== play2 && board[1][1]== play2 && board[1][2]== play2) ||
		(board[2][0]== play2 && board[2][1]== play2 && board[2][2]== play2) ||
		(board[0][0]== play2 && board[1][1]== play2 && board[2][2]== play2) ||
		(board[2][0]== play2 && board[1][1]== play2 && board[0][2]== play2))
		return 1;

	else 
		return -1;	 
}

void inputcheckandmove(int row, int column, char board[][3], char player)
{
	while (!((row >= 1 && row <=3) && (column >= 1 && column <=3)))// to check if row and column number between 1-3
	{
		cout << "The row and/or column number you've entered is invalid.  Please enter a valid row and column number.\n" ;
		cin >> row >> column;
		cin.sync();
		cin.clear();
	}

	while (!(board[row-1][column-1]==' '))// to check if space isn't already filled
	{
		cout << "The space you've chosen is already filled. Please enter another row and column number." << endl;
		cin >> row >> column;
		cin.sync();
		cin.clear();
		while (!((row >= 1 && row <=3) && (column >= 1 && column <=3)))
		{
			cout << "The row and/or column number you've entered is invalid.  Please enter a valid row and column number.\n" ;
			cin >> row >> column;
			cin.sync();
			cin.clear();
		}
	}
	board[row-1][column-1]=player; // if input is okay, marks X or O on board
}