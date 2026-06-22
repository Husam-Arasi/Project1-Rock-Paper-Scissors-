#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int HowManyRounds() {
	int ReadRounds = 0;

	do {
		cout << "How many rounds do you want to play from 1 to 10 ? " << endl;
		cin >> ReadRounds;
		cout << endl;

	} while (ReadRounds < 1 || ReadRounds > 10);

	return ReadRounds;
}

int RandomEquation(short from, short to) {
	int randNumber = rand() % (to - from + 1) + from;
	return randNumber;
}

enum enChoiceItem { Rock = 1, Paper = 2, Scissors = 3 };
enum enChoiceWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {
	short RoundNumber;
	enChoiceItem PlayerChoice;
	enChoiceItem ComputerChoice;
	enChoiceWinner Winner;
	string WinnerName;
};

struct stGameInfo {
	short GameRounds = 0;
	short PlayerTimes = 0;
	short ComputerTimes = 0;
	short DrawTimes = 0;
	enChoiceWinner GameWinner;
	string WinnerName;
};

enChoiceItem GetComputerChoice() {
	return (enChoiceItem)RandomEquation(1, 3);
}

enChoiceItem PlayerChoice() {
	short Choice = 0;

	do {
		cout << "Please choose one of them [1] Rock , [2] Paper , [3] Scissors ? \n";
		cin >> Choice;
		cout << endl;

	} while (Choice < 1 || Choice > 3);

	return (enChoiceItem)Choice;
}

enChoiceWinner WhoWonTheRound(stRoundInfo RoundInfo) {

	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
		return enChoiceWinner::Draw;

	switch (RoundInfo.PlayerChoice) {

	case enChoiceItem::Rock:
		if (RoundInfo.ComputerChoice == enChoiceItem::Paper)
			return enChoiceWinner::Computer;
		break;

	case enChoiceItem::Paper:
		if (RoundInfo.ComputerChoice == enChoiceItem::Scissors)
			return enChoiceWinner::Computer;
		break;

	case enChoiceItem::Scissors:
		if (RoundInfo.ComputerChoice == enChoiceItem::Rock)
			return enChoiceWinner::Computer;
		break;
	}

	return enChoiceWinner::Player;
}

enChoiceWinner WhoWonTheGame(short PlayerWins, short ComputerWins) {

	if (PlayerWins > ComputerWins)
		return enChoiceWinner::Player;
	else if (ComputerWins > PlayerWins)
		return enChoiceWinner::Computer;
	else
		return enChoiceWinner::Draw;
}

string arrChoiceItem(enChoiceItem ChoiceItem) {
	string arrChoiceItem[3] = { "Rock", "Paper", "Scissors" };
	return arrChoiceItem[ChoiceItem - 1];
}

string arrChoiceWinner(enChoiceWinner WinnerChoice) {
	string arrChoiceWinner[3] = { "Player", "Computer", "Draw" };
	return arrChoiceWinner[WinnerChoice - 1];
}

void SetScreenColor(enChoiceWinner WinnerScreen) {

	switch (WinnerScreen) {

	case enChoiceWinner::Player:
		system("Color 2F");
		break;

	case enChoiceWinner::Computer:
		system("Color 4F");
		break;

	default:
		system("Color 6F");
		break;
	}
}

string Tabs(short NumberOfTabs) {

	string t = "";

	for (int i = 0; i < NumberOfTabs; i++)
		t += "\t";

	return t;
}

void PrintRoundResult(stRoundInfo RoundInfo) {

	cout << "____________________________Round[" << RoundInfo.RoundNumber << "]________________________________\n";
	cout << "Player Choice: " << arrChoiceItem(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << arrChoiceItem(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner: " << arrChoiceWinner(RoundInfo.Winner) << endl;
	cout << "___________________________________________________________________________" << endl;

	SetScreenColor(RoundInfo.Winner);
}

void PrintGameOver() {

	cout << Tabs(2) << "_______________________________________________________________________" << endl;
	cout << Tabs(2) << "                        +++     G A M E    O V E R    +++              " << endl;
	cout << Tabs(2) << "_______________________________________________________________________" << endl;
}

void PrintGameResult(stGameInfo GameInfo) {

	cout << Tabs(2) << "______________________________________[Game Results]_______________________________________\n";
	cout << Tabs(2) << "Rounds Game                                  :" << GameInfo.GameRounds << endl;
	cout << Tabs(2) << "Player Times                                 :" << GameInfo.PlayerTimes << endl;
	cout << Tabs(2) << "Computer Times                               :" << GameInfo.ComputerTimes << endl;
	cout << Tabs(2) << "Draw Times                                   :" << GameInfo.DrawTimes << endl;
	cout << Tabs(2) << "Winner Name                                  :" << GameInfo.WinnerName << endl;

	SetScreenColor(GameInfo.GameWinner);
}

stGameInfo FillGameResult(int GameRounds, short PlayerTimes, short ComputerTimes, short DrawTimes) {

	stGameInfo GameResult;

	GameResult.GameRounds = GameRounds;
	GameResult.PlayerTimes = PlayerTimes;
	GameResult.ComputerTimes = ComputerTimes;
	GameResult.DrawTimes = DrawTimes;

	GameResult.GameWinner = WhoWonTheGame(PlayerTimes, ComputerTimes);
	GameResult.WinnerName = arrChoiceWinner(GameResult.GameWinner);

	return GameResult;
}

stGameInfo PlayGame(short HowManyRounds) {

	stRoundInfo RoundInfo;

	short PlayerTimes = 0;
	short ComputerTimes = 0;
	short DrawTimes = 0;

	for (int GameRound = 1; GameRound <= HowManyRounds; GameRound++) {

		cout << "Round[" << GameRound << "] begin : " << endl;

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = PlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = arrChoiceWinner(RoundInfo.Winner);

		if (RoundInfo.Winner == enChoiceWinner::Player)
			PlayerTimes++;
		else if (RoundInfo.Winner == enChoiceWinner::Computer)
			ComputerTimes++;
		else
			DrawTimes++;

		PrintRoundResult(RoundInfo);
	}

	return FillGameResult(HowManyRounds, PlayerTimes, ComputerTimes, DrawTimes);
}

void ResetScreen() {
	system("cls");
	system("Color 0F");
}

void StartGame() {

	char PlayAgain = 'Y';

	do {
		ResetScreen();

		stGameInfo GameResults = PlayGame(HowManyRounds());

		PrintGameOver();
		PrintGameResult(GameResults);

		cout << endl << Tabs(3) << "Do you want to play again ? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main() {

	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}