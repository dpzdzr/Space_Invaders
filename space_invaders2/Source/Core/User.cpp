#include "User.h"

User::User()
{
}

User::User(std::string username)
{
}

User::~User()
{
}

const std::string &User::getUsername() const
{
    return username;
}

void User::setUsername(const std::string &username)
{
    this->username = username;
}
