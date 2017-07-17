#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <utility>
#include <cstdlib>
#include <cmath>
#include "Jotto_utils.h"
#include "Guesser.h"
#include "Possibility.h"
#include "JottoVar.h"

using namespace std;

double my_log2(const double&);
bool compare_wordinfos(const pair<const string, double>&, const pair<const string, double>&);
const int Guesser::JOTTO_LENGTH = 5;


Guesser::Guesser (const string& name, const PlayerType& pt, const string& path_to_wordlist) :
    player(name), player_type(pt), guesses(), alphabet(), possibilities()
{
    set_wordlist(path_to_wordlist);
    set_codeword();
}

abd c bacd 3 abde --> ab*(cd' + c'd)*(ef' + e'f)
                        *()
abc d bacd 3           (abc + abd)(ed + ef + df + f)
abf d fabd 3           
abd f fabd 3          
abe f fabe 3
abf e fabe 3



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
        reset_alphabet();
        return 0;
    }
    else
    {
        return 1;
    }
}


void Guesser::set_codeword()
{
    if (player_type == HUMAN)
    {
        cout << "Enter your codeword: ";
        if(cin >> codeword)
        {
            // Check that it is a valid word
            // Check that the word is in the dictionary
            if (find(wordlist.begin(), wordlist.end(), codeword) != wordlist.end())
            {
                return;
            }
            else
            {
                throw invalid_argument("Invalid Codeword: Your codeword is not in the dictionary.");
            }
        }
        else
        {
            cout << "Thanks for playing!" << endl;
            exit(0);
        }
    }
    else
    {
       codeword = random_guess(); 
    }
}


// Set inital alphabet probabilities
void Guesser::reset_alphabet()
{
    // Accumulate unigram char frequencies
    int char_counter = 0;
   
    // Clear alphabet frequencies
    for (map<const char, double>::iterator it = alphabet.begin();
         it != alphabet.end(); ++it)
    {
        it->second = 0;
    }
     
    // Get character counters
    for (list<const string>::const_iterator it_w = wordlist.begin();
         it_w != wordlist.end(); ++it_w)
    {
        for (string::const_iterator it_c = (*it_w).begin();
             it_c != (*it_w).end(); ++it_c)
        {
            alphabet[*it_c] += 1; 
            ++char_counter;
        }
    }

    // Divide each character counter by a scalar (char_counter)
    for (map<const char, double>::iterator it = alphabet.begin();
         it != alphabet.end(); ++it)
    {
        it->second = it->second / char_counter; 
    }
}

// "Set" guesses by adding a new guess
void Guesser::add_guess(const string& word, const int& word_score)
{
    pair<const string, int> guess(word, word_score);
    guesses.push_back(guess);
}


void Guesser::add_possibilities()
{
    // Take last guess and generate all combinations
    vector<string> combs;
    vector<Possibility> new_possibilities;
    string last_guess = guesses.back().first;
    int last_score = guesses.back().second;
    combinations(last_guess, last_score, combs);
   
    // For each combination create the possibility and add it
    // to the new_possibility vector
    for (vector<string>::const_iterator it = combs.begin();
         it != combs.end(); ++it)
    {
        Possibility p_new(*it, last_guess);
        if (!possibilities.empty())
        {
            for (vector<Possibility>::const_iterator itp = possibilities.begin();
                 itp != possibilities.end(); ++itp)
            {
                Possibility prod = (*itp) * p_new;
                if (!prod.empty())
                {
                    new_possibilities.push_back((*itp) * p_new);
                }
            }
        }
        else
        {
            new_possibilities.push_back(p_new);
        }
    }

    // Finally remove any duplicates
    vector<Possibility>::iterator it1 = new_possibilities.begin();
    int i = 0;
    while(it1 != new_possibilities.end())
    {
        vector<Possibility>::iterator it2 = it1 + 1;
        while(it2 != new_possibilities.end())
        {
            if((*it1) == (*it2))
            {
                it1->print();
                it2->print();
                it2 = new_possibilities.erase(it2);
            }
            else
            {
                ++it2;
            }
        }
        ++i;
        it1 = new_possibilities.begin() + i;     
    }
    possibilities = new_possibilities;
}

// Get the player name
string Guesser::get_player() const
{
    return player;
}

string Guesser::get_codeword() const
{
    return codeword;
}

list<const string>::size_type Guesser::get_wordlist_size() const
{
    return wordlist.size();
}


vector<Possibility>::size_type Guesser::get_possibilities_size() const
{
    return possibilities.size();
}


PlayerType Guesser::get_player_type() const
{
    return player_type;
}


// Update all guesser information including remaining possible words,
// Letter probabilities, etc.. 
void Guesser::ai_maxinfo_update()
{
    // Score all words in the dictionary against w and remove
    // all entries that have a different score

    list<const string>::iterator it = wordlist.begin();
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
    list<const string>::const_iterator last_it = find(wordlist.begin(), wordlist.end(), guesses.back().first); 
    if (last_it != wordlist.end())
    {
        wordlist.erase(last_it);
    }
    reset_alphabet();

    if (wordlist.empty())
    {
        cout << "Error: No more possible words in the dictionary." << endl;
        cout << "Either you discovered a bug in the program, or used";
        cout << " an invalid word" << endl;
        exit(1);
    }
}


void Guesser::ai_combo_update()
{
    add_possibilities();
    // Remove duplicate possibilities if possible
}



string Guesser::manual_guess() const
{
    string guess;
    if(cin >> guess)
    {
        // Check that the word is in the dictionary
        if (find(wordlist.begin(), wordlist.end(), guess) != wordlist.end())
        {
            return guess;
        }
        else
        {
            throw invalid_argument("Invalid Guess: Your guess is not in the dictionary.");
        }   
    }
    else
    {
        cout << "Thanks for playing!" << endl;
        exit(0);
    }
}


string Guesser::combo_guess() const
{
    // Choose word randomly from dictionary
    // Udate possibilities
    // When all possibilities are equal eliminate all words from dictionary 
    // that don't match the possibilities 
    if(get_possibilities_size() == 1)
    {
        if(possibilities.begin()->get_count() == 5)
        {
            // Only guess words combatible with the possibility
        }
        else
        {
            // Only guess words with letters we have not yet seen   
        }
    
    }
    return "hello";
}


string Guesser::random_guess() const
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


string Guesser::maxinfo_guess() const
{
    string best_word = random_guess();
   
    int numwords = wordlist.size(); 
    double max_info = 0.0;
     
    // Find the sampling granularity
    double sampling_prob;
    switch(player_type) 
    {
        case HUMAN : sampling_prob = 0.9; break;
        case LEVEL1_AI : sampling_prob = 2*0.25; break;
        case LEVEL2_AI : sampling_prob = 2*0.125; break;
        case LEVEL3_AI : sampling_prob = 2*0.0625; break;
        case LEVEL4_AI : sampling_prob = 2*0.03125; break;
        case LEVEL5_AI : sampling_prob = 2*0.01525; break;
    }
   
    int i = 0;
    for(list<const string>::const_iterator it = wordlist.begin();
        it != wordlist.end(); ++it)
    {
        if ((rand() % numwords) > (numwords * sampling_prob)) 
        {
            double w_info = calc_information(*it);
            if(w_info > max_info)
            {
                max_info = w_info;
                best_word = *it; 
            }
            ++i;
        }
    }
    return best_word;      
}    


double Guesser::calc_information (const string& s) const
{
    double count_of_counts [JOTTO_LENGTH + 1];
    //for w in wordlist
    for (list<const string>::const_iterator it = wordlist.begin();
         it != wordlist.end(); ++it)
    {
        ++count_of_counts[score(s, *it)];
    }
    
    double information = 0.0;
    // Calculate entropy (bits of information)
    for (int i = 0; i < JOTTO_LENGTH + 1; ++i)
    {
        double frac = count_of_counts[i] / wordlist.size();
        information += -1 * frac * my_log2(frac);
    } 
    return information; 
}

/****************** Print functions ***************************/
void Guesser::print_wordlist (int max_rows) const
{
    int num_rows = 0;
    list<const string>::size_type numwords = wordlist.size();

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


void Guesser::print_guesses() const
{
    cout << " -------- Guesses ------ " << player << " ----------------- " << endl;
    for (vector< pair<const string, int> >::const_iterator it = guesses.begin();
         it != guesses.end(); ++it)
    {
        cout << it->first << " :: " << it->second << endl;
    } 
}


void Guesser::print_alphabet () const
{
    cout << " ----------- Possible Letters ----------------- " << endl;
    for (map<const char, double>::const_iterator it = alphabet.begin();
         it != alphabet.end(); ++it)
    {
        if (it->second != 0.0)
        {
            cout << it->first << " :: " << it->second << endl; 
        }
    }
    cout << " ----------------------------------------- " << endl;
}


void Guesser::print_possibilities () const
{
    cout << "=========== Possibilities List ================ " << endl;
    for(vector<Possibility>::const_iterator it = possibilities.begin();
        it != possibilities.end(); ++it)
    {
        (*it).print();
    }
    cout << "=============================================== " << endl;
}

/************************ Helper Functions *******************************/

bool Guesser::compare_words (const string& w) const
{
    // Get last word
    pair<const string, int> last_guess = guesses.back();
    return score(last_guess.first, w) != last_guess.second; 
}

double my_log2(const double& d)
{
    return log(d)/log(2);
}

bool compare_wordinfos(const pair<const string, double> &a, const pair<const string, double> &b)
{
           return a.second > b.second;
}
