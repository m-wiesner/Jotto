#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include "Jotto_utils.h"
#include "Guesser.h"
#include "RandomGuesser.h"


using namespace std;

RandomGuesser::RandomGuesser (const string& name, const string& path_to_wordlist) :
    Guesser(name, path_to_wordlist) {}


/*************** Actions ****************/
void RandomGuesser::update()
{
    // Score all words in the dictionary against w and remove
    // all entries that have a different score
    list<string>::iterator it = wordlist.begin();
    while (it != wordlist.end())
    {
        if (compare_words(*it))
        {
            it = wordlist.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
    // Takes care of removing words that are only permuations of letters
    list<string>::const_iterator last_it = find(wordlist.begin(), wordlist.end(), guesses.back().first); 
    if (last_it != wordlist.end())
    {
        wordlist.erase(last_it);
    }

    if (wordlist.empty())
    {
        cout << "Error: No more possible words in the dictionary." << endl;
        cout << "Either you discovered a bug in the program, or used";
        cout << " an invalid word" << endl;
        exit(1);
    }
}


/************************ Helper Functions *******************************/
bool RandomGuesser::compare_words (const string& w) const
{
    // Get last word
    pair<string, int> last_guess = guesses.back();
    return score(last_guess.first, w) != last_guess.second; 
}

