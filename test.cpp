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
#include "db.hpp"

using namespace cv;
using namespace std;
 
int main(int, char**) {

    DataBase db;

    //Create
    db.create("Hola", 23, "A01099911", "https://www.thispersondoesnotexist.com/image", Mat::zeros( 4, 4, CV_32FC2 ));
    //Read
    //db.readAll();
    //db.readOne("A01021111");
    //Update
    //db.updateName("Luis Garcia ","Victor Coeto");
    //db.updateMatricula("A01021111", "A01025986");
    //Delete
    //ddb.eleteOne("Victor Coeto");

}