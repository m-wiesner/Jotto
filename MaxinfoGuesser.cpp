#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <cstdlib>
#include <cmath>
#include "Jotto_utils.h"
#include "RandomGuesser.h"
#include "MaxinfoGuesser.h"


using namespace std;

double my_log2(const double&);


MaxinfoGuesser::MaxinfoGuesser (const string& name, const string& path_to_wordlist) :
    RandomGuesser(name, path_to_wordlist) {}


string MaxinfoGuesser::submit_codeword() const
{
    return RandomGuesser::guess();
}



string MaxinfoGuesser::guess() const
{
    string best_word = RandomGuesser::guess();
   
    int numwords = get_wordlist_size();
    double max_info = 0.0;
     
    int i = 0;
    for(list<string>::const_iterator it = wordlist.begin();
        it != wordlist.end(); ++it)
    {
        if ((rand() % numwords) < (numwords * SAMPLING_PROB)) 
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


double MaxinfoGuesser::calc_information (const string& s) const
{
    double count_of_counts [JOTTO_LENGTH + 1];
    //for w in wordlist
    for (list<string>::const_iterator it = wordlist.begin();
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


double my_log2(const double& d)
{
    return log(d)/log(2);
}

