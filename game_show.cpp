#include<iostream>
#include <stdfix.h>
#include<string>
#include<vector>
#include<fstream>
#include "json/single_include/nlohmann/json.hpp"
#include<array>
#include<algorithm>

using namespace std;
using json = nlohmann::json;

string welcome(){
    string name="Player";
    cout << "Greetings Player. Welcome to our quiz gameshow\nThis quiz will contain 10 randomized questions!\nThe more you get correct the better the prizes you will win!\n";
    cout << "Before we get started lets get your name.\nWhat is your name (Player): ";
    cin >> name;
    cout << "Welcome " << name << " let's begin the game!\n";
    return name;
};

string check_answer(){
    bool answerBool=true;
    string answer;
    while (answerBool){
        cout << "Answer: ";
        cin >> answer;
        if (answer == "1" | answer =="2" | answer =="3" | answer =="4"){
            answerBool=false;
        }
        else{
            cout << "Please enter the number associated with the answer\n";
            
        }
    }
    return answer;
}

bool play_again(){
    string answer;
    bool reply=true;
    while (reply){
        cout << "Would you like to play again?\n";
        cin >> answer;
        if (answer=="yes"){
            cout << "Playing again\n";
            reply=false;
            return true, 0;
        }
        else if (answer=="no"){
            cout << "Ending Program. Thank you for playing!\n";
            exit(0);
        }
        else{
            cout << "Sorry I didn't understand that. Please try again\n";
        };
    };
    return true, 10;
};

int main(){
    // Reading json file of questions
    std::ifstream questionfile("data/questions.json", std::ifstream::binary);
    json questions;
    questionfile >> questions;

    // Variables
    int count=0;
    double correct=0;
    double incorrect=0;
    double average;
    bool play=true;
    bool checkQuestion;
    int lowest=0, highest=14;
    int range=(highest-lowest)+1;
    int i=lowest + int(range*rand()/(RAND_MAX + 1.0));
    vector<int> usedQuestions;

    srand (time(NULL));
    string name=welcome();
    while (play){
        cout << "\n\n------------------------------------------------------";
        cout << "\n-                  BEGINNING GAME                   -\n";
        cout << "------------------------------------------------------\n\n";
        
        usedQuestions={};
        while (count < 10){
            checkQuestion=true;
            while (checkQuestion){
                i = lowest + int(range*rand()/(RAND_MAX + 1.0));
                if (!(find(usedQuestions.begin(), usedQuestions.end(), i) !=usedQuestions.end())){
                    usedQuestions.push_back(i);
                    checkQuestion=false;
                }
               
                
            }

            
            cout << "\n\n------------------------------------------------------";
            cout << "\n-                     QUESTION " << count+1 << "                     -\n";
            cout << "------------------------------------------------------\n\n";
            cout << questions[i]["question"] << "\n";
            for (int j=0; j<questions[i]["options"].size(); j++){
                cout << "\t" << j+1 <<") " << questions[i]["options"][j] << "\n";
            };
            
            string answer;
            answer=check_answer();
            if (answer==questions[i]["answer-index"]){
                cout << "\n\n------------------------------------------------------";
                cout << "\n-                     CORRECT                        -\n";
                cout << "------------------------------------------------------\n\n";
                correct++;
            }
            else{
               
                cout << "\n\n------------------------------------------------------";
                cout << "\n-                   INCORRECT                        -\n";
                cout << "------------------------------------------------------\n\n";
                incorrect++;
            }
            count++;
        };
   
        cout << "\n\n------------------------------------------------------";
        cout << "\n-                   GAME OVER                        -\n";
        cout << "------------------------------------------------------\n\n";
        
        cout << "Correct: " << correct << "\nIncorrect: " << incorrect << "\nCorrect %: " << correct/10*100 << "%\n"; 
        play, count=play_again();
    };
    
   
  return 0;
}