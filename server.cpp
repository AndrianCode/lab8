#include "server.h"
#include "QJsonDocument.h"
#include <QJsonObject>
#include <QJsonArray>
#include <progbase-cpp/net.h>
#include <string>
#include <QFile>
#include <QTextStream>
#include "jsonparser.h"
using namespace progbase::net;

const QString filePath = ":/data/data.txt";

string Server::parse_rec_data(string data) {
    try {
        data.erase(data.find("GET"), data.find(" ")+1);
        data.erase(data.find("HTTP")-1, data.length()-1);
        return data;
    }
    catch (out_of_range otf) {
        return "err";
    }
}

void Server::default_data() {
    chrs.push_back(character("Tayler", "Fight Club", chrs.size()));
    chrs.push_back(character("Gordon", "Batman", chrs.size()));
    chrs.push_back(character("Denis", "Lighter", chrs.size()));
}

Server::Server(int serverPort)
{
    default_data();

    TcpListener listener;
    NetMessage message(10000);
    try {
        listener.bind(IpAddress("127.0.0.1", serverPort));
        listener.start();
        while (true) {
            cout << ">> Waiting for clients at " << serverPort << "..." << endl;
            TcpClient * client = listener.accept();
            client->receive(message);
            cout << ">> Received: " << endl << message.dataAsString() << endl;

            string data = message.dataAsString();

            string mes = parse_rec_data(data);
            //cout << "Parsed data:" << mes << "space" << endl;

            string sendmes = determine_data(mes);
            message.setDataString(sendmes);
            client->send(message);
            cout << ">> Response sent." << endl;
            cout << sendmes << endl;
            delete client;
        }
    } catch(NetException const & exc) {
        cerr << exc.what() << endl;
    }
}

string Server::get_key(string mes) { //for /favorites?{key}={value}
    int bpos = mes.find("{");
    int epos = mes.find("}");
    string key = mes.substr(bpos+1, epos-bpos-1);
    return key;
}

string Server::get_value(string mes) { //for /favorites?{key}={value}
    int start_pos = mes.find("}");
    int bpos2 = mes.find("{", start_pos+1);
    int epos2 = mes.find("}", start_pos+1);
    string val = mes.substr(bpos2+1, epos2-bpos2-1);
    return val;
}

string Server::readFile() {
    string txt;
    QFile inputFile(filePath);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          txt += line.toStdString() + "\n";
       }
       inputFile.close();
    }
    else {
        return "ERROR: Cannot open file";
    }
    return txt;
}

string Server::get_nums(string data) {
    int count = 0;
    bool contains = false;
    vector<int> nums;
    while(data.size() > 0) {
        if (count%2!=0 && isdigit(data[0])) {
            int num = stoi(data);
            nums.push_back(num);

            int slide = (int)(log(num)/log(10)) + 1;
            data.erase(0, slide);

            count+=slide;
            contains = true;
        }
        else {
            data.erase(0, 1);
            count++;
        }
    }
    if (contains) {
        JsonParser jp;
        return jp.file_data_tojson(nums);
    }
    else return "ERROR: File doesn't contains numbers";
}

string Server::get_time() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

string Server::determine_data(string mes) {
    if (mes=="/") {
        JsonParser jp;
        return jp.main_data_tojson("My Server", "Andrian Poyda", get_time());
    }
    else if (mes=="/favorites") {
        JsonParser jp;
        return jp.objects_data_tojson(chrs);
    }
    else if (mes.find("/favorites?{") != string::npos && mes.find("}={") != string::npos && mes.find("}") != string::npos) {
        string key = get_key(mes);
        string val = get_value(mes);

        JsonParser jp;
        return jp.key_obj_tojson(chrs, key, val);
    }
    else if (mes.find("/favorites/%7B") != string::npos && mes.find("%7D") != string::npos) {
        mes.replace(mes.find("%7B"), 3, "{");
        mes.replace(mes.find("%7D"), 3, "}");
        cout << mes << endl;
        string id = get_key(mes);

        JsonParser jp;
        return jp.id_obj_tojson(chrs, id);
    }
    else if (mes.find("/file") != string::npos && mes.find("/file/data") == string::npos) {
        return readFile();
    }
    else if (mes.find("/file/data") != string::npos) {
        return get_nums(readFile());
    }
    return "404: Not Found";
}

