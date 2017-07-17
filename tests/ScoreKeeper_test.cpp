#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Guesser.h"
#include "ManualGuesser.h"
#include "RandomGuesser.h"
#include "MaxinfoGuesser.h"
#include "ScoreKeeper.h"

using namespace std;

void clear_screen();

int main(int argc, char** argv)
{
    string path_to_dict = "wordlist.txt";
    
    // Default names
    string name1 = "AI1";
    string name2 = "AI2";

    srand((int)time(0));
    Guesser *g1;
    Guesser *g2;
   
    switch(stoi(argv[1]))
    {
        case 0: cout << "Enter your name: ";
                cin >> name1;
                g1 = new ManualGuesser(name1, path_to_dict);
                break;
        case 1: g1 = new Guesser(name1, path_to_dict); break;
        case 2: g1 = new RandomGuesser(name1, path_to_dict); break;
        case 3: g1 = new MaxinfoGuesser(name1, path_to_dict); break;
    }

    switch(stoi(argv[2]))
    {
        case 0: cout << "Enter your name: ";
                cin >> name1;
                g2 = new ManualGuesser(name1, path_to_dict);
                break;
        case 1: g2 = new Guesser(name2, path_to_dict); break;
        case 2: g2 = new RandomGuesser(name2, path_to_dict); break;
        case 3: g2 = new MaxinfoGuesser(name2, path_to_dict); break;
    }

    ScoreKeeper sk(g1, g2);
  
    clear_screen(); 
   
    int turnnumber = 1; 
    clear_screen();
    cout << " ========= Turn " << turnnumber << " ============== " << endl;
    while(sk.give_turn_to(g1) && sk.give_turn_to(g2))
    {
        clear_screen();
        cout << " ========= Turn " << turnnumber << " ============== " << endl;
        g1->update();
        g2->update();
        ++turnnumber;
    }
    
    delete g1;
    delete g2;
    return 0;
}


void clear_screen()
{
    for (int i = 0; i < 3; ++i)
    {
        cout << endl;
    }
}
