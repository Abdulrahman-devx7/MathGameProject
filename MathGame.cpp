#include <iostream>
#include <cmath>
#include <cstdlib> 
#include <ctime>  
#include <climits> 
#include <string>
#include <vector>

using namespace std;
enum class enQuestionsLevel {Easy=1, Mid=2, Hard=3, Mixed =4};
enum class  enOperationType { Add = 1, Subtr = 2, Multi = 3, Div = 4, Mixed = 5 };


const string TEXT_RED = "\033[31m";
const string TEXT_YELLOW = "\033[33m";
const string TEXT_RESET = "\033[0m"; 

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

struct stCustomModeStats
{
    enOperationType OpType = enOperationType::Add; //Can be any of the enumerators in enOperationType
    enQuestionsLevel level = enQuestionsLevel::Easy;
    vector <stQuestionStats> questions;

    int numQuestions = 0;
    int numCorrectAnswers = 0;
    int numWrongAnswers = 0;

    bool didPlayerPass = false;
};

struct stDedicatedModeStats
{
    //The numbers of questions, easy, medium, and hard are defaulted to the values of easy mode 
    short numEasyQuestions = 9;
    short numMediumQuestions = 4;
    short numHardQuestions = 2;
    short numQuestions = numEasyQuestions + numMediumQuestions + numHardQuestions;
    int numCorrectAnswers = 0;
    int numWrongAnswers = 0;
    enQuestionsLevel level = enQuestionsLevel::Easy;

    //I need to investigate whether using a vector constructor here would consume memory or not, even if I didn't initialize a struct
    vector <stQuestionStats> questions;
    short playerScore = 0;
};

struct stInputData
{
    string inputMessage;
    int from = INT_MIN;
    int to = INT_MAX;
    string validationErrorMessage = "Please, enter a valid input!\n";
};

void DefaultBackGroundColor()
{
    system("color 0f");
}

int ReadNumber(const stInputData& input)
{
    int Number = 0;
    cout << input.inputMessage << endl;
    cin >> Number;

   while (cin.fail() || Number < input.from || Number > input.to
         || (std::cin.peek() != '\n' && std::cin.peek() != EOF))
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

void PrintMainMenu()
{
    cout << "Please, enter the number of the game mode you would like to play\n";
    cout << "[1]: Custom game mode\n";
    cout << "[2]: 3-level 15 Questions mode\n";
    cout << "[3]: 3-level 20 Questions mode\n";
    cout << "[4]: 3-level 25 Questions mode\n";
}

short ReadGameMode()
{
    stInputData inputData;
    inputData.from = 1;
    inputData.to = 4;
    PrintMainMenu();
    
    return ReadNumber(inputData);
}

void PrintNextLevelAtPoint(stDedicatedModeStats& game, short PointNextLevel)
{
    if (PointNextLevel == game.numEasyQuestions+1)
    {
        string separator = string(50, '-');

        DefaultBackGroundColor();
        cout << separator << endl;
        cout << "              NEXT LEVEL: "<< TEXT_YELLOW << "MEDIUM              " << TEXT_RESET << endl;
        cout << separator << endl << endl;;
    }
    else if(PointNextLevel == game.numEasyQuestions + game.numMediumQuestions+1)
    {
        string separator = string(50, '-');

        DefaultBackGroundColor();
        cout << separator << endl;
        cout << "              NEXT LEVEL: " << TEXT_RED << "HARD              " << TEXT_RESET << endl;
        cout << separator << endl << endl;;

    }
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

short ReturnScore(bool correct, enQuestionsLevel level)
{
    if (!correct)
        return 0;
    else
    {
        switch (level) {
        case enQuestionsLevel::Easy:
            return 1;
        case enQuestionsLevel::Mid:
            return 2;
        case enQuestionsLevel::Hard:
            return 3;
        }
    }
}

short GenerateQuestionAddSubtract(enQuestionsLevel level)
{
    switch (level)
    {
    case enQuestionsLevel::Easy:
        return RandomNumber(60, 120);

    case enQuestionsLevel::Mid:
        return RandomNumber(250, 500);

    case enQuestionsLevel::Hard:
        return RandomNumber(850, 1500);
    default:
        return RandomNumber(60, 120);
    }
}

short GenerateQuestionMultiDivision(enQuestionsLevel level)
{
    switch (level)
    {
    case enQuestionsLevel::Easy:
        return RandomNumber(10, 20);

    case enQuestionsLevel::Mid:
        return RandomNumber(20, 45);

    case enQuestionsLevel::Hard:
        return RandomNumber(40, 60);
    default:
        return RandomNumber(10, 20);
    }
}

short GenerateQuestionNumber(stQuestionStats &question)
{
    if (question.OpType == enOperationType::Add ||
                    question.OpType == enOperationType::Subtr)
    {
        return GenerateQuestionAddSubtract(question.level);
    }
    else return GenerateQuestionMultiDivision(question.level);
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

    question.firstNumber = GenerateQuestionNumber(question);
    question.secondNumber = GenerateQuestionNumber(question);
    question.correctAnswer = CalcCorrectAnswer(question);
    question.questionNumber = number;
    
    return question;
}

void PrintQuestion(const stQuestionStats &stats, int numberQuestion)
{
    std::cout << "Question: [" << stats.questionNumber+1 << "/" << numberQuestion << "]\n\n";

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

void IsAnswerCorrect(stQuestionStats& questionStats, stCustomModeStats &gameStats)
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

void IsAnswerCorrect(stQuestionStats& questionStats, stDedicatedModeStats& gameStats)
{
    if (questionStats.userAnswer == questionStats.correctAnswer)
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

short DetermineNumQuestions(enQuestionsLevel level)
{
    switch (level) {
    case enQuestionsLevel::Easy:
        return 15;
    case enQuestionsLevel::Mid:
        return 20;
    case enQuestionsLevel::Hard:
        return 25;
    default:
        return 15;
    }
}

void PrepareQuestions(stCustomModeStats &game)
{
    for (short Question = 0; Question < game.numQuestions; Question++)
    {
        stQuestionStats question = GenerateQuestion(game.level, game.OpType, Question);
        game.questions.push_back(question);
    }
}

void PrepareQuestions(stDedicatedModeStats& game)
{
    short numQuestions = game.numQuestions;
    short addMediumPoint = game.numEasyQuestions-1;
    short addHardPoint = addMediumPoint + game.numMediumQuestions;

    for (short Question = 0; Question < numQuestions; Question++)
    {
        enOperationType opType = GenerateRandomOperation();
        enQuestionsLevel level;

        if (Question > addHardPoint)
            level = enQuestionsLevel::Hard;
        else if (Question > addMediumPoint)
            level = enQuestionsLevel::Mid;
        else level = enQuestionsLevel::Easy;

        stQuestionStats question = GenerateQuestion(level, opType, Question);
        game.questions.push_back(question);
    }
}

stDedicatedModeStats PrepareEasyMode()
{
    stDedicatedModeStats stats;
    stats.numEasyQuestions = 9;
    stats.numMediumQuestions = 4;
    stats.numHardQuestions = 2;
    stats.level = enQuestionsLevel::Easy;

    PrepareQuestions(stats);
    return stats;
}

stDedicatedModeStats PrepareMediumMode()
{
    stDedicatedModeStats stats;
    stats.numEasyQuestions = 12;
    stats.numMediumQuestions = 6;
    stats.numHardQuestions = 3;
    stats.level = enQuestionsLevel::Mid;

    PrepareQuestions(stats);
    return stats;
}

stDedicatedModeStats PrepareHardMode()
{
    stDedicatedModeStats stats;
    stats.numEasyQuestions = 13;
    stats.numMediumQuestions = 7;
    stats.numHardQuestions = 5;
    stats.level = enQuestionsLevel::Hard;

    PrepareQuestions(stats);
    return stats;
}

void ShowQuestionAndEvaluateAnswer(stCustomModeStats &game)   
{
    for (int Question = 1; Question <= game.numQuestions; Question++)
    {
        PrintQuestion(game.questions[Question-1], game.numQuestions);

        stInputData inputData;
        inputData.inputMessage = "Please, enter your answer: ";

        game.questions[Question-1].userAnswer = ReadNumber(inputData);

        IsAnswerCorrect(game.questions[Question-1], game);
    }
    game.didPlayerPass = (game.numCorrectAnswers >= game.numWrongAnswers);
}

void ShowQuestionScore(short score)
{
    cout << "You got " << score << " points!\n";
}

void ShowQuestionAndEvaluateScore(stDedicatedModeStats& game)
{
    short numQuestions = game.numQuestions;
    for (int Question = 1; Question <= numQuestions; Question++)
    {
        PrintNextLevelAtPoint(game, Question);
        PrintQuestion(game.questions[Question - 1], numQuestions);

        stInputData inputData;
        inputData.inputMessage = "Please, enter your answer: ";

        game.questions[Question - 1].userAnswer = ReadNumber(inputData);

        IsAnswerCorrect(game.questions[Question - 1], game);
        game.playerScore += ReturnScore(game.questions[Question - 1].isCorrect, game.level);

        ShowQuestionScore(ReturnScore(game.questions[Question - 1].isCorrect, game.level));
    }
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

void PrintGameResults(const stCustomModeStats &Results)
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

void PrintGameResults(const stDedicatedModeStats& Results)
{
   
   cout << "Number of Right Answers: " << Results.numCorrectAnswers << endl;
   cout << "Number of Wrong Answers: " << Results.numWrongAnswers << endl << endl;
   cout << "Your final score is: " << Results.playerScore << "\n\n";

   cout << "You can do better!\n";
}

stCustomModeStats PlayGame(int NumQuestions)
{
    stCustomModeStats game;

    game.level = ReadQuestionsLevel();
    game.OpType = ReadOperationType();
    game.numQuestions = NumQuestions;

    PrepareQuestions(game);

    ShowQuestionAndEvaluateAnswer(game);

    return game;
}

void ResetScreen()
{
    system("cls");
    system("color 0f");
}

char DetermineAgain(string message)
{
    char PlayAgain;
    cout << message;
    cin >> PlayAgain;

    while (cin.fail() || (toupper(PlayAgain) != 'N' && toupper(PlayAgain) != 'Y')
          || (std::cin.peek() != '\n' && std::cin.peek() != EOF))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please, enter a valid Choice (Y/N)!\n";

        cin >> PlayAgain;
    }

    return toupper(PlayAgain);
}

void PrintQuestionReviewCard(const stQuestionStats& question, short totalQuestions)
{
    PrintQuestion(question, totalQuestions);
    cout << "Your answer: " << question.userAnswer << endl;
    cout << "The correct answer: " << question.correctAnswer << endl;
}

//We might overload a version of this function
void ReviewAnswers(stCustomModeStats& game)
{
    stInputData inputData;
    inputData.from = 1;
    inputData.to = game.numQuestions;
    inputData.inputMessage = "Please, enter the number of the question you'd like to review ("
        + to_string(inputData.from) + '-' + to_string(inputData.to) + ')';

    while (DetermineAgain("Do you want to review your answer to a question (Y/N)?\n") == 'Y')
    {   
        DefaultBackGroundColor();
        short QuestionNum = ReadNumber(inputData);
        PrintQuestionReviewCard(game.questions[QuestionNum - 1], game.numQuestions);
    }
}

void ReviewAnswers(stDedicatedModeStats& game)
{
    short numQuestions = game.numQuestions;

    stInputData inputData;
    inputData.from = 1;
    inputData.to = numQuestions;
    inputData.inputMessage = "Please, enter the number of the question you'd like to review ("
        + to_string(inputData.from) + '-' + to_string(inputData.to) + ')';

    while (DetermineAgain("Do you want to review your answer to a question (Y/N)?\n") == 'Y')
    {
        DefaultBackGroundColor();
        short QuestionNum = ReadNumber(inputData);
        PrintQuestionReviewCard(game.questions[QuestionNum - 1], numQuestions);
    }

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

void StartCustomMode()
{
     stCustomModeStats customStats;
     customStats.numQuestions = ReadNumberOfQuestions();

     customStats = PlayGame(customStats.numQuestions);
     PrintGameResults(customStats);
     ReviewAnswers(customStats);

     ResetScreen();
}

void StartDedicatedMode(short modeNumber)
{
    stDedicatedModeStats modeStats;

    if (modeNumber == 2)
        modeStats = PrepareEasyMode();
    else if (modeNumber == 3)
        modeStats = PrepareMediumMode();

    else modeStats = PrepareHardMode();

    ShowQuestionAndEvaluateScore(modeStats);
    PrintGameResults(modeStats);
    ReviewAnswers(modeStats);

    ResetScreen();
}

void StartGame()
{
    short GameModeChoice;
    do
    {
        GameModeChoice = ReadGameMode();
        if (GameModeChoice == 1)
            StartCustomMode();
        else
            StartDedicatedMode(GameModeChoice);

    } while (DetermineAgain("Do You want to play again (Y/N)?\n") == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

    StartGame();
}
