/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   multipleSource.cpp
 * Author: augusto
 * 
 * Created on 12 de Setembro de 2017, 10:09
 */


#include "classes.h"

multipleSource::multipleSource() {
}



//multipleSource::~multipleSource() {
//}

void multipleSource::addSourceAndPath(signal* signal_obj,vector<map<string,gate>::iterator> gate_path){
    
    vector<vector<map<string,gate>::iterator> > aux;
   
    aux.push_back(gate_path);
    if(source_to_paths.find(signal_obj)== source_to_paths.end())
    {
        this->source_to_paths.insert(pair<signal*,vector<vector<map<string,gate>::iterator> > > (signal_obj,aux));
        
    }
  
    else
        source_to_paths.find(signal_obj)->second.push_back(gate_path);
    
    
}

void multipleSource::clear(){
    this->source_to_paths.clear();
}

 map<signal*,vector<vector<map<string,gate>::iterator> > > multipleSource::getMapSourceToPaths(){
     return this->source_to_paths;
 }
 
 void multipleSource::printMultipleSource(){
     map<signal*,vector<vector<map<string,gate>::iterator> > >::iterator it;
     

     for(it=this->source_to_paths.begin();it!=this->source_to_paths.end();it++)
     {
         
         for(int i=0;i<it->second.size();i++)
         {
             cout<<it->first->getName()<<":";
             for(int j=0;j<it->second[i].size();j++)
                 cout<<it->second[i][j]->first<<",";
             cout<<endl;
         }    
     }


 }
//vector<signal*> multipleSource::getMultipleSource(){
//    return this->sources;
//}

 
 bool multipleSource::hasSignalAsSource(signal* signal_pointer){
     if(source_to_paths.find(signal_pointer)!=source_to_paths.end())
         return true;
     else
         return false;
 }
