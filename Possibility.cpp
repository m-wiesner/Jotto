#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "JottoVar.h"
#include "Possibility.h"


using namespace std;


const int Possibility::JOTTO_LENGTH = 5; 


Possibility::Possibility (const string& comb, const string& word)
{
    map<const char, int> char_counts;
    map<const char, int> char_count_comb;

    // Get char counts for word
    for (string::const_iterator it = word.begin();
         it != word.end(); ++it)
    {
        ++char_counts[*it];
    }
    
    // Get char counts for comb and create JottoVar objects
    for (map<const char, int>::const_iterator it = char_counts.begin();
         it != char_counts.end(); ++it)
    {
        int max_size = JOTTO_LENGTH;
        char_count_comb[it->first] = count(comb.begin(), comb.end(), it->first);
        if (char_count_comb[it->first] < char_counts[it->first])
        {
            max_size = char_count_comb[it->first]; 
        }
        JottoVar j(string(1, it->first), char_count_comb[it->first], max_size);
        vars[it->first] = j;
    }
   
    int count = get_count(); 
    // Fix max counts
    for (map<const char, JottoVar>::iterator it = vars.begin();
         it != vars.end(); ++it)
    {
        (it->second).max_size = min((it->second).count + (JOTTO_LENGTH - count),
                                    (it->second).max_size); 
    } 
}


Possibility::Possibility (const map<const char, JottoVar>& m)
{
    for(map<const char, JottoVar>::const_iterator it = m.begin();
        it != m.end(); ++it)
    {
        vars[it->first] = it->second;
    }
}


int Possibility::get_count() const
{
    int total_count = 0;
    for(map<const char, JottoVar>::const_iterator it = vars.begin();
        it != vars.end(); ++it)
    {
        total_count += (it->second).count;
    }
    return total_count; 
}



Possibility Possibility::operator* (const Possibility& p) const
{
    int count = 0; 
    map<const char, JottoVar> p_map;
    Possibility pFalse("", "");


    // I actually do need a copy of all the keys
    string keys;
    for (map<const char, JottoVar>::const_iterator it = p.vars.begin();
        it != p.vars.end(); ++it)
    {
        keys += it->first;
    }


    // For each var check that it is multiplicable
    for(map<const char, JottoVar>::const_iterator it = vars.begin();
        it != vars.end(); ++it)
    {
        // If the var exists in both possibilities check
        // var compatibility and update total count
        map<const char, JottoVar>::const_iterator itp = p.vars.find(it->first);
        if ( itp != p.vars.end())  
        {
            // Remove the found key from keys
            keys.erase(remove(keys.begin(), keys.end(), itp->first), keys.end());
            if (!((it->second).ismultiplicable(itp->second)))
            {
                return pFalse;
            }
            
            count += max((it->second).count, (itp->second).count);
            p_map[it->first] = it->second * itp->second; 
            if (count > JOTTO_LENGTH)
            {
                return pFalse;
            }
        }
        else
        {
            count += (it->second).count;
            p_map[it->first] = it->second; 
            if (count > JOTTO_LENGTH)
            {
                return pFalse;
            }
        }
    }

    // For all remaining keys add their counts
    for(string::const_iterator it = keys.begin();
        it != keys.end(); ++it)
    {
        map<const char, JottoVar>::const_iterator itp = p.vars.find(*it);
        count += (itp->second).count;
        p_map[*it] = itp->second; 
        if (count > JOTTO_LENGTH)
        {
            return pFalse;
        }
    }
    
    // Adjust max_size to account for max number of counts  
    for (map<const char, JottoVar>::iterator it = p_map.begin();
         it != p_map.end(); ++it)
    {
        (it->second).max_size = min((it->second).count + (JOTTO_LENGTH - count),
                                    (it->second).max_size); 
    } 
        
    
    Possibility pTrue(p_map);
    return pTrue;
}        
        

bool Possibility::operator== (const Possibility& p) const
{
    for(map<const char, JottoVar>::const_iterator it = vars.begin();
        it != vars.end(); ++it)
    {
        map<const char, JottoVar>::const_iterator itp = p.vars.find(it->first);
        if (itp == p.vars.end())
        {
            return false;
        }
        
        if (!(itp->second == it->second))
        {
            return false;
        }
    }
    return true;
}


bool Possibility::empty() const
{
    return vars.empty();
}


void Possibility::print() const
{
    // Print something
    cout << " -------------- Possibility --------------- " << endl;
    for(map<const char, JottoVar>::const_iterator it = vars.begin();
        it != vars.end(); ++it)
    {
        if ((it->second).max_size != 0)
        {
            (it->second).print();
        }
    }
    cout << " ------------------------------------------ " << endl;
}

