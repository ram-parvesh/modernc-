// to compile g++ -std=c++17 main_basics2.cpp -o main
#include<iostream>
#include <string>
#include <vector>

class Vector3{
    public:
    float x,y,z;
};

class Array{
    public:
    //constructor
    Array(){
        std::cout<<"constructor"<<std::endl;
        data = new int[10];
        for (int i =0; i<10;i++){
            data[i]=i*i;
        }
    }
    void printdata(){
        for(int i=0;i<10;i++){
            std::cout<<data[i]<<std::endl;
        }
    }

    void setdata(int index , int value){
        data[index]=value;
    }

    //destructor
    ~Array(){
        std::cout<<"donstructor"<<std::endl;
        delete[] data;
    }

    //copy constructor
    Array(const Array& rhs){
        std::cout<<"copy-constructor"<<std::endl;
        delete [] data;
        data = new int[10];
        for (int i=0;i<10;i++){
            data[i]=rhs.data[i];
        }
    }
    //copy-assignment operator
    Array& operator=(const Array& rhs){
        std::cout<<"copy assignment operator"<<std::endl;
        if(&rhs ==this){
            return *this;
        }
        
        if(data!=nullptr){
            delete []  data;
        }
        data = new int[10];
        for (int i=0;i<10;i++){
            data[i]=rhs.data[i];
        }
        return *this;
    }
    
    private:
    int* data;
    // std::vector<int> data; //if this is the case do not write delete [] data in destructor
};

int main(){

    {
    // std::cout<<"assignment operator"<<std::endl;
    // std::string ram = "ram";
    // std::string ram2 = ram;
    // std::cout<< ram <<std::endl;
    // std::cout<< ram2 <<std::endl;
    }
    {   
    
        // std::cout<<"default copy-assignment operator"<<std::endl;
        // Vector3 myvector;
        // myvector.x=0;
        // myvector.y=5;
        // myvector.z=3;
        // Vector3 myvector2;
        
        // myvector2=myvector; //copy-assignment operator -by default we get this also in c++

        // std::cout<<myvector.x<< ", "<<myvector.y<< ", "<<myvector.z<< ", "<<std::endl;
        // std::cout<<myvector2.x<< ", "<<myvector2.y<< ", "<<myvector2.z<< ", "<<std::endl;
    }

    std::cout<<"+++++++++Program Starts++++++++++"<<std::endl;
    {
        Array myarray;
        // Array myarray2 = myarray; //shallow-copy
        myarray.setdata(2,50);
        myarray.setdata(5,1000);
        // myarray.printdata();

        Array myarray2 ;
        myarray2 = myarray; // copy-assignment operator
        myarray.printdata(); 
        myarray2.printdata();


    }
    std::cout<<"+++++++++Program Ends++++++++++"<<std::endl;
    return 0;
}