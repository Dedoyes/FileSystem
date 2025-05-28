#ifndef __GENERAL_HPP
#define __GENERAL_HPP

#include <ctime>
#include <ostream>
#include <vector>
#include "cereal/include/cereal/archives/binary.hpp"
#include "cereal/include/cereal/types/string.hpp"

#define VDISK_START_FILE "virtual_start_disk.bin"
#define VDISK_FILE "virtual_disk.bin"
#define START_DISK_SIZE 10 * 1024 * 1024
#define DATA_DISK_SIZE 10 * 1024 * 1024
#define BLOCK_SIZE 4096
#define MAX_INDEX_NODE_NUM 2560
#define MAX_BLOCK_NUM 2560
#define MAX_MEM_INODE_NUM 1024
#define MAX_USER_NUM 8
#define REGULAR_FILE 0
#define DIRETORY 1
#define SYMBOLIC_LINK 2
#define BLOCK_DEVICE_FILE 3
#define CHARACTER_DEVICE_FILE 4
#define FIFO 5
#define SOCKET 6
#define READ "r"
#define WRITE "w"
#define EXECUTE "x"
#define BLOCK_SIZE 4096
#define LOCK 0
#define CHANGING 1
#define FREE 2

class Time {
private : 
    short year, month, date, hour, minute, second;
public :
    friend std::ostream &operator << (std::ostream &os, const Time &t) { 
        os << t.year << ":" << t.month << ":" << t.date << ":" << t.hour << ":" << t.minute << ":" << t.second;
        return os;
    }
    template <class Archive>
    void serialize (Archive& ar) {
        ar (year, month, date, hour, minute, second);
    }
    Time () {
        std::time_t now = std::time (nullptr);
        std::tm* localTime = std::localtime (&now);
        this->year = localTime->tm_year;
        this->month = localTime->tm_mon;
        this->date = localTime->tm_mday;
        this->hour = localTime->tm_hour;
        this->minute = localTime->tm_min;
        this->second = localTime->tm_sec;
    }
    Time (short _year, short _month, short _date, short _hour, short _minute, short _second) {
        this->year = _year;
        this->month = _month;
        this->date = _date;
        this->hour = _hour;
        this->minute = _minute;
        this->second = _second;
    }
    bool operator < (const Time &t) const {
        if (this->year != t.year) 
            return this->year < t.year;
        if (this->month != t.month) 
            return this->month < t.month;
        if (this->date != t.date) 
            return this->date < t.date;
        if (this->hour != t.hour) 
            return this->hour < t.hour;
        if (this->minute != t.minute)
            return this->minute < t.minute;
        return this->second < t.second;
    }
    bool operator == (const Time &t) const {
        if (this->year != t.year)
            return false;
        if (this->month != t.month) 
            return false;
        if (this->date != t.date) 
            return false;
        if (this->hour != t.hour)
            return false;
        if (this->minute != t.minute)
            return false;
        if (this->second != t.second) 
            return false;
        return true;
    }
    bool operator > (const Time &t) const {
        return t < (*this);
    }
    bool operator != (const Time &t) const {
        return !((*this) == t);
    }
    bool operator >= (const Time &t) const {
        return ((*this) == t) || ((*this) > t);
    }
    bool operator <= (const Time &t) const {
        return ((*this) == t) || ((*this) < t);
    }
};

#endif
