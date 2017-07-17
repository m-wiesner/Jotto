#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <cassert>
#include <cstdlib>
#include "Guesser.h"
#include "Jotto_utils.h"

using namespace std;


/****************** Constructor ********************/
Guesser::Guesser (const string& name, const string& path_to_wordlist) :
    player(name), guesses()
{
    set_wordlist(path_to_wordlist);
}



/*****************  Setters *********************/
// Set wordlist from path to dictionary
int Guesser::set_wordlist(const string& path_to_wordlist)
{
    ifstream infile(path_to_wordlist);
    string line;

    if (infile.is_open())
    {
        while(getline(infile, line))
        {
            assert(line.size() == JOTTO_LENGTH);
            wordlist.push_back(line);
        }
        infile.close();
        return 0;
    }
    else
    {
        return 1;
    }
}

// Set Codeword
string Guesser::submit_codeword() const
{
    // Submit a random codeword
    return guess(); 
}


// "Set" guesses by adding a new guess
void Guesser::add_guess(const string& word, const int& word_score)
{
    pair<const string, int> g(word, word_score);
    guesses.push_back(g);
}


/***************** Getters ************************/
// Get the player name
string Guesser::get_player() const
{
    return player;
}


// Get wordlist size
list<const string>::size_type Guesser::get_wordlist_size() const
{
    return wordlist.size();
}


/************** Actions *******************/
string Guesser::guess() const
{
    int numwords = wordlist.size(); 
    
    // Random word
    list<const string>::const_iterator itr = wordlist.begin();
    int stop = rand() % numwords;
    for(int i = 0; i < stop; ++i)
    {
        ++itr; 
    }

    return *itr;
}


void Guesser::update() {}

/***************** Print Functions ******************/
// Print wordlist
void Guesser::print_wordlist (int max_rows) const
{
    int num_rows = 0;
    list<const string>::size_type numwords = get_wordlist_size();

    // Print first max_rows number of words  
    cout << " --------------------------------------- " << endl;
    for (list<const string>::const_iterator it = wordlist.begin();
         (it != wordlist.end()) && (num_rows < max_rows); ++it)
    {
        cout << *it << endl;
        ++num_rows;
    }


    // Print last max_rows number of words
    if ((int)numwords > 2 * max_rows)
    {
        cout << "..." << endl;
        cout << "... " << numwords << " words ..." << endl;
        cout << "..." << endl; 
    }
}


// Print guesses
void Guesser::print_guesses() const
{
    cout << " -------- Guesses ------ " << player << " ----------------- " << endl;
    for (vector< pair<const string, int> >::const_iterator it = guesses.begin();
         it != guesses.end(); ++it)
    {
        cout << it->first << " :: " << it->second << endl;
    } 
}


