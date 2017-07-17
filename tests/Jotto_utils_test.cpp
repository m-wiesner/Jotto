#include <iostream>
#include <string>
#include <vector>
#include "Jotto_utils.h"


using namespace std;


int main(int argc, char **argv)
{
    string w1, w2;
    string intersection;
    vector<string> combs;
    w1 = argv[1];

    cout << "Enter word: ";
    while(cin >> w2)
    {
        cout << endl;
        intersection = score(w1, w2);
        combinations(w2, intersection.size(), combs);
        cout << "-----------------" << endl;
        for(vector<string>::const_iterator it = combs.begin();
            it != combs.end(); ++it)
        {
            cout << *it << endl;
        }
        cout << "-----------------" << endl;
    }
    return 0;
}
