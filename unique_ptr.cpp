// to compile :      g++ -std=c++17 unique_ptr.cpp -o prog


#include <iostream>
#include <memory>

void raw_ptr(){

    int x= 10;
    //pointer to x
    int*  ptr = &x;

    std::cout<<"*ptr : " << *ptr <<std::endl;

    // create a second pointer
    int* ptr2 = ptr;   //pointing to ptr

    std::cout<<"*ptr2 : "<< *ptr2 <<std::endl;

    delete ptr;

    std::cout<<"*ptr2 : "<< *ptr2 <<std::endl;


}


void raw_ptr_array(){

    int* array = new int[100];
    for (int i =0;i<100;i++){
            array[i]=i;
        }
    
    int* ptr = array;

    //output value pointed to by ptr
    std::cout<<"*ptr : "<<*ptr <<std::endl;
    array[1]=5;
    array[0]=52;
    
    //create a second pointer
    int* ptr2 = ptr;
    std::cout<<"array[0] : "<<array[0]<<std::endl;
    std::cout<<"*array :"<<*array<<std::endl;
    std::cout<<"*(array+0) :"<<*(array+0)<<std::endl;
    std::cout<<"*(ptr+0) is equivalent to array[0] after (int* ptr = array) : "<< *(ptr+0)<<std::endl;
    std::cout<<array[1]<<std::endl;

    
    delete [] array;
    
    //
    float *newarray = new float[100];
    std::cout<<"*ptr2 : "<<*ptr2 <<std::endl;
    std::cout<<array[0]<<std::endl; // after deleting array , pointing to it again. --->segmentation fault

}


class UDT{
    public:
        UDT(){std::cout<<"UDT created"<<std::endl;}
        ~UDT(){std::cout<<"UDT Destroyed"<<std::endl;}
        
};

int main(){

    // raw_ptr();
    // raw_ptr_array();

    // creating ram using simple  method ---use delete ram
    // UDT ram;



    //unique ptr 
    //1.we cannot share(no copies allows)
    //2.we dont have to delete

    //creating one unique pointer ----does not require to delete
    std::unique_ptr<UDT>ram = std::unique_ptr<UDT>(new UDT);
    //uncomment and try to copy next line 
    // std::unique_ptr<UDT>copy = ram; //at compile it will throw error
    //but move semantic is allowed
    std::unique_ptr<UDT>copy = std::move(ram);



    //create an array that is pointed to, by one unique ptr
    // std::unique_ptr<UDT[]>ram_array = std::unique_ptr<UDT[]>(new UDT[5]);

    //this is equvalent to above line
    // std::unique_ptr<UDT[]>ram_array2 = std::make_unique<UDT[]>(5);
    

    //share_ptr
    



    return 0;
}