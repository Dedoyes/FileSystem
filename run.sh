g++ -std=c++17 -I ./cereal/include -c ./storage.cpp
g++ -std=c++17 -I ./cereal/include -c ./utilize.cpp
g++ -std=c++17 -I ./cereal/include -c ./main.cpp
g++ -std=c++17 -I ./cereal/include -c ./command.cpp
g++ -std=c++17 -I ./cereal/include -c ./FileTreePrinter.cpp

g++ storage.o utilize.o command.o FileTreePrinter.o main.o -o ./program

./program
