#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <mongocxx/uri.hpp>
// #include <opencv2/core/mat.hpp>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>


using namespace std;
// Creando la conexion al cluster
mongocxx::instance instance{};
mongocxx::client conn{mongocxx::uri{"mongodb+srv://saul-admin:Saul098923.23@cluster0-f1rg5.mongodb.net/test?retryWrites=true&w=majority"}};

//Seleccionando la base de datos Cuatecs
mongocxx::database db = conn["cuatecs"];

//Seleccionando la coleccion
mongocxx::collection coll = db["subjects"];

//Create
void create(string nombre, int edad, string matricula, string imgURL){
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
    << "nombre" << nombre
    << "imgURL" << imgURL
    << "edad" << edad
    << "matricula" << matricula
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

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = 
    coll.insert_one(doc_value.view()); //Inserting Document
    cout << "Inserted " << result->inserted_id().get_oid().value.to_string() << endl;

    //cout << result->inserted_id().get_int64() << "\n";
}
//Read
void readAll(){
    mongocxx::cursor cursor = coll.find({});
    for(auto doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << "\n";
    }
}
void readOne(string id){
    bsoncxx::stdx::optional<bsoncxx::document::value> doc =
    coll.find_one(bsoncxx::builder::stream::document{} << "_id" 
    << bsoncxx::builder::stream::open_document
    << "$oid" << id
    << bsoncxx::builder::stream::close_document
    << bsoncxx::builder::stream::finalize);
    cout << bsoncxx::to_json(doc->view()) << "\n";
}
// void readOne(string id){
//     //bsoncxx::oid oid = bson[id].get_oid().value;
//     //bsoncxx::oid myoid(accountId);
//     bsoncxx::stdx::optional<bsoncxx::document::value> doc =
//     coll.find_one(bsoncxx::builder::stream::document{} << "nombre" << id << bsoncxx::builder::stream::finalize);
//     cout << bsoncxx::to_json(doc->view()) << "\n";
// }

//Update
void updateName(string nombre, string nuevoNombre){
    coll.update_one(bsoncxx::builder::stream::document{} << "nombre" << nombre << bsoncxx::builder::stream::finalize,
                      bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document <<
                        "nombre" << nuevoNombre << bsoncxx::builder::stream::close_document 
                        << bsoncxx::builder::stream::finalize);
}
void updateMatricula(string matricula, string nuevaMatricula){
    coll.update_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize,
                      bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document <<
                        "matricula" << nuevaMatricula << bsoncxx::builder::stream::close_document 
                        << bsoncxx::builder::stream::finalize);
}
//Delete
void deleteOne(string nombre){
    coll.delete_one(bsoncxx::builder::stream::document{} << "nombre" << nombre << bsoncxx::builder::stream::finalize);
}
 
int main(int, char**) {

    //Create
    //create("Victor Coeto", 21, "A01024637", "https://www.thispersondoesnotexist.com/image");
    //Read
    //readAll();
    //readOne("5e818f73fbb03685bf11a4a0");
    //Update
    // updateName("Luis Garcia ","Victor Coeto");
    // updateMatricula("A01025975", "A01025986");
    //Delete
    deleteOne("Victor Coeto");


}