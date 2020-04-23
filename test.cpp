#include "Database.hpp"

using namespace cv;
using namespace std;

int main(int, char**) {

    Database db;

    //Mat m = imread( "img.jpg",1);

    //Create
    //db.create("YAML.GZ", 1, "PruebaGZ", "https://www.thispersondoesnotexist.com/image", m);
    //Read
    //db.readAll();
    //db.readOne("A01021111");
    //Update
    //db.updateName("Luis Garcia ","Victor Coeto");
    //db.updateMatricula("A01021111", "A01025986");
    //Delete
    //db.deleteOne("Victor Coeto");

    Mat  m2 = db.readMat("Prueba");
    imshow("m2", m2);
    waitKey();

}