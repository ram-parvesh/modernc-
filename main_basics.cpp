//to compile g++ -std=c++17 student.cpp main_basics.cpp -o main
//to run ./main

#include<iostream>
#include "student.hpp"
int main(){

    std::cout<<"+++++++++++Program starts+++++++++++"<<std::endl;

    //test 1
    //an instance of student(ie an object)
    {
        // the way it is declared 
        //both constructor and destructor is created and destroyed
        // Student ram;
        // ram.my_name = "Ram";   //works only when my_name variable defined in student.cpp is public
        
    }


    //test 2
    {
        //conctructor is initiized with parameter
        Student ram("RAMM");
        ram.printname();
    }


    //test 3
    {
    // the way it is declared 
    //both constructor and destructor is created but we have to delete destructor explicitly
    Student* raju =new Student; //default constructor is created
    // raju->my_name = "Raju Singh";  //works only is my_name variable is public
    raju->printname();
    delete raju;
               
    }


    //test 4
    {
        Student* raju1 =new Student("RAJU SINGH"); //contructor with paramater  is called
        delete raju1;
    }
    std::cout<<"-----------Program ends-----------"<<std::endl;

    return 0;
}