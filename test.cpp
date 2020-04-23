#include "Database.hpp"


int main(int, char**) {

    Database db;
    //WRITE yml to store 
    Mat m = imread( "img.jpg",1);
    // //Mat m(2,2,CV_8UC3);
    // FileStorage storage("data.yml.gz", FileStorage::WRITE);
    // storage << "data" << m;
    // storage.release();

    // string storageString = storage.releaseAndGetString();
    // cout << storageString << endl;
    // cout << code << endl;


    //READ yml from db
    // Mat m2;
    // FileStorage storage("data.yml.gz", FileStorage::READ);
    // storage["data"] >> m2;
    // storage.release();

    // imshow("m2", m2);
    // waitKey();

    //Create
    //db.create("YAML.GZ", 1, "PruebaGZ", "https://www.thispersondoesnotexist.com/image", m);
    //Read
    //db.readAll();
    //db.readOne("A01021111");
    //Update
    //db.updateName("Luis Garcia ","Victor Coeto");
    //db.updateMatricula("A01021111", "A01025986");
    //Delete
    //ddb.eleteOne("Victor Coeto");

    // Mat  m2 = db.readMat("Prueba");
    // imshow("m2", m2);
    // waitKey();

}