#ifndef COMBGUESSER_H
#define COMBGUESSER_H
#include <string>
#include <vector>
#include "Jotto_utils.h"
#include "Possibility.h"
#include "JottoVar.h"



// Guesser Class
class ComboGuesser : public Guesser
{
    public:
        // Constructors
        ComboGuesser (const std::string&, const std::string&);         
      
        // Getters
        std::vector<Possibility>::size_type get_possibilities_size() const;
        
        // Setters
        void add_possibilities ();

        // Core
        std::string guess() const; 
        void update();
        
        // Print Functions
        void print_possibilities() const;
    private:
        // Members 
        std::vector<Possibility> possibilities; // List of letter possibilities
                                                // and associates probs
}; 

#endif









