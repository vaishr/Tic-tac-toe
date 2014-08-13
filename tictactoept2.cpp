#include <iostream>
#include <fstream>

using namespace std;

int row, column, size, neworsaved, numberofplayers, winseqcount, playorsave;
char **board;
int checkgamesettings (int size, int winseqcount, int numberofplayers);
void displayboard(int size, char **board);
int checkforwinner(int winseqcount, char **board, int size, const char player [26], int m);
void markmove (int row, int column, char **board, int size);
int movecount;
int m; // keeps track of which player's turn it is
const char player[26]= {'X', 'O', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'Y', 'Z'}; 


int main()
{
	cout << "Welcome!  Press 1 to start a New Game or 2 to resume a Saved Game" << endl;
	cin.sync();
	cin.clear();
	cin >> neworsaved;
	if (neworsaved==2)
	{
		ifstream in ("gamestate.txt");
		in >> numberofplayers >> m >> winseqcount >> size >> movecount;
		board= new char *[size];
		for (int i=0; i<size; ++i)
			board[i]= new char [size];
		for (int i=0; i < size; i++)
		{
			for (int j = 0; j < size; j++) 
			{
				in>>board[i][j];
			}
		}
		in.close();
		displayboard(size, board);

	}

	if (neworsaved==1)
	{
		{
			cout << "How many players for this game?  Enter a number from 2-26" << endl;
			while(cin.fail() || numberofplayers > 26 || numberofplayers < 2)
			{
				cin.sync();
				cin.clear();
				cin >> numberofplayers;
				if (numberofplayers >= 2 && numberofplayers <= 26)
					break;
				cout << "Your entry is invalid.  Please enter a number from 2-26 for number of players" << endl;
			}

			cout << endl << "What size board do you want for this game?  Enter a number n to create a board of size (n x n)" << endl;
			while (cin.fail() || size < 3)
			{
				cin.sync();
				cin.clear();
				cin >> size;
				if (size >= 3)
					break;
				cout << "Your entry is invalid.  Please enter an integer n that is > or = to 3 to create a board of size n x n" << endl;
			}

			cout << endl << "What do you want the win sequence count to be for this game?" << endl;
			while (cin.fail() || winseqcount < 3)
			{
				cin.sync();
				cin.clear();
				cin >> winseqcount;
				if (winseqcount >= 3)
					break;
				cout << "Your entry is invalid.  Please enter an integer greater than or equal to 3 for the win sequence count";
			}
		}

		while (checkgamesettings (size, winseqcount, numberofplayers)==2)// repeats if combination of winseq, #ofplayers and board size is invalid
		{
			cout << "How many players for this game?  Enter a number from 2-26" << endl;
			while(!(cin>>numberofplayers) || numberofplayers > 26 || numberofplayers < 2)
			{
				cin.sync();
				cin.clear();
				if (numberofplayers >= 2 && numberofplayers <= 26)
					break;
				cout << "Your entry is invalid.  Please enter a number from 2-26 for number of players" << endl;
			}

			cout << endl << "What size board do you want for this game?  Enter a number n to create a board of size (n x n)" << endl;
			cin >> size;
			while (cin.fail()|| size < 3)
			{
				cin.sync();
				cin.clear();
				if (size >= 3)
					continue;
				cout << "Your entry is invalid.  Please enter an integer n that is > or = to 3 to create a board of size n x n" << endl;
			}

			cout << endl << "What do you want the win sequence count to be for this game?" << endl;
			while (!(cin >> winseqcount) || winseqcount < 3)
			{
				cin.sync();
				cin.clear();
				if (winseqcount >= 3)
					break;
				cout << "Your entry is invalid.  Please enter an integer greater than or equal to 3 for the win sequence count";
			}
		}

		if (checkgamesettings(size, winseqcount, numberofplayers)==1)
		{

			board= new char *[size];

			for (int i=0; i<size; ++i)
				board[i]= new char [size];
			for (int i=0; i < size; i++)
			{
				for (int j = 0; j < size; j++) 
				{
					board[i][j]= '_';
				}
				cout << endl;
			}

			displayboard(size, board);

		}

	}
	while (movecount <= (size*size))
	{

		cout << "Player " << m+1 << "Do you want to keep playing or save and exit?  Press 1 to play or 2 to save" << endl;
		while (!(cin>>playorsave) || ( playorsave != 1 && playorsave != 2) )// checks if input is valid
		{
			cin.sync();
			cin.clear();
			cout << "Your entry is invalid.  Please press 1 to keep playing or 2 to save and exit." << endl;

		}

		if (playorsave==1)// if user wants to keep playing
		{
			cout << endl<< "Player "<< m+1 << ", enter a row and column number" << endl;
			while (!(cin >> row >> column) || row > size || column > size || board[row-1][column-1] != '_')
			{
				cin.sync();
				cin.clear();
				if (row <= size && column <= size && board[row-1][column-1]== '_')
					break;//
				cout << "The row or column number you've entered is invalid OR the space you've entered is already taken.  Please enter another row and column number" << endl;
			}

			++ movecount;
			board[row-1][column-1]= player[m]; 
			displayboard(size, board);	
			cout << endl;
			if (checkforwinner(winseqcount, board, size, player, m) >= 0)
			{
				cout << "Congratulations Player " << m+1 << ", you won!" << endl;
				break;
			}

			if (movecount==(size*size))
			{
				cout << "Game Over.  It's a tie! "<< endl;  
			}

		}
		if (playorsave== 2) // if user opts to save and exit
		{
			ofstream out ("gamestate.txt");
			out << numberofplayers <<" "<< m << " "<<  winseqcount << " " << size << " " << movecount <<  " ";
			for (int i = 0; i< size ; i++)
				for (int j = 0; j< size; j++)
					out<<board[i][j]<<" ";
			out.close();
			break;
		}
		
		m++;
		if (m> numberofplayers-1)
			m=0;								// resets m for next turn
	}
	
	for (int i=0; i< size; i++)
					delete board[i];
						delete []board;			// deletes allocated memory

}


int checkgamesettings(int size, int winseqcount, int numberofplayers)
{
	if ((size*size) >= (numberofplayers *(winseqcount-1) + 1))
		return 1;
	else 
	{
		cout << "The combination of number of players, board size, and win sequence count you've entered is invalid." << endl << endl;
		return 2;
	}
}

void displayboard(int size, char **board)
{   
	cout << "Tic Tac Toe game" << endl << endl;
	for (int i=0; i < size; i++)
	{ 
		if (i==0)
			cout << "  ";
		cout  << i+1 << "   ";// for displaying column numbers
	}

	cout << endl;
	for (int i=0; i < size; i++)
	{
		cout << i + 1 << " ";
		// For showing row numbers
		for (int j = 0; j < size; j++) 
		{

			cout << board[i][j] ;
			if (j != size - 1) 
			{
				cout << " | ";
			}
		}
		cout << endl;

		if (i != size - 1) 
		{
			cout << "  ";
			for (int h=0; h < size; h++) 
			{
				if (h != size - 1) {
					cout << "____";
				} else
				{
					cout << "__";
				}
			}
			cout << endl;
		}

	}
}		

int checkforwinner(int winseqcount, char **board, int size, const char player[26], int m)
{                                                          
    int ro = 0, col = 0, i = 0;
    char currentChar = player[m];

    for (ro = 0; ro < size; ro++) // checks every row
    {
        for ( col = 0; col < (size-(winseqcount-1)); col++) // checks every column
        {
            while (board[ro][col] == currentChar) // checks consecutive symbols of current player for each row
            {
                col++;
                i++; // adds 1 for each consecutive symbol found for current player
                if (i == winseqcount)
                {
                    return m; // returns index of player[26] associated with current player in case of win by row
                }
            }
            i = 0;
        }
    }

    for ( col = 0; col < size; col++)                       // checks columns for consecutive symbols
    {
        for ( ro = 0; ro < (size-(winseqcount-1)); ro++)
        {
            while (board[ro][col] == currentChar)
            {
                ro++;
                i++;
                if (i == winseqcount)
                {
                    return m;
                }
            }
            i = 0;
        }
    }

    for ( col = 0; col < (size - (winseqcount-1)); col++)             // checks for forwards diagonals
    {
        for ( ro = 0; ro < (size-(winseqcount-1)); ro++)
        {
            while (board[ro][col] == currentChar)
            {
                ro++;
                col++;
                i++;
                if (i == winseqcount)
                {
                    return m;
                }
            }
            i = 0;
        }
    }
    for ( col = size-1; col > 0+(winseqcount-2); col--)           // checks for backwards diagonals
    {                                                   
        for ( ro = 0; ro < (size-(winseqcount-1)); ro++)       
        {
            while (board[ro][col] == currentChar)  
            {
                ro++;                                  
                col--;                                  
                i++;                                   
                if (i == winseqcount)                             
                {
                    return m;                      
                }                                
            }                                           
            i = 0;                                      
        }                                               
    }

    return -1;                                           
}   

