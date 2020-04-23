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

//TODO: try catch connection to db
// Creando la conexion al cluster

mongocxx::instance instance{};
mongocxx::client conn{mongocxx::uri{URI}};
//Seleccionando la base de datos Cuatecs
mongocxx::database db = conn["cuatecs"];
//Seleccionando la coleccion
mongocxx::collection coll = db["subjects"];

class Database
{
public:
    Database(/* args */);
    ~Database();
    void create(std::string nombre, int edad, std::string matricula, std::string imgURL, cv::Mat m);
    void readAll();
    void readOne(std::string matricula);
    void updateName(std::string nombre, std::string nuevoNombre);
    void updateMatricula(std::string matricula, std::string nuevaMatricula);
    void deleteOne(std::string matricula);
    cv::Mat readMat(std::string matricula);
    void matMatch(cv::Mat m);
};

#endif