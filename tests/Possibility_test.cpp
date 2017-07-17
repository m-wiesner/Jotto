#include <iostream>
#include <string>
#include "Possibility.h"
#include "JottoVar.h"

using namespace std;

int main()
{
    string comb, word;
    cout << "Enter possibilty: ";
    cin >> comb >> word;
    Possibility p1(comb, word);

    cout << "Enter another possibility: ";
    while(cin >> comb >> word)
    {
        Possibility p2(comb, word);
        cout << endl;
        cout << endl;
        //(p1 * p2).print();
        if (p1 == p2)
        {
            cout << "EQUAL" << endl;
        }
        else
        {
            cout << "NOT EQUAL" << endl;
        }
        cout << endl;
        cout << endl;
        cout << "Enter another possibility: ";
    }
    cout << endl;
    return 0;
}
