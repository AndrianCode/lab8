/** @file
 * @brief Describes a server
*/

#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include "character.h"
#include <vector>
using namespace std;

class Server
{
public:
    Server(int serverPort);
    /**
     * @brief determine_data - processes requests
     * @param mes - get request
     * @return message that will be sent to the client
     */
    string determine_data(string mes);
    /**
     * @brief parse_rec_data - gets a way from request
     * @param data - get request
     * @return way
     */
    string parse_rec_data(string data);
    vector<character> chrs;
    /**
     * @brief get_key - gets a key from a way /favorites?{key}={value}
     * @param mes - get request
     * @return key
     */
    string get_key(string mes);
    /**
     * @brief get_value - gets a value from a way /favorites?{key}={value}
     * @param mes - get request
     * @return value
     */
    string get_value(string mes);
    /**
     * @brief readFile - gets data from a file
     * @return data
     */
    string readFile();
    /**
     * @brief get_nums - gets JSON-list of all the numbers on odd position in the string
     * @param data - data received from the file
     * @return JSON-list of the numbers
     */
    string get_nums(string data);
    /**
     * @brief default_data - adds default data to the list of characters
     */
    void default_data();
    /**
     * @brief get_time gets current time
     * @return string time
     */
    string get_time();
};

#endif // SERVER_H
