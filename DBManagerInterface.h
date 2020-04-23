#ifndef DB_H
#define DB_H

#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "EnvironmentVariables.h"

class DBManagerInterface
{
public:
    mongocxx::database db;
    mongocxx::client conn;
    mongocxx::collection coll;
    DBManagerInterface(std::string uri, std::string db, std::string coll);
    ~DBManagerInterface();
    void create(std::string nombre, int edad, std::string matricula, cv::Mat imgURL, cv::Mat m);
    void readAll();
    void readOne(std::string matricula);
    void updateName(std::string nombre, std::string nuevoNombre);
    void updateMatricula(std::string matricula, std::string nuevaMatricula);
    void deleteOne(std::string matricula);
    cv::Mat readMat(std::string matricula);
    void matMatch(cv::Mat m);
};

#endif