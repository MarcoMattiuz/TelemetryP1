// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

enum Role{
    None=0,
    Admin=1,
    Engineer=2,
    Pilot=3
};

namespace glb {
    extern std::string username;
    extern Role role;
    extern const int n_roles;
}

void setRole(int x);
std::string getRoleStr(Role role);
Role getRoleByN(int n);
void logout();

#endif // GLOBALS_H