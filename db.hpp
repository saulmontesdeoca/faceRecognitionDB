#ifndef DB_H
#define DB_H
using namespace std;
using namespace cv;

// Creando la conexion al cluster
mongocxx::instance instance{};
mongocxx::client conn{mongocxx::uri{"mongodb+srv://saul-admin:Saul098923.23@cluster0-f1rg5.mongodb.net/DataBase?retryWrites=true&w=majority"}};
//Seleccionando la base de datos Cuatecs
mongocxx::database db = conn["cuatecs"];
//Seleccionando la coleccion
mongocxx::collection coll = db["subjects"];

class DataBase
{
private:
    /* data */
public:
    DataBase(/* args */);
    ~DataBase();
    void create(string nombre, int edad, string matricula, string imgURL, Mat m);
    void readAll();
    void readOne(string matricula);
    void updateName(string nombre, string nuevoNombre);
    void updateMatricula(string matricula, string nuevaMatricula);
    void deleteOne(string matricula);

};

DataBase::DataBase()
{
}

DataBase::~DataBase()
{
}
//Create
void DataBase::create(string nombre, int edad, string matricula, string imgURL, Mat m){
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
    << "nombre" << nombre
    << "imgURL" << imgURL
    << "edad" << edad
    << "matricula" << matricula
    << "identificacionFacial" << m
    << bsoncxx::builder::stream::finalize;

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = 
    coll.insert_one(doc_value.view()); //Inserting Document
    cout << "Inserted " << result->inserted_id().get_oid().value.to_string() << endl;

    //cout << result->inserted_id().get_int64() << "\n";
}
// void DataBase::create(string nombre, int edad, string matricula, string imgURL, Mat m){
//     auto builder = bsoncxx::builder::stream::document{};
//     bsoncxx::document::value doc_value = builder
//     << "nombre" << nombre
//     << "imgURL" << imgURL
//     << "edad" << edad
//     << "matricula" << matricula
//     << "identificacionFacial" << bsoncxx::builder::stream::open_document
//         << "rostro1" << bsoncxx::builder::stream::open_array
//             << 32 << 54 << 87 << -33 << 12
//             << bsoncxx::builder::stream::close_array
//         << "rostro2" << bsoncxx::builder::stream::open_array
//             << 32 << 54 << 87 << -33 << 12
//             << bsoncxx::builder::stream::close_array
//         << "rostro3" << bsoncxx::builder::stream::open_array
//             << 32 << 54 << 87 << -33 << 12
//             << bsoncxx::builder::stream::close_array
//     << bsoncxx::builder::stream::close_document
//     << bsoncxx::builder::stream::finalize;

//     bsoncxx::stdx::optional<mongocxx::result::insert_one> result = 
//     coll.insert_one(doc_value.view()); //Inserting Document
//     cout << "Inserted " << result->inserted_id().get_oid().value.to_string() << endl;

//     //cout << result->inserted_id().get_int64() << "\n";
// }
//Read
void DataBase::readAll(){
    mongocxx::cursor cursor = coll.find({});
    for(auto doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << "\n";
    }
}
void DataBase::readOne(string matricula){
    bsoncxx::stdx::optional<bsoncxx::document::value> doc =
    coll.find_one(bsoncxx::builder::stream::document{} << "matricula" << matricula
    << bsoncxx::builder::stream::finalize);
    cout << bsoncxx::to_json(doc->view()) << "\n";
}
//Read with id
// void DataBase::readOne(string id){
//     //bsoncxx::oid oid = bson[id].get_oid().value;
//     //bsoncxx::oid myoid(accountId);
//     bsoncxx::stdx::optional<bsoncxx::document::value> doc =
//     coll.find_one(bsoncxx::builder::stream::document{} << "nombre" << id << bsoncxx::builder::stream::finalize);
//     cout << bsoncxx::to_json(doc->view()) << "\n";
// }

//Update
void DataBase::updateName(string nombre, string nuevoNombre){
    coll.update_one(bsoncxx::builder::stream::document{} << "nombre" << nombre << bsoncxx::builder::stream::finalize,
                      bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document <<
                        "nombre" << nuevoNombre << bsoncxx::builder::stream::close_document 
                        << bsoncxx::builder::stream::finalize);
}
void DataBase::updateMatricula(string matricula, string nuevaMatricula){
    coll.update_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize,
                      bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document <<
                        "matricula" << nuevaMatricula << bsoncxx::builder::stream::close_document 
                        << bsoncxx::builder::stream::finalize);
}
//Delete
void DataBase::deleteOne(string matricula){
    coll.delete_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize);
}

#endif