//
// Created by domin on 9/16/2019.
//

#ifndef PROJECT1_READ_CONFIG_H
#define PROJECT1_READ_CONFIG_H

#include <cstdio>
#include <fstream>
#include "definitions.h"
//function to read from config file
int* read_config() {
    std::ifstream infile("/Users/domin/CLionProjects/project1/config.txt");
    std::string str;


    int i = 0;
    while (std::getline(infile, str)){
        int space_pos = str.find(" ");

        str = str.substr(space_pos, 'n');

        int val = stoi(str);
        vals[i] = val;

        i++;
    }

    return vals;
}





#endif //PROJECT1_READ_CONFIG_H
