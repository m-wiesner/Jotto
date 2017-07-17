#ifndef JottoUtils_H
#define JottoUtils_H
#include <string>
#include <vector>

// Find all character combinations of length k
int combinations (const std::string&, int, std::vector<std::string>& combs);

// Score w1 against w2
int score (std::string, std::string);

static const int JOTTO_LENGTH = 5; 
static const double SAMPLING_PROB = 0.3;
static const int WINDOW_LENGTH = 60;
static const int MAX_MENU_ROWS = 10;

#endif

