@echo off
:: 编译 .cpp 文件
g++ -std=c++17 -I ./cereal/include -c storage.cpp
g++ -std=c++17 -I ./cereal/include -c utilize.cpp
g++ -std=c++17 -I ./cereal/include -c main.cpp
g++ -std=c++17 -I ./cereal/include -c FileTreePrinter.cpp
:: 链接生成可执行文件 program.exe
g++ storage.o utilize.o main.o FileTreePrinter.o -o program.exe

:: 运行可执行文件
program.exe

pause
