#include <iostream>
#include <string>
#include "JottoVar.h"

using namespace std;

int main()
{
    cout << "Testing is multiplicable ..." << endl;
    JottoVar j1("j1",1,1);
    JottoVar j2("j2",1,2);
    JottoVar j3("j3",0,1);
    JottoVar j4("j4",2,4);
    JottoVar j5("j5",1,4);
    
    j1.print();
    j2.print();
    j3.print();
    j4.print();
    j5.print();

    cout << "j1 and j2: " << j1.ismultiplicable(j2) << endl;
    cout << "j1 and j3: " << j1.ismultiplicable(j3) << endl;
    cout << "j1 and j4: " << j1.ismultiplicable(j4) << endl;
    cout << "j1 and j5: " << j1.ismultiplicable(j5) << endl;
    cout << "j2 and j3: " << j2.ismultiplicable(j3) << endl;
    cout << "j2 and j4: " << j2.ismultiplicable(j4) << endl;
    cout << "j2 and j5: " << j2.ismultiplicable(j5) << endl;
    cout << "j3 and j4: " << j3.ismultiplicable(j4) << endl;
    cout << "j3 and j5: " << j3.ismultiplicable(j5) << endl;
    cout << "j4 and j5: " << j4.ismultiplicable(j5) << endl;

    (j1 * j2).print();
    (j1 * j3).print();
    (j1 * j4).print();
    (j1 * j5).print();
    (j2 * j3).print();
    (j2 * j4).print();
    (j2 * j5).print();
    (j3 * j4).print();
    (j3 * j5).print();
    (j4 * j5).print();

    return 0;
}
