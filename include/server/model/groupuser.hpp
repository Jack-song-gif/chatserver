#ifndef GROUPUSER_H
#define GROUPUSER_H

#include "user.hpp"


//群组用户，多了一个role角色信息，继承User，复用其他信息
class GroupUser : public User
{
public:
    void setRole(string role) { this->role = role; }
    string getRole() { return this->role; }

private:
    string role;
};
#endif
