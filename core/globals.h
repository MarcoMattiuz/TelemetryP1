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
}
void setRole(int x);
std::string getRole(Role role);
#endif // GLOBALS_H