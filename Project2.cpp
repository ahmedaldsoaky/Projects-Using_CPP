#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
#define Ahmed_Abu_Code_Fast ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

enum enQuestionLevel { EasyLevel = 1, MediamLevel = 2, HardLevel = 3, Mix = 4 };

enum enOperatationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

string GetQuestionLevelTxt(enQuestionLevel Level)
{
    string arr[] = { "Easy", "Mediam", "Hard", "Mix" };
    return arr[Level - 1];
}

short RandomNumber(short From, short To)
{
    return rand() % (To - From + 1) + From;
}



struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enQuestionLevel QuestionLevel;
    enOperatationType OperatationType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions = 0;
    enQuestionLevel QuestionLevel;
    enOperatationType OpType;
    short NumberOfRigthAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool IsPass = false;
};

int ReadHowManyQuestions()
{
    int Rounds;
    do {
        cout << "How many question Do you want to answer 1 - 10?";
        cin >> Rounds;
    } while (Rounds < 1 || Rounds > 10);
    return Rounds;
}

enQuestionLevel ReadQuestionLevel()
{
    short QuestionLevel;
    do {
        cout << "Enter Question Level { Easy[1], Mediam[2], Hard[3], Mix[4] }\n";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enQuestionLevel) QuestionLevel;
}

enOperatationType ReadOperatorType()
{
    short Choise;
    do {
        cout << "Do You want Exam about { Sum[1], Sub[2], Div[3], Mult[4], Mix[5] }";
        cin >> Choise;
    } while (Choise < 1 || Choise > 5);
    return (enOperatationType) Choise;
}

int SimpleCalculator(int Number1, int Number2, enOperatationType OpType)
{
    switch (OpType)
    {
    case Add:
        return Number1 + Number2;
    case Sub:
        return Number1 - Number2;
    case Mult:
        return Number1 * Number2;
    case Div:
        return Number1 / Number2;
    }
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperatationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::Mix)
        QuestionLevel = (enQuestionLevel) RandomNumber(1, 3);


    if (OpType == enOperatationType::MixOp)
        OpType = (enOperatationType)RandomNumber(1, 4);
    Question.QuestionLevel = QuestionLevel;
    Question.OperatationType = OpType;

    switch (QuestionLevel)
    {
    case EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
        return Question;
    case MediamLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
        return Question;
    case HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
        return Question;
    }

}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (size_t i = 0; i < Quizz.NumberOfQuestions; i++)
    {
        Quizz.QuestionList[i] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
    }
}

string GetOpTypeSymbol(enOperatationType Type)
{
    switch (Type)
    {
    case Add:
        return "+";
    case Sub:
        return "-";
    case Mult:
        return "*";
    case Div:
        return "/";
    default:
        return "MIX";
    }
}

void PrintQuestion(stQuizz Quizz, short QuestionNumber)
{
    cout << "\nQuestion [" << QuestionNumber + 1 << '/' << Quizz.NumberOfQuestions << "]\n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << "\t\t" << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperatationType) << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << endl;
    cout << "--------------\n";
}

int ReadQuestionAnswer()
{
    int Answer;
    cin >> Answer;
    return Answer;
}

void SetScreenColor(bool Right)
{
    (Right) ? system("color 2F") : system("color 4F");//turn screen to Green else Red
    if(!Right)
        cout << '\a';
}

void CorrectQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].CorrectAnswer != Quizz.QuestionList[QuestionNumber].PlayerAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = 0;
        Quizz.NumberOfWrongAnswers++;

        cout << "Wrong answer :-( \n";
        cout << "The right answer is:  " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = 1;
        Quizz.NumberOfRigthAnswers++;

        cout << "Right answer :-) \n";
    }
    cout << endl;
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (size_t i = 0; i < Quizz.NumberOfQuestions; i++)
    {
        PrintQuestion(Quizz, i);

        Quizz.QuestionList[i].PlayerAnswer = ReadQuestionAnswer();

        CorrectQuestionAnswer(Quizz, i);
    }
    Quizz.IsPass = (Quizz.NumberOfRigthAnswers >= Quizz.NumberOfWrongAnswers);
}

void PrintFinalResult(stQuizz Quizz)
{
    cout << "\n-------------------------------------------\n\n";
    cout << "  Final Result is " << (Quizz.IsPass ? "PASS :-)" : "Fali :-(");
    cout << "\n-------------------------------------------\n";

    cout << "\nNumber Of Questions is : " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level : " << GetQuestionLevelTxt(Quizz.QuestionLevel) << endl;
    cout << "Operation Type : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of right answer : " << Quizz.NumberOfRigthAnswers << endl;
    cout << "Number of wrong answer : " << Quizz.NumberOfWrongAnswers << endl;
    cout << "\n-------------------------------------------\n";

}

void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.OpType = ReadOperatorType();

    GenerateQuizzQuestions(Quizz);

    AskAndCorrectQuestionListAnswers(Quizz);
    
    PrintFinalResult(Quizz);
}

void ResetScreen()
{
    system("color 0F");
    system("CLS");
}


void StartGame()
{
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        PlayMathGame();

        cout << "\nDo you want to paly again ? Y/N ...  ";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
        Ahmed_Abu_Code_Fast

    srand((unsigned)time(NULL));

        StartGame();
}