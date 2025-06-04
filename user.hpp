#ifndef __USER_HPP
#define __USER_HPP

#include <iostream>
#include <string>
#include "./cereal/include/cereal/archives/binary.hpp"
#include "./cereal/include/cereal/types/string.hpp"
#include "general.hpp"

class User {
private :
    short userId;
    std::string name;
    std::string password;
public :
    template <class Archive> 
    void serialize (Archive& ar) {
        ar (userId, name, password);
    }
    User () {
        this->userId = 0;
        this->name = "";
        this->password = "";
    }
    User (short _userId, std::string _name, std::string _password) {
        this->userId = _userId;
        this->name = _name;
        this->password = _password;
    }
    void changeName (std::string newName) {
        this->name = newName;
    }
    void changePassword (std::string newPassword) {
        std::string temp;
        std::cout << "please input former password : " << std::endl;
        std::cin >> temp;
        if (temp == this->password) {
            this->password = newPassword;
            std::cout << "Success : new password is " << newPassword << std::endl;
        } else {
            std::cout << "Warning : password wrong." << std::endl;
        }
    }
    inline std::string getName () {
        return this->name; 
    }
    inline std::string getPassword () {
        return this->password;
    }
    inline short getUserId () {
        return this->userId;
    }
};

extern short currentUserId;

class UserCluster {
public :
    short userNum;
    std::vector <User> user;  // MAX_USER_NUM
    template <class Archive>
    void serialize (Archive& ar) {
        ar (userNum, user);
    }
    UserCluster () {
        userNum = 0;
        user.resize (MAX_USER_NUM);
    }
    void addNewUser (std::string name, std::string password) {
        if (userNum == MAX_USER_NUM) {
            std::cout << "Warning : user number is max." << std::endl;
            return;
        }
        user[userNum] = User (userNum, name, password);
        currentUserId = userNum;
        userNum++;
    }
};

#endif
