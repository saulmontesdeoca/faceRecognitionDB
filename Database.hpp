#include "Database.h"

Database::Database()
{
}

Database::~Database()
{
}

//Create
void Database::create(string nombre, int edad, string matricula, string imgURL, Mat m){
        // //WRITE yml to store    
    FileStorage storage("data.yml.gz", FileStorage::WRITE | FileStorage::MEMORY);
    storage << "data" << m;
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
    << "nombre" << nombre
    << "imgURL" << imgURL
    << "edad" << edad
    << "matricula" << matricula
    << "identificacionFacial" << bsoncxx::builder::stream::open_array
        << storage.releaseAndGetString()
    << bsoncxx::builder::stream::close_array
    << bsoncxx::builder::stream::finalize;


    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = 
    coll.insert_one(doc_value.view()); //Inserting Document
    cout << "Inserted " << result->inserted_id().get_oid().value.to_string() << endl;
}

//Read
void Database::readAll(){
    mongocxx::cursor cursor = coll.find({});
    for(auto doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << "\n";
    }
}

void Database::readOne(string matricula){
    bsoncxx::stdx::optional<bsoncxx::document::value> doc =
    coll.find_one(bsoncxx::builder::stream::document{} << "matricula" << matricula
    << bsoncxx::builder::stream::finalize);
    cout << bsoncxx::to_json(doc->view()) << "\n";
}

//Read with id
// void Database::readOne(string id){
//     //bsoncxx::oid oid = bson[id].get_oid().value;
//     //bsoncxx::oid myoid(accountId);
//     bsoncxx::stdx::optional<bsoncxx::document::value> doc =
//     coll.find_one(bsoncxx::builder::stream::document{} << "nombre" << id << bsoncxx::builder::stream::finalize);
//     cout << bsoncxx::to_json(doc->view()) << "\n";
// }

//Update
void Database::updateName(string nombre, string nuevoNombre){
    coll.update_one(bsoncxx::builder::stream::document{} << "nombre" << nombre << bsoncxx::builder::stream::finalize,
                      bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document <<
                        "nombre" << nuevoNombre << bsoncxx::builder::stream::close_document 
                        << bsoncxx::builder::stream::finalize);
}

void Database::updateMatricula(string matricula, string nuevaMatricula){
    coll.update_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize,
                      bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document <<
                        "matricula" << nuevaMatricula << bsoncxx::builder::stream::close_document 
                        << bsoncxx::builder::stream::finalize);
}

//Delete
void Database::deleteOne(string matricula){
    coll.delete_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize);
}
Mat Database::readMat(string matricula)
{
    Mat m;

    return m;
};