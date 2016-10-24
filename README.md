This is the first homework assignment from PIC 10C.

To compile, type the following command within the project directory:
   g++ -std=c++11 *.h *.cpp
   ./a.out

Known bugs:
The current version has a minor issue with the g++ compiler:
The first time player draws a card, the card won't be added into the 
player's hand for some reason (compiler optimization issue?).
But it runs perfectly in Visual Studio.