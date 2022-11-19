#include <iostream>
#include <stdfix.h>
#include <string>
#include <vector>
#include <fstream>
#include "json/single_include/nlohmann/json.hpp"
#include <array>
#include <algorithm>

using namespace std;
using json = nlohmann::json;

string welcome()
{
    string name = "Player";
    cout << "\n\n------------------------------------------------------";
    cout << "\n-                  GAMESHOW QUIZ                     -\n";
    cout << "------------------------------------------------------\n\n";
    cout << "Before we get started let's get your name.\nWhat is your name (Player): ";

    getline(cin, name);
    if (name.empty())
    {
        cout << "\nWelcome Player!\n";
    }
    else
    {
        cout << "\nWelcome " << name << "!\n";
    }
    return name;
};

void get_rules()
{
    bool rules = true;
    while (rules)
    {
        string answer;
        cout << "Would you like to see the rules?\nAnswer: ";
        cin >> answer;
        if (answer == "yes" | answer == "Yes")
        {
            cout << "\n\n------------------------------------------------------";
            cout << "\n-                     RULES                          -\n";
            cout << "------------------------------------------------------\n\n";
            cout << "10 Questions\n4 Options\nEnter the number associated with the correct answer.\nThe more correct answers the bigger the prizes!";
            rules = false;
        }
        else if (answer == "no" | answer == "No")
        {

            rules = false;
        }
        else
        {
            cout << "\nSorry. I did not get that. Please try again.\n";
        }
    }
}

string check_answer()
{
    bool answerBool = true;
    string answer;
    while (answerBool)
    {
        cout << "Answer: ";
        cin >> answer;
        if (answer == "1" | answer == "2" | answer == "3" | answer == "4")
        {
            answerBool = false;
        }
        else
        {
            cout << "Please enter the number associated with the answer\n";
        }
    }
    return answer;
}

bool play_again()
{
    string answer;
    bool reply = true;
    while (reply)
    {
        cout << "Would you like to play again?\n";
        cin >> answer;
        if (answer == "yes")
        {
            cout << "Playing again\n";
            reply = false;
            return true, 0;
        }
        else if (answer == "no")
        {
            cout << "Ending Program. Thank you for playing!\n";
            exit(0);
        }
        else
        {
            cout << "Sorry I didn't understand that. Please try again\n";
        };
    };
    return true, 10;
};

void display_game_over()
{
    cout << "\n\n------------------------------------------------------";
    cout << "\n-                   GAME OVER                        -\n";
    cout << "------------------------------------------------------\n\n";
};

void display_correct()
{
    cout << "\n\n------------------------------------------------------";
    cout << "\n-                     CORRECT                        -\n";
    cout << "------------------------------------------------------\n\n";
}

void display_incorrect()
{
    cout << "\n\n------------------------------------------------------";
    cout << "\n-                   INCORRECT                        -\n";
    cout << "------------------------------------------------------\n\n";
}

void display_status(double correct, double incorrect)
{
    cout << "Correct: " << correct << "\nIncorrect: " << incorrect << "\nCorrect %: " << correct / 10 * 100 << "%\n";
}

int main()
{
    // Reading json file of questions
    std::ifstream questionfile("data/questions.json", std::ifstream::binary);
    json questions;
    questionfile >> questions;

    // Variables
    int count = 0;

    double average;
    bool play = true;
    bool checkQuestion;
    int lowest = 0, highest = 14;
    int range = (highest - lowest) + 1;
    int i = lowest + int(range * rand() / (RAND_MAX + 1.0));
    vector<int> usedQuestions;

    srand(time(NULL));
    string name = welcome();
    get_rules();
    while (play)
    {
        double correct = 0;
        double incorrect = 0;
        cout << "\n\n------------------------------------------------------";
        cout << "\n-                  BEGINNING GAME                   -\n";
        cout << "------------------------------------------------------\n\n";

        usedQuestions = {};
        while (count < 10)
        {
            checkQuestion = true;
            while (checkQuestion)
            {
                i = lowest + int(range * rand() / (RAND_MAX + 1.0));
                if (!(find(usedQuestions.begin(), usedQuestions.end(), i) != usedQuestions.end()))
                {
                    usedQuestions.push_back(i);
                    checkQuestion = false;
                }
            }

            cout << "\n\n------------------------------------------------------";
            cout << "\n-                     QUESTION " << count + 1 << "                     -\n";
            cout << "------------------------------------------------------\n\n";
            cout << questions[i]["question"] << "\n";
            for (int j = 0; j < questions[i]["options"].size(); j++)
            {
                cout << "\t" << j + 1 << ") " << questions[i]["options"][j] << "\n";
            };

            string answer;
            answer = check_answer();
            if (answer == questions[i]["answer-index"])
            {
                display_correct();
                correct++;
            }
            else
            {
                display_incorrect();
                incorrect++;
            }
            count++;
        };

        display_game_over();
        display_status(correct, incorrect);
        play, count = play_again();
    };
    return 0;
}