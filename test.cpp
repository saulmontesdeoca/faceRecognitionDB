#include <iostream>
#include <vector>
#include <cstdint>
#include <mongocxx/uri.hpp>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

 
int main(int, char**) {

    // Creando la conexion al cluster
    mongocxx::instance instance{};
    mongocxx::client conn{mongocxx::uri{"mongodb+srv://saul-admin:Saul098923.23@cluster0-f1rg5.mongodb.net/test?retryWrites=true&w=majority"}};
    
    //Seleccionando la base de datos Cuatecs
    mongocxx::database db = conn["cuatecs"];

    //Seleccionando la coleccion
    mongocxx::collection coll = db["subjects"];

    // collection.insert_one(document.view());
    mongocxx::cursor cursor = coll.find({});
    for(auto doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << "\n";
    }

    //Create
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
    << "nombre" << "Juan Carlos Hurtado"
    << "edad" << 22
    << "matricula" << "A01029354"
    << "identificacionFacial" << bsoncxx::builder::stream::open_document
        << "rostro1" << bsoncxx::builder::stream::open_array
            << 32 << 54 << 87 << -33 << 12
            << bsoncxx::builder::stream::close_array
        << "rostro2" << bsoncxx::builder::stream::open_array
            << 32 << 54 << 87 << -33 << 12
            << bsoncxx::builder::stream::close_array
        << "rostro3" << bsoncxx::builder::stream::open_array
            << 32 << 54 << 87 << -33 << 12
            << bsoncxx::builder::stream::close_array
    << bsoncxx::builder::stream::close_document
    << bsoncxx::builder::stream::finalize;

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(doc_value.view()); //Inserting Document


}