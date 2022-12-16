#include"User.h"
#include<algorithm>
bool User::operator<(const User& user2)const{
    std::string s1 = this->getUsername();
    std::string s2 = user2.getUsername();

    return std::lexicographical_compare(s1.begin(),s1.end(),s2.begin(),s2.end());
    
    //return username<user2.getUsername();
}
std::string User::toString(){

    std::string res = to_string(this->getType())+" "+this->getUsername()+" "+this->getPassword()+" ";
    return res;
}