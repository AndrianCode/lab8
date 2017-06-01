#include "character.h"
#include <string>

character::character(string name, string movie, int id)
{
    this->name = name;
    this->movie = movie;
    this->id = id;
}

string character::get_name() { return name; }

string character::get_movie() { return movie; }

string character::get_id() { return to_string(id); }
