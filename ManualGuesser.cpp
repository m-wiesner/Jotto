#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include "Guesser.h"
#include "ManualGuesser.h"
#include "Jotto_utils.h"

using namespace std;

ManualGuesser::ManualGuesser (const string& name, const string& path_to_wordlist) :
    Guesser(name, path_to_wordlist) {}


/*****************  Setters *********************/
string ManualGuesser::submit_codeword() const
{
    cout << "Enter your codeword: ";
    return random_guess();
}


string ManualGuesser::guess() const
{
    cout << "Enter guess: ";
    string g = random_guess(); 
    cout << "\r";
    return g;
}


/*************** Actions *****************/
string ManualGuesser::random_guess() const
{
    string guess;
    do
    {
        if(cin >> guess)
        {
            if (find(wordlist.begin(), wordlist.end(), guess) == wordlist.end())
            {
                cout << "Bad Input: That word is not in the dictionary." << endl; 
                cout << "Enter a different word: ";
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << "\rThanks for playing!" << endl;
            exit(0);
        }
    }while (true);

    return guess;
}
