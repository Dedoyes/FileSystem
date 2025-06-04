#ifndef __UTILIZE_HPP
#define __UTILIZE_HPP

#include <iostream>
#include <set>
#include <string>
#include <conio.h>
#include "general.hpp"


void write_block (int block_number, int offset, const void* data);

void read_block (int block_number, int offset, void* buffer, int len);

template <typename T>
size_t estimate_set_memory (const std::set <T> &s);

std::string reguPermission (std::string s);

bool hasRead (std::string s);

bool hasWrite (std::string s);

bool hasExecute (std::string s);

void my_getline(std::string& content);

#endif
