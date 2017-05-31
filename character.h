/** @file
 * @brief Contains data about "My favorite actor"
*/

#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
using namespace std;

class character
{
    int id;
    string name;
    string movie;
public:
    character(string name, string movie, int id);
    /**
     * @brief get_name - gets name
     * @return name
     */
    string get_name();
    /**
     * @brief get_movie - gets movie
     * @return movie
     */
    string get_movie();
    /**
     * @brief get_id - gets id
     * @return id
     */
    string get_id();
};

#endif // CHARACTER_H
