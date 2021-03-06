// SevenSeg Cipher.cpp
// Solution to r/DailyProgrammer challenge #358 by Tony Delgado

#include <iostream>;
#include <string>;
using namespace std;

void interpret(string inOne, string inTwo, string inThree);

int main()
{
	//9x9 arrays
	//Read three lines, 27 char long each
	//Top read: check char 2, 5, 8, 11, 14, 17, 20, 23, 26.  If no "_", 1 or 4
	//Mid read: Check 1 & 3, 4 & 6, etc.
	string lineOne =	"    _  _     _  _  _  _  _ ";
	string lineTwo =	"  | _| _||_||_ |_   ||_||_|";
	string lineThree =	"  ||_  _|  | _||_|  ||_| _|";
	string lineFour =	"    _  _  _  _  _  _  _  _ ";
	string lineFive =	"|_| _| _||_|| ||_ |_| _||_ ";
	string lineSix =	"  | _| _||_||_| _||_||_  _|";
	string lineSeven =	" _  _  _  _  _  _  _  _  _ ";
	string lineEight =	"|_  _||_ |_| _|  ||_ | ||_|";
	string lineNine =	" _||_ |_||_| _|  ||_||_||_|";
	string lineTen =	" _  _        _  _  _  _  _ ";
	string lineEleven = "|_||_ |_|  || ||_ |_ |_| _|";
	string lineTwelve = " _| _|  |  ||_| _| _| _||_ ";
	interpret(lineOne, lineTwo, lineThree);
	interpret(lineFour, lineFive, lineSix);
	interpret(lineSeven, lineEight, lineNine);
	interpret(lineTen, lineEleven, lineTwelve);
	system("pause");
    return 0;
}

void interpret(string inOne, string inTwo, string inThree)
{
	bool cipher[10][9];
	int pos;
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 9; y++)
			cipher[x][y] = 0;
	}
	for (int x = 0; x < inOne.size(); x++)
	{	
		//if x+2 divisible by 3, check
		if( ((x+2)%3)  == 0 )
		{
			pos = (((x + 2) / 3)-1);
			if (inOne[x] == '_')
			{
				cipher[1][pos] = 1;
				cipher[4][pos] = 1;
			}
			else
			{
				cipher[0][pos] = 1;
				cipher[2][pos] = 1;
				cipher[3][pos] = 1;
				cipher[5][pos] = 1;
				cipher[6][pos] = 1;
				cipher[7][pos] = 1;
				cipher[8][pos] = 1;
				cipher[9][pos] = 1;
			}
		}
	}
	for (int x = 0; x < inTwo.size(); x++)
	{
		if ((x % 3) == 0)
		{
			pos = (x / 3);
			if (inTwo[x] == '|')
			{
				cipher[1][pos] = 1;  //If 1 or 4, then it's 4
				if (cipher[4][pos]== 1) //Goes from (0,2,3,5,6,7,8,9) to (0,5,6,8,9)
				{
					cipher[2][pos] = 1;
					cipher[3][pos] = 1;
					cipher[7][pos] = 1;
				}
			}
			else
			{
				cipher[4][pos] = 1; //If 1 or 4, then it's 1
				if (cipher[1][pos] == 1) //Goes from (0,2,3,5,6,7,8,9) to (2,3,7,)
				{
					cipher[0][pos] = 1;
					cipher[5][pos] = 1;
					cipher[6][pos] = 1;
					cipher[8][pos] = 1;
					cipher[9][pos] = 1;
				}
			}
		}
		if (((x-1) % 3) == 0)
		{
			pos = ((x - 1) / 3);
			if(cipher[1][pos] == 1 && cipher[4][pos] == 1) //Skip if it's 1 or 4, already decided
			if (inTwo[x] == '_')
			{				//Set becomes (5,6,8,9) or (2,3)
				cipher[0][pos] = 1;
				cipher[7][pos] = 1;
			}
			else
			{				//Becomes 0 or 7
				if (cipher[0][pos] == 0)
				{
					cipher[5][pos] = 1;
					cipher[6][pos] = 1;
					cipher[8][pos] = 1;
					cipher[9][pos] = 1;
				}
				else
				{
					cipher[2][pos] = 1;
					cipher[3][pos] = 1;
				}
			}
		}
		if (((x - 2) % 3) == 0)
		{
			pos = ((x - 2) / 3);
			if (inTwo[x] == '|')
			{			//Set becomes (8,9) or remains (2,3)
				cipher[5][pos] = 1;
				cipher[6][pos] = 1;
			}
			else
			{			//Set becomes (5,6)
				cipher[8][pos] = 1;
				cipher[9][pos] = 1;
			}
		}
	}
	for (int x = 0; x < inThree.size(); x++)
	{
		if ((x % 3) == 0)
		{
			pos = (x / 3);
			if (inThree[x] == '|')
			{	//Becomes 8, 2 or 6
				if (cipher[8][pos] == 0)
					cipher[9][pos] = 1;
				else if (cipher[2][pos] == 0)
					cipher[3][pos] = 1;
				else
					cipher[5][pos] = 1;
			}
			else
			{	//Becomes 9, 3 or 5
				if (cipher[8][pos] == 0)
					cipher[8][pos] = 1;
				else if (cipher[2][pos] == 0)
					cipher[2][pos] = 1;
				else
					cipher[6][pos] = 1;
			}
		}
	}
	//[num][pos]
	for (int x = 0; x < 9; x++)
	{
		
		for (int y = 0; y < 10; y++)
		{
			switch (y)
			{
				case 0: 
					if (cipher[y][x] == 0)
						cout << 0;
					break;
				case 1:
					if (cipher[y][x] == 0)
						cout << 1;
					break;
				case 2:
					if (cipher[y][x] == 0)
						cout << 2;
					break;
				case 3:
					if (cipher[y][x] == 0)
						cout << 3;
					break;
				case 4:
					if (cipher[y][x] == 0)
						cout << 4;
					break;
				case 5:
					if (cipher[y][x] == 0)
						cout << 5;
					break;
				case 6:
					if (cipher[y][x] == 0)
						cout << 6;
					break;
				case 7:
					if (cipher[y][x] == 0)
						cout << 7;
					break;
				case 8:
					if (cipher[y][x] == 0)
						cout << 8;
					break;
				case 9:
					if (cipher[y][x] == 0)
						cout << 9;
					break;
			}
			
		}
	}
	cout << endl << endl;
}
