#include <iostream>
#include <stdlib.h>
#include <time.h>


using namespace std;
#define Ahmed_Abu_Code_Fast ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);


enum enChoseMath {Easy = 1, Mediam = 2, Hard = 3, enMix = 4};

enum enChoseOperatation {Sum = 1, Sub = 2, Div = 3, Mult = 4, Mix = 5};

struct  stTowNumbers
{
    short Number1;
    short Number2;
};

struct stIsPass
{
    short NumberOfRight = 0;
    short NumberOfWrong = 0;
};

string PrintLevel(enChoseMath Level)
{
    string arr[] = { "Easy", "Mediam", "Hard", "Mix" };
    return arr[Level - 1];
}

string PrintOperationAsItIs(enChoseOperatation Operatation)
{
    string arr[] = { "Sum", "Sub", "Div", "Mult", "Mix"};
    return arr[Operatation - 1];
}

short RandomNumber(short From, short To)
{
    return rand() % (To - From + 1) + From;
}

bool ChechCorrectance(int UserAns, int RightAns)
{
     return UserAns == RightAns;
}


int AnswerOfUser()
{
    int Ans;
    cin >> Ans;
    return Ans;
}



int DoEquation(char Operator, stTowNumbers Numbers)
{
    switch (Operator)
    {
    case '+':
        return Numbers.Number1 + Numbers.Number2;
    case '-':
        return Numbers.Number1 - Numbers.Number2;
    case '*':
        return Numbers.Number1 * Numbers.Number2;
    default://Div
        return Numbers.Number1 / Numbers.Number2;
    }
}

char MathOperation(enChoseOperatation Operatation)
{
    char OperationChoise[5] = { '+','-','/','*' };
    if (Operatation != enChoseOperatation::Mix)
        return OperationChoise[Operatation - 1];
    else
        return OperationChoise[RandomNumber(1,4) - 1];
}

stTowNumbers GetTwoNumbersOfMathEquation(enChoseMath Equation)
{

    stTowNumbers Tow;
    switch (Equation)
    {
    case Easy:
        Tow.Number1 = RandomNumber(1, 10);
        Tow.Number2 = RandomNumber(1, 10);
        break;
    case Mediam:
        Tow.Number1 = RandomNumber(10, 50);
        Tow.Number2 = RandomNumber(10, 50);
        break;
    case Hard:
        Tow.Number1 = RandomNumber(51, 100);
        Tow.Number2 = RandomNumber(51, 100);
        break;
    default:
        Tow.Number1 = RandomNumber(1, 100);
        Tow.Number2 = RandomNumber(1, 100);
        break;
    }
    return Tow;
}


enChoseMath QuestionLevel()
{
    short Choise;
    do {
        cin >> Choise;
    } while (Choise < 1 || Choise > 4);
    return (enChoseMath) Choise;
}

enChoseOperatation EnterOperatorType()
{
    short Choise;
    do {
        cin >> Choise;
    } while (Choise < 1 || Choise > 5);
    return (enChoseOperatation)Choise;
}


int HowManyRounds()
{
    int Rounds;
    do {
        //cout << "How many question Do you want to answer 1 - 10?";
        cin >> Rounds;
    } while (Rounds < 1 || Rounds > 10);
    return Rounds;
}
void PrintEquation(stTowNumbers TowNumbers, char Operation)
{
    cout << endl;
    cout << TowNumbers.Number1 << endl;
    cout << '\t' << Operation << endl;
    cout << TowNumbers.Number2 << endl;
    cout << "\n-------------\n";
}

void ColorCorrectance(bool IsCorrect)
{
    if (IsCorrect)
    {
        cout << "\nCorrect Answer :-)\n";
        system("color 2F");
    }
    else
    {
        cout << "\nWrong Answer :-(\n";
        system("color 4F");
        cout << '\a';
    }
}

bool IsPass(stIsPass Pass)
{
    bool PassOrNot = Pass.NumberOfRight >= Pass.NumberOfWrong;
    ColorCorrectance(PassOrNot);
    return PassOrNot;
}

void PrintFinalResult(bool IsPass, int Rounds, string QuestionLevel, string OperationType, stIsPass Pass)
{
    cout << "\n-------------------------------------------\n";
    cout << "  Final Result is " << (IsPass ? "PASS :-)" : "Fali :-(");
    cout << "\n-------------------------------------------\n";
    
    cout << "\nNumber Of Questions is : " << Rounds << endl;
    cout << "Questions Level : " << QuestionLevel << endl;
    cout << "Operation Type : " << OperationType << endl;
    cout << "Number of right answer : " << Pass.NumberOfRight << endl;
    cout << "Number of wrong answer : " << Pass.NumberOfWrong << endl;
    cout << "\n-------------------------------------------\n";

}
void PlayAgain()
{
    system("color 0F");
    system("CLS");

}
void StartGame()
{
    char A;
    do {
        cout << "How many question Do you want to answer 1 - 10?";
        int Rounds = HowManyRounds();

        cout << "Enter Question Level { Easy[1], Mediam[2], Hard[3], Mix[4] }\n";
        enChoseMath Level = QuestionLevel();

        cout << "Do You want Exam about { Sum[1], Sub[2], Div[3], Mult[4], Mix[5] }";
        enChoseOperatation OperationType = EnterOperatorType();
        bool IsMix = OperationType == 5;
        char Operation;
        stIsPass Pass;
        for (size_t i = 0; i < Rounds; i++)
        {
            char Operation = MathOperation(OperationType);
            stTowNumbers TowNumbers = GetTwoNumbersOfMathEquation(Level);
            cout << "\nQuestion [" << i + 1 << "] \n";
            PrintEquation(TowNumbers, Operation);
            int UserAnswer = AnswerOfUser();

            int EquationAnswer = DoEquation(Operation, TowNumbers);

            bool IsCorrect = ChechCorrectance(UserAnswer, EquationAnswer);

            ColorCorrectance(IsCorrect);
            if (IsCorrect)
                Pass.NumberOfRight++;
            else
            {
                Pass.NumberOfWrong++;
                cout << "\nThe Right answer is : " << EquationAnswer << endl;
            }
        }

        string QuestionLevel = PrintLevel(Level);
        string OperationTypeString = PrintOperationAsItIs(OperationType);
        PrintFinalResult(IsPass(Pass), Rounds, QuestionLevel, OperationTypeString, Pass);

        cout << "Do you want to paly again ?";
        cin >> A;
        if (A == 'y' || A == 'Y')
            PlayAgain();
    } while (A == 'y' || A == 'Y');
}

int main()
{
        Ahmed_Abu_Code_Fast

    srand((unsigned)time(NULL));
        StartGame();
}