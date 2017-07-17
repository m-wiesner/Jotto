#ifndef RANDGUESSER_H
#define RANDGUESSER_H
#include <string>
#include "Guesser.h"
#include "Jotto_utils.h"


// Guesser Class
class RandomGuesser : public Guesser
{
    public:
        // Constructors
        RandomGuesser (const std::string&, const std::string&);         
        void update();  
    protected:
        bool compare_words(const std::string&) const;
}; 
                
#endif









