#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
#include "Jotto_utils.h"
#include "Guesser.h"
#include "ManualGuesser.h"
#include "RandomGuesser.h"
#include "MaxinfoGuesser.h"
#include "ScoreKeeper.h"

using namespace std;

void clear_screen(int nr);
void print_intro();
void print_level();


int main(int argc, char** argv)
{
    string path_to_dict = "./text_files/wordlist.txt";
    char read_rules;
    char play_to_end;
    int level;
    cout << "========================================";
    cout << "========================================" << endl;
    cout << "                                !!  JOTTO  !!";
    cout << "                                " << endl;
    cout << "========================================";
    cout << "========================================" << endl;

    cout << "Do you want to read the rules? (y)/(n)";
    do
    {   if (!(cin >> read_rules))
        {
            exit (0);
        }
    } while ((read_rules != 'y' && read_rules != 'n') && (cout << "Enter (y) or (n)."));
    
    if (read_rules == 'y')
    {
        print_intro();      
    }



    cout << endl << endl << endl;
    cout << "========================================";
    cout << "========================================" << endl;
    cout << "                                !! START GAME !!";
    cout << "                                " << endl;
    

    print_level();
    do
    {
        if(!(cin >> level))
        {
            exit(0);
        }
        cout << "LEVEL: " << level << endl;
    } while (((level != 1) && (level != 2) && (level !=3)) && (cout << "Enter a level (1-3)"));
    


    // Default names
    string name1 = "AI1";
    string name2 = "AI2";

    srand((int)time(0));
    Guesser *g1;
    Guesser *g2;
  
    g1 = new ManualGuesser(name1, path_to_dict); 
    //switch (level)
    //{
    //    case 0: cout << "Enter your name: ";
    //            cin >> name1;
    //            g1 = new ManualGuesser(name1, path_to_dict);
    //            break;
    //    case 1: g1 = new Guesser(name1, path_to_dict); break;
    //    case 2: g1 = new RandomGuesser(name1, path_to_dict); break;
    //    case 3: g1 = new MaxinfoGuesser(name1, path_to_dict); break;
    //}

    switch (level)
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
  
    clear_screen(3); 
   
    int turnnumber = 1; 
    cout << " ========= Turn " << turnnumber << " ============== " << endl;
    while (sk.give_turn_to(g1) && sk.give_turn_to(g2))
    {
        clear_screen(3);
        cout << " ========= Turn " << turnnumber << " ============== " << endl;
        g1->update();
        g2->update();
        ++turnnumber;
    }

    cout << "Do you want to keep guessing? (y)/(n)";
    do
    {   if(!(cin >> play_to_end))
        {
            cout << "Codeword were ..." << endl;
            sk.print_codewords();
            exit(0);
        }
    } while ((play_to_end != 'y' && play_to_end != 'n') && (cout << "Enter (y) or (n)."));
    
    if (play_to_end == 'y')
    {
        while(sk.give_turn_to(g1))
        {
            clear_screen(3);
            cout << " ========= Turn " << turnnumber << " ============== " << endl;
            g1->update();
            ++turnnumber;
        }
    } 
    else
    {
        cout << "Codewords were ..." << endl;
        sk.print_codewords();
    } 
    delete g1;
    delete g2;
    return 0;
}


void clear_screen(int nr)
{
    for (int i = 0; i < nr; ++i)
    {
        cout << endl;
    }
}


void print_intro()
{
    vector<string> lines;
    string line;
    ifstream infile("./text_files/jotto_intro.txt");
    if(infile.is_open())
    {
        while(getline(infile, line))
        {
            lines.push_back(line);
        }
    }

    infile.close();
    cin.ignore();
    for(vector<string>::const_iterator it = lines.begin();
        it != lines.end() - MAX_MENU_ROWS; ++it)
    {
        cout << "\r";
        clear_screen(MAX_MENU_ROWS);

        cout << "________________________________________";
        cout << "________________________________________" << endl;  
        int i = 0;
        vector<string>::const_iterator it2 = it;
        while (i < MAX_MENU_ROWS)
        {
            cout << *it2 << endl; 
            ++it2;
            ++i;
        }
        cout << "__________ Press (Enter) for next row ________" << flush;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(!(cin))
        {
            cout << endl;
            cout << "Thanks for reading the rules!" << endl;
            exit (0);
        }
    }
}


void print_level()
{
    cout << "----------------------------------------";
    cout << "----------------------------------------" << endl;
    cout << "1 -- Random Guessing from dictionary." << endl;
    cout << "2 -- Random guessing removing impossible words"
         << endl <<  "     from the dictionary" << endl;
    cout << "3 -- Guessing word with maximum information from"
         << endl << "      the dictionary with impossible words removed." << endl;
    cout << "________________________________________";
    cout << "________________________________________" << endl;
 
    cout << "Choose the level (strategy) against which you wish to play: ";
}
