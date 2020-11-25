/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   signals.cpp
 * Author: root
 * 
 * Created on July 12, 2016, 8:20 PM
 */

#include "classes.h"

///////////////////SIGNAL/////////////////
signal::signal(){
    bit=-1;
    probability=-1.0;
    FOLSet=false;
};
signal::signal(string sig_name){
    name=sig_name;
    probability=-1.0;
    bit=-1;
    FOLSet=false;
}

void signal::setName(string param){
    this->name=param;
    bit=-1;
}

void signal::printSignal(){
    cout<<"SIGNAL-> Nome:"<<this->name;
    cout<<" Source:"<<source->getName();
    cout<<" Drives:";
    for(int i=0; i<this->drives.size();i++)
        cout<<this->drives[i]->getName()<<",";
    cout<<endl;
}


void signal::pushDrive(gate param) {
    this->drives.push_back(&param);
}
void signal::pushDrivePointer(gate* param){
    this->drives.push_back(param);
}

//void signal::setSource(gate source) {
//    this->source = &source;
//}

void signal::setSourcePointer(gate* source){
    this->source = source;
}
//void signal::setTest(gate param){
//    test_gate=param;
//}
//gate signal::getTest(){
//    return *test_gate;
//}

string signal::getName(){
    return this->name;
}

vector<gate*> signal::getDrivesPointer(){
    return this->drives;
}

gate* signal::getSourcePointer(){
    return source;
}

double signal::getProbability(){
    return this->probability;
}

void signal::setProbability(double param){
    this->probability=param;
}

//void signal::setDumbProbability(double param){
//    this->probability=param;
//}

void signal::changeBit(){
    if(bit)
        bit=0;
    else
        bit=1;
}

int signal::getBit(){
    return bit;
}

void signal::setBit(int param){
    bit=param;
}
void signal::resetBit(){
    bit=-1;
}

void signal::clear(){
    this->drives.clear();
    this->name="";
    this->source=NULL;
    FOLSet=false;
}

void signal::setLogicFunction(string sink_name,vector<probability_variable> logic_vec){
    this->sink_to_function.insert(pair<string,vector<probability_variable> > (sink_name,logic_vec));
}

vector<probability_variable> signal::getLogicFunction(string sink_name){
    if(this->sink_to_function.find(sink_name)==sink_to_function.end())
        cout<<"No logic function for "<<this->getName()<<" with "<<sink_name<<" as sink. (getLogicFunction)"<<endl;
    return this->sink_to_function.find(sink_name)->second;
}

//void signal::addDumbProbability(){
//    this->probability++;
//}

//double signal::getDumbProbability(){
//    return this->probability;
//}
//
//void signal::setDumbProbability(double param){
//    this->probability=param;
//}

//bool signal::isSource(string sink_name){
//    for(int i=0;i<this->)
//}

bool signal::isFOLSet(){
    return this->FOLSet;
}

void signal::setFOL(vector<FOL_count> FOL_vec){
    this->FOLSet=true;
    this->FOL=FOL_vec;
}

void signal::addRFOL(FOL_count param){
    this->RFOL.push_back(param);
}

vector<FOL_count> signal::getFOL(){
    return this->FOL;
}

vector<FOL_count> signal::getRFOL(){
    return this->RFOL;
}

vector<FOL_count> signal::getPRFOL(){
    return this->primary_RFOL;
}

void signal::resetFOL(){
    this->FOL.clear();
    this->FOLSet=false;
}

void signal::setRFOL(vector<FOL_count> RFOL_vec){
    this->RFOL=RFOL_vec;
}

void signal::setPRFOL(vector<FOL_count> PRFOL_vec){
    this->primary_RFOL=PRFOL_vec;
}


map<string,vector<probability_variable> > signal::getAllLogicFunction(){
    return this->sink_to_function;
}