#include <iostream>
#include <string>
#include <algorithm>
#include "JottoVar.h"

using namespace std;


const int JottoVar::JOTTO_LENGTH = 5; 

JottoVar::JottoVar ()
{
    name = "";
    count = 0;
    max_size = JOTTO_LENGTH;
}


JottoVar::JottoVar (const string& name, const int& count, const int& max_size) :
    name(name), count(count), max_size(max_size){}


JottoVar::JottoVar (const JottoVar& j)
{
    name = j.name;
    count = j.count;
    max_size = j.max_size;
}


JottoVar JottoVar::operator* (const JottoVar& j) const
{
    string new_name = ((name == j.name) ? name : name + j.name);
    if (ismultiplicable(j))
    {
        return JottoVar(new_name, max(count, j.count), min(max_size, j.max_size)); 
    }
    else
    {
        return JottoVar(new_name, 0, 0);
    }
} 


bool JottoVar::operator== (const JottoVar& j) const
{
    return (name == j.name) && (count == j.count) && (max_size == j.max_size);
}


bool JottoVar::ismultiplicable (const JottoVar& j) const
{
    // Count must be less than maxsize
    return (j.count <= max_size) && (count <= j.max_size);
}

void JottoVar::print () const
{
    cout << "JottoVar : " << name << " --- ";
    cout << "Count: " << count;
    cout << " --- Max Size: " << max_size << " ---- " << endl;
}

