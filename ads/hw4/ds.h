#include <exception>
#include <string>

using namespace std;

/*
    Errors handling class
*/
class Error : public exception {
    public:
        string message;

        Error() {};
        Error(string information);

        virtual const char * what () const throw () {
            return message.c_str();
        }
};

/*
    Struct for shops handling
*/
typedef struct Shop {
    char name[250];
} shop;
