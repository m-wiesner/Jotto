#include <iostream>
#include <string>
#include <exception>
#include "Jotto_utils.h"
#include "Guesser.h"
#include "ManualGuesser.h"
#include "RandomGuesser.h"
#include "MaxinfoGuesser.h"

using namespace std;

void print_spaces(int);

int main(int argc, char** argv)
{
    int new_score;
    Guesser *g = new MaxinfoGuesser("AI", "./wordlist.txt"); 

    string codeword = g->submit_codeword();
    cout << "Codeword: " << codeword << endl;
    string guess = g->guess(); 
    cout << "Score " << guess << ": ";
    
    while(cin >> new_score)
    {
        g->add_guess(guess, new_score);
        g->update();
        g->print_wordlist();
        g->print_guesses();
        guess = g->guess();
        cout << "Score " << guess << ": ";
    }
    cout << endl;
    delete g;
    return 0;
}

void print_spaces(int n)
{
    for(int i = 0; i < n; ++i)
    {
        cout << endl;
    }
}
