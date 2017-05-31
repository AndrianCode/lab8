/** @file
 * @brief Parses different data to json format
*/

#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <iostream>
#include "character.h"
#include <vector>
using namespace std;

class JsonParser
{
public:
    JsonParser();
    /**
     * @brief main_data_tojson - parses data to json format
     * @param title - value to parse
     * @param dev - value to parse
     * @param time - valuse to parse
     * @return json string
     */
    string main_data_tojson(string title, string dev, string time);
    /**
     * @brief objects_data_tojson - parses data to json format
     * @param chrs - list of characters to parse
     * @return json string
     */
    string objects_data_tojson(vector<character> chrs);
    /**
     * @brief key_obj_tojson - parses data by the key
     * @param chrs - list of characters to parse
     * @param key - key by which to parse
     * @param val - value of the key
     * @return json string
     */
    string key_obj_tojson(vector<character> chrs, string key, string val);
    /**
     * @brief id_obj_tojson - parses data by od
     * @param chrs - list of characters to parse
     * @param id - id by which to parse
     * @return json string
     */
    string id_obj_tojson(vector<character> chrs, string id);
    /**
     * @brief file_data_tojson - parses list of int values
     * @param data - list of integers to parse
     * @return json string
     */
    string file_data_tojson(vector<int> data);
};

#endif // JSONPARSER_H
