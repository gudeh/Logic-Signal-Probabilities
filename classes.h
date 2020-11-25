/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   classes.h
 * Author: gudeh
 *
 * Created on 10 de Maio de 2016, 14:24
 */


#ifndef CLASSES_H
#define CLASSES_H
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm> //isspace
#include <queue>
#include <sys/time.h>
//#include <gtkmm.h> //
using namespace std;


class signal;
class gate;
////////////////////////STRUCTS//////////////////
struct FOL_count{
    int count;
    signal* signal_pointer;
};
struct source_data{
    bool bit;
    float probability;
};
struct probability_variable{
    bool is_operand;
    bool is_operator;
    bool is_number;
    string variable;
};

struct time_info{
    double cpu_time,human_time;
    string calculation_type;
};

struct possible_cluster{
        signal* fanout_source;
        vector<map <string,gate>::iterator> path;
};

struct tupla{
    vector<FOL_count> fol;
    vector<FOL_count> rfol;
};

//////////////////////////CELL/////////////////////////////
class cell {
    string type;
    vector <string> input, output;
    map <string,string> pin_to_funcs;
    map <string,vector <string> > pin_to_funcs_postfix;
    double area,power;

private:
    void makePostFix(map<string,string> param);

public:
    cell(string param_type, vector <string> in, vector <string> out, map<string,string> funcs);
    cell(string type_name, vector <string> in, vector <string> out);
    cell();
    
    void setArea(double);
    void setPower(double);
    double getArea();
    double getPower();
    
    string getFunc(string pin_name);
    vector<string> getPostFix(string pin_name);
    void printCell();
    string getType();
    vector<string> getInput();
    vector<string> getOutput();
};

//////////////////////////LIBRARY/////////////////////////////
class library {
    string name;
    map <string, cell> mymap;

public:
    library();
    library(string library_name);
    void pushCell(string cell_name, cell cell_object);
    void printLibrary();
    cell findCell(string);
    map <string,cell> getMap();
};




//////////////////////CLUSTER////////////////////////
class cluster{
    signal* source;
    vector<vector<map<string,gate>::iterator> > gate_paths;
    
public:
    cluster();
    void setSource(signal*);
    signal* getSource();
    void addGatePaths(vector<map<string,gate>::iterator>);
    vector<vector<map<string,gate>::iterator> > getGatePaths();
    
    void clear();
    void printReconvergentPath();
    void erasePath(int);
};



////////////////MULTIPLE SOURCES CLUSTER/////////////////////
class multipleSource{
    map<signal*,vector<vector<map<string,gate>::iterator> > >source_to_paths;
    
//    vector<signal*> sources;
    
public:
    multipleSource();
    void clear();
    map<signal*,vector<vector<map<string,gate>::iterator> > > getMapSourceToPaths();

    void addSourceAndPath(signal*,vector<map<string,gate>::iterator>);
    void printMultipleSource();
    bool hasSignalAsSource(signal* signal_pointer);
};

class circuit;
//////////////////////////GATE/////////////////////////////

class gate {
    string name;
    string type;
    vector<signal*> inputs;
    vector<signal*> outputs;
    
    map<string,signal*> pin_and_signal;
    cell cell_obj;
    int level, visit_count;
    bool tagged,tagged_fanout_check,is_sink;
    

    map <signal*,multipleSource> input_to_cluster;
    map <signal*,vector<map<string,gate>::iterator> > input_to_gates;
//    map <signal*,vector<string> > signal_to_function;
    vector <FOL_count> primary_RFOL;
    
private:
    vector<probability_variable> makePostFix(vector<probability_variable> sources);
    vector<probability_variable> handleXOR(vector<probability_variable> prob_vec,int index);
    
public:
    gate();
    gate(string,string);
    gate(library, string, string);
    void printGate();
    void pushInput(signal*);
    void pushOutput(signal*);
    void setLevel(int);
    void setName(string);
    void setVisitCount(int);
    void setMapPinSignal(map<string,signal*>);
    void addCluster(cluster);
    void setLogicFunctionOnOutputs(gate* sink,vector<FOL_count> primaries);
//    void setFunctionOnInputs();
    void setPRFOL(vector<FOL_count> primaries);
    
    string getName();
    string getType();
    int getVisitCount();
    int getLevel();
    cell getCell();
    vector<signal*> getInputsPointer();
    vector<signal*> getOutputsPointer();
    map<signal*,multipleSource> getMapInputToCluster();
    vector<map<string,gate>::iterator> getUnaryGateList(signal* input_obj);
    vector<FOL_count> getPRFOL();
    
    signal* getSignalToThisGate(string gate_destination);
    string getPinName(string signal_name);
    signal* getSignalFromPinName(string pin_name);
    
    bool hasAllInputSet();
    bool hasAllBitInputSet();
    bool isFinalLevel();
    bool isFinal();
    string isFinalSetSink(vector<FOL_count> primaries);
    bool isFinalReconverg();
    bool isTagged();
    bool isSink();
    bool isOnCluster(string other_gate_name);
    bool isThisASource(string signal_name);
    
    void tag();
    void checkToTag();
    void untag();
    bool isTaggedFanoutCheck();
    void tagFanoutCheck();
    void untagFanoutCheck();
    bool isCircuitOutput(string signal_name);
    bool isCircuitInput();
    bool isDone();
    void clear();
    
    signal* getSignalToSmallerLvl();
    gate* getNextGate();
    gate* getNextGateReconverg();
    gate* getNextGateSetSink(vector<FOL_count> primaries);
    double getNumbers(vector<string>);
    int getBits(vector<string>);
    int makeSignalProbability(vector<string>,string);
    
    void setGateProbability();
    void setSinkProbability(circuit* circuit_obj);
    void propagateBit();
    void setInitialBits();
    
};



//////////////////////////SIGNAL/////////////////////////////
class signal {
    string name;
    double probability;
    int bit;
    gate* source;
    vector<gate*> drives;
    vector<signal*> fanouts_on_path;
    map<string,vector<probability_variable> > sink_to_function;
    bool FOLSet;
    vector<FOL_count> FOL,RFOL,primary_RFOL; //Fan Out List and Reconvergent Fan Out List
    
public:
    signal();
    signal(string);
    string getName();
    void setName(string);
    void setBit(int);
    void printSignal();
    void changeBit();
    void resetBit();
    void clear();
    void resetFOL();
    
//    bool isSource(string sink_name);
    bool isFOLSet();
    
    void pushDrive(gate);
    void pushDrivePointer(gate*);
    void setSourcePointer(gate*);
    void setProbability(double);
//    void setDumbProbability(double);
    void setLogicFunction(string sink_name,vector<probability_variable> logic_vec);
    void setFOL(vector<FOL_count> FOL_vec);
    void addRFOL(FOL_count);
    void setRFOL(vector<FOL_count> RFOL_vec);
    void setPRFOL(vector<FOL_count> PRFOL_vec);
    
    
    gate* getSourcePointer();
    vector<gate*> getDrivesPointer();
    double getProbability();
//    double getDumbProbability();
    int getBit();
    vector<probability_variable> getLogicFunction(string sink_name);
    map<string,vector<probability_variable> > getAllLogicFunction();
    vector<FOL_count> getFOL();
    vector<FOL_count> getRFOL();
    vector<FOL_count> getPRFOL();
    
    void setTest(gate *param);
    gate getTest();

};

//////////////////////////CIRCUIT///////////////////////
class circuit{
    string name;
    time_info probability_info,reconvergent_info;
    map <string,gate> all_gates;
    map <string,signal> all_signals;
    vector<signal*> input,output;
    signal null_signal;
    gate null_gate_in,null_gate_out;
    
    vector<cluster> clusters;
    vector<possible_cluster> all_possible_paths;
    
//    map <string,gate>::iterator it_gate;
//    map <string,signal>::iterator it_signal;
//    
private:
    void setSinks();
    void debugReconvergent();
    double getCpuTime();
    double getWallTime();
    void untagAll();
    void tagAll();
    void resetAllProb(double);
    void resetAllBits();
    void resetAllNotInBits();
    void setAllBitsZero();
    void prepareToDFS(vector<map<string,gate>::iterator> list_of_gates);
    void resetFOLs();
    tupla rfolReduction(vector<FOL_count> FOL,vector<FOL_count> RFOL);
    void askForInputProb();
    
    
public:
    circuit();
    circuit(string);
    void setName(string);
    string getName();
    void clear(); //clear attributes
    //void suicide(circuit);
    
    //getters and setters
    void pushIn(signal*);
    void pushOut(signal*);
    void pushGate(gate);
    void pushSignal(signal);
    signal* getSignalPointer(string);
    gate* getGatePointer(string);
    void setDriveEInput(string signal_name,string gate_name);
    void setSourceEOutput(string signal_name,string gate_name);
    
    //internal methods
    void setVoidOnSignalSource(string signal_name);
    void pushVoidOnSignalDestination(string signal_name);
    void pushVoidOnGateOutput(string gate_name);
    bool isSignalInside(string);
    gate* getNextGate(gate*);//used for depth-first search (unused)
    vector<map <string,gate>::iterator> recursiveDFS(vector<map <string,gate>::iterator>);
     
     
    //important ones
    int checkLevels();
    void setProbSignalPropagation();
    void setProbabilitiesDepth();
    void setProbabilitiesDepthNew();
    void findReconvergentPaths();
    
    
    //print options for class circuit
    void printCircuit();
    void printAllGates();
    void printAllSignals();
    void printGatesInfo();
    void printLevelOnGates();
    void printProbabilities();
    void printReconvergent();
    
//    void printDumbProbabilities();
    
    //write to file options
    void writeProbabilities(string);
    void writeSignalVSFanout();
//    void writeDumbProbabilities(string);
    void writeInputProbEachGate();
    void writeProbabilityTable();
    void writeCircuitResume(library);
    void writeReconvergent();
    
    //debugs with couts
    void debugInOut();
    void debugBits();
};



/////////////////////////INTERFACE  - MYPROGRAM/////////////////////////
class MyProgram {
    circuit circuit_obj;
    library library_obj;
public:
    MyProgram();
    bool interface(vector<string>,int);
    //void print_all_gates();
    //void print_all_signals();
    virtual ~MyProgram();
    
private:
    //string removeBlankSpaces(string);
    string wordSelector(string,int);
    string limpa(string);
    string doErase(string,int);
    //string doEraseIO(string,int);
    bool ignore(string);
    bool isGate(string);
    bool isInOut(string);
    bool isSig(string);
    void runCommand(string);
    
    library readLibV(std::ifstream& read_param, string lib_name);
    library readLiberty(ifstream& read_param, string lib_name);
    library readGenlib(ifstream&,string);
    void readCircuit(ifstream&,string);
    map <string,signal*> createMapPinSignal(string line,gate* gate_obj);
};



#endif /* CLASSES_H */