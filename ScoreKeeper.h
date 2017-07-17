#ifndef SKEEPER_H
#define SKEEPER_H
#include <string>
#include <map>
#include "Guesser.h"
#include "MaxinfoGuesser.h"

class ScoreKeeper
{
    public:
        // Constructors 
        ScoreKeeper (Guesser*, Guesser*); 
       
        // Control functions
        std::string solicit_codeword(Guesser*) const;   
        std::string solicit_guess(Guesser*) const; // ask guess to submit a guess
        bool submit_score(const std::string&, Guesser*); // submit score of string to guesser
        bool give_turn_to(Guesser*);
        
        // Print Function
        void print_codewords() const;           
    
    private:
        std::map<std::string, std::string> codewords;
};

#endif
