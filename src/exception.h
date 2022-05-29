//
// Created by pbarbeira on 29-05-2022.
//

#ifndef DA_PROJECT_EXCEPTION_H
#define DA_PROJECT_EXCEPTION_H

#include <iostream>
#include <exception>

class FileNotFound : std::exception{
    const char* err;
public:
    explicit FileNotFound(std::string name){
        std::string e = "File " + name + " not found\n";
        err = e.c_str();
    };
    [[nodiscard]] const char * what() const noexcept override{
        return err;
    }
};


#endif //DA_PROJECT_EXCEPTION_H
