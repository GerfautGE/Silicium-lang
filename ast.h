#pragma once
#include <string>

enum class Tag {
    Tfundef,
    Tfuname,
    Tfunargs,
    Tfunboby,
    Tret,
    Tnum,
    Tlistglobdef,
};

static std::string tag_to_string(Tag tag) {
    switch (tag)
    {
    case Tag::Tfundef:
        return std::string("Tfundef");
    case Tag::Tfuname:
        return std::string("Tfuname"); 
    case Tag::Tfunargs:
        return std::string("Tfunargs");   
    case Tag::Tfunboby:
        return std::string("Tfunbody");
    case Tag::Tret:
        return std::string("Tret");
    case Tag::Tnum:
        return std::string("Tnum");
    case Tag::Tlistglobdef:
        return std::string("Tlistglobdef");
    default:
        return std::string("Unknown");
    }

};

