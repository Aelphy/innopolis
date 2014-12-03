#include <exception>
#include <string>

using namespace std;

class Error : public exception {
    public:
        string message;

        Error() {};
        Error(string information);

        virtual const char * what () const throw () {
            return message.c_str();
        }
};

typedef struct Shop {
    char name[250];
} shop;
