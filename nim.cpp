#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
//#include<sstream>
#include<cstdlib>


using namespace std;

struct state{
	int A;
	int B;
	int C;
	bool safe;

	bool operator==(const state & state1) const
	{
		return state1.A == A && state1.B == B && state1.C == C;
	}
};





state initChips(int &A, int &B, int &C);

string intToString(int number);
int stoi(string s);
void afterMove(state curr);
void makeMove(state curr, state goal);
vector<state> playGame(vector<state> unsafe, state initState, string & computerWin);
void printState(state s);
vector<state> readFile(fstream & inOut);
state machineMove(vector<state> unsafe, state curr);
void addAndSort(fstream & inOut, vector<state> unsafe, vector<state> gameStates);


int main()
{

	int A = 0;
	int B = 0;
	int C = 0;
	
	fstream inOut("unsafe", ios::in | ios::out);
	
	state initState = initChips(A, B, C);

	vector<state> unsafe = readFile(inOut);

	inOut.seekg(0);


	string computerWin;
	vector<state> gameStates = playGame(unsafe, initState, computerWin);
	

	if(computerWin.compare("false") == 0)
	{	
		cout << "Wow! You're pretty good at this game :-)" << endl;
		addAndSort(inOut,unsafe, gameStates);

	//	inOut.clear();
	//	inOut.seekg(0);

		
	}
	else
		cout << "Good game! I was just too smart for you :-)" << endl;

//	addAndSort(inOut,unsafe, gameStates);

	inOut.clear();
	inOut.seekg(0);

	return 0;
}

bool compareState(const state & a, const state & b)
{
	if(a.A < b.A)
		return true;
	if(a.A > b.A)
		return false;
	//a.A and b.A are equal
	
	if(a.B < b.B)
		return true;
	if(a.B > b.B)
		return false;
	//a.B and b.B are equal
	
	if(a.C < b.C)
		return true;
	
	return false;
}

string intToString(int number)
{
	if (number == 0)
		return "0";

	string temp = "";
	string toreturn = "";


	while (number>0)
	{
		temp += (number%10) + 48;
		number/=10;
	}

	for (int i=0;i<temp.length();i++)
	{	
		toreturn += temp[temp.length()-i-1];
	}
	
	return toreturn;
}



//called only if computer loses
void addAndSort(fstream & inOut, vector<state> unsafe, vector<state> gameStates)
{
	//adds any new unsafe states to the original unsafe
	for(int i = 0; i < gameStates.size(); i++)
	{
		if(!count(unsafe.begin(), unsafe.end(), gameStates[i]))
			unsafe.push_back(gameStates[i]);
	}

	//sorts the unsafe states
	
	sort(unsafe.begin(), unsafe.end(), compareState);

	// replace the inOut with the updated unsafe

	inOut.clear();
	inOut.seekg(0);


	for(int i = 0; i < unsafe.size(); i++)
	{
		int tempA = unsafe[i].A;
		int tempB = unsafe[i].B;
		int tempC = unsafe[i].C;

		string Astring = intToString(tempA);
		string Bstring = intToString(tempB);
		string Cstring = intToString(tempC);

		string tot = Astring + " " + Bstring + " " + Cstring;

		inOut << tot << endl;;
	}

	

}


//returns the state of the board after the machine moves
state machineMove(vector<state> unsafe, state curr)
{
	vector<state> moves; // all possible moves that can be made
	vector<state> safeMoves; //if move is not in the unsafe file, put it here

	state temp;
	temp.A = curr.A;
	temp.B = curr.B;
	temp.C = curr.C;

	if(curr.A - 1 >= 0)
	{
		temp.A = curr.A - 1;

		moves.push_back(temp);

		if(!count(unsafe.begin(), unsafe.end(), temp)) //if don't find this possible state in unsafe moves, then add it to safe moves
			safeMoves.push_back(temp);
	}
	
	if(curr.A - 2 >= 0)
	{
		temp.A = curr.A - 2;

		moves.push_back(temp);
		if(!count(unsafe.begin(), unsafe.end(), temp)) //if don't find this possible state in unsafe moves, then add it to safe moves
			safeMoves.push_back(temp);
	}

	if(curr.A - 3 >= 0)
	{
		temp.A = curr.A - 3;

		moves.push_back(temp);
		if(!count(unsafe.begin(), unsafe.end(), temp)) //if don't find this possible state in 
			safeMoves.push_back(temp);
	}

	temp.A = curr.A;

	if(curr.B - 1 >= 0)
	{
		temp.B = curr.B - 1;

		moves.push_back(temp);
		if(!count(unsafe.begin(), unsafe.end(), temp)) //if don't find this possible state in 
			safeMoves.push_back(temp);
	}
	if(curr.B - 2 >= 0)
	{
		temp.B = curr.B - 2;

		moves.push_back(temp);
		if(!count(unsafe.begin(), unsafe.end(), temp)) //if don't find this possible state in 
			safeMoves.push_back(temp);
	}

	if(curr.B - 3 >= 0)
	{
		temp.B = curr.B - 3;

		moves.push_back(temp);
		if(!count(unsafe.begin(), unsafe.end(), temp)) //if don't find this possible state in 
			safeMoves.push_back(temp);
	}
	temp.B = curr.B;

	if(curr.C - 1 >= 0)
	{
		temp.C = curr.C - 1;

		moves.push_back(temp);
		if(!count(unsafe.begin(), unsafe.end(), temp)) //if don't find this possible state in 
			safeMoves.push_back(temp);
	}

	if(curr.C - 2 >= 0)
	{
		temp.C = curr.C - 2;

		moves.push_back(temp);
		if(!count(unsafe.begin(), unsafe.end(), temp)) //if don't find this possible state in 
			safeMoves.push_back(temp);
	}

	if(curr.C - 3 >= 0)
	{
		temp.C = curr.C - 3;

		moves.push_back(temp);
		if(!count(unsafe.begin(), unsafe.end(), temp)) //if don't find this possible state in 
			safeMoves.push_back(temp);
	}

	temp.C = curr.C;

	if(!safeMoves.empty())
	{
	//	int random = (rand() % safeMoves.size());

		
		safeMoves[0].safe = true;
		makeMove(curr, safeMoves[0]);
		return safeMoves[0];
	}
	else
	{


		moves[0].safe = false;
		makeMove(curr, moves[0]);
		return moves[0];
	}

}

void makeMove(state curr, state goal)
{
	cout << endl;

	if(curr.A != goal.A)
	{
		int diff = curr.A - goal.A;

		cout << "The machine takes "<< diff << " chip(s) from pile A" << endl;
	}

	if(curr.B != goal.B)
	{
		int diff = curr.B - goal.B;

		cout << "The machine takes "<< diff << " chip(s) from pile B" << endl;
	}

	
	if(curr.C != goal.C)
	{
		int diff = curr.C - goal.C;

		cout << "The machine takes " << diff << " chip(s) from pile C" << endl;
	}

	cout << endl;

}



// Surprise! Please enjoy this cat
//              __..--''``---....___   _..._    __
//    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
//   ///_.-' _..--.'_    \                    `( ) ) // //
//   / (_..-' // (< _     ;_..__               ; `' / ///
//    / // // //  `-._,_)' // / ``--...____..-' /// / //


vector<state> playGame(vector<state> unsafe, state initState, string & computerWin)
{
	vector<state> gameStates; //states of the board AFTER the machine moves

	int choice = 0;

	while(true)
	{

		cout << endl;
		cout << " Type 0 if you want the MACHINE to start. Type 1 if YOU want to start: ";

		cin >> choice;

		if(choice == 0 || choice == 1)
			break;
		else
		{
			cout << "Invalid number entered. Please try again." << endl;
		}

	}

//	bool computerWin;
	state curr;
	state next;


	curr.A = initState.A;
	curr.B = initState.B;
	curr.C = initState.C;

	if(choice == 0)
	{
		while(true)
		{
			next = machineMove(unsafe, curr);

			printState(next);

			if(count(unsafe.begin(), unsafe.end(), next)) //if don't find this possible state in 
			{

				state temp;

				temp.A = curr.A;
				temp.B = curr.B;
				temp.C = curr.C;

			
				temp.A = curr.A + 1;
				gameStates.push_back(temp);

				temp.A = curr.A + 2;
				gameStates.push_back(temp);

				temp.A = curr.A + 3;
				gameStates.push_back(temp);

				temp.A = curr.A;//resets value of the pile A of temp


				temp.B = curr.B + 1;
				gameStates.push_back(temp);
		
				temp.B = curr.B + 2;
				gameStates.push_back(temp);

				temp.B = curr.B + 3;
				gameStates.push_back(temp);

				temp.B = curr.B; // resets value of pile B of temp
		
	
				temp.C = curr.C + 1;
				gameStates.push_back(temp);

				temp.C = curr.C + 2;
				gameStates.push_back(temp);

				temp.C = curr.C + 3;
				gameStates.push_back(temp);

			}
//			makeMove(curr, next);
	
			curr.A = next.A;
			curr.B = next.B;
			curr.C = next.C;

			gameStates.push_back(curr);

			afterMove(curr);

			if(curr.A == 0 && curr.B == 0 && curr.C == 0)
			{
				computerWin = "false";
				break;
			}
			//human move


			while(true)
			{
				char pile;
				int num;


				cout << "Enter the pile letter (A, B, C) and the number of chips to remove: ";

				cin >> pile;
				cin >> num;

				if(pile != 'A' && pile != 'B' && pile != 'C')
					cout << "Invalid pile. Please choose A, B, or C";
				else if(num > 3 || num <= 0)
					cout << "You can't take that many chips! Please select a number between 1 and 3" << endl;
				else
				{
					if(pile == 'A')
					{
						if((curr.A - num) < 0)
							cout << "You tried to remove too many chips! Try again." << endl << endl;
						else
						{
							curr.A = curr.A - num;
							break;
						}
					}
					if(pile == 'B')
					{
						if((curr.B - num) < 0)
							cout << "You tried to remove too many chips! Try again." << endl << endl;
						else
						{
							curr.B = curr.B - num;
							break;
						}
					}
					if(pile == 'C')
					{
						if((curr.C - num) < 0)
							cout << "You tried to remove too many chips! Try again." << endl << endl;
						else
						{
							curr.C = curr.C - num;
							break;
						}
					}

				}
				
			}

			afterMove(curr);

			if(curr.A == 0 && curr.B == 0 && curr.C == 0)
			{
				computerWin = "true";
				break;
			}
		}
	}
	else
	{
		while(true)
		{
			//human move
			while(true)
			{
				char pile;
				int num;


				cout << "Enter the pile letter (A, B, C) and the number of chips to remove: ";

				cin >> pile;
				cin >> num;

				if(pile != 'A' && pile != 'B' && pile != 'C')
					cout << "Invalid pile. Please choose A, B, or C";
				else if(num > 3 || num <= 0)
					cout << "You can't take that many chips! Plaese select a number between 1 and 3";
				else
				{
					if(pile == 'A')
					{
						if((curr.A - num) < 0)
							cout << "You tried to remove too many chips! Try again.";
						else
						{
							curr.A = curr.A - num;
							break;
						}
					}
					if(pile == 'B')
					{
						if((curr.B - num) < 0)
							cout << "You tried to remove too many chips! Try again.";
						else
						{
							curr.B = curr.B - num;
							break;
						}
					}
					if(pile == 'C')
					{
						if((curr.C - num) < 0)
							cout << "You tried to remove too many chips! Try again.";
						else
						{
							curr.C = curr.C - num;
							break;
						}
					}

				}
				
			}

			afterMove(curr);

			if(curr.A == 0 && curr.B == 0 && curr.C == 0)
			{
				computerWin = "true";
				break;
			}

			next = machineMove(unsafe, curr);
			
			if(count(unsafe.begin(), unsafe.end(), next)) //if don't find this possible state in 
			{

				state temp = curr;

				temp.A = curr.A;
				temp.B = curr.B;
				temp.C = curr.C;

			
				temp.A = curr.A + 1;
				gameStates.push_back(temp);
			

				temp.A = curr.A + 2;
				gameStates.push_back(temp);

				temp.A = curr.A + 3;
				gameStates.push_back(temp);

				temp.A = curr.A;//resets value of the pile A of temp


				temp.B = curr.B + 1;
				gameStates.push_back(temp);
		
				temp.B = curr.B + 2;
				gameStates.push_back(temp);

				temp.B = curr.B + 3;
				gameStates.push_back(temp);

				temp.B = curr.B; // resets value of pile B of temp
		
	
				temp.C = curr.C + 1;
				gameStates.push_back(temp);

				temp.C = curr.C + 2;
				gameStates.push_back(temp);

				temp.C = curr.C + 3;
				gameStates.push_back(temp);
			}	

			curr.A = next.A;
			curr.B = next.B;
			curr.C = next.C;
	
			gameStates.push_back(curr);
	
			afterMove(curr);

			if(curr.A == 0 && curr.B == 0 && curr.C == 0)
			{	
				computerWin = "false";
				break;
			}
		}
	}

	return gameStates;

}

void afterMove(state curr)
{
	cout << endl;

	cout << "The number of chips in each pile now is:" << endl;

	printState(curr);

	cout << endl;
}



state initChips(int &A, int &B, int &C)
{
	
	while(true)
	{
		cout << "Enter a positive number of chips for piles A B C: ";

		cin >> A;
		cin >> B;
		cin >> C;
		
		cout << endl;

		if(A < 0 || B < 0 || C < 0)
		{
			cout << "Negative number entered. Please try again.";
			cout << endl << endl;;
		}
		else
			break;
	}


	state initState;

	initState.A = A;
	initState.B = B;
	initState.C = C;

	printState(initState);

	return initState;


}

//returns vector of unsafe moves
vector<state> readFile(fstream & inOut)
{
	inOut.seekg(0);

	vector<string> unsafeMoves;

	string line = "";
		
	getline(inOut, line);

	while(inOut)
	{
		unsafeMoves.push_back(line);
	
		getline(inOut, line);
	}

	inOut.clear(); // return to the beginning of the file
	inOut.seekg(0);

	vector<state> unsafeState;
	for(int i = 0; i < unsafeMoves.size(); i++)
	{
		string t = unsafeMoves[i];
		
		string Apile = t.substr(0, 1);
		string Bpile = t.substr(2, 1);
		string Cpile = t.substr(4, 1);

		state temp;
		
		int Atemp = stoi(Apile);
		int Btemp = stoi(Bpile);
		int Ctemp = stoi(Cpile);

		temp.A = Atemp;
		temp.B = Btemp;
		temp.C = Ctemp;
		temp.safe = false;

		unsafeState.push_back(temp);
	}


	return unsafeState;	

}

int stoi(string s)
{
	int result = 0;

	for(int i = 0; i < s.size(); i++)
	{
		result = (result * 10) + (s[i] - '0');
	}

	return result;

}

void printState(state s)
{
	cout << "A:" << s.A << " B:" << s.B << " C:" << s.C << endl;
}
