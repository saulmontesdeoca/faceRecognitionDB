
#ifndef DB_H
#define DB_H
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <mongocxx/uri.hpp>
#include <opencv2/core.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
using namespace std;
// Creando la conexion al cluster
mongocxx::instance instance{};
mongocxx::client conn{mongocxx::uri{"mongodb+srv://saul-admin:Saul098923.23@cluster0-f1rg5.mongodb.net/DataBase?retryWrites=true&w=majority"}};
//Seleccionando la base de datos Cuatecs
mongocxx::database db = conn["cuatecs"];
//Seleccionando la coleccion
mongocxx::collection coll = db["subjects"];

class DataBase
{
public:
    DataBase(/* args */);
    ~DataBase();
    void create(string nombre, int edad, string matricula, string imgURL);
    void readAll();
    void readOne(string matricula);
    void updateName(string nombre, string nuevoNombre);
    void updateMatricula(string matricula, string nuevaMatricula);
    void deleteOne(string matricula);

};
#endif