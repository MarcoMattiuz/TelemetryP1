#include "globals.h"
#include <string>
namespace glb
{
std::string username;
Role role = None;
const int n_roles = 4;}

void logout(){
    glb::role = None;
    glb::username.clear();
   
}

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

std::string getRoleStr(Role role){
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


Role getRoleByN(int n){
    Role rl=None;

    switch (n)
    {
    case 1:;
    rl=Admin;
        break;
    case 2:
    rl=Engineer;
        break;
    case 3:
    rl=Pilot;
        break;    
    default:
    rl=None;
        break;
    }

    return rl;
}