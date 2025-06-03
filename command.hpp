#ifndef __COMMAND_HPP
#define __COMMAND_HPP

#include <string>

void formatDisk (std::string diskName);

void login (std::string userName, std::string password);

void logout (void);

void create (std::string fileName);

void ls (void);

void mkdir (std::string dirName, bool general);

void cd (std::string dirName);

void open (std::string fileName);

void close (std::string fileName);

void lopen (void);

#endif
