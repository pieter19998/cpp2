#pragma once

#include <string>
#include <iostream>
#include <fstream>

template<typename T>

void WriteToLogFile(const T& location, const T &data){
    std::ofstream outfile;
    outfile.open(location, std::ios_base::app);
    outfile << data + "\n";
}