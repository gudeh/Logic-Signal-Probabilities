/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyProgram.cpp
 * Author: root
 * 
 * Created on August 23, 2016, 10:02 PM
 */

#include "classes.h"





MyProgram::MyProgram()  {
    
}
//string MyProgram::removeBlankSpaces(string param){
//    
//    cout<<"in :"<<param<<endl;
//    std::string::iterator end_pos = std::remove(param.begin(), param.end(), ' ');
//    param.erase(end_pos, param.end());
//    cout<<"out:"<<param<<endl;
//    return param;
//}]


//pretty similar do doErase, although this is better used on genlib
//returns a word from a phrase, words are expected to be separeted by any number of blank spaces
string MyProgram::wordSelector(string line, int word_index){
    int i=1;
    line.erase(0,line.find_first_not_of(" "));
    while(i<word_index)
    {
        line.erase(0,line.find_first_not_of(' '));
        line.erase(0,line.find_first_of(' ')+1);
        line.erase(0,line.find_first_not_of(' '));
        i++;
    }
    if(line.find(' ')!=string::npos)
        line.erase(line.find_first_of(' '),line.size());
    cout<<line<<endl;
    return line;
    
}
string MyProgram::limpa(string param){
    
    while((param.find(' ')!=string::npos) || (param.find(',')!=string::npos) || (param.find(';')!=string::npos) || (param.find('(')!=string::npos) || (param.find(')')!=string::npos) || (param.find('.')!=string::npos))
    {
        if((param.find('.')!=string::npos))
            param.erase(param.find_first_of('.'),param.find_first_of('.')+1);
        if(param.find(' ')!=string::npos)
            param.erase(param.find_first_of(' '),param.find_first_of(' ')+1);
        
        if(param.find(',')!=string::npos)
            param.erase(param.find_first_of(','),param.find_first_of(',')+1);
        
        if(param.find(';')!=string::npos)
            param.erase(param.find_first_of(';'),param.find_first_of(';')+1);
        
        if(param.find('(')!=string::npos)
            param.erase(param.find_first_of('('),param.find_first_of('(')+1);
        
        if(param.find(')')!=string::npos)
            param.erase(param.find_first_of(')'),param.find_first_of(')')+1);
    }
    return param;
}
string MyProgram::doErase(string param, int word_index){
//    cout<<"dentro:"<<param<<" index:"<<word_index<<endl;
    if(param.find("module")==string::npos)
    {
        replace( param.begin(), param.end(), ',', ' ');
        replace( param.begin(), param.end(), '(', ' ');
        replace( param.begin(), param.end(), ')', ' ');
    }
    int i=1;
    param.erase(0,param.find_first_not_of(' '));
    while(i<word_index)
    {
        param.erase(0,param.find_first_not_of(' '));
        param.erase(0,param.find_first_of(' ')+1);
        param.erase(0,param.find_first_not_of(' '));
        i++;
    }
//    for(int i=0;i<param.size();i++)
//    {
//        if(param[i]==" " || param[i]=="(" || param[i]==")")
//            param
//    }
    if(param.find(' ')!=string::npos)
        param.erase(param.find_first_of(' '),param.size());
    param=limpa(param);
//    cout<<"fora:"<<param<<endl;
  
    return param;
}
bool MyProgram::ignore(string param){
    if(param.find_first_not_of(' ')==string::npos)
        return true;
    else if(param.find("module")!=string::npos)
        return true;
    else if(param.find("//")!=string::npos)
        return true;
    else if(param.find("assign")!=string::npos)
        return true;
    else
        return false;
}
bool MyProgram::isInOut(string param){
    if(param.find("input")!=string::npos || param.find("output")!=string::npos)
        return true;
    else 
        return false;
}
bool MyProgram::isGate(string param){
    if(param.find('.')!=string::npos)
        return true;
//    else if (param.find("module")==string::npos && param.find("input")==string::npos
//             && param.find("output")==string::npos && param.find("wire")==string::npos
//            && param.find("assign")==string::npos && param.find_first_not_of(" ")!=string::npos)
//        return true;
    else 
        return false;
}
bool MyProgram::isSig(string param){
    if(param.find("wire")!=string::npos || param.find("register")!=string::npos || param.find("reg")!=string::npos)
        return true;
    else 
        return false;
}
map <string,signal*> MyProgram::createMapPinSignal(string line,gate* gate_ptr){
    map<string,signal*> pin_and_signal;
    map<string,signal*>::iterator it_pin;
    string pin_name,signal_name;
    signal* signal_ptr;
    
//    cout<<"gate to be added pins "<<gate_ptr->getName()<<" with "<<gate_ptr->getInputsPointer().size()<<" signals."<<endl;
    for(int i=4;i<=((gate_ptr->getCell().getInput().size()+gate_ptr->getCell().getOutput().size())*2)+2;i+=2)
    {
        string line_aux=line;
//        cout<<"line_aux:"<<line_aux<<endl;
//        line_aux.erase(0,line_aux.find_first_of('.')+1);
//        line.erase(0,line.find_first_of('.')+1);
//        line_aux.erase(line_aux.find_first_of(' '),line_aux.size());
        pin_name=doErase(line,i-1);
        signal_name=doErase(line,i);
//        cout<<"pin "<<pin_name<<" signal "<<signal_name<<endl;
        
        for(int j=0;j<gate_ptr->getInputsPointer().size();j++)
        {
            if(signal_name==gate_ptr->getInputsPointer()[j]->getName())
                signal_ptr=gate_ptr->getInputsPointer()[j];
        }
        for(int j=0;j<gate_ptr->getOutputsPointer().size();j++)
        {
            if(signal_name==gate_ptr->getOutputsPointer()[j]->getName())
                signal_ptr=gate_ptr->getOutputsPointer()[j];
        }
        
        pin_and_signal.insert(pair<string,signal*> (pin_name,signal_ptr));
    }
//    for(it_pin=pin_and_signal.begin();it_pin!=pin_and_signal.end();it_pin++)
//        cout<<it_pin->first<<"->"<<it_pin->second->getName()<<endl;
    return pin_and_signal;
}

library MyProgram::readLibV(std::ifstream& read_param, string lib_name){
    cout<<"Reading library file(.v)"<<endl;
    string line,cell_name;
    library mylibrary(lib_name);
    vector <string> input,output;
        
    while (getline(read_param,line))
    {
        if((line.find("module")!=string::npos) && line.find("endmodule")==string::npos)
        {
            input.clear();
            output.clear();
            while(line.find("endmodule")==string::npos)
            {
                if(line.find("module")!=string::npos)
                    cell_name=doErase(line,2);
                if(line.find("input")!=string::npos)
                    input.push_back(doErase(line,2));
                if(line.find("output")!=string::npos)
                    output.push_back(doErase(line,2));
                getline(read_param,line);
            }
            cell cell_obj (cell_name,input,output);
            
            mylibrary.pushCell(cell_name,cell_obj);
        }
    }
//    mylibrary.printLibrary();
    return mylibrary;
}
library MyProgram::readLiberty(ifstream& read_param, string lib_name){
    cout<<"Reading library liberty type"<<endl;
    string line,cell_name,pin_name,logic_func;
    library mylibrary(lib_name);
    vector <string> input,output;
    map <string,string> logic_funcs;
    int brackets=0,inside_brackets=0;
    double power,area;
        
    while (getline(read_param,line))
    {
        if(line.find("cell (")!=string::npos && line.find("{")!=string::npos)
        {
            brackets=1;
            input.clear();
            output.clear();
            logic_funcs.clear();
            line.erase(0,line.find_first_of('(')+1);
            line.erase(line.find_last_of(')'),line.size());
            cell_name=line;
            while(brackets>0 && getline(read_param,line))
            {
                if(line.find('{')!=string::npos)
                    brackets++;
                if(line.find('}')!=string::npos)
                    brackets--;
                if(line.find("cell_leakage_power :")!=string::npos)
                {
//                    cout<<"RJAEOPJRIPAE"<<endl;
                    
                    line.erase(0,line.find(":")+2);
                    line.erase(line.find(";"),line.size());
                    power=atof(line.c_str());
//                    cout<<power<<endl;
                }
                if(line.find("area :")!=string::npos)
                {
//                    cout<<"RJAEOPJRIPAE"<<endl;
//                    double area;
                    line.erase(0,line.find(":")+2);
                    line.erase(line.find(";"),line.size());
                    area=atof(line.c_str());
//                    cout<<power<<endl;
                }
                if(line.find("pin(")!=string::npos)
                {
                    line.erase(0,line.find_first_of('(')+1);
                    line.erase(line.find_last_of(')'));
                    pin_name=line;
                    inside_brackets=1;
                    
                    while(inside_brackets>0 && getline(read_param,line))
                    {
//                        cout<<"JRAEIORJIOEA"<<endl;
                        //TODO -> CHECK IF 2 OUTPUTS ARE BEING CONSIDERED
                        if(line.find("function :")!=string::npos)
                        {
                            line.erase(0,line.find_first_of('"')+1);
                            line.erase(line.find_last_of('"'));
//                            cout<<"pin:"<<pin_name<<"/logic_func:"<<line<<endl;
                            logic_func=line;
                            logic_funcs.insert(pair<string,string> (pin_name,logic_func));
                        }
                        if(line.find("direction : output")!=string::npos)
                            output.push_back(pin_name);
                        if(line.find("direction : input")!=string::npos)
                            input.push_back(pin_name);
                        if(line.find('{')!=string::npos)
                        {
                            brackets++;
                            inside_brackets++;
                        }
                        if(line.find('}')!=string::npos)
                        {
                            brackets--;
                            inside_brackets--;
                        }
                    }
                }       
            }
        cell cell_obj (cell_name,input,output,logic_funcs);
        cell_obj.setArea(area);
        cell_obj.setPower(power);
        mylibrary.pushCell(cell_name,cell_obj);
        }
    }
//    mylibrary.printLibrary();
    return mylibrary;
}


library MyProgram::readGenlib(ifstream& read_param, string lib_name){
    cout<<"Reading library genlib type"<<endl;
    string line,aux,cell_name,pin_name,logic_func;
    library mylibrary(lib_name);
    vector <string> input,output;
    map <string,string> logic_funcs;
    int brackets=0,inside_brackets=0;
    
        while (getline(read_param,line))
    {
            if(line.find("GATE")!=string::npos)
            {
                aux=line;
                aux.erase(0,aux.find_first_of(" ")+1);
                aux.erase(aux.find_first_of(" "),line.size());
                cout<<"cell name:"<<aux<<endl;
                
                aux=line;
                aux=wordSelector(aux,1);
                cell_name=aux;
            }
    }
    
    return mylibrary;
}


void MyProgram::readCircuit(ifstream& read_param, string circuit_name){
    cout<<"Reading circuit:"<<circuit_name<<endl;
    int input_num,output_num,i=0;
    string line,line_aux,line_aux2,gate_name,gate_type,signal_name;

    

    circuit_obj.clear();
    circuit_obj.setName(circuit_name);
    //circuit_obj.setName();
    signal signal_obj("1'b1");
//    circuit_obj.pushSignal(signal_obj);
//    circuit_obj.setVoidOnSignalSource("1'b1");


    while (getline(read_param,line))
    {
    //////////////////////CREATING SIGNALS//////////////////////////
        if(!ignore(line) && ((isSig(line) || isInOut(line) )) )
        {

            while(line.find(';')==string::npos)
            {
                getline(read_param,line_aux);
                line.append(line_aux);
            }
            line.erase(0,line.find_first_of(' ',line.find_first_not_of(' '))+1);
                while(!line.empty())
                {
                    signal_name=doErase(line, 1);
                   
                    if(line.find(',')!=string::npos)   
                        line.erase(0,line.find_first_of(',')+1);
                    else
                        line.clear();

                    if(!circuit_obj.isSignalInside(signal_name))
                    {
//                        cout<<signal_name<<endl;
                        signal signal_obj(signal_name);
                        circuit_obj.pushSignal(signal_obj);
                    }
                } 
            }
//        }
        
        
    //////////////////////CREATING GATES///////////////////////////
        if(!ignore(line) && isGate(line))
        {
//            cout<<"Line:"<<line<<endl;
            map<string,signal*> pin_and_signal;
//            map<string,string>::iterator it_pin;
            while(line.find(';')==string::npos)
            {
                getline(read_param,line_aux);
                line.append(line_aux);
            }
            gate_name=doErase(line,2);
//            cout<<"gate_name"<<gate_name<<endl;
            gate_type=doErase(line,1);
//            cout<<"gate_type:"<<gate_type<<endl;
            
            gate gate_obj(library_obj,gate_name,gate_type);
            circuit_obj.pushGate(gate_obj);
            
            input_num=library_obj.findCell(gate_type).getInput().size();
            output_num=library_obj.findCell(gate_type).getOutput().size();
            
            for(i=4;i<=(input_num*2)+2;i+=2)
            {
                
                signal_name=doErase(line,i);
//                cout<<"index:"<<i<<" sig_name:"<<signal_name<<endl;
                circuit_obj.setDriveEInput(signal_name,gate_name);
            }
            for(i;i<=((input_num+output_num)*2) +2;i+=2)
            {
//                cout<<"index:"<<i;
                signal_name=doErase(line,i);
//                cout<<" outsig_name:"<<signal_name<<endl;
                if(signal_name!="")
                    circuit_obj.setSourceEOutput(signal_name,gate_name);
                else
                    circuit_obj.pushVoidOnGateOutput(gate_name);
            }
            
            pin_and_signal=createMapPinSignal(line,circuit_obj.getGatePointer(gate_name));
            circuit_obj.getGatePointer(gate_name)->setMapPinSignal(pin_and_signal);
        }
    }
    
    /////////////////////////CREATING CIRCUIT////////////////////////
    read_param.close();
    read_param.open(circuit_name.c_str(), ios::in);

    line.clear();
    while (getline(read_param,line))
    {
//        cout<<"line:"<<line<<endl;
        if(!ignore(line) && isInOut(line))
        {
            while(line.find(';')==string::npos)
            {
                getline(read_param,line_aux2);
                line.append(line_aux2);
            }
            line_aux=line;
            string line_main=line;
//            cout<<"line:"<<line<<endl;
            line.erase(0,line.find_first_of(' ',line.find_first_not_of(' '))+1);
                while(!line.empty())
                {
                    signal_name=doErase(line, 1);
//                    cout<<"signal_name:"<<signal_name<<endl;
                    if(line.find(',')!=string::npos)   
                        line.erase(0,line.find_first_of(',')+1);
                    else
                        line.clear();
                    if(signal_name==circuit_obj.getSignalPointer(signal_name)->getName())
                    {
                        if(line_aux.find("input")!=string::npos)
                        {
                            circuit_obj.setVoidOnSignalSource(signal_name);
                            circuit_obj.pushIn(circuit_obj.getSignalPointer(signal_name));
                        }
                        else if (line_aux.find("output")!=string::npos)
                        {
                            circuit_obj.pushVoidOnSignalDestination(signal_name);
                            circuit_obj.pushOut(circuit_obj.getSignalPointer(signal_name));
                        }
                        else
                            cout<<"Nao encontrado nem input, nem output na linha:"<<line<<endl;
                    }
                    else
                        cout<<"Algo errado, signal nao encontrado em all_signals."<<endl;

                }
//            }
        }
    }
//    return circuit_obj;
}

void MyProgram::runCommand(string command){
    ifstream read_lib,read_circ;
    string lib_name, circuit_name,str;
    if(command=="v")
        {
//            lib_name="mcnc.genlib";
//            read_lib.open(lib_name.c_str());
//            library_obj=readGenlib(read_lib,lib_name);
            
            lib_name="libr.lib";
            circuit_name="c5315.v";
            read_lib.open(lib_name.c_str());
            read_circ.open(circuit_name.c_str());
            if(lib_name.find(".v")!=string::npos)
                library_obj=readLibV(read_lib,lib_name);

            else if (lib_name.find(".lib")!=string::npos)
                library_obj=readLiberty(read_lib,lib_name);
//            library_obj.printLibrary();
            
            readCircuit(read_circ,circuit_name);
           // circuit_obj.setVoidOnSignalSource("\\2GAT");
           // cout<<"===============>"<<circuit_obj.getGatePointer("g0")->getInputsPointer()[0]->getSourcePointer()->getName()<<endl;
            
            circuit_obj.printCircuit();
            circuit_obj.printAllGates();
            circuit_obj.printAllSignals();
            
            //circuit_obj.writeCircuitResume(library_obj);
           circuit_obj.findReconvergentPaths();
//            circuit_obj.setProbSignalPropagation();
//            circuit_obj.printDumbProbabilities();
//            circuit_obj.setProbabilitiesDepth();
            circuit_obj.setProbabilitiesDepthNew();
//            circuit_obj.printGatesInfo();
//            circuit_obj.printProbabilities();
//            circuit_obj.debugInOut();
//            circuit_obj.checkLevels();
        }
        else if(command.find("read_library")==0)
        { 
            command.erase(0,command.find_first_of(" ")+1);
            if(command.find(".v")==string::npos && command.find(".lib")==string::npos || command.find(" ")!=string::npos)
                cout<<"File name not expected."<<endl;
            else
            {
                lib_name=command;
                read_lib.close();
                read_lib.open(lib_name.c_str());
                if(read_lib.is_open())
                {
                    if(lib_name.find(".v")!=string::npos)
                        library_obj=readLibV(read_lib,lib_name);

                    else if (lib_name.find(".lib")!=string::npos)
                        library_obj=readLiberty(read_lib,lib_name);
                }
                else
                    cout<<"Error, file not open. Is the file name correct?"<<endl;
            }
            
        }
        else if(command.find("read_circuit")==0)
        {
            command.erase(0,command.find_first_of(" ")+1);
            if(command.find(".v")==string::npos || command.find(" ")!=string::npos)
                cout<<"File name not expected."<<endl;
            else
            {
                circuit_name=command;
                read_circ.close();
                read_circ.open(circuit_name.c_str());
                if(read_circ.is_open())
                    readCircuit(read_circ,circuit_name);
                else
                    cout<<"Error, file not open. Is the file name correct?"<<endl;
            }
        }
        else if (command.find("find_reconvergent")!=string::npos)
            circuit_obj.findReconvergentPaths();
        else if (command.find("compute_levels")!=string::npos)//compute_levels
            circuit_obj.checkLevels();
        else if(command.find("compute_probabilities")!=string::npos && command.size()==21)
            circuit_obj.setProbSignalPropagation();
        else if(command.find("compute_old_probabilities")!=string::npos)
            circuit_obj.setProbabilitiesDepth();
        else if(command.find("compute_new_probabilities")!=string::npos)
            circuit_obj.setProbabilitiesDepthNew();
//        else if(command.find("compute_probabilities_exhaustive")!=string::npos && command.size()==32)
//            circuit_obj.setProbSignalPropagation();
        else if(command.find("print_reconvergent")!=string::npos)
            circuit_obj.printReconvergent();
        else if(command.find("print_probabilities")!=string::npos && command.size()==19)
            circuit_obj.printProbabilities();
//        else if(command.find("print_old_probabilities")!=string::npos)
//            circuit_obj.printOldProbabilities();
//        else if(command.find("print_probabilities_exhaustive")!=string::npos && command.size()==30)
//            circuit_obj.printDumbProbabilities();
        else if(command.find("print_library")!=string::npos)
            library_obj.printLibrary();
        else if(command.find("print_circuit")!=string::npos)
            circuit_obj.printCircuit();
        else if((command.find("print_gates")!=string::npos) && (command.size()==11))
            circuit_obj.printAllGates();
        else if(command.find("print_signals")!=string::npos)
            circuit_obj.printAllSignals();
        else if(command.find("print_level_on_gates")!=string::npos)
            circuit_obj.printLevelOnGates();
        else if(command.find("print_gates_info")!=string::npos && command.size()==16)
            circuit_obj.printGatesInfo();
        else if(command.find("write_probabilities")!=string::npos)
        {
            str=command;
            str.erase(0,20);
            circuit_obj.writeProbabilities(str);
        }
//            else if(command.find("write_old_probabilities")!=string::npos)
//        {
//            str=command;
//            str.erase(0,23);
//            circuit_obj.writeOldProbabilities(str);
//        }
        else if (command.find("write_input_prob_each_gate")!=string::npos)
            circuit_obj.writeInputProbEachGate();
        else if(command.find("write_table")!=string::npos)
            circuit_obj.writeProbabilityTable();
        else if (command.find("write_fanout_count")!=string::npos)
            circuit_obj.writeSignalVSFanout();
        else if (command.find("write_reconvergent")!=string::npos)
            circuit_obj.writeReconvergent();
        else if (command.find("write_resume")!=string::npos)
            circuit_obj.writeCircuitResume(library_obj);
//        else if(command.find("write_probabilities_exhaustive")!=string::npos && command.size()==30)
//            circuit_obj.writeDumbProbabilities();
        
        
        else if(command.find("help")!=string::npos)
        {
            cout<<"Input commands:"<<endl;
            cout<<"read_library [library_name]"<<endl;
            cout<<"read_circuit [circuit_name]"<<endl;
            cout<<endl<<"Operation commands:"<<endl;
            cout<<"compute_levels"<<endl;
            cout<<"find_reconvergent"<<endl;
            cout<<"compute_probabilities"<<endl;
            cout<<"compute_old_probabilities"<<endl;
            cout<<"compute_new_probabilities"<<endl;
//            cout<<"compute_probabilities_exhaustive"<<endl;
            cout<<endl<<"Printing commands:"<<endl;
            cout<<"print_library"<<endl;
            cout<<"print_circuit"<<endl;
            cout<<"print_gates"<<endl;
            cout<<"print_signals"<<endl;
            cout<<"print_reconvergent"<<endl;
            cout<<"print_probabilities"<<endl;
//            cout<<"print_old_probabilities"<<endl;
//            cout<<"print_probabilities_exhaustive"<<endl;
            cout<<"print_level_on_gates"<<endl;
            cout<<"print_gates_info"<<endl;
            cout<<endl<<"File output commands:"<<endl;
            cout<<"write_probabilites"<<endl;
//            cout<<"write_old_probabilites"<<endl;
            cout<<"write_input_prob_each_gate"<<endl;
            cout<<"write_table"<<endl;
            cout<<"write_fanout_count"<<endl;
            cout<<"write_reconvergent"<<endl;
            cout<<"write_resume"<<endl;
//            cout<<"write_probabilities_exhaustive"<<endl;
            cout<<endl;
        }
        
        else if(command.find("quit")==0)
        {
            cout<<"Bye"<<endl;
        }
        else
            cout<<"Unexpected command. Please use 'help' for a list of commands."<<endl;
}

bool MyProgram::interface(vector<string> param_argv,int param_argc){
    
        
    int command_count=1;
    string lib_name, circuit_name,str,command,line;
    char input[100];
    ifstream read_lib,read_circ,readzin;
    

    while(command!="quit")
    {
        if(command_count<10)
            cout<<"00";
        else if(command_count<100)
            cout<<"0";
        cout<<command_count<<">>";
        
        if(param_argc==1)
        {
            
            //cout<<"param_argv1:"<<param_argv[1]<<endl;
            cin.getline(input,sizeof(input));
            command=(string)input;
            runCommand(command);
        }
        else if (param_argv[1]=="--script" || param_argv[1]=="--s")
        {
            readzin.open(param_argv[2].c_str());
            if(readzin.is_open())
            {
                while(getline(readzin,line))
                {
                    command=line;
                    cout<<command<<endl;
                    if(command=="quit")
                        return true;
                    runCommand(line);
                }
            }
            else
                cout<<"Error, couldn't open script file. (interface)"<<endl;
        }
        else
            cout<<"Error, unexpected behavior on interface."<<endl;
        
        
        command_count++;
    }
}



MyProgram::~MyProgram() {}

