#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Jotto_utils.h"

using std::vector;
using std::string;

void _combinations (const string&, int, string, vector<string>&);


/* ******* FIND ALL CHARACTER COMBINATIONS OF length k *****************
    
    Recursive call to _combinations(...) to find all combinations. 
    
************************************************************************/ 

// Wrapper function for Jotto_utils.h interface (combinations) of _combinations
int combinations (const string& word, int k, vector<string>& combs)
{
    _combinations(word, k, "", combs);
    return 0;
}


void _combinations (const std::string& word, int k, std::string out,
                   std::vector<std::string>& combs)
{
    typedef string::size_type sz;

    if (out.size() == k)
    {
        combs.push_back(out); 
        return;
    }

    for (sz i = 0; i < word.size(); ++i)
    {
        _combinations(word.substr(i + 1, word.size()), k, out + word[i], combs); 
    }
}


/* *************** SCORE WORD 2 AGAINST WORD 1 ********************

    For each letter in the reference try to match it with a letter
    in w. If a match is found, remove that letter and move the the next
    letter in reference
*********************************************************************/ 

int score(string w1, string w2)
{
     
    sort(w1.begin(), w1.end());
    sort(w2.begin(), w2.end());

    string intersection;
    set_intersection(w1.begin(), w1.end(),
                     w2.begin(), w2.end(), back_inserter(intersection));
  
    return intersection.size();
}


