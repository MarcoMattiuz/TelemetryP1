#include "globals.h"
#include <string>
namespace glb
{std::string username;
Role role = None;}

void setRole(int x){
    switch (x)
    {
    case 1:;
    glb::role=Admin;
        break;
    case 2:
    glb::role=Engineer;
        break;
    case 3:
    glb::role=Pilot;
        break;    
    default:
    glb::role=None;
        break;
    }
}

std::string getRole(Role role){
    std::string ret = "None";
    switch (role)
    {
    case Admin:
    ret = "Admin";
        break;
    case Engineer:
    ret = "Engineer";
        break;
    case Pilot: 
    ret = "Pilot";
        break;    
    default:
    ret = "None";
        break;
    }

    return ret;
}