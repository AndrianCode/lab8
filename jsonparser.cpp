#include "jsonparser.h"
#include "QJsonDocument"
#include <QJsonArray>
#include <QJsonObject>

JsonParser::JsonParser()
{

}

string JsonParser::main_data_tojson(string title, string dev, string time) {
    QJsonObject j_obj;
    QString f("title");
    j_obj.insert(f, QJsonValue(QString::fromStdString(title)));
    QString f2("dev");
    j_obj.insert(f2, QJsonValue(QString::fromStdString(dev)));
    QString f3("time");
    j_obj.insert(f3, QJsonValue(QString::fromStdString(time)));

    QJsonDocument j_doc(j_obj);
    return j_doc.toJson(QJsonDocument::Indented).toStdString();
}

string JsonParser::objects_data_tojson(vector<character> chrs) {
    QJsonObject jobj;
    for (unsigned int i=0; i<chrs.size(); i++) {
        character chr = chrs.at(i);
        QJsonObject j_obj;
        QString f("Name");
        j_obj.insert(f, QJsonValue(QString::fromStdString(chr.get_name())));
        QString f2("Movie");
        j_obj.insert(f2, QJsonValue(QString::fromStdString(chr.get_movie())));

        jobj.insert(QString::fromStdString(chr.get_id()), j_obj);
    }

    QJsonDocument j_doc(jobj);
    return j_doc.toJson(QJsonDocument::Indented).toStdString();
}

string JsonParser::key_obj_tojson(vector<character> chrs, string key, string val) {
    QJsonObject jobj;
    if (key=="name") for (unsigned int i=0; i<chrs.size(); i++) {
        character chr = chrs.at(i);
        if (chr.get_name()!=val) continue;
        QJsonObject j_obj;
        QString f("Name");
        j_obj.insert(f, QJsonValue(QString::fromStdString(chr.get_name())));

        jobj.insert(QString::fromStdString(chr.get_id()), j_obj);
    }
    else if (key=="movie") for (unsigned int i=0; i<chrs.size(); i++) {
        character chr = chrs.at(i);
        if (chr.get_movie()!=val) continue;
        QJsonObject j_obj;
            QString f2("Movie");
            j_obj.insert(f2, QJsonValue(QString::fromStdString(chr.get_movie())));

        jobj.insert(QString::fromStdString(chr.get_id()), j_obj);
    }

    QJsonDocument j_doc(jobj);
    return j_doc.toJson(QJsonDocument::Indented).toStdString();
}

string JsonParser::id_obj_tojson(vector<character> chrs, string id) {
    QJsonObject jobj;
    if (stoi(id, nullptr, 10) < 0 || stoi(id, nullptr, 10) > chrs.size()-1) {
        return "404: Not Found";
    }
    for (unsigned int i=0; i<chrs.size(); i++) {
        character chr = chrs.at(i);
        if (chr.get_id()==id) {
            QJsonObject j_obj;
            QString f("Name");
            j_obj.insert(f, QJsonValue(QString::fromStdString(chr.get_name())));
            QString f2("Movie");
            j_obj.insert(f2, QJsonValue(QString::fromStdString(chr.get_movie())));

            jobj.insert(QString::fromStdString(chr.get_id()), j_obj);
            break;
        }
    }

    QJsonDocument j_doc(jobj);
    return j_doc.toJson(QJsonDocument::Indented).toStdString();
}

string JsonParser::file_data_tojson(vector<int> data) {
    QJsonObject j_obj;
    QJsonArray j_arr;

    for (unsigned int i=0; i<data.size(); i++) {
        j_arr.append(QJsonValue(data.at(i)));
    }
    QString d("Data");
    j_obj.insert(d, QJsonValue(j_arr));

    QJsonDocument j_doc(j_obj);
    return j_doc.toJson(QJsonDocument::Indented).toStdString();
}
