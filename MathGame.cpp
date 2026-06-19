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

    int firstNumber = 0;
    int secondNumber = 0;
    int correctAnswer = 0;
    int questionNumber = 0;

    int userAnswer = 0;
    bool isCorrect = false;
};

struct stGameStats
{
    enOperationType OpType; //Can be any of the enumerators in enOperationType
    enQuestionsLevel level;

    int numQuestions = 0;
    int numCorrectAnswers = 0;
    int numWrongAnswers = 0;

    bool didPlayerPass = false;
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
        std::cout << "Enter the questions level: [1] Easy, [2] Medium, [3] Hard, [4] Mix? ";
        std::cin >> choice;
        
    } while (choice > 4 || choice < 1);

    return enQuestionsLevel(choice);
}

enOperationType ReadOperationType()
{
    int choice;
    do
    {
        std::cout << "Enter the operation type: [1] Addition, [2] Subtraction, [3] Multiplication, [4] Division, [5] Mix? ";
        std::cin >> choice;

    } while (choice > 5 || choice < 1);

    return enOperationType(choice);
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

void ChangeBackgroundColor(bool result)
{
    if (result == true) std::system("color 2F");
    else std::system("color 4F");
}

enOperationType GenerateRandomOperation()
{
    int Operation = RandomNumber(1, 4);
    return (enOperationType)Operation;
}

int CalcCorrectAnswer(stQuestionStats &stats)
{
    switch (stats.opType)
    {
    case Add:
        return stats.firstNumber + stats.secondNumber;

    case Subtr:
        return stats.firstNumber - stats.secondNumber;

    case Multi:
        return stats.firstNumber * stats.secondNumber;

    case Div:
        //The decimal part is ignored here, meaning if the result is 0.7 for example, the answer is 0.
        return stats.firstNumber / stats.secondNumber;
    }
}

stQuestionStats GenerateQuestion(enQuestionsLevel level, enOperationType type, int number)
{
    stQuestionStats question;

    if (level == Mixed1)
        question.level = (enQuestionsLevel)RandomNumber(1, 3);
    if (type == Mixed2)
        question.opType = GenerateRandomOperation();

    question.opType = type;
    question.level = level;

    question.firstNumber = GenerateQuestionNumber(level);
    question.secondNumber = GenerateQuestionNumber(level);
    question.correctAnswer = CalcCorrectAnswer(question);
    question.questionNumber = number;
    
    return question;
}

void PrintQuestion(const stQuestionStats &stats, int numberQuestion)
{
    std::cout << "Question: [" << stats.questionNumber << "/" << numberQuestion << "]\n\n";

    switch (stats.opType)
    {
    case Add:
        std::cout << stats.firstNumber << "\n" << stats.secondNumber << " +\n" << "----------\n";
        break;

    case Subtr:
        std::cout << stats.firstNumber << "\n" << stats.secondNumber << " -\n" << "----------\n";
        break;

    case Multi:
        std::cout << stats.firstNumber << "\n" << stats.secondNumber << " *\n" << "----------\n";
        break;

    case Div:
        std::cout << stats.firstNumber << "\n" << stats.secondNumber << " /\n" << "----------\n";
        break;
    }
}

void IsAnswerCorrect(stQuestionStats& questionStats, stGameStats &gameStats)
{
    if (questionStats.userAnswer==questionStats.correctAnswer)
    {
        std::cout << "Your answer is right! :-)\n\n";
        gameStats.numCorrectAnswers++;
        questionStats.isCorrect = true;
    }
    else
    {
        std::cout << "Your answer is wrong! :-( \nThe right answer is: " << questionStats.correctAnswer << "\n\n";
        gameStats.numWrongAnswers++;
        //The isCorrect field is false by default in stQuestionStats
    }
    ChangeBackgroundColor(questionStats.isCorrect);
}

void ShowQuestionAndEvaluateAnswer(stGameStats &game)   
{
    for (int Question = 1; Question <= game.numQuestions; Question++)
    {
        stQuestionStats question = GenerateQuestion(game.level, game.OpType, Question);
        PrintQuestion(question, game.numQuestions);

        question.userAnswer = ReadNumber("Please, enter your answer: ");
        IsAnswerCorrect(question, game);
    }
    game.didPlayerPass = (game.numCorrectAnswers >= game.numWrongAnswers);
}

string ReturnPassOrFail(bool result)
{
    if (result == true) return "pass! :-)";
    else return "fail! :-(";
}

void PrintResultHeader(bool result)
{
    std::cout << "---------------------------------\n";
    std::cout << " Your final result is " << ReturnPassOrFail(result) << "\n";
    std::cout << "---------------------------------\n";
    ChangeBackgroundColor(result);
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
    std::cout << "Number of Questions: " << Results.numQuestions << std::endl;

    std::cout << "Questions Level  : " << 
        ReturnQuestionLevel (Results.level)<< std::endl;

    std::cout << "Operation Type   : " <<
        ReturnOperationType(Results.OpType) << std::endl;

    std::cout << "Number of Right Answers: " << Results.numCorrectAnswers << std::endl;
    std::cout << "Number of Wrong Answers: " << Results.numWrongAnswers << std::endl;
    ChangeBackgroundColor(Results.didPlayerPass);
}



stGameStats PlayGame(int NumQuestions)
{
    stGameStats game;

    game.level = ReadQuestionsLevel();
    game.OpType = ReadOperationType();
    game.numQuestions = NumQuestions;

    ShowQuestionAndEvaluateAnswer(game);

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


