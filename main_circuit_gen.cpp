/* 
 * File:   main_circuit_gen.cpp
 * Author: Augusto
 *
 * Created on 26 de Abril de 2016, 10:41
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "classes.h"

using namespace std;



int main(int argc, char* argv[]) {
//    cout<<"argc:"<<argc<<endl;
    MyProgram myprogram_obj;
    vector<string> vec_string;
    for(int i=0;i<argc;i++)
    {
//        cout<<"argv:"<<argv[i]<<endl;
        string str(argv[i]);
        vec_string.push_back(str);
    }
//    for(int a=0;a<vec_string.size();a++)
//        cout<<"vec_string:"<<vec_string[a]<<endl;
    myprogram_obj.interface(vec_string,argc);
    return 0;
}

