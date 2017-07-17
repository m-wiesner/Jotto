#ifndef MANGUESSER_H
#define MANGUESSER_H
#include <string>
#include "Guesser.h"
#include "Jotto_utils.h"


// Guesser Class
class ManualGuesser : public Guesser
{
    public:
        // Constructors
        ManualGuesser (const std::string&, const std::string&);         
        
        // Setters
        std::string submit_codeword () const;

        // Core
        std::string guess() const; 
    private:
        std::string random_guess() const;
}; 

#endif









