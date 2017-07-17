#ifndef GUESSER_H
#define GUESSER_H
#include <string>
#include <vector>
#include <utility>
#include <list>
#include "Jotto_utils.h"


// Guesser Class
class Guesser {
    public:
        // Constructors
        Guesser (const std::string&, const std::string&);         
      
        // Getters
        std::string get_player() const;
        std::list<std::string>::size_type get_wordlist_size() const;
        
        // Setters
        int set_wordlist (const std::string&);

        // Core
        virtual std::string guess() const;
        virtual std::string submit_codeword () const;
        virtual void update();
        
        void add_guess (const std::string&, const int&);
        
        // Print Functions
        void print_guesses() const;
        void print_wordlist(int maxrows = 10) const;
    protected:
        // Members 
        std::string player;
        std::vector< std::pair<std::string, int> > guesses; // List of guesses and scores
        std::list<std::string> wordlist; // List of candidate words
}; 

#endif


