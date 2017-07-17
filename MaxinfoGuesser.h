#ifndef MAXIGUESSER_H
#define MAXIGUESSER_H
#include <string>
#include "RandomGuesser.h"
#include "Jotto_utils.h"


// Guesser Class
class MaxinfoGuesser : public RandomGuesser
{
    public:
        // Constructors
        MaxinfoGuesser (const std::string&, const std::string&);         
        std::string guess() const;
        std::string submit_codeword() const;
    private: 
        double calc_information (const std::string&) const;

}; 

#endif









