CPPFLAGS= -std=c++11 -ggdb -I/usr/local/include/mongocxx/v_noabi \-I/usr/local/include/bsoncxx/v_noabi \-L/usr/local/lib -lmongocxx -lbsoncxx
db:
	$(CXX) $(CPPFLAGS) test.cpp -o test `pkg-config opencv4 --cflags --libs`