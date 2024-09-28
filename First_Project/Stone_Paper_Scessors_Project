#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <string>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3};
enum enWinner { Player1 = 1, Computer = 2, Drow = 3 };
struct stRoundInfo
{
    short RoundNumber;
    enGameChoice Player1Choise;
    enGameChoice ComputerChoise;
    enWinner Winner;
    string WinnerName;
};
struct stGameResult
{
    short GameRounds;
    short Player1WinTimes;
    short ComputerWinTimes;
    short DrowTimes;
    enWinner GameWinner;
    string WinnerName;
};


int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

enGameChoice ReadPlayer1Choise()
{
    short Choise;
    do {
        cout << "Your Choice : [1] : Stone, [2] :Paper, [3] : Scissors ?";
        cin >> Choise;
    } while (Choise > 3 || Choise < 1);

    return (enGameChoice)Choise;
}

enGameChoice GetComputerChoise()
{
    return (enGameChoice) RandomNumber(1, 3);
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case Player1:
        system("color 2F");// Green Screen
        return;
    case Computer:
        system("color 4F");// Red Screen
        cout << "\a";
        return;
    default:
        system("color 6F");// Yellow Screen
        return;
    }
}

enWinner HowWonTheRound(stRoundInfo RoundInfo)
{

    if (RoundInfo.Player1Choise == RoundInfo.ComputerChoise)
    {
        return Drow;
    }

    switch (RoundInfo.Player1Choise)
    {
    case Stone:
        if(RoundInfo.ComputerChoise == Paper)
            return Computer;
        else
            break;


    case Paper:
        if (RoundInfo.ComputerChoise == Scissors)
            return Computer;
        else
            break;

    case Scissors:
        if (RoundInfo.ComputerChoise == Stone)
            return Computer;
        else
            break;

    }

    return Player1;
}

string GetChoiseName(enGameChoice Choise)
{
    string ArrayGameChoise[3] = { "Stone", "Paper", "Scissors" };
   
    return ArrayGameChoise[Choise - 1];
}

string WinnerName(enWinner Winner)
{
    string ArrayWinnerName[3] = { "Player1", "Computer", "Drow" };
    return ArrayWinnerName[Winner - 1];
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << "\n\nRound [" << RoundInfo.RoundNumber << "]\n\n";
    cout << "Player1 Choise: " << GetChoiseName(RoundInfo.Player1Choise) << '\n';
    cout << "\nComputer Choise: " << GetChoiseName(RoundInfo.ComputerChoise) << '\n';
    cout << "\nRound Winner\t:[" << RoundInfo.WinnerName << "]\n";
    cout << "\n\n------------------------------\n\n";
    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner HowWonTheGame(short Player1WinTimes, short ComputerWinTimes, short DrowTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return Player1;
    else if (Player1WinTimes < ComputerWinTimes)
        return Computer;
    else
        return Drow;
}

stGameResult FillGameResults(short RoundNumber, short Player1WinTimes, short ComputerWinTimes, short DrowTimes)
{
    stGameResult GameResult;
    GameResult.GameRounds = RoundNumber;
    GameResult.Player1WinTimes = Player1WinTimes;
    GameResult.ComputerWinTimes = ComputerWinTimes;
    GameResult.DrowTimes = DrowTimes;
    GameResult.GameWinner = HowWonTheGame(Player1WinTimes, ComputerWinTimes, DrowTimes);
    GameResult.WinnerName = WinnerName(GameResult.GameWinner);
    return GameResult;
   
}

string Tabs(short n)
{
    string t = "";
    for (size_t i = 0; i < n; i++)
    {
        t += "\t";
        cout << t;
    }
    return t;
}

void ShowFinalResult(stGameResult GameResult)
{
    cout << Tabs(2) << "------------------[ Game Results ]------------------\n\n";
    cout << Tabs(2) << "Game Rounds\t\t: " << GameResult.GameRounds << endl;
    cout << Tabs(2) << "Player1 Won Times\t: " << GameResult.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer Won Times\t: " << GameResult.ComputerWinTimes << endl;
    cout << Tabs(2) << "Drow Won Times\t\t: " << GameResult.DrowTimes << endl;
    cout << Tabs(2) << "Final Winner\t\t: " << GameResult.WinnerName << endl;
    cout << Tabs(2) << "----------------------------------------------------\n\n";

    SetWinnerScreenColor(GameResult.GameWinner);
}

stGameResult PlayGame(short Rounds)// Core
{
    stRoundInfo RoundInfo;
    short ComputerWinTimes = 0, Player1WinTimes = 0, DrowTimeTimes = 0;


    for (short i = 1; i <= Rounds; i++)
    {
        RoundInfo.RoundNumber = i;
        cout << "\n\n----------Round [" << i << "]------------\n\n";
        RoundInfo.Player1Choise = ReadPlayer1Choise();
        RoundInfo.ComputerChoise = GetComputerChoise();
        RoundInfo.Winner = HowWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (Player1 == RoundInfo.Winner)
            Player1WinTimes++;
        else if (Computer == RoundInfo.Winner)
            ComputerWinTimes++;
        else
            DrowTimeTimes++;

        PrintRoundResult(RoundInfo);
    }
    return FillGameResults(Rounds,ComputerWinTimes, Player1WinTimes, DrowTimeTimes);
}

void HowGameOverScreen()
{
    cout << "\n\n\t\t\t--------------------------------------------\n\n";
    cout << "\n\n\t\t\t\t+++ G A M E  O V E R +++\n\n";
    cout << "\n\n\t\t\t--------------------------------------------\n\n";
}

int HowMRounds()
{
    cout << "How Many Rounds 1 to 10 ?";
    int Rounds;
    cin >> Rounds;
    return Rounds;
}

void ResetScreen()
{
    system("CLS");
    system("color 0F");
}


void StartGame()
{
    char x = 'y';
    do
    {
        ResetScreen();
        short Rounds = HowMRounds();
        stGameResult GameResult = PlayGame(Rounds);

        HowGameOverScreen();
        ShowFinalResult(GameResult);

        cout << Tabs(2) << "Do You Want to play again? Y/N?";
        cin >> x;
    } while (x == 'y' || x == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}