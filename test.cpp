#include "Database.cpp"

using namespace cv;
using namespace std;

int main() {

    Database db(URI, DATABASE, COLLECTION);
    Mat m = imread( "img.jpg",1);
    Mat m2 = imread( "img.jpg",1);

    //Create
    db.create("route2", 222, "route3", m2, m);
    //Read
    //db.readAll();
    //db.readOne("A01021111");
    //Update
    //db.updateName("Luis Garcia ","Victor Coeto");
    //db.updateMatricula("A01021111", "A01025986");
    //Delete
    //db.deleteOne("Victor Coeto");

    // Mat  m2 = db.readMat("route2");

    // imshow("m2", m2);
    // waitKey();

}