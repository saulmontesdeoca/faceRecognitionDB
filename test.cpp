#include "Database.hpp"

using namespace cv;
using namespace std;
 
int main(int, char**) {

    DataBase db;

    //Create
    db.create("Prueba de headers", 113, "Prueba", "https://www.thispersondoesnotexist.com/image");
    //Read
    //db.readAll();
    //db.readOne("A01021111");
    //Update
    //db.updateName("Luis Garcia ","Victor Coeto");
    //db.updateMatricula("A01021111", "A01025986");
    //Delete
    //ddb.eleteOne("Victor Coeto");

}