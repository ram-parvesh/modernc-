//to compile g++ -std=c++17 funtcptr.cpp -o main
#include<iostream>
#include<string>


void swap(int* a, int* b){
    int temp = *a;
    *a=*b;
    *b=temp;
}
int add(int a,int b){
    return a+b;
}


int substract(int a, int b){
    return a-b;
}

int multiply(int a, int b){

    return a*b;
}

int divide(int a , int b){
        return a/b;
}

void calc(int a, int b, int(*funcptr)(int c, int d)){
    std::cout<<"called calc function: "<<funcptr(a,b)<<std::endl;
}



int main(){

    //please copy and paste in chrome and search
    //Declare a C/C++ function returning pointer to array of integer pointers

    std::cout<<"funtion pointer tutor begins"<<std::endl;
    // Without using addressof operator
    {   //return_type (*FuncPtr) (parameter type, ....);  
        int (*funcptr) (int , int); //funtion ptr decleration
        funcptr = multiply;   // pointer_name = &function_name ------> Without using addressof operator
        int result = funcptr(5, 7);  //call the function using the ptr
        std::cout<<"multiply 7 * 5 :"<<result<<std::endl;
    }

    //Using addressof operator
    {   //return_type (*pointer_name)(parameter_types); 
        int (*funcptr) (int , int); //funtion ptr decleration
        // Assigning address of add() functoin to fptr
        funcptr = &add;   // funcptr initialization
        // Calling function using function pointer
        int result = funcptr(5, 10);  //call the function using the ptr
        std::cout<<"sum of 5 and 10 is: "<<result<<std::endl;
    }

    {   //return_type (*pointer_name)(parameter_types); 
        calc(10,6,substract); //without using addressof function
        calc(10,6,&add); //using addressof funtion
    }

    {
    // Declare an array of function pointers
    int (*farr[])(int, int) = {add, substract, multiply, divide};
    int x = 10, y = 5;
    std::cout<<"divide : "<<farr[3](x,y)<<std::endl;
    std::cout<<"multiply : "<<farr[2](x,y)<<std::endl;
    std::cout<<"subtract : "<<farr[1](x,y)<<std::endl;

    }

    {
        int s=5, d=7;
        std::cout<<"before swapping :"<<s<<" "<<d<<std::endl;
        swap(&s, &d);
        std::cout<<"after swapping :"<<s<<" "<<d<<std::endl;
        //swap using functptr
        void (*swapping)(int *, int*);
        swapping = swap;
        swapping(&s,&d);
        std::cout<<s<<" "<<d<<std::endl;

    
    }

    std::cout<<"funtion pointer tutor end "<<std::endl;

    return 0;
}