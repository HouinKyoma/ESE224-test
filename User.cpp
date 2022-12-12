#include"User.h"
bool User::operator<(const User& user2)const{
    return username<user2.getUsername();
}