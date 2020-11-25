/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   library.cpp
 * Author: root
 * 
 * Created on July 12, 2016, 8:19 PM
 */

#include "classes.h"

//////////////////////////LIBRARY/////////////////////////////
library::library(){}
library::library(string library_name){
    name=library_name;
}

void library::pushCell(string cell_name,cell cell_object){
    mymap.insert(pair<string,cell> (cell_name,cell_object));
}

void library::printLibrary(){
    cout<<"Library "<<name<<" info:"<<endl;
    map<string,cell>::iterator it;
    for(it=mymap.begin();it!=mymap.end();it++)
    {
        cout<<it->first<<endl;
        it->second.printCell();
        cout<<endl<<"----------------"<<endl;
    }
}

cell library::findCell(string cell_type){
    map<string,cell>::iterator it;
    if((it=mymap.find(cell_type))!=mymap.end())
        return(it->second);
    else
    {
        cout<<"ALGO ESTA MUITO ERRADO, "<<cell_type<<" nao foi encontrado no mapa."<<endl;
        cell celula;
        return celula;
    }
}


map <string,cell> library::getMap(){
    return this->mymap;
}