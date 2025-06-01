g++ -std=c++17 -I ./cereal/include -c ./storage.cpp
g++ -std=c++17 -I ./cereal/include -c ./utilize.cpp
g++ -std=c++17 -I ./cereal/include -c ./main.cpp
g++ storage.o utilize.o main.o -o ./program
./program
