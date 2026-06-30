#include <iostream>
#include <cmath>
#include <cstdlib> 
#include <ctime>  
#include <climits> 

using namespace std;
enum class enQuestionsLevel {Easy=1, Mid=2, Hard=3, Mixed =4};
enum class  enOperationType { Add = 1, Subtr = 2, Multi = 3, Div = 4, Mixed = 5 };

struct stQuestionStats
{
    enOperationType OpType = enOperationType::Add; //Will be either easy, mid, or hard. Can't be mixed
    enQuestionsLevel level = enQuestionsLevel::Easy;

    int firstNumber = 0;
    int secondNumber = 0;
    int correctAnswer = 0;
    int questionNumber = 0;

    int userAnswer = 0;
    bool isCorrect = false;
};

struct stGameStats
{
    enOperationType OpType = enOperationType::Add; //Can be any of the enumerators in enOperationType
    enQuestionsLevel level = enQuestionsLevel::Easy;

    int numQuestions = 0;
    int numCorrectAnswers = 0;
    int numWrongAnswers = 0;

    bool didPlayerPass = false;
};

struct stInputData
{
    string inputMessage;
    int from = INT_MIN; 
    int to = INT_MAX;
    string validationErrorMessage = "Please, enter a valid input!\n";
};

struct stSessionStats

int ReadNumber(const stInputData& input)
{
    int Number = 0;
    cout << input.inputMessage << endl;
    cin >> Number;

    while (cin.fail() || Number < input.from || Number > input.to)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << input.validationErrorMessage;

        cin >> Number;
    }

    return Number;
}

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

enQuestionsLevel ReadQuestionsLevel()
{
    stInputData inputData;
    inputData.inputMessage = "Enter the questions level: [1] Easy, [2] Medium, [3] Hard, [4] Mix? ";
    inputData.from = 1;
    inputData.to = 4;
    inputData.validationErrorMessage = "Please, provide a level using the numbers representing the question level: (1-4)\n";


    return (enQuestionsLevel)ReadNumber(inputData);
}

enOperationType ReadOperationType()
{
    stInputData inputData;
    inputData.inputMessage = "Enter the operation type for the question: [1] Addition, [2] Subtraction, [3] Multiplication, [4] Division, [5] Mix? ";
    inputData.from = 1;
    inputData.to = 5;
    inputData.validationErrorMessage = "Please, provide an operation type using the numbers representing each operation : (1-5)\n";

    return (enOperationType)ReadNumber(inputData);
}

int GenerateQuestionNumber(enQuestionsLevel level)
{
    switch (level)
    {
    case enQuestionsLevel::Easy:
        return RandomNumber(1, 10);

    case enQuestionsLevel::Mid:
        return RandomNumber(10, 50);

    case enQuestionsLevel::Hard:
        return RandomNumber(50, 100);
    default:
        return RandomNumber(1, 10);
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
    switch (stats.OpType)
    {
    case enOperationType::Add:
        return stats.firstNumber + stats.secondNumber;

    case enOperationType::Subtr:
        return stats.firstNumber - stats.secondNumber;

    case enOperationType::Multi:
        return stats.firstNumber * stats.secondNumber;

    case enOperationType::Div:
        //The decimal part is ignored here, meaning if the result is 0.7 for example, the answer is 0.
        return stats.firstNumber / stats.secondNumber;
    }
}

stQuestionStats GenerateQuestion(enQuestionsLevel level, enOperationType type, int number)
{
    stQuestionStats question;

    if (level == enQuestionsLevel::Mixed)
        level = (enQuestionsLevel)RandomNumber(1, 3);
    if (type == enOperationType::Mixed)
        type = GenerateRandomOperation();

    question.OpType = type;
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

    switch (stats.OpType)
    {
    case enOperationType::Add:
        std::cout << stats.firstNumber << "\n" << stats.secondNumber << " +\n" << "----------\n";
        break;

    case enOperationType::Subtr:
        std::cout << stats.firstNumber << "\n" << stats.secondNumber << " -\n" << "----------\n";
        break;

    case enOperationType::Multi:
        std::cout << stats.firstNumber << "\n" << stats.secondNumber << " *\n" << "----------\n";
        break;

    case enOperationType::Div:
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

        stInputData inputData;
        inputData.inputMessage = "Please, enter your answer: ";
        inputData.from = INT_MIN;
        inputData.to = INT_MAX;

        question.userAnswer = ReadNumber(inputData);
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
    case enQuestionsLevel::Mixed:  return "Mixed";
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
    case enOperationType::Mixed:  return "Mixed";
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

char DeterminePlayAgain()
{
    char PlayAgain;
    cout << endl << "Do you want to play again? Y/N\n";
    cin >> PlayAgain;

    while (cin.fail() || (toupper(PlayAgain) != 'N' && toupper(PlayAgain) != 'Y'))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please, enter a valid Choice (Y/N)!\n";

        cin >> PlayAgain;
    }

    return toupper(PlayAgain);
}

int ReadNumberOfQuestions()
{
    stInputData inputData;
    inputData.inputMessage = "Please, enter the number of questions you want to answer(1 - 200): ";
    inputData.from = 1;
    inputData.to = 200;
    inputData.validationErrorMessage = "Please, enter a valid number between 1 and 200!\n";

    return ReadNumber(inputData);
}

void StartGame()
{
    do
    {

        ResetScreen();

        int NumQuestions = ReadNumberOfQuestions();
        stGameStats GameResults = PlayGame(NumQuestions);
        PrintGameResults(GameResults);

    } while (DeterminePlayAgain()=='Y');
}

int main()
{
	srand((unsigned)time(NULL));

    StartGame();
}
