#include <iostream>
using namespace std;

enum enGameChoice { Stone = 1, Paper , Scissors };
enum enWinner {Player1 =1 , Computer , Draw};

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;

};

struct stGameResult
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";

};

short RandomNumebr(short From ,short To)
{
    return rand() % (To - From + 1) + From;
}

short ReadHowManyRounds()
{
    short NoOfRounds;
    do
    {
        cout << "How Many Rounds 1 to 10 ?\n";
        cin >> NoOfRounds;

    } while (NoOfRounds<1 || NoOfRounds > 10);

    return NoOfRounds;
}

enGameChoice ReadPlayer1Choice()
{
    short Choice = 1;
    do
    {
        cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?";
        cin >> Choice;

    } while (Choice < 1 || Choice > 3);
  
 
    return enGameChoice(Choice);
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumebr(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }
    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        if(RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == Stone)
        {
            return enWinner::Computer;
        }
        break;

        
    

    default:
        break;
    }

    return enWinner::Player1;

}

string WinnerName(enWinner Winner)
{
    string arrName[3] = { "Player1" , "Computer" , "NoWinner" };
    return arrName[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
    string arrChoices[3] = { "Stone","Paper","Scissors" };
    return arrChoices[Choice - 1];
}

void  PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n_______________________"
        << " Round [" << RoundInfo.RoundNumber << "] "
        << "_______________________" << endl;
    cout << "Player1  Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round  Winner  : " << RoundInfo.WinnerName << endl;
    cout << "_________________________________________________________" << endl;

}

enWinner WhoWinTheGame(short PlayerWins, short ComputerWins)
{
    if (PlayerWins > ComputerWins)
    {
        return enWinner::Player1;
    }
    else if (ComputerWins > PlayerWins)
    {
        return enWinner::Computer;
    }
    else
    {
        return enWinner::Draw;
    }

}

stGameResult FillGameResults(short NOofRounds, short Player1Wins, short ComputerWins, short DrawTimes)
{
    stGameResult GameResults;

    GameResults.GameRounds = NOofRounds;
    GameResults.Player1WinTimes = Player1Wins;
    GameResults.ComputerWinTimes = ComputerWins;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWinTheGame(Player1Wins, ComputerWins);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

stGameResult PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short Round = 1; Round <= HowManyRounds; Round++)
    {
        cout << "\nRound [" << Round << "] begins: \n";
        RoundInfo.RoundNumber = Round;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        //CalcWins and Draws
        if (RoundInfo.Winner == enWinner::Player1)
        {
            Player1WinTimes++;
        }
        else if (RoundInfo.Winner == enWinner::Computer)
        {
            ComputerWinTimes++;
        }
        else
        {
            DrawTimes++;
        }

        PrintRoundResults(RoundInfo);

    }
   
    return FillGameResults(HowManyRounds,Player1WinTimes,ComputerWinTimes,DrawTimes);
}

void ResetScreen()
{
    system("cls");
    system("Color 0F");
}

string TabSpace(short NoofTabs)
{
    string Tab = "";

    for (int i = 1; i <= NoofTabs; i++)
    {
        Tab += "\t";
        cout << Tab;
    }

    return Tab;
}

void ShowGameOver()
{
    cout << TabSpace(2) << "___________________________________________________________ \n\n";
    cout << TabSpace(2) << "                    +++ G a m e  O v e r +++                \n\n";
    cout << TabSpace(2) << "___________________________________________________________ \n\n";

}

void WinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case Player1:
        system("color 2F"); // Turn Screen to Green
        break;
    case Computer:
        system("color 4F"); // Turn Screen to Red
        cout << "\a";       // Sound of Bell 
        break;
    case Draw:
        system("color 6F"); // Turn Screen to Yellow
        break;
    default:
        break;
    }
}

void ShowGameResult(stGameResult GameResult)
{
    cout << TabSpace(2) << "__________________  [ Game Results ]  __________________\n\n";
    cout << TabSpace(2) << " Game  Rounds       : " << GameResult.GameRounds << endl;
    cout << TabSpace(2) << " Player1  Won times : " << GameResult.Player1WinTimes << endl;
    cout << TabSpace(2) << " Computer Won times : " << GameResult.ComputerWinTimes << endl;
    cout << TabSpace(2) << " Draw  times        : " << GameResult.DrawTimes << endl;
    cout << TabSpace(2) << " Final Winner       : " << GameResult.WinnerName << endl;

    WinnerScreenColor(GameResult.GameWinner);
}

void StartGame()
{
    char PlayAgain = 'y';

    do
    {
        ResetScreen();
        stGameResult GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOver();
        ShowGameResult(GameResults);

        cout << endl << TabSpace(4) << "Do you want to play again? Y/N?";
        cin >> PlayAgain;


    } while (PlayAgain == 'Y' || PlayAgain == 'y');


}

int main()
{
    //Seeds the random number generator in C++, called only once in main().
    srand((unsigned)time(NULL));


    StartGame();


    return 0;
}