#ifndef SKILLS_HPP
#define SKILLS_HPP

#include <string>

class Skill {
    public:
        std::string name;
        std::string description;
        void use(character& user, character& target){};
};


#endif