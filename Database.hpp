#include "Database.h"

Database::Database()
{
}

Database::~Database()
{
}

//Create
void Database::create(std::string nombre, int edad, std::string matricula, std::string imgURL, cv::Mat m){
        // //WRITE yml to store 
    std::string fileRoute =  "./MatFiles/" + matricula + ".yml.gz";  
   cv::FileStorage storage(fileRoute, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML);
    storage << "data" << m;
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
    << "nombre" << nombre
    << "imgURL" << imgURL
    << "edad" << edad
    << "matricula" << matricula
    << "identificacionFacial" << bsoncxx::builder::stream::open_array
        << fileRoute
    << bsoncxx::builder::stream::close_array
    << bsoncxx::builder::stream::finalize;

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = 
    coll.insert_one(doc_value.view()); //Inserting Document
    std::cout << "Inserted " << result->inserted_id().get_oid().value.to_string() << std::endl;
    storage.release();

}

//Read
void Database::readAll(){
    mongocxx::cursor cursor = coll.find({});
    for(auto doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << "\n";
    }
}

void Database::readOne(std::string matricula){
    bsoncxx::stdx::optional<bsoncxx::document::value> doc =
    coll.find_one(bsoncxx::builder::stream::document{} << "matricula" << matricula
    << bsoncxx::builder::stream::finalize);
    std::cout << bsoncxx::to_json(doc->view()) << "\n";
}

//Read with id
// void Database::readOne(std::string id){
//     //bsoncxx::oid oid = bson[id].get_oid().value;
//     //bsoncxx::oid myoid(accountId);
//     bsoncxx::stdx::optional<bsoncxx::document::value> doc =
//     coll.find_one(bsoncxx::builder::stream::document{} << "nombre" << id << bsoncxx::builder::stream::finalize);
//     cout << bsoncxx::to_json(doc->view()) << "\n";
// }

//Update
void Database::updateName(std::string nombre, std::string nuevoNombre){
    coll.update_one(bsoncxx::builder::stream::document{} << "nombre" << nombre << bsoncxx::builder::stream::finalize,
                      bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document <<
                        "nombre" << nuevoNombre << bsoncxx::builder::stream::close_document 
                        << bsoncxx::builder::stream::finalize);
}

void Database::updateMatricula(std::string matricula, std::string nuevaMatricula){
    coll.update_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize,
                      bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document <<
                        "matricula" << nuevaMatricula << bsoncxx::builder::stream::close_document 
                        << bsoncxx::builder::stream::finalize);
}

//Delete
void Database::deleteOne(std::string matricula){
    coll.delete_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize);
}
cv::Mat Database::readMat(std::string matricula)
{
    cv::Mat m;
    bsoncxx::stdx::optional<bsoncxx::document::value> doc =
    coll.find_one(bsoncxx::builder::stream::document{} << "matricula" << matricula
    << bsoncxx::builder::stream::finalize);
    bsoncxx::document::view view = doc->view();
    auto matString = view["identificacionFacial"][0].get_utf8().value.to_string();
    std::cout << matString << std::endl;
    cv::FileStorage fs(matString, cv::FileStorage::READ | cv::FileStorage::MEMORY);
    fs["data"] >> m;
    fs.release();
    return m;
};