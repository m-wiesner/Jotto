Jotto: Jotto.o Jotto_utils.o Guesser.o ManualGuesser.o RandomGuesser.o MaxinfoGuesser.o ScoreKeeper.o
	g++ -o Jotto Jotto.o Jotto_utils.o Guesser.o ManualGuesser.o RandomGuesser.o MaxinfoGuesser.o ScoreKeeper.o

Jotto.o: Jotto.cpp Jotto_utils.h Guesser.h ManualGuesser.h RandomGuesser.h MaxinfoGuesser.h ScoreKeeper.h
	g++ -c Jotto.cpp

ScoreKeeper.o: ScoreKeeper.cpp Guesser.h Jotto_utils.h
	g++ -c ScoreKeeper.cpp 

MaxinfoGuesser.o: MaxinfoGuesser.cpp RandomGuesser.h Guesser.h Jotto_utils.h
	g++ -c MaxinfoGuesser.cpp

RandomGuesser.o: RandomGuesser.cpp Guesser.h Jotto_utils.h
	g++ -c RandomGuesser.cpp

ManualGuesser.o: ManualGuesser.cpp Guesser.h Jotto_utils.h
	g++ -c ManualGuesser.cpp

Guesser.o: Guesser.cpp Jotto_utils.h
	g++ -c Guesser.cpp

Jotto_utils.o: Jotto_utils.cpp
	g++ -c Jotto_utils.cpp

clean: 
	rm Jotto Jotto_utils.o Guesser.o ManualGuesser.o RandomGuesser.o MaxinfoGuesser.o ScoreKeeper.o Jotto.o 
