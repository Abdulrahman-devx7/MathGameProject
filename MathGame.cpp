#include <iostream>
#include <cmath>
#include <windows.h>
#include <cstdlib> 
#include <ctime>  
using namespace std;
enum enQuestionsLevel {Easy=1, Mid=2, Hard=3, Mixed1 =4};
enum enOperationType { Add = 1, Subtr = 2, Multi = 3, Div = 4, Mixed2 = 5 };

struct stQuestionStats
{
    enOperationType opType; //Will be either easy, mid, or hard. Can't be mixed
    enQuestionsLevel level;
    int correctAnswer = 0;
};

struct stGameStats
{
    enOperationType OpType; //Can be any of the enumerators in enOperationType
    enQuestionsLevel level;
    int numQuestions = 0;
    int numCorrectAnswers = 0;
    int numWrongAnswers = 0;
};

int ReadNumber(string Message)
{
    //Validation will be added later

    int Number = 0;
    cout << Message << endl;
    cin >> Number;

    return Number;
}

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

enQuestionsLevel ReadQuestionsLevel()
{
    int choice;
    do
    {
        cout << "Enter the questions level: [1] Easy, [2] Medium, [3] Hard, [4] Mix? ";
        cin >> choice;
        
    } while (choice > 4 || choice < 1);

    return enQuestionsLevel(choice);
}

enOperationType ReadOperationType()
{
    int choice;
    do
    {
        cout << "Enter the operation type: [1] Addition, [2] Subtraction, [3] Multiplication, [4] Division, [5] Mix? ";
        cin >> choice;

    } while (choice > 5 || choice < 1);

    return enOperationType(choice);
}

bool IsLevelMixed(enQuestionsLevel level)
{
    if (level== Mixed1)
        return true;

    return false;
}

bool IsTypeMixed(enOperationType type)
{
    if (type == Mixed2)
        return true;
    
    return false;
}

int GenerateQuestionNumber(enQuestionsLevel level)
{
    switch (level)
    {
    case Easy:
        return RandomNumber(1, 10);

    case Mid:
        return RandomNumber(10, 50);

    case Hard:
        return RandomNumber(50, 100);
    }
}

enOperationType GenerateRandomOperation(short randomOp)
{
    switch ((enOperationType)randomOp)
    {
    case Add:
        return Add;

    case Subtr:
        return Subtr;

    case Multi:
        return Multi;

    case Div:
        return Div;
    }
}

void CalcCorrectAnswer(short firstNumber, short secondNumber, stQuestionStats &stats)
{
    switch (stats.opType)
    {
    case Add:
        stats.correctAnswer = firstNumber + secondNumber;
        break;

    case Subtr:
        stats.correctAnswer = firstNumber - secondNumber;
        break;

    case Multi:
        stats.correctAnswer = firstNumber * secondNumber;
        break;

    case Div:
        //The decimal part is ignored here, meaning if the result is 0.7 for example, the answer is 0.
        stats.correctAnswer = firstNumber / secondNumber;
        break;
    }
}

void FillQuestionOperation(stQuestionStats& questionStats, stGameStats& gameStats)
{
    if (IsTypeMixed(gameStats.OpType))
        questionStats.opType = GenerateRandomOperation(RandomNumber(1, 4));
    else
        questionStats.opType = gameStats.OpType;
}

void FillTwoNumbersForQuestion(stQuestionStats& questionStats, enQuestionsLevel level, short &firstNumber, short &secondNumber)
{
    firstNumber = GenerateQuestionNumber(level);
    secondNumber = GenerateQuestionNumber(level);
}

void HandleChoiceMix(stQuestionStats &questionStats, stGameStats &gameStats, short &firstNumber, short &secondNumber)
{
    enQuestionsLevel level;
    if (IsLevelMixed(gameStats.level))
    {
        FillQuestionOperation(questionStats, gameStats);
        level = (enQuestionsLevel)RandomNumber(1, 3);
        FillTwoNumbersForQuestion(questionStats, level, firstNumber, secondNumber);
    }
    else
    {
        FillQuestionOperation(questionStats, gameStats);
        level = gameStats.level;
        FillTwoNumbersForQuestion(questionStats, level, firstNumber, secondNumber);
    }
}

void ShowQuestion(const short firstNumber, const short secondNumber, stQuestionStats questionStats)
{
    switch (questionStats.opType)
    {
    case Add:
        cout << firstNumber << "\n" << secondNumber << " +\n" << "----------\n";
        break;

    case Subtr:
        cout << firstNumber << "\n" << secondNumber << " -\n" << "----------\n";
        break;

    case Multi:
        cout << firstNumber << "\n" << secondNumber << " *\n" << "----------\n";
        break;

    case Div:
        cout << firstNumber << "\n" << secondNumber << " /\n" << "----------\n";
        break;
    }
}

bool IsAnswerCorrect(const stQuestionStats& stats, int userAnswer)
{
    if (userAnswer == stats.correctAnswer)
    {
        cout << "Your answer is right! :-)\n\n";
        system("color 2F");
        return true;
    }
    else
    {
        cout << "Your answer is wrong! :-( \nThe right answer is: " << stats.correctAnswer<<"\n\n";
        system("color 4F");
        return false;
    }
}

bool DidUserPass(const stGameStats &stats)
{
    return (stats.numCorrectAnswers >= stats.numWrongAnswers);
}

void PrintResultHeader(bool result)
{
    //Linking the change of the background color (i.e. red or green) better be linked to determining if the user 
    //passed or not. This should be done while also printing out a certain pass/fail header depending on the result as well
    if (result == true)
    {
        std::cout << "---------------------------------\n";
        std::cout << " Your final result is pass! :-)  \n";
        std::cout << "---------------------------------\n";
        std::system("color 2F");  

    }
    else
    {
        std::cout << "---------------------------------\n";
        std::cout << " Your final result is fail! :-(  \n";
        std::cout << "---------------------------------\n";
        std::system("color 4F");  
    }
}

void FillGameResults(stGameStats &stats ,int numQuestions, int numCorrectAnswers, int numWrongAnswers)
{
    stats.numQuestions = numQuestions;
    stats.numCorrectAnswers = numCorrectAnswers;
    stats.numWrongAnswers = numWrongAnswers;
}

std::string ReturnQuestionLevel(enQuestionsLevel level)
{
    switch (level)
    {
    case enQuestionsLevel::Easy:   return "Easy";
    case enQuestionsLevel::Mid:    return "Mid";
    case enQuestionsLevel::Hard:   return "Hard";
    case enQuestionsLevel::Mixed1: return "Mixed";
    default:                       return "Unknown";
    }
}

std::string ReturnOperationType(enOperationType type)
{
    switch (type)
    {
    case enOperationType::Add:    return "Add";
    case enOperationType::Subtr:  return "Subtr";
    case enOperationType::Multi:  return "Multi";
    case enOperationType::Div:    return "Div";
    case enOperationType::Mixed2: return "Mixed";
    default:                      return "Unknown";
    }
}

void PrintGameResults(const stGameStats &Results)
{
    PrintResultHeader(DidUserPass(Results));
    
    std::cout << "Number of Questions: " << Results.numQuestions << std::endl;

    std::cout << "Questions Level  : " << 
        ReturnQuestionLevel (Results.level)<< std::endl;

    std::cout << "Operation Type   : " <<
        ReturnOperationType(Results.OpType) << std::endl;

    std::cout << "Number of Right Answers: " << Results.numCorrectAnswers << std::endl;
    std::cout << "Number of Wrong Answers: " << Results.numWrongAnswers << std::endl;
}

stGameStats PlayGame(int NumQuestions)
{
    stGameStats game;
    stQuestionStats question;

    int NumCorrectAnswers = 0, NumWrongAnswers = 0;

    game.level = ReadQuestionsLevel();
    game.OpType = ReadOperationType();

    short FirstNumber = 0, SecondNumber = 0, Answer = 0;

    for (int i = 1; i <= NumQuestions; i++)
    {
        HandleChoiceMix(question, game, FirstNumber, SecondNumber);

        std::cout << "Question: [" << i << "/" << NumQuestions << "]\n\n";
        ShowQuestion(FirstNumber, SecondNumber, question);
        CalcCorrectAnswer(FirstNumber, SecondNumber, question);

        Answer = ReadNumber("Enter your answer: ");

        if (IsAnswerCorrect(question, Answer))
            NumCorrectAnswers++;
        else NumWrongAnswers++;
    }
    FillGameResults(game, NumQuestions, NumCorrectAnswers, NumWrongAnswers);
    return game;
}

void ResetScreen()
{
    system("cls");
    system("color 0f");
}

void StartGame()
{
    char PlayAgain;
    do
    {
        ResetScreen();
        int NumQuestions = ReadNumber("Please, enter the number of questions you want to answer: ");
        stGameStats GameResults = PlayGame(NumQuestions);
        PrintGameResults(GameResults);

        cout << endl << "Do you want to play again? Y/N\n";
        cin >> PlayAgain;

    } while (PlayAgain=='Y' || PlayAgain=='y');

}

int main()
{
	srand((unsigned)time(NULL));

    StartGame();
}



