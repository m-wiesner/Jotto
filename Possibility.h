#ifndef POSS_H
#define POSS_H
#include <iostream>
#include <string>
#include <map>
#include "JottoVar.h"


// Guesser Class
class Possibility {
    public:
        // Constructors
        Possibility (const std::string&, const std::string&);         
        Possibility (const std::map<const char, JottoVar>&); 
        
        Possibility operator* (const Possibility&) const;
        bool operator== (const Possibility&) const;
                
        int get_count() const;
                
        bool empty() const;
        
        void print() const;
    private:
        // Members 
        static const int JOTTO_LENGTH; 
        std::map<const char, JottoVar> vars;
        
}; 


#endif

