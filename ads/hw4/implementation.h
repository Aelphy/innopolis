#include <exception>
#include <string>

using namespace std;

/*
    Errors handling class
*/
class Error : public exception {
    public:
        string message;

        Error() {};                 // default constructor
        Error(string information);  // constructor with string
        virtual ~Error() throw ()   // destructor
        {

        }
        // what method reloading
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

// swap elements of array
void swap(int *a, int i, int j);

// reverse array a from i upto j elements
void reverse(int *a, int i, int j);

// generate next permutation
bool permutate(int *a, int n);
