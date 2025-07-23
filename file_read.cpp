#include <iostream>
#include <memory>
#include <fstream>
#include <typeinfo>
#include <string>
#include <map>
#include <sstream>

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int main(){

    std::map<std::string, std::string> config ;

    std::string file_path = "/home/ram/modernc-/config.txt";
    // std::cout<<"file_path : "<<file_path<<std::endl;

    std::ifstream file(file_path.c_str());

    std::cout<<"path : "<<file_path.c_str()<<std::endl;

    std::string line;

    if(file.is_open()){
        while(getline(file,line)){
            std::stringstream linestream (line);
            std::string key_data;
            std::string value_data;
            if(getline(linestream, key_data,',') && linestream >> value_data ){
                config.insert(make_pair(key_data,value_data));
            }
        }

    }

    std::cout<<config.size()<<std::endl;
    return 0;
}
