#ifndef JVAR_H
#define JVAR_H
#include <string>

class Possibility;

// Jotto Variable Class
class JottoVar
{
    public:
        // Constructors
        JottoVar ();
        JottoVar (const std::string&, const int&, const int& max_size=JOTTO_LENGTH); 
        JottoVar (const JottoVar&);
                 
        JottoVar operator*(const JottoVar&) const;
        bool operator==(const JottoVar&) const;
         
        bool ismultiplicable(const JottoVar&) const;
        void print() const;
        friend class Possibility;

    private:
        // Constants
        static const int JOTTO_LENGTH; 
        
        // Members
        std::string name; 
        int max_size;
        int count;
}; 


#endif

