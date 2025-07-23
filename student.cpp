#include "student.hpp"
#include <iostream>
Student:: Student(){
            my_name = "no_name";
            std::cout<<"Default Constructor : "<<std::endl;
            std::cout<<"my_name is : "<<my_name<<std::endl;
        }

Student:: Student(std::string name){
            my_name = name;
            std::cout<<"Constructor with parameter : "<<std::endl;
            std::cout<<"my_name is : "<<my_name<<std::endl;
        }
       
Student:: ~Student(){
            std::cout<<"Donstructor : "<<std::endl;
        }
void Student::printname(){
            std::cout<<"my name is : "<<my_name<<std::endl;
        }
