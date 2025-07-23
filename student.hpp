#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <string>

class Student{
    public:
        //Action - default Constructor
        Student();
        // constructor with parameter
        Student(std::string name);
        //Action - Destructor
        ~Student();
        
        //member function decleration
        void printname();

    //hidden field or "attributes"
    private:
    std::string my_name;


};



#endif