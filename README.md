JOTTO
===============================================================================
Jotto is a code breaking game played between two players.

Each player picks a secret code word from the provided dictionary that the
other player must try to guess. Every word in the dictionary is a lower-case
5-letter word in the English language, though some are somewhat obsure. 
 
Players alternate taking turns guessing words from the dictionary until one has
correctly identified his oppenent's word. After each guess the player is told
how many of the letters in his word appeared in his oppent's secret word.

Examples:
_______________________________________________________________________________
Player1 has secret word "hello"
Player2 guesses the word "world"

      w : Absent from hello   0
      o : Present in hello  + 1 
      r : Absent from hello + 0
      l : Present in hello  + 1
      d : Absent from hello + 0
      --------------------------
                              2
      world scores 2
_______________________________________________________________________________

_______________________________________________________________________________
Player1 has secret word "hello"
Player2 guesses the word "skill"

      s : Absent from hello         0
      k : Absent from hello       + 0
      i : Absent from hello       + 0
      l : Present in hello        + 1
      l : Present again in hello  + 1
      --------------------------------
                                    2
      skill scores 2
____________________________________________________________

INSTALLATION 
===============================================================================
After cloning the repo, just type in the terminal.

   make

To "uninstall" type 

  make clean


RULES
===============================================================================

1. At the beginning of the game when promted, enter a valid 5 letter word to be
   your codeword.

2. On your turn when prompted, enter a valid 5 letter word in all lower case
   letters.


FUTURE WORK
===============================================================================
1. Language Fluency

  a. LM for AI generated guesses and codeword
    Many of the words in the dictionary I provided are somewhat obscure. I would
    like to give them weights according to their unigram frequencies in other
    text corpora and use these to assign probabilities of picking words, either
    guesses or codewords. I might disallow infrequent words all together since
    it seems unfair for the computer to have access to all such words.

  b. Language Fluence for Different AI Levels
    I could also use a convex combination of unigram language model (LM) scores
    with a score based on maximum information in order to decide the optimal
    guess. The "dumber" AI will pick with a higher LM score and the best AI will
    ignore the LM completely.

  c. Language Fluency for Final Guess
    The LM might also be useful in guessing the final word once 4 or all letters
    are known, as it seems more likely for people to pick common words than
    obscure ones.


2. Human-like Guess Generator 

I am also almost done with a more human-like approach to guessing words which
involves looking at valid combinations of letters given certain guesses, but
there are some final bits of logic for generating new guesses that I need to
work out and program.


3. Machine Aided Guessing

I would like to add a few features that allows the user to view candidate words
from the word list given certain criteria, as well as to automatically view the
potential valid letter combinations for each guess. This will require more of
an event based program.


4. GUI
I would like to make a basic GUI for the user. The terminal version of the
game is fine for now, but it would be nice to have something more natural.



