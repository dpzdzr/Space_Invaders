#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:
    std::string username;

public:
    User();
    User(std::string username);
    ~User();

    // Accessors
    const std::string &getUsername() const;

    // Modifiers
    void setUsername(const std::string &username);
};

#endif