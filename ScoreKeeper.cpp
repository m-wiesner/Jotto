#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "Jotto_utils.h"
#include "Guesser.h"
#include "ScoreKeeper.h"

using namespace std;


/********************** CONSTRUCTORS ************************/
ScoreKeeper::ScoreKeeper(Guesser *g1, Guesser *g2)
{
    string n1 = g1->get_player();
    string n2 = g2->get_player();
    
    codewords[n1] = solicit_codeword(g2); // get codeword g1 tries to guess
    codewords[n2] = solicit_codeword(g1); // get codeword g2 tries to guess
}


/***************** Actions ********************/
bool ScoreKeeper::give_turn_to(Guesser *g)
{
    cout << "---------- Turn: " << g->get_player() << " -----------" << endl;  
    return submit_score(solicit_guess(g), g);
}


string ScoreKeeper::solicit_codeword(Guesser *g) const
{
    return g->submit_codeword();    
}


string ScoreKeeper::solicit_guess(Guesser *g) const // ask guesser to submit a guess
{
    return g->guess();
}


bool ScoreKeeper::submit_score (const string& guess, Guesser *g)// submit score of string to guesser
{
    if (codewords[g->get_player()] == guess)
    {
        cout << endl;
        cout << "!!! " << g->get_player() << " GUESSED " << guess;
        cout << " AND WON !!!" << endl;
        return false;
    }
     
    int s = score(guess, codewords[g->get_player()]); 
    g->add_guess(guess, s);
    g->print_guesses();
    return true;
}

/******************* Print *******************/
void ScoreKeeper::print_codewords () const
{
    for (map<string, string>::const_iterator it = codewords.begin();
         it != codewords.end(); ++it)
    {
        cout << it->first << "  ::  " << it->second << endl;
    }
}

