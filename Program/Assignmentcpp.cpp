// Fruit Machine
// Cameron Cottam
// Sumbited on the 2nd Decemember

#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <ctime>
#include <math.h>
#include <ctype.h> 


using namespace std;


bool Value_Type_Check_1 = false;
bool Value_Type_Check_2 = false;  // Verifying the right data type (used in loops for logic & lines)
bool Value_Type_Check_3 = false;


int slot_machine = 1; // The game loop
int balance = 0; // The users balance
int bet = 0; // Users bet
int Deduction = 0; // Deductions from balance, if the user uses slow mode.
int tries = 0; // Balance attempts & used for how many times the game is being played.
int lines = 0; // How many lines the users is wanting to play.
char input; // User Input
int Hold_Num; // For the user to enter an int number in the holding section of the game.
char Temp; // For the position swapping in the holds.
char f = 156; // This is £ symbol


int Lines_payout[5]; // Combines the pay of each lines together and is stored in an array.



void logic(); // The users input data (Balance, Bet, Lines)
void Reels(); // The Rotating Slots                  				
int Money(int& balance); // The Money for the first lines with the Line_2 - 5 being referenced in this function
void Continue(); // Asks the user if they want to continue
int Verify(int& balance); // Checks the users balance to see if it's less than or equal to 0

void Line_2();
void Line_3(); // The different lines. 
void Line_4();
void Line_5();
void Money_Display(); // Displays the amount of money in total the user earned through each of the lines, if they enter which lines to play for.
void Hold(); // Push down one slot while holding two others


char Slot1[3] = { '#','%','!' };
char Slot2[3] = { '#','%','!' }; // Three slots
char Slot3[3] = { '#','%','!' };

char Rotate_1[3] = { '#','%','!' };
char Rotate_2[3] = { '!','#','%' }; // The slots used for rototating. 
char Rotate_3[3] = { '%','!','#' };

bool All_In_Mode = false; // Optional bonus mode


void Header(); // For updating the bets, balance.

HANDLE hconsole;         // handle to console 


int main()
{

	while (slot_machine == 1)
	{
		Header();

		if (tries >= 3)
		{
			// If the game has been going on for 3 or more times, This section executes and asks the user if they would like to take part in the bonus gamemode.
			cout << "Want to try All In Mode?" << endl;
			cout << "Put all you're money on the line with no hold option?" << endl;
			cout << "Enter y to play." << endl;
			cout << "Note: This will reappear as an option later." << endl;
			cin >> input;
			if (input == 'y')
			{
				bet = bet + balance;
				balance = 0;
				lines = 1;
				All_In_Mode = true;
				Reels();
				Money(balance);
				Money_Display();
				Continue();
				Verify(balance);
			}
			else if (input != 'y')
			{
				All_In_Mode = false;
				tries = 0;
			}
		}
		else if (All_In_Mode == false) // If the user does not want to play the All In mode then the game will carry on as normal.
		{
			logic();
			Reels();
			Hold();
			Money(balance);
			Money_Display();
			Continue();
			Verify(balance);
		}
	}

	system("cls");
	cout << "Hope you enjoyed this game by Cameron Cottam" << endl;
	cout << "Game Over" << endl;
	system("pause");
}

// ------------------- Graphics -----------------------

void Header()
{

	system("cls");
	cout << "\t\t\t Fruit Machine " << "                                            Balance:" << f << balance << endl;
	cout << "                                                                                   Bet:" << f << bet << endl;
	cout << "                                                                                   Deductions:" << Deduction << endl;
	cout << "                                                                                   Lines:" << lines << endl;
	cout << " S - Stop  P - Slow" << endl;


	for (int i = 0; i < 3; i++)
	{
		cout << "|" << Slot1[i] << "|" << Slot2[i] << "|" << Slot3[i] << "|" << endl;
	}
}


// ---------------- User Input --------------------
void logic()
{
	// The purpose of tries is to make the user enter there balance once and acts as a game counter
	if (tries == 0)
	{
		cout << "Please enter your balance" << endl;
		while (!Value_Type_Check_1)		// Checks the balance is not a negative number and not a letter
		{
			Value_Type_Check_1 = true;
			while (balance > 100 || balance <= 0)
			{
				cin >> balance;
				cout << "Sorry you're balance must be within 1 - 100 number" << endl;
				if (cin.fail()) // This stops the game from crashing, if the user entered the wrong data type. This is used throughout the program
				{
					Header();
					cin.clear();
					cin.ignore();
					cout << "Sorry you're balance must be within 1 - 100 number." << endl;
					Value_Type_Check_1 = false;
				}
			}
		}
	}

	Header();
	tries++; // Counts how many times the game has been played. This is used to trigger the All In mode when the game has been played three times.

	while (!Value_Type_Check_2) // This stops the game from crashing, if the user entered the wrong data type. This is used throughout the program
	{
		Value_Type_Check_2 = true;
		cout << "How much money would you like to bet with. Max bet is " << f << "10 Min Bet is " << f << "1" << endl;
		cin >> bet;
		if (cin.fail())
		{
			Header();
			cin.clear();
			cin.ignore();
			cout << "Please enter a postive." << endl;
			Value_Type_Check_2 = true;
		}
	}

	while (bet > 10 || bet < 1)
	{
		Header();
		cout << "Please re-enter a bet that is within the range. " << f << "1 to  " << f << "10" << endl;
		cin >> bet;
		if (cin.fail())
		{
			Header();
			cin.clear();
			cin.ignore();
			cout << "Please re-enter a bet that is within the range." << endl;
		}
	}

	Header();

	//If the users bet is greater than the balance  so bet:5 > balance:2. It would ask the user to re-enter their bet.
	if (bet > balance)
	{
		while (bet > balance)
		{
			Header();
			cout << "Sorry you're bet is over you're balance please re-eneter an apportatie bet" << endl;
			cout << "Please re-enter a bet that is within the range. " << f << "1 to " << f << "10" << endl;
			cin >> bet;
			if (cin.fail())
			{
				Header();
				cin.clear();
				cin.ignore();
				cout << "Please enter in the right amount" << endl;
			}
		}
	}

	balance = balance - bet;

	Header();

	//Asks the user to input how many lines they want to play for.
	cout << "How many lines do you want to play for? max is 5!" << endl;

	while (!Value_Type_Check_3)
	{
		Value_Type_Check_3 = true;
		cin >> lines;
		if (cin.fail())
		{
			Header();
			cin.clear();
			cin.ignore();
			cout << "Please enter an int value." << endl;
			Value_Type_Check_3 = false;
		}
	}

	// To make sure the appropriate data is entered.
	if (lines > 5 || lines <= 0)
	{
		while (lines > 5 || lines <= 0)
		{
			cout << "Sorry the max number of lines is 5" << endl;
			cin >> lines;
			if (cin.fail())
			{
				Header();
				cin >> lines;
				cin.clear();
				cin.ignore();
			}
		}
	}

	Header();
	cout << "Once you enter any letter , the game will start" << endl;
	cin >> input;
}



void Reels()
{
	// Index is used as a counter for the rotating. 
	int index = 0;
	// -------------------- Reel1 -------------
	bool reel = true;
	bool Spin_1 = true;
	bool Spin_2 = true;
	bool Spin_3 = true;

	while (Spin_1 == true) // Rototating for Slot1, slot2 and Slot3.
	{
		system("cls");
		cout << "\t\t\t Fruit Machine " << "                                            Balance:" << f << balance << endl;
		cout << "                                                                                   Bet:" << f << bet << endl;
		cout << "                                                                                   Deductions:" << Deduction << endl;
		cout << "                                                                                   Lines:" << lines << endl;
		cout << " S - Stop  P - Slow" << endl;
		index++;

		Slot1[0] = Rotate_1[index % 3]; // The first position in the array is equal to the position in the Rotate_1 array by the modulous of the index counter.
		Slot1[1] = Rotate_2[index % 3]; // This is done for each slot.
		Slot1[2] = Rotate_3[index % 3];


		Slot2[0] = Rotate_1[index % 3];
		Slot2[1] = Rotate_2[index % 3];
		Slot2[2] = Rotate_3[index % 3];

		Slot3[0] = Rotate_1[index % 3];
		Slot3[1] = Rotate_2[index % 3];
		Slot3[2] = Rotate_3[index % 3];

		if (index > 3)
		{
			index = 0;
		}

		for (int i = 0; i < 3; i++) //This for loop is to display all the slots rototating.
		{
			cout << "|" << Slot1[i] << "|" << Slot2[i] << "|" << Slot3[i] << "|" << endl;
		}
		if (_kbhit()) // Checks what keys are being pressed by the user.
		{
			char key = toupper(_getch());
			if (key == 'S')
			{
				Spin_1 = false;
			}
			if (key == 'P')
			{
				Sleep(200); // Slows down the print
				Deduction++; // Counts how many times the slow mode has been used for.
			}
		}
	}
	while (Spin_2 == true) // Rototating for slot2 and Slot3
	{
		system("cls");
		cout << "\t\t\t Fruit Machine " << "                                            Balance:" << f << balance << endl;
		cout << "                                                                                   Bet:" << f << bet << endl;
		cout << "                                                                                   Deductions:" << Deduction << endl;
		cout << "                                                                                   Lines:" << lines << endl;
		cout << " S - Stop  P - Slow" << endl;
		index++;

		Slot2[0] = Rotate_1[index % 3];
		Slot2[1] = Rotate_2[index % 3];
		Slot2[2] = Rotate_3[index % 3];

		Slot3[0] = Rotate_1[index % 3];
		Slot3[1] = Rotate_2[index % 3];
		Slot3[2] = Rotate_3[index % 3];


		if (index > 3)
		{
			index = 0;
		}

		for (int i = 0; i < 3; i++)
		{
			cout << "|" << Slot1[i] << "|" << Slot2[i] << "|" << Slot3[i] << "|" << endl;
		}
		if (_kbhit())
		{
			char key = toupper(_getch());
			if (key == 'S')
			{
				Spin_2 = false;
			}
			if (key == 'P')
			{
				Sleep(200); // Slows down the print
				Deduction++;
			}
		}
	}


	while (Spin_3 == true)
	{

		system("cls");
		cout << "\t\t\t Fruit Machine " << "                                            Balance:" << f << balance << endl;
		cout << "                                                                                   Bet:" << f << bet << endl;
		cout << "                                                                                   Deductions:" << Deduction << endl;
		cout << "                                                                                   Lines:" << lines << endl;
		cout << " S - Stop  P - Slow" << endl;
		index++;

		Slot3[0] = Rotate_1[index % 3];
		Slot3[1] = Rotate_2[index % 3];
		Slot3[2] = Rotate_3[index % 3];

		if (index > 3)
		{
			index = 0;
		}

		for (int i = 0; i < 3; i++)
		{
			cout << "|" << Slot1[i] << "|" << Slot2[i] << "|" << Slot3[i] << "|" << endl;
		}
		if (_kbhit())
		{
			char key = toupper(_getch());
			if (key == 'S')
			{
				Spin_3 = false;
			}
			if (key == 'P') // if the user enters p, it will execute slow mode.
			{
				Sleep(200); // Slows down the print
				Deduction++;
			}
		}
	}
}


void Hold() // This section is optional for the user. If the user wants to push one slot down,
{
	bool check = true;
	cout << "Enter y if you would like to push one slot down." << endl;
	cin >> input;
	if (input == 'y')
	{

		while (check == true)
		{
			Header();
			cout << "What number would you like to hold?" << endl;
			cin >> Hold_Num;
			// This part of the code acts as way to make sure the user enters the right number of which slot, the user wants to push down.
			if (Hold_Num == 1)
			{
				Header();
				check = false;
			}
			else if (Hold_Num == 2)
			{
				Header();
				check = false;
			}
			else if (Hold_Num == 3)
			{
				Header();
				check = false;
			}
		}
		if (Hold_Num == 1)
		{
			// If the user wants to push a slot down, I use a variable to temporarily  hold the position of Slot[1] then assign the Temp to the Slot1[2]
			Temp = Slot1[1];
			Slot1[1] = { Slot1[0] };
			Slot1[0] = { Slot1[2] };
			Slot1[2] = { Temp };
		}
		else if (Hold_Num == 2)
		{
			Temp = Slot2[1];
			Slot2[1] = { Slot2[0] };
			Slot2[0] = { Slot2[2] };
			Slot2[2] = { Temp };
		}
		else if (Hold_Num == 3)
		{
			Temp = Slot3[1];
			Slot3[1] = { Slot3[0] };
			Slot3[0] = { Slot3[2] };
			Slot3[2] = { Temp };

		}
	}
}

// Win checking
int Money(int& balance)
{
	system("cls");
	if (lines >= 1 && All_In_Mode == false)
	{


		if (Slot1[1] == Slot2[1] && Slot1[1] == Slot3[1]) // If the positions in each array are the same then the user wins money.
		{
			Lines_payout[0] = bet + 5;
			balance = balance + bet;

			if (Deduction > 0)
			{
				cout << "Since you used the slow mode, you're balance is deducted by 1 per click" << endl;
				balance = balance - (Deduction + 5);
			}
		}
		else if (Slot1[1] == Slot2[1]) // If two positions in the array are the same then the user will still gain money.    
		{
			Lines_payout[0] = bet + 3;
			balance = balance + bet;

			if (Deduction > 0)
			{
				cout << "Since you used the slow mode, you're balance is deducted by 1 per click" << endl;
				balance = balance - (Deduction + 5);
			}

		}
		else
		{
			if (Deduction > 0)
			{
				cout << "Since you used the slow mode, you're balance is deducted by 1 per click" << endl;
				balance = balance - (Deduction + 5);
			}

		}
	}
	else if (lines >= 1 && All_In_Mode == true)
	{
		if (Slot1[1] == Slot2[1] && Slot1[1] == Slot3[1])
		{

			Lines_payout[0] = bet + bet;
			balance = balance + bet;

			if (Deduction > 0)
			{
				cout << "Since you used the slow mode, you're balance is deducted by 1 per click" << endl;
				balance = balance - (Deduction + 10);
			}
		}
	}
	// If the entered a value between 2 - 5 it will check the lines and  run the functions.

	if (lines == 2)
	{
		Line_2();
	}
	else if (lines == 3)
	{
		Line_2();
		Line_3();
	}
	else if (lines == 4)
	{
		Line_2();
		Line_3();
		Line_4();
	}
	else if (lines == 5)
	{
		Line_2();
		Line_3();
		Line_4();
		Line_5();
	}
	return balance;
}

// Lines 392 - 441 are the different lines in the Fruit Machine. Ie Line 2 is the top line, line 3 is the bottom line etc.
void Line_2()
{
	if (Slot1[0] == Slot2[1] && Slot1[0] == Slot3[2])
	{
		Lines_payout[1] = bet + 8;
		balance = balance + bet;

	}
	else if (Slot1[0] == Slot2[1])
	{
		Lines_payout[1] = bet + 4;
		balance = balance + bet;

	}
}

void Line_3()
{
	if (Slot1[1] == Slot2[2] && Slot1[1] == Slot3[1])
	{
		Lines_payout[2] = bet + 10;
		balance = balance + bet;

	}
	else if (Slot1[1] == Slot2[2])
	{
		Lines_payout[2] = bet + 5;
		balance = balance + bet;

	}
}

void Line_4()
{
	if (Slot1[0] == Slot2[1] && Slot1[0] == Slot3[0])
	{
		Lines_payout[3] = bet + 14;
		balance = balance + bet;

	}
	else if (Slot1[0] == Slot2[1])
	{
		Lines_payout[3] = bet + 7;
		balance = balance + bet;

	}
}


void Line_5()
{
	if (Slot1[2] == Slot2[1] && Slot1[2] == Slot3[0])
	{
		Lines_payout[4] = bet + 20;
		balance = balance + bet;

	}
	else if (Slot1[2] == Slot2[1])
	{
		Lines_payout[4] = bet + 5;
		balance = balance + bet;

	}
}

//Basically prints out the total winnings depending on how many lines have been entered.
void Money_Display()
{
	Header();
	cout << "This is you're prize money in total: " << endl;
	int Numbers[5] = { 1, 2, 3, 4, 5 }; // To show the number of lines.
	for (int i = 0; i < lines; i++)
	{
		cout << "line " << Numbers[i] << ":" << f << Lines_payout[i] << endl;
		balance = balance + Lines_payout[i];
	}
	if (Deduction > 0)
	{
		cout << "But you lost " << f << Deduction << endl;
	}
}

// Asks the user if they want to continue playing the game.
void Continue()
{
	cout << "if you like to continue enter y, otherwise the game will end." << endl;
	cin >> input;

	if (input == 'y')
	{
		//It also resets the bet and deduction values. Allowing the user to re-enter there bet.
		for (int i = 0; i < lines; i++)
		{
			Lines_payout[i] = 0;
		}
		bet = 0;
		Deduction = 0;
		lines = 0;
	}
	else
	{
		slot_machine = 0;
	}

}

// Just to Verify that when the use does want to continue playing it will check there balance to be valid.
int Verify(int& balance)
{
	if (balance <= 0)
	{
		slot_machine = 0;
	}
	return 0;
}
