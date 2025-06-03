#ifndef __UTILIZE_HPP
#define __UTILIZE_HPP

#include <iostream>
#include <set>
#include <string>
#include "general.hpp"

void write_block (int block_number, const void* data);

void read_block (int block_number, void* buffer);

template <typename T>
size_t estimate_set_memory (const std::set <T> &s);

std::string reguPermission (std::string s);

bool hasRead (std::string s);

bool hasWrite (std::string s);

bool hasExecute (std::string s);

#endif
