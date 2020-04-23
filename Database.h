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

using namespace std;
using namespace cv;

//TODO: try catch connection to db
// Creando la conexion al cluster

mongocxx::instance instance{};
mongocxx::client conn{mongocxx::uri{"mongodb+srv://saul-admin:Saul098923.23@cluster0-f1rg5.mongodb.net/DataBase?retryWrites=true&w=majority"}};
//Seleccionando la base de datos Cuatecs
mongocxx::database db = conn["cuatecs"];
//Seleccionando la coleccion
mongocxx::collection coll = db["subjects"];

class Database
{
public:
    Database(/* args */);
    ~Database();
    void create(string nombre, int edad, string matricula, string imgURL, Mat m);
    void readAll();
    void readOne(string matricula);
    void updateName(string nombre, string nuevoNombre);
    void updateMatricula(string matricula, string nuevaMatricula);
    void deleteOne(string matricula);
    Mat readMat(string matricula);
};

#endif