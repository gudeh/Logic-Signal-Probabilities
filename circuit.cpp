/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   classes.cpp
 * Author: gudeh
 * 
 * Created on 10 de Maio de 2016, 14:24
 */

#include "classes.h"


////////////////////CIRCUIT///////////////////////
circuit::circuit(){
    null_gate_in.setName("null_gate_in");
    null_gate_out.setName("null_gate_out");
    null_gate_out.tag();
    null_gate_in.tag();
    null_signal.setName("null_signal");
}

circuit::circuit(string circuit_name){
    name=circuit_name;
    null_gate_in.setName("null_gate_in");
    null_gate_out.setName("null_gate_out");
    null_gate_out.tag();
    null_gate_in.tag();
    null_signal.setName("null_signal");
}

void circuit::pushIn(signal* param){
    input.push_back(param);
}

void circuit::pushOut(signal* param){
    output.push_back(param);
}

void circuit::pushGate(gate param){
    all_gates.insert(pair<string,gate> (param.getName(),param));
}

void circuit::pushSignal(signal param){
    all_signals.insert(pair<string,signal> (param.getName(),param));
}

signal* circuit::getSignalPointer(string param){
    map <string,signal>::iterator it_signal;
    if((it_signal=all_signals.find(param))!=all_signals.end())
        return(&it_signal->second);
    else
        cout<<"Erro, signal nao encontrado em all_signals.(getSignalPointer)"<<endl;
    
}


gate* circuit::getGatePointer(string param){
    map <string,gate>::iterator it_gate;
    if((it_gate=all_gates.find(param))!=all_gates.end())
        return(&it_gate->second);
    else
        cout<<"Erro, gate nao encontrado em all_gates. (getGatePointer)"<<endl;         
}


void circuit::setDriveEInput(string signal_name, string gate_name){
    map <string,signal>::iterator it_signal;
    map <string,gate>::iterator it_gate;
    gate* gate_ptr;
    signal* signal_ptr;
    if((it_gate=all_gates.find(gate_name))!=all_gates.end())
        gate_ptr=this->getGatePointer(gate_name);
    else
        cout<<"Error, gate not found in all_gates.(setDriveEInput)"<<endl;
    
    
    if((it_signal=all_signals.find(signal_name))!=all_signals.end())
        signal_ptr=this->getSignalPointer(signal_name);
    else
    {
        cout<<"Error, signal "<<signal_name<<" not found in all_signals.(setDriveEInput)"<<endl;
//        for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
//            cout<<it_signal->first<<",";
//        cout<<endl;
    }
    
    it_gate->second.pushInput(signal_ptr);
    it_signal->second.pushDrivePointer(gate_ptr);
}

void circuit::setSourceEOutput(string signal_name, string gate_name){
    map <string,signal>::iterator it_signal;
    map <string,gate>::iterator it_gate;
    gate* gate_ptr;
    signal* signal_ptr;
    if((it_gate=all_gates.find(gate_name))!=all_gates.end())
        gate_ptr=this->getGatePointer(gate_name);
    else
        cout<<"Erro, gate nao encontrado em all_gates.(setSourceEOutput)"<<endl;
    
    if((it_signal=all_signals.find(signal_name))!=all_signals.end())
        signal_ptr=this->getSignalPointer(signal_name);
    else
    {
        cout<<"Erro, signal "<<signal_name<<" nao encontrado em all_signals.(setSourceEOutput)"<<endl;
        for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
            cout<<it_signal->first<<",";
        cout<<endl;
    }
    
    it_gate->second.pushOutput(signal_ptr);
    it_signal->second.setSourcePointer(gate_ptr);
}

void circuit::setVoidOnSignalSource(string signal_name){
    map <string,signal>::iterator it_signal;
    if((it_signal=all_signals.find(signal_name))!=all_signals.end())
    {
        it_signal->second.setSourcePointer(&this->null_gate_in);
        this->null_gate_in.pushOutput(&it_signal->second);
    }
    else
        cout<<"Erro, signal "<<signal_name<<" nao encontrado em all_signals.(setVoidOnSignalSource)"<<endl;
}

void circuit::pushVoidOnSignalDestination(string signal_name){
    map <string,signal>::iterator it_signal;
    if((it_signal=all_signals.find(signal_name))!=all_signals.end())
    {
        it_signal->second.pushDrivePointer(&this->null_gate_out);
        this->null_gate_out.pushOutput(&it_signal->second);
    }
    else
        cout<<"Erro, signal "<<signal_name<<" nao encontrado em all_signals.(pushVoidOnSignalDestination)"<<endl;
    
}

void circuit::pushVoidOnGateOutput(string gate_name){
    map <string,gate>::iterator it_gate;
    if((it_gate=all_gates.find(gate_name))!=all_gates.end())
    {
        it_gate->second.pushOutput(&null_signal);
        this->null_signal.pushDrivePointer(&it_gate->second);
    }
    else
        cout<<"Erro, gate "<<gate_name<<" nao encontrado em all_gates.(pushVoidOnGateOutput)"<<endl;

}

void circuit::printCircuit(){
    map <string,signal>::iterator it_signal;
    map <string,gate>::iterator it_gate;
    
    cout<<null_gate_out.getName();
//    cout<<this->null_gate_in.getOutputsPointer()[1]->getName();
    cout<<"Circuit name:"<<name;
    cout<<endl<<endl<<"Inputs"<<"("<<input.size()<<"):";
    for(int i=0; i<input.size();i++)
        cout<<input[i]->getName()<<",";
    cout<<endl<<endl<<"Outputs:"<<"("<<output.size()<<")";
    for(int i=0; i<output.size();i++)
        cout<<output[i]->getName()<<",";
    cout<<endl<<endl<<"Signals inside"<<"("<<all_signals.size()<<"):";
    for(it_signal=all_signals.begin(); it_signal!=all_signals.end(); it_signal++)
    {
        cout<<it_signal->second.getName();
        cout<<",";
    }
    cout<<endl<<endl<<"Gates inside"<<"("<<all_gates.size()<<"):";
    for(it_gate=all_gates.begin();it_gate!=all_gates.end();it_gate++)
    {
        cout<<it_gate->second.getName();
        cout<<",";
    }
    cout<<endl;
}

void circuit::printAllGates(){
    cout<<"Number of gates:"<<all_gates.size()<<endl;
    map <string,gate>::iterator it_gate;
    for(it_gate=all_gates.begin();it_gate!=all_gates.end();it_gate++)
        it_gate->second.printGate();
}

void circuit::printAllSignals(){
    cout<<"Number of signals:"<<all_signals.size()<<endl;
    map <string,signal>::iterator it_signal;
    for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
        it_signal->second.printSignal();
}

void circuit::writeCircuitResume(library lib){
    int fanout_count=0;
    ofstream write;
    map<string,signal>::iterator it_signal;
    map <string,gate>::iterator it_gate;
    map<string,cell> mapzin;
    map<string,cell>::iterator it_lib;
    map<string,int> type_count;
    map<string,int>::iterator it_type;
    write.open("circuit resume.csv", ios::app);
    write<<"Nome,Gates,Sinais,";
    mapzin=lib.getMap();
    for(it_lib=mapzin.begin();it_lib!=mapzin.end();it_lib++)
        write<<it_lib->first<<",";
    write<<"Fanouts"<<endl;
    write<<this->name<<","<<this->all_gates.size()<<","<<this->all_signals.size()<<",";
    
    
    for(it_lib=mapzin.begin();it_lib!=mapzin.end();it_lib++)
        type_count.insert(pair<string,int> (it_lib->first,0));
    
    for(it_lib=mapzin.begin();it_lib!=mapzin.end();it_lib++)
    {
        for(it_gate=all_gates.begin();it_gate!=all_gates.end();it_gate++)
        {
            if(it_gate->second.getType()==it_lib->first)
            {
                type_count.find(it_lib->first)->second++;
            }
        }
    }
    
    for(it_type=type_count.begin();it_type!=type_count.end();it_type++)
        write<<it_type->second<<",";
    
    for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
    {
        if(it_signal->second.getDrivesPointer().size()>1) //if this signal is a fanout then ++
            fanout_count++;
    }
    write<<fanout_count<<","<<endl;
          
   
}

int circuit::checkLevels(){
    this->untagAll();
    
    vector<map <string,gate>::iterator> gates_stack;
    map<string,gate>::iterator it_gate;
    int i=0,lvls=0;
    
    for(int k=0;k<this->input.size();k++)
        input[k]->getSourcePointer()->setLevel(0);
    //depth search
    for(i=0;i<this->output.size();i++)
    {
//        cout<<this->output.size()<<endl;
        if((it_gate=all_gates.find(this->output[i]->getSourcePointer()->getName()))==all_gates.end()) //for each circuit output.
            cout<<"ERROR, the gate "<<this->output[i]->getSourcePointer()->getName()<<" was not found on "<<this->output[i]->getName()<<"(chechLevels)"<<endl;
//        cout<<this->output[i].getName()<<endl;
//        cout<<it_gate->first<<endl;
//        while(!it_gate->second.isCircuitOutput(this->output.front().getName()))
//            it_gate++;

        gates_stack.push_back(it_gate);
        while(!gates_stack.empty())
        {
//            cout<<endl;
//            cout<<"The stack: ";
//            cout<<gates_stack.size()<<"->";
//            for(int j=0;j<gates_stack.size();j++)
//                cout<<gates_stack[j]->first<<",";
//            cout<<endl;
//            
//            cout<<"All sources from "<<it_gate->first<<":";
//            for(int x=0;x<it_gate->second.getInputsPointer().size();x++)
//                cout<<it_gate->second.getInputsPointer()[x]->getSourcePointer()->getName()<<",";
//                cout<<endl;
            if(lvls<gates_stack.size())
                lvls=gates_stack.size();
            it_gate->second.setLevel(gates_stack.size());
            if(it_gate->second.isFinalLevel())
            {
//                cout<<"Trying to remove: "<<it_gate->first<<endl;
                it_gate->second.tag();
                gates_stack.pop_back();
                it_gate=gates_stack.back();
            }
            else
            {
//                cout<<"Trying to find gate "<<it_gate->second.getSignalToSmallerLvl()->getSourcePointer()->getName()<<endl;
                it_gate=all_gates.find(it_gate->second.getSignalToSmallerLvl()->getSourcePointer()->getName());
//                cout<<"Adding "<<it_gate->first<<" to the stack."<<endl;
                gates_stack.push_back(it_gate);
//                
            }
        }
    }
    int j=0;
    for(it_gate=all_gates.begin();it_gate!=all_gates.end();it_gate++)
    {
        if(it_gate->second.isTagged())
            j++;
        it_gate->second.setLevel((it_gate->second.getLevel()-lvls-1)*(-1) );
    }
    cout<<"Circuit level: "<<lvls<<endl;
    cout<<j<<" gates were tagged on the depth-first search. From a total of "<<all_gates.size()<<" gates in the circuit."<<endl;
    return lvls;
}

void circuit::setProbSignalPropagation(){
    cout<<"Setting signal probabilities through exhaustive mode (signal propagation)."<<endl;
    double wall_depois,wall_antes,cpu_antes,cpu_depois;
    this->untagAll();
    this->resetAllBits();
    this->resetAllProb(0);
    vector<map <string,gate>::iterator> gates_stack;
    map<string,signal>::iterator it_signal;
    map<string,gate>::iterator it_gate;
    
    
    //Asking for input signals probabilities
    this->askForInputProb();
    
    cout<<"Total number of iterations:"<<pow(2,null_gate_in.getOutputsPointer().size())<<endl;
    /////////////////////SIGNAL PROPAGATION STARTS HERE//////////////////////////////////
    wall_antes=getWallTime();
    cpu_antes=getCpuTime(); 
    for(int n=0;n<pow(2,null_gate_in.getOutputsPointer().size());n++)
    {
        if(n%1000==0)
            cout<<"Working on iteration: "<<n<<endl;
//        cout<<n<<",";
        //cout<<endl<<endl;
        this->resetAllNotInBits();
        this->untagAll();
        //cout<<null_gate_in.getOutputsPointer().size()<<;
        for(int a=0;a<null_gate_in.getOutputsPointer().size();a++)
        {
            if(n%(int)(pow(2,a))==0)
                null_gate_in.getOutputsPointer()[a]->changeBit();
        }    
        //cout<<endl;
//        for(int b=0;b<null_gate_in.getOutputsPointer().size();b++)
//            cout<<null_gate_in.getOutputsPointer()[b]->getName()<<":"<<null_gate_in.getOutputsPointer()[b]->getBit();
//            cout<<endl;
        
        for(int i=0;i<this->output.size();i++)//for each circuit output.
        {
            if((it_gate=all_gates.find(this->output[i]->getSourcePointer()->getName()))==all_gates.end()) 
                cout<<"ERROR, the gate "<<this->output[i]->getSourcePointer()->getName()<<" was not found on "<<this->output[i]->getName()<<"(setProbSignalPropagation1)"<<endl;
            
            gates_stack.push_back(it_gate);
            

            
            
            
            while(!gates_stack.empty()) //propagating THE SIGNALS, not the probabilities
            {
                
//                for(int x=0;x<gates_stack.size();x++)
//                    cout<<gates_stack[x]->first<<",";
//                cout<<endl;
                
//                cout<<"1;"<<gates_stack.back()->first<<endl;
                if(gates_stack.back()->second.hasAllBitInputSet())
                {
//                    cout<<"1.1;";
                    it_gate->second.propagateBit();
                    gates_stack.back()->second.tag();
                    gates_stack.pop_back();
                    if(!gates_stack.empty())
                            it_gate=gates_stack.back();
                }
                else
                {
//                    cout<<"1.2;";
                    if((it_gate=all_gates.find(gates_stack.back()->second.getNextGate()->getName()))==all_gates.end()) 
                        cout<<"ERROR, the gate "<<gates_stack.back()->second.getNextGate()->getName()<<" was not found on "<<this->output[i]->getName()<<"(setProbSignalPropagation2)"<<endl;
                    
                    gates_stack.push_back(it_gate);
                }
            }
        }
        //////////DONE SETTING THE BITS////////
        
        
        /////////now set the probabilities from the bit values///////
        
        double x;
        for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
        {
            if(it_signal->second.getSourcePointer()->getName()!="null_gate_in" && it_signal->second.getBit()==1)
            {
                x=1;
                for(int a=0;a<null_gate_in.getOutputsPointer().size();a++)
                {
                    if(null_gate_in.getOutputsPointer()[a]->getBit()==1)
                        x*=null_gate_in.getOutputsPointer()[a]->getProbability();
                    else
                        x*=(1-null_gate_in.getOutputsPointer()[a]->getProbability());
                }
               // cout<<"signal "<<it_signal->second.getName()<<" had prob: "<<it_signal->second.getProbability();
                it_signal->second.setProbability((it_signal->second.getProbability()+x));
                //cout<<". Now has prob: "<<it_signal->second.getProbability()<<endl;
            }
        }
    }
    wall_depois=getWallTime();
    cpu_depois=getCpuTime();
    this->probability_info.calculation_type="Signal propagation (exahustive)";
    this->probability_info.cpu_time=cpu_depois-cpu_antes;
    this->probability_info.human_time=wall_depois-wall_antes;
//    double p=pow(2,null_gate_in.getOutputsPointer().size());
}

void circuit::setProbabilitiesDepthNew(){
    cout<<"Setting probabilities through depth-first search with reconvergence awarness."<<endl;
    this->untagAll();
    this->resetAllProb(-1.0);
    
    double wall_depois,wall_antes,cpu_antes,cpu_depois;
    vector<map <string,gate>::iterator> gates_stack;
    map<string,gate>::iterator it_gate;
    
    
    for(int i=0;i<null_gate_in.getOutputsPointer().size();i++)
        null_gate_in.getOutputsPointer()[i]->setProbability(0.5);
        
    wall_antes=getWallTime();
    cpu_antes=getCpuTime();
    //for each circuit output
    for(int i=0;i<this->output.size();i++)
    {
        //One DFS for each output
        if((it_gate=all_gates.find(this->output[i]->getSourcePointer()->getName()))==all_gates.end()) //for each circuit output.
            cout<<"ERROR, the gate "<<this->output[i]->getSourcePointer()->getName()<<" was not found on "<<this->output[i]->getName()<<"(setProbabilitiesDepthNew)"<<endl;
    
        gates_stack.push_back(it_gate);
        while(!gates_stack.empty())
        {
//            for(int x=0;x<gates_stack.size();x++)
//                cout<<gates_stack[x]->first<<",";
//            cout<<endl;
//            for(int x=0;x<gates_stack.size();x++)
//            {
//                cout<<gates_stack[x]->first<<",";
////                for(int a=0;a<gates_stack[x]->second.getOutputsPointer().size();a++)
////                {
////                    for(int b=0;b<gates_stack[x]->second.getOutputsPointer()[a]->getDrivesPointer().size();b++)
////                        cout<<gates_stack[x]->second.getOutputsPointer()[a]->getDrivesPointer()[b]->getName()<<endl;
////                }
//                
//            }
//            cout<<endl;
            if(it_gate->second.hasAllInputSet())
            {
//                cout<<"Gate "<<it_gate->first<<" being solved"<<endl;
                //if gate isn't a sink solve its output probability directly
                if(!it_gate->second.isSink())
                    it_gate->second.setGateProbability();
                //if the gate is a sink, solve with reconvergent data
                else
                    it_gate->second.setSinkProbability(this);
                    
                it_gate->second.tag();
                gates_stack.pop_back();
                it_gate=gates_stack.back();
            }
//                else
//                    cout<<"ERROR, gate "<<it_gate->first<<" is final but doenst have all inputs set.(setProbabilitiesDepth)"<<endl;
            else
            {
                it_gate=all_gates.find(it_gate->second.getNextGate()->getName());
                gates_stack.push_back(it_gate);
            }
        }
    
    }
    wall_depois=getWallTime();
    cpu_depois=getCpuTime();
    this->probability_info.calculation_type="Depth First (reconvergence aware)";
    this->probability_info.cpu_time=cpu_depois-cpu_antes;
    this->probability_info.human_time=wall_depois-wall_antes;
}

void circuit::setProbabilitiesDepth(){
    cout<<"Setting probabilities through depth-first search, no reconvergence handled."<<endl;
    this->untagAll();
    this->resetAllProb(-1.0);
    
    double wall_depois,wall_antes,cpu_antes,cpu_depois;
    vector<map <string,gate>::iterator> gates_stack;
    map<string,gate>::iterator it_gate;
    
    
    this->askForInputProb();
        
    wall_antes=getWallTime();
    cpu_antes=getCpuTime();
    //for each circuit output   
    for(int i=0;i<this->output.size();i++)
    {
        //One DFS for each output
        if((it_gate=all_gates.find(this->output[i]->getSourcePointer()->getName()))==all_gates.end()) //for each circuit output.
            cout<<"ERROR, the gate "<<this->output[i]->getSourcePointer()->getName()<<" was not found on "<<this->output[i]->getName()<<"(setProbabilitiesDepth)"<<endl;
    
        gates_stack.push_back(it_gate);
        while(!gates_stack.empty())
        {
//            for(int x=0;x<gates_stack.size();x++)
//                cout<<gates_stack[x]->first<<",";
//            cout<<endl;
//            for(int x=0;x<gates_stack.size();x++)
//            {
//                cout<<gates_stack[x]->first<<",";
////                for(int a=0;a<gates_stack[x]->second.getOutputsPointer().size();a++)
////                {
////                    for(int b=0;b<gates_stack[x]->second.getOutputsPointer()[a]->getDrivesPointer().size();b++)
////                        cout<<gates_stack[x]->second.getOutputsPointer()[a]->getDrivesPointer()[b]->getName()<<endl;
////                }
//                
//            }
//            cout<<endl;
//            cout<<"working on gate "<<it_gate->first<<endl;
            if(it_gate->second.hasAllInputSet())
            {
                it_gate->second.setGateProbability();
                it_gate->second.tag();
                gates_stack.pop_back();
                it_gate=gates_stack.back();
            }
//                else
//                    cout<<"ERROR, gate "<<it_gate->first<<" is final but doenst have all inputs set.(setProbabilitiesDepth)"<<endl;
            else
            {
                it_gate=all_gates.find(it_gate->second.getNextGate()->getName());
                gates_stack.push_back(it_gate);
            }
        }
    
    }
    wall_depois=getWallTime();
    cpu_depois=getCpuTime();
    this->probability_info.calculation_type="Depth First (no reconvergence handled)";
    this->probability_info.cpu_time=cpu_depois-cpu_antes;
    this->probability_info.human_time=wall_depois-wall_antes;
}

void circuit::setName(string param){
    this->name=param;
}

void circuit::printProbabilities(){
    if(this->probability_info.calculation_type=="")
    {
        cout<<"ERROR, probabilities weren't calculated"<<endl;
        return;
    }
    else
    {
        
        map<string,signal>::iterator it_signal;
        for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
            cout<<it_signal->second.getName()<<":"<<it_signal->second.getProbability()<<endl;
        cout<<"Probabilities were calculated by "<<this->probability_info.calculation_type<<endl;
        cout<<"Human time to calculate the probabilities "<<this->probability_info.human_time<<endl;
        cout<<"Time measured by cpu usage "<<this->probability_info.cpu_time<<endl;
    }
}

void circuit::writeProbabilities(string param){
    if(this->probability_info.calculation_type=="")
    {
        cout<<"ERROR, probabilities weren't calculated"<<endl;
        return;
    }
    else
    {
        ofstream write;
        if(param=="")
        {
            param.append(this->name);
            param.append(" ");
            param.append(this->probability_info.calculation_type);
        }
            param.append(".txt");
        
        write.open(param, ofstream::out | ofstream::trunc);
        map<string,signal>::iterator it_signal;
        
        for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
            write<<it_signal->second.getName()<<":"<<it_signal->second.getProbability()<<endl;
        write<<"Probabilities were calculated by "<<this->probability_info.calculation_type<<endl;
        write<<"Human time to calculate the probabilities "<<this->probability_info.human_time<<endl;
        write<<"Time measured by cpu usage "<<this->probability_info.cpu_time<<endl;
        write.close();
    }
}

void circuit::writeProbabilityTable(){
    ofstream write;
    write.open("Table.csv", ofstream::out | ofstream::app);
    write<<endl;
    //        NAME                  CALCULATION TYPE                         NUMBER OF INPUT SIGNALS                HUMAN TIME TO CALCULATE      CPU TIME TO CALCULATE
    write<<this->name<<","<<this->probability_info.calculation_type<<","<<this->null_gate_in.getOutputsPointer().size()<<","<<this->probability_info.human_time<<","<<this->probability_info.cpu_time<<endl;
    write.close();
}

//void circuit::printDumbProbabilities(){
//    map<string,signal>::iterator it_signal;
//    for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
//        cout<<it_signal->second.getName()<<":"<<it_signal->second.getProbability()<<endl;
//
//}

bool circuit::isSignalInside(string param){
    if(all_signals.find(param)==all_signals.end())
        return false;
    else
        return true;
}

void circuit::untagAll(){
    map<string,gate>::iterator it_gate;
    for(it_gate=all_gates.begin();it_gate!=all_gates.end();it_gate++)
    {
        it_gate->second.untagFanoutCheck();
        it_gate->second.untag();
        it_gate->second.setVisitCount(0);
    }
}

void circuit::debugInOut(){
    cout<<"These should be outputs from the circuit: "<<endl;
    for(int a=0;a<this->output.size();a++)
    {
        cout<<"gate:"<<output[a]->getSourcePointer()->getName()<<" has signal "<<output[a]->getName()<<". Which has destinations:";
        for(int b=0;b<output[a]->getDrivesPointer().size();b++)
                cout<<output[a]->getDrivesPointer()[b]->getName()<<",";
        cout<<endl;
    }
    
    cout<<"These should be inputs from the circuit: "<<endl;
    for(int a=0;a<this->input.size();a++)
    {
        cout<<"Signal:"<<input[a]->getName()<<" comes from "<<input[a]->getSourcePointer()->getName()<<" goes to gates:";
        for(int b=0;b<input[a]->getDrivesPointer().size();b++)
            cout<<input[a]->getDrivesPointer()[b]->getName()<<",";
        cout<<endl;
    }
}

void circuit::printLevelOnGates(){
    for(map<string,gate>::iterator it_gate=all_gates.begin();it_gate!=all_gates.end();it_gate++)
    {
        cout<<it_gate->first<<":"<<it_gate->second.getLevel()<<endl;
    }
}

void circuit::printGatesInfo(){
    for(map<string,gate>::iterator it_gate=all_gates.begin();it_gate!=all_gates.end();it_gate++)
    {
        cout<<"gate_name:"<<it_gate->first<<"\tarea:"<<it_gate->second.getCell().getArea()<<"\t";
        cout<<"power:"<<it_gate->second.getCell().getPower()<<endl;
    }
}


void circuit::resetAllProb(double param){
    map<string,signal>::iterator it_signal;
    for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
        it_signal->second.setProbability(param);
}

void circuit::resetAllBits(){
    map<string,signal>::iterator it_signal;
    for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
            it_signal->second.resetBit();
}

void circuit::resetAllNotInBits(){
    map<string,signal>::iterator it_signal;
    for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
    {
        if(it_signal->second.getSourcePointer()->getName()!="null_gate_in")
            it_signal->second.resetBit();
    }
}

void circuit::setAllBitsZero(){
    map<string,signal>::iterator it_signal;
    for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)  
            it_signal->second.setBit(0);
}

void circuit::debugBits(){
    cout<<"List of bits inside each signal in the circuit:"<<endl;
    map<string,signal>::iterator it_signal;
    for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
        cout<<it_signal->first<<":"<<it_signal->second.getBit()<<endl;
    
}



//void circuit::writeProbabilities(string param){
//    ofstream write;
//    if(param=="")
//        write.open("probabilities exhaustive.txt", ofstream::out | ofstream::trunc);
//    else
//    {
//        param.append(".txt");
//        write.open(param, ofstream::out | ofstream::trunc);
//    }
//    map<string,signal>::iterator it_signal;
//    for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
//            write<<it_signal->second.getName()<<":"<<it_signal->second.getProbability()<<endl;
//    write.close();
//}

//void circuit::suicide(circuit* circuit_param){
//    delete this;
//    circuit_param=0;
//    
//}


string circuit::getName(){
    return this->name;
}


void circuit::writeInputProbEachGate(){
    ofstream write;
    write.open("Input on each gate");
    map<string,gate>::iterator it_gate;
    
    for(it_gate=all_gates.begin();it_gate!=all_gates.end();it_gate++)
    {
        write<<it_gate->first<<"\t\t"<<it_gate->second.getType()<<"\t\t";
        for(int a=0;a<it_gate->second.getInputsPointer().size();a++)
        {
            write<<it_gate->second.getInputsPointer()[a]->getProbability()<<"\t\t";
        }
        write<<endl;
    }
    write.close();
}


void circuit::clear(){
    this->all_gates.clear();
    this->all_signals.clear();
    this->name.clear();
    this->input.clear();
    this->output.clear();
    this->probability_info.calculation_type="";
    this->probability_info.cpu_time=0;
    this->probability_info.human_time=0;
    this->null_gate_in.clear();
    this->null_gate_out.clear();
    this->null_signal.clear();
    this->clusters.clear();
}


double circuit::getWallTime(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
double circuit::getCpuTime(){
    return (double)clock() / CLOCKS_PER_SEC;
}




vector<map <string,gate>::iterator> circuit::recursiveDFS(vector<map <string,gate>::iterator> gates_stack){
    possible_cluster possible_obj;
    
//    cout<<"DFS on path:"<<endl;
//    for(int i=0;i<gates_stack.size();i++)
//        cout<<gates_stack[i]->first<<",";
//    cout<<endl;
    
    //check if input signal is a fanout
        for(int j=0;j<gates_stack.back()->second.getInputsPointer().size();j++) //for each input signal in the gate
        {
            if(gates_stack.back()->second.getInputsPointer()[j]->getDrivesPointer().size()>1) //if a fanout was found
            {
                //save the path, as a possible reconvergent one
                possible_obj.fanout_source=gates_stack.back()->second.getInputsPointer()[j];
                possible_obj.path=gates_stack;
                all_possible_paths.push_back(possible_obj);
            }
        }
//    cout<<"4"<<endl;
//    cout<<gates_stack.back()->first<<endl;
    //continuing the DFS recursively
    bool aux=true;
    for(int b=0;b<gates_stack.back()->second.getInputsPointer().size();b++)
    {
        if(gates_stack.back()->second.getInputsPointer()[b]->getSourcePointer()->getName()!="null_gate_in")
        {
            aux=false;
//            cout<<"gate "<<gates_stack.back()->second.getInputsPointer()[b]->getSourcePointer()->getName()<<" is not null_gate_in"<<endl;
        }
    }

//    cout<<"5"<<endl;
    if(!aux)
    {
        for(int a=0;a<gates_stack.back()->second.getInputsPointer().size();a++)
        {
            if(gates_stack.back()->second.getInputsPointer()[a]->getSourcePointer()->getName()!="null_gate_in")
            {
                gates_stack.push_back(all_gates.find(gates_stack.back()->second.getInputsPointer()[a]->getSourcePointer()->getName()));
                this->recursiveDFS(gates_stack);
                gates_stack.pop_back();
            }
        }
    }
    else
        gates_stack.pop_back();
    
//    cout<<"STACK:";
//    for(int u=0;u<gates_stack.size();u++)
//        cout<<gates_stack[u]->first<<",";
//    cout<<endl;
    
    return gates_stack;
}

struct myComp{
    bool operator()(const FOL_count param1,const FOL_count param2) const{
//        cout<<"COMPARINNGGGGGGGG: "<<param1.signal_pointer->getName()<<"="<<param1.signal_pointer->getSourcePointer()->getLevel()<<" and "<<param2.signal_pointer->getName()<<"="<<param2.signal_pointer->getSourcePointer()->getLevel()<<endl;
        if(param1.signal_pointer==param2.signal_pointer)
            return true;
        else if(param1.signal_pointer->getSourcePointer()->getLevel() < param2.signal_pointer->getSourcePointer()->getLevel())
            return true;
        else if(param1.signal_pointer->getSourcePointer()->getLevel() > param2.signal_pointer->getSourcePointer()->getLevel())
            return false;
    //    cout<<"THIS CANT HAPPENNNNNNNNNNNNNNNNNNNNNNNNNNN"<<endl;
    }
};
    
void circuit::findReconvergentPaths(){
    this->null_signal.setName("null_signal");
    this->untagAll();
    double wall_antes,cpu_antes,wall_depois,cpu_depois;
    
    vector<map <string,gate>::iterator> gates_stack;
    map<string,gate>::iterator it_gate;
    
    wall_antes=getWallTime();
    cpu_antes=getCpuTime(); 
  
//    for (it_possible_sink=all_gates.begin();it_possible_sink!=all_gates.end();it_possible_sink++) //depth search on each gate
//    {
//        cout<<"DFS being done on:"<<it_possible_sink->first<<endl;
//        all_possible_paths.clear();
//        this->untagAll();
//        gate_name=it_possible_sink->first;
//        gates_stack.clear();
//        gates_stack.push_back(it_possible_sink);
//        gates_stack=this->recursiveDFS(gates_stack); //call to recursive depth-first search
//      
//        
//        vector<possible_cluster>::iterator possible_ita,possible_itb;
//        
////        cout<<"ALL PATHS TO BE COMPARED:"<<endl;
////        for(int a=0;a<all_possible_paths.size();a++)
////        {
////            cout<<all_possible_paths[a].fanout_source->getName()<<":";
////            for(int b=0;b<all_possible_paths[a].path.size();b++)
////                cout<<all_possible_paths[a].path[b]->first<<",";
////            cout<<endl;
////        }
//        //checking for paths that actually reconverge and dividing them in clusters        
//        for(possible_ita=all_possible_paths.begin();possible_ita!=all_possible_paths.end();)
//        {
//            reconvergent_obj.clear();
//            for(possible_itb=possible_ita+1;possible_itb!=all_possible_paths.end();)
//            {
////                cout<<"COMPARING:";
////                for(int g=0;g<possible_ita->path.size();g++)
////                    cout<<possible_ita->path[g]->first<<",";
////                cout<<endl;
////                cout<<"with:";
////                for(int g=0;g<possible_itb->path.size();g++)
////                    cout<<possible_itb->path[g]->first<<",";
////                cout<<endl;
//                if(possible_ita->fanout_source->getName()==possible_itb->fanout_source->getName()) //if the path has the same source
//                {
//                    if(possible_ita->path[0]->first==possible_itb->path[0]->first) //and the same sink
//                    {
//                        if(reconvergent_obj.getGatePaths().size()==0)
//                            {
//                                reconvergent_obj.setSource(possible_ita->fanout_source);
//                                reconvergent_obj.addGatePaths(possible_ita->path);
//                                //reconvergent_obj.setLogicFunction();
//                            }
//                        reconvergent_obj.addGatePaths(possible_itb->path);
//                        all_possible_paths.erase(possible_itb);
//                    }
//                    else
//                        possible_itb++;
//                }
//                else
//                    possible_itb++;
//            }
//            
//            if(reconvergent_obj.getGatePaths().size()>0)
//            {
////                reconvergent_obj.setLogicFunction();
//                all_clusters.push_back(reconvergent_obj);
//            }
//            
//            all_possible_paths.erase(possible_ita);
//        }
//        all_possible_paths.clear();
//    }
//    
//    all_clusters_aux=all_clusters;

    
    
    /////////////////looking for reconvergences///////////////////////
    //setting gates' logic level
    this->checkLevels();
    
    //setting Fan Out Lists (FOL) on each circuit input 
    FOL_count fol_obj;
    vector<FOL_count> FOL_vec(20);
    for(int t=0;t<this->input.size();t++)
    {
        FOL_vec.clear();
        if(input[t]->getDrivesPointer().size()>1)
        {
//            cout<<"----------->"<<input[t]->getName()<<endl;
            fol_obj.count=1;
            fol_obj.signal_pointer=&all_signals.find(input[t]->getName())->second;
            FOL_vec.push_back(fol_obj);
            input[t]->setFOL(FOL_vec);
        }
        else
        {
//            fol_obj.count=1;
//            fol_obj.signal_pointer=&this->null_signal;
//            FOL_vec.push_back(fol_obj);
            input[t]->setFOL(FOL_vec);
        }
    }
    
    
//    cout<<"INPUT FOLS:"<<endl;
//    for(int t=0;t<this->input.size();t++)
//    {
//        cout<<input[t]->getName()<<":";
//        for(int o=0;o<input[t]->getFOL().size();o++)
//            cout<<input[t]->getFOL()[o].signal_pointer->getName()<<',';
//            cout<<endl;
//    }
//    cout<<endl;
    //DFS on each output gate
    for(int t=0;t<this->output.size();t++)
    {
        it_gate=all_gates.find(output[t]->getSourcePointer()->getName());
//        this->resetFOLs();
        gates_stack.clear();
        gates_stack.push_back(it_gate);
        
        //DFS
        while(!gates_stack.empty())
        {
//            cout<<"STACK:";
//            for(int y=0;y<gates_stack.size();y++)
//                cout<<gates_stack[y]->first<<",";
//            cout<<endl;
            vector<FOL_count> FOL_vec,RFOL_vec;
            FOL_count fol_obj;
            bool confere=false,confere2=false;
            if(gates_stack.back()->second.isFinalReconverg())
            {
                //set each gate's output fol
                //check for RFOL
                
                //uniting input FOLs
                if(gates_stack.back()->second.getInputsPointer().size()>1)
                {
                    RFOL_vec.clear();
                    FOL_vec=gates_stack.back()->second.getInputsPointer()[0]->getFOL();
                    for(int in=1;in<gates_stack.back()->second.getInputsPointer().size();in++)
                    {
                        for(int u=0;u<gates_stack.back()->second.getInputsPointer()[in]->getFOL().size();u++)
                        {
                            confere=false;
                            for(int y=0;y<FOL_vec.size();y++)
                            {
                                if(FOL_vec[y].signal_pointer==gates_stack.back()->second.getInputsPointer()[in]->getFOL()[u].signal_pointer) 
                                {
                                    
                                    FOL_vec[y].count=FOL_vec[y].count+gates_stack.back()->second.getInputsPointer()[in]->getFOL()[u].count;
                                    confere=true;
                                    fol_obj.count=FOL_vec[y].count;
                                    fol_obj.signal_pointer=FOL_vec[y].signal_pointer;
//                                    FOL_vec[y].signal_pointer->addRFOL(fol_obj
                                    confere2=false;
                                    for (int h=0;h<RFOL_vec.size();h++)
                                    {
                                        if(RFOL_vec[h].signal_pointer==fol_obj.signal_pointer)
                                        {
                                            RFOL_vec[h].count=RFOL_vec[h].count+fol_obj.count;
                                            confere2=true;
                                            break;
                                        }
                                    }

                                    if(confere2==false)
                                        RFOL_vec.push_back(fol_obj);
                                    
                                    break;
                                }
                            }
                            if(confere==false)
                                FOL_vec.push_back(gates_stack.back()->second.getInputsPointer()[in]->getFOL()[u]);
                        }
                    }
                }
                else if(gates_stack.back()->second.getInputsPointer().size()==1)
                    FOL_vec=gates_stack.back()->second.getInputsPointer()[0]->getFOL();
                    
                else
                {
                    cout<<"ERROR, inputs has neither >1 neither ==1 size (findReconvergentPaths)"<<endl;
                    return;
                }
                
                sort(FOL_vec.begin(),FOL_vec.end(),myComp());
                if(RFOL_vec.size()>1);
                    sort(RFOL_vec.begin(),RFOL_vec.end(),myComp());
                //each output has a differente behavior with the united FOL
                for(int s=0;s<gates_stack.back()->second.getOutputsPointer().size();s++)
                {
                    //if this output is a fan out
                    if(gates_stack.back()->second.getOutputsPointer()[s]->getDrivesPointer().size()>1)
                    {
                        fol_obj.count=1;
                        fol_obj.signal_pointer=&all_signals.find(gates_stack.back()->second.getOutputsPointer()[s]->getName())->second;
                        FOL_vec.push_back(fol_obj);
                        gates_stack.back()->second.getOutputsPointer()[s]->setFOL(FOL_vec);
                        
                        if(RFOL_vec.size()>=1)
                        {
                            tupla tupla_obj;
                            tupla_obj=rfolReduction(FOL_vec,RFOL_vec);
                            RFOL_vec=tupla_obj.rfol;
                            FOL_vec=tupla_obj.fol;
                            gates_stack.back()->second.getOutputsPointer()[s]->setFOL(FOL_vec);
                            gates_stack.back()->second.getOutputsPointer()[s]->setRFOL(RFOL_vec);//RFOL REDUCED
                        }
                            
                        
                        //pop itself out for the next output
                        FOL_vec.pop_back(); 
                    }
                    else
                    {
                        gates_stack.back()->second.getOutputsPointer()[s]->setFOL(FOL_vec);
                        if(RFOL_vec.size()>=1)
                        {
                            tupla tupla_obj;
                            tupla_obj=rfolReduction(FOL_vec,RFOL_vec);
                            RFOL_vec=tupla_obj.rfol;
                            FOL_vec=tupla_obj.fol;
                            gates_stack.back()->second.getOutputsPointer()[s]->setFOL(FOL_vec);
                            gates_stack.back()->second.getOutputsPointer()[s]->setRFOL(RFOL_vec); //RFOL REDUCED
                        }
                    }
                    
                    //saving primary sources of reconvergence
                    vector<FOL_count> primary_RFOL;
                    primary_RFOL.clear();
                    bool conf=false;
                    for(int v=0;v<RFOL_vec.size();v++)
                    {
                        //if the signal in rfol has only itself on its fol then it is a primary source
                        if(RFOL_vec[v].signal_pointer->getFOL().size()==1 && RFOL_vec[v].signal_pointer->getFOL()[0].signal_pointer==RFOL_vec[v].signal_pointer)
                        {
                            primary_RFOL.push_back(RFOL_vec[v]);
                            conf=true;
                        }
                        else
                        {
                            for(int t=0;t<RFOL_vec[v].signal_pointer->getFOL().size();t++)
                            {
                                conf=false;
                                if(RFOL_vec[v].signal_pointer->getFOL()[t].signal_pointer!=RFOL_vec[v].signal_pointer)
                                {
                                    for(int a=0;a<RFOL_vec.size();a++)
                                    {
                                        if(RFOL_vec[a].signal_pointer==RFOL_vec[v].signal_pointer->getFOL()[t].signal_pointer)
                                        {
                                            conf=true;
                                            break;
                                        }
                                    }
                                }
                                if(conf)
                                    break;
                            }
                        }
                        if(!conf)
                            primary_RFOL.push_back(RFOL_vec[v]);
                    }
                    if(primary_RFOL.size()>=1)
                    {
                        gates_stack.back()->second.getOutputsPointer()[s]->setPRFOL(primary_RFOL);
                        gates_stack.back()->second.setPRFOL(primary_RFOL);
                    }
                    if(RFOL_vec.size()>=1 && primary_RFOL.size()<=0)
                        cout<<"ERROR. RFOL_vec and primary_RFOL doesnt match. (findReconvergentPaths)"<<endl;
//                    cout<<"primary_RFOL of "<<gates_stack.back()->second.getOutputsPointer()[s]->getName()<<":";
//                    for(int y=0;y<gates_stack.back()->second.getOutputsPointer()[s]->getPRFOL().size();y++)
//                        cout<<gates_stack.back()->second.getOutputsPointer()[s]->getPRFOL()[y].signal_pointer->getName()<<"("
//                                <<gates_stack.back()->second.getOutputsPointer()[s]->getPRFOL()[y].count<<")"<<",";
//                    cout<<endl;
//                    cout<<"FOL of "<<gates_stack.back()->second.getOutputsPointer()[s]->getName()<<":";
//                    for(int y=0;y<gates_stack.back()->second.getOutputsPointer()[s]->getFOL().size();y++)
//                        cout<<gates_stack.back()->second.getOutputsPointer()[s]->getFOL()[y].signal_pointer->getName()<<"("
//                                <<gates_stack.back()->second.getOutputsPointer()[s]->getFOL()[y].count<<")"<<",";
//                    cout<<endl;
//                    cout<<"reduced RFOL of "<<gates_stack.back()->second.getOutputsPointer()[s]->getName()<<":";
//                    for(int y=0;y<gates_stack.back()->second.getOutputsPointer()[s]->getRFOL().size();y++)
//                        cout<<gates_stack.back()->second.getOutputsPointer()[s]->getRFOL()[y].signal_pointer->getName()<<"("
//                                <<gates_stack.back()->second.getOutputsPointer()[s]->getRFOL()[y].count<<")"<<",";
//                    cout<<endl<<endl;
                }
                gates_stack.pop_back();
            }
            else
                gates_stack.push_back(all_gates.find( gates_stack.back()->second.getNextGateReconverg()->getName()));
                
        }
    }
    
    
    

    
    //removing clusters with empty paths
//    for(int c=0;c<all_clusters.size();c++)
//    {
//        if(all_clusters[c].getGatePaths().size()<=1)
//        {
//            all_clusters.erase(all_clusters.begin()+c);
//            all_clusters_aux.erase(all_clusters_aux.begin()+c);
//        }
//    }
//
//    //taking only clusters with primary sources
//    for(int a=0;a<all_clusters.size()-1;a++)
//    {
//        label:
//        for(int b=a+1;b<all_clusters.size();b++)
//        {
//            for(int x=0;x<all_clusters[b].getGatePaths().size();x++)
//            {
//                for(int y=all_clusters[b].getGatePaths()[x].size()-1;y>0;y--)
//                {
//                    if(all_clusters[a].getSource()->getName()==all_clusters[b].getGatePaths()[x][y]->second.getSignalToThisGate(all_clusters[b].getGatePaths()[x][y-1]->second.getName())->getName())
//                    {
//                        all_clusters.erase(all_clusters.begin()+a);
//                        all_clusters_aux.erase(all_clusters_aux.begin()+a);
//                        goto label;
//                    }
//                }
//            }
//        }
//    }
    wall_depois=getWallTime();
    cpu_depois=getCpuTime(); 
    
    this->reconvergent_info.cpu_time=cpu_depois-cpu_antes;
    this->reconvergent_info.human_time=wall_depois-wall_antes;
    this->setSinks();
//    this->debugReconvergent();
    
    //writing each source to each sink
//    map<string,gate>::iterator it;
//    write.open("sink->sources.txt");
//    write<<"circuit:"<<this->name;
//    for(it=this->all_gates.begin();it!=all_gates.end();it++)
//    {
//        if(it->second.isSink())
//        {
//            write<<it->first<<":";
//            for(int h=0;h<it->second.getPRFOL().size();h++)
//                write<<it->second.getPRFOL()[h].signal_pointer->getName()<<",";
//            write<<endl;
//        }
//    }
    
    
       //writing number of sinks and time to find sinks
    int count;
    map<string,gate>::iterator it;
    for(it=all_gates.begin();it!=all_gates.end();it++)
    {
        if(it->second.isSink())
            count++;
    }
    ofstream write;
    write.open("time to find reconvergent.csv", ios::app);
    write<<this->name<<","<<all_gates.size()<<","<<count<<","<<this->reconvergent_info.cpu_time<<endl;
    write.close();
    
}

void circuit::setSinks(){
    //passing reconvergent paths from circuit to each sink gate
//    for(int i=0;i<this->clusters.size();i++)
//    {
//        if(all_gates.find(clusters[i].getGatePaths()[0][0]->first)!=all_gates.end())
//           all_gates.find(clusters[i].getGatePaths()[0][0]->first)->second.addCluster(clusters[i]);
//        else
//            cout<<"ERROR (setSinks)"<<endl;
//    }
    
    //same info on circuit level is redundant
//    this->clusters.clear();
    
    
    //building logic funcion for each sink input signal
    map<string,gate>::iterator sink_it;
    vector<map <string,gate>::iterator> gates_stack;
    string next_gate_name;
//    ofstream writeout;
//    writeout.open("DEBUGANDOAGORAEPA2.txt");
    //asking for input circuit probabilities
    
    
    
    
    /////////////////////////////////UNCOMENT//////////////////////////////////
    this->askForInputProb();
    /////////////////////////////////UNCOMENT//////////////////////////////////
    
    for(sink_it=all_gates.begin(); sink_it!=all_gates.end(); sink_it++)
    {
        //if gate is a sink, do a DFS on it
        if(sink_it->second.isSink())
        {
            
//            writeout<<sink_it->second.getName()<<":";
//            for(int et=0;et<sink_it->second.getPRFOL().size();et++)
//                writeout<<sink_it->second.getPRFOL()[et].signal_pointer->getName()<<",";
//            writeout<<endl;
            
            //for each sink's input signal
            for(int a=0;a<sink_it->second.getInputsPointer().size();a++)
            {
                //DEPTH FIRST SEARCH!
                gates_stack.clear();
                this->untagAll();
//                cout<<"sink:"<<sink_it->first<<endl;
                
                vector<probability_variable> prob_vec;
                probability_variable aux;
                
                //different behaviour if sink's input is its own primary source
                if(sink_it->second.isThisASource(sink_it->second.getInputsPointer()[a]->getName()))
                {
//                    cout<<"rejairejijoreajirea"<<endl;
                    prob_vec.clear();
                    aux.is_number=false;
                    aux.is_operand=true;
                    aux.is_operator=false;
                    aux.variable=sink_it->second.getInputsPointer()[a]->getName();
                    prob_vec.push_back(aux);
                    sink_it->second.getInputsPointer()[a]->setLogicFunction(sink_it->first,prob_vec);
                }
                //start from gate that drives the sink's input
                else if(sink_it->second.getInputsPointer()[a]->getSourcePointer()->getName()!="null_gate_in")
                {
                    gates_stack.push_back(all_gates.find(sink_it->second.getInputsPointer()[a]->getSourcePointer()->getName()));
//                    cout<<endl<<endl;
//                    cout<<"input:"<<sink_it->second.getInputsPointer()[a]->getName()<<endl;
                    while(!gates_stack.empty())
                    {
//                        cout<<"stack:";
//                        for(int h=0;h<gates_stack.size();h++)
//                            cout<<gates_stack[h]->first<<",";
//                        cout<<endl;
                        next_gate_name=gates_stack.back()->second.isFinalSetSink(sink_it->second.getPRFOL());
//                        cout<<"gate name:"<<next_gate_name<<endl;
                        if(next_gate_name=="final")
                        {
    //                        cout<<"certo>>>"<<gates_stack.back()->second.getInputsPointer()[0]->getName()<<":"<<gates_stack.back()->second.getInputsPointer()[0]<<endl;
    //                        cout<<sink_it->second.getMapInputToCluster().begin()->first->getName()<<":"<<sink_it->second.getMapInputToCluster().begin()->first<<endl;
                            gates_stack.back()->second.setLogicFunctionOnOutputs(&sink_it->second,sink_it->second.getPRFOL());

                            //tagging this gate and popping from stack
                            gates_stack.back()->second.tag();
                            gates_stack.pop_back();
                        }
                        else
                            //push the next gate on the stack
                            gates_stack.push_back(all_gates.find(next_gate_name));
                    }
                }
                else
                {
                    prob_vec.clear();
                    aux.is_number=true;
                    aux.is_operand=false;
                    aux.is_operator=false;
                    aux.variable=sink_it->second.getInputsPointer()[a]->getName();
                    prob_vec.push_back(aux);
                    sink_it->second.getInputsPointer()[a]->setLogicFunction(sink_it->first,prob_vec);
                }
                
            }
//            cout<<"Sink:"<<sink_it->first;
//            for(int z=0;z<sink_it->second.getOutputsPointer().size();z++)
//            {
//                cout<<sink_it->second.getOutputsPointer()[z]->getName()<<":";
//                for(int zz=0;zz<sink_it->second.getOutputsPointer()[z]->getLogicFunction(sink_it->first).size();zz++)
//                    cout<<sink_it->second.getOutputsPointer()[z]->getLogicFunction(sink_it->first)[zz].variable<<',';
//                cout<<endl;
//            }
        }
        
    }
//    //checking FOLs
//    map<string,signal>::iterator sig_it;
//    map<string,vector<probability_variable> >::iterator sink_func;
//    map<string,vector<probability_variable> > auxzin;
//    
//    for(sig_it=this->all_signals.begin();sig_it!=all_signals.end();sig_it++)
//    {
////        writeout<<sig_it->first<<":";
////        for(int kk=0;kk<sig_it->second.getFOL().size();kk++)
////            writeout<<sig_it->second.getFOL()[kk].signal_pointer->getName()<<',';
////            writeout<<endl;
//        cout<<"SIGNAL "<<sig_it->first<<endl;
//        if(sig_it->second.getAllLogicFunction().size()>0)
//        {
//            auxzin=sig_it->second.getAllLogicFunction();
//            for(sink_func=auxzin.begin();sink_func!=auxzin.end();sink_func++)
//            {
//                cout<<sink_func->first<<":";
//                for(int x=0;x<sink_func->second.size();x++)
//                    cout<<sink_func->second[x].variable;
//                cout<<endl;
//            }
//            
//        }
//    }
//    writeout.close();
    
    
 
}


void circuit::debugReconvergent(){
    map<int,int> num_sources_to_sink;
    map<int,int>::iterator it;
    map<string,signal>::iterator it_signal;
    map<string,signal*> sources;
    int sinks=0;
    for(it_signal=this->all_signals.begin();it_signal!=all_signals.end();it_signal++)
    {
        if(it_signal->second.getSourcePointer()->getName()!="null_gate_in")
        {
            if(it_signal->second.getPRFOL().size()==0);
//                cout<<"gate "<<it_signal->second.getSourcePointer()->getName()<<" is not a sink";
            else if(it_signal->second.getPRFOL().size()>=1)
            {
//                cout<<"gate "<<it_signal->second.getSourcePointer()->getName()<<" is a sink:";
//                cout<<it_signal->second.getPRFOL().size()<<" sources";
                if(it_signal->second.getSourcePointer()->getOutputsPointer().size()>1)
                    cout<<"gate "<<it_signal->second.getSourcePointer()->getName()<<" has more then 1 output"<<endl;
                
                if(num_sources_to_sink.find(it_signal->second.getPRFOL().size())==num_sources_to_sink.end())
                    num_sources_to_sink.insert(pair<int,int> (it_signal->second.getPRFOL().size(),1));
                else
                    num_sources_to_sink.find(it_signal->second.getPRFOL().size())->second++;
                sinks++;
            }
//            for(int i=0;i<it_signal->second.getRFOL().size();i++)
//                cout<<it_signal->second.getRFOL()[i].signal_pointer->getName()<<"("<<it_signal->second.getRFOL()[i].count<<"),"; 
//            cout<<endl;
            
        }
    }
    ofstream write;
    double um,dois;
    um=((double)sinks/(double)this->all_gates.size())*100;
    dois=((double)sources.size()/(double)this->all_signals.size())*100;
    write.open("sinks sources.csv",ios::app);
    write<<this->getName()<<","<<this->all_gates.size()<<","<<sinks<<","<<(int)um<<"%"<<",";
    write<<this->all_signals.size()<<","<<num_sources_to_sink.rbegin()->first<<","<<num_sources_to_sink.rbegin()->second<<endl;
    write.close();
    
    ofstream write2;
    write2.open("#source each sink.csv",ios::app);
    write2<<this->name<<endl;
    cout<<num_sources_to_sink.size()<<endl;
    for(it=num_sources_to_sink.begin();it!=num_sources_to_sink.end();it++)
        write2<<it->first<<","<<it->second<<endl;
    write2.close();
}


void circuit::writeSignalVSFanout(){
    ofstream write;
    int fanout_count=0;
    map<string,signal>::iterator it_signal;
    write.open("Signals VS fanout.csv", ofstream::app);
    write<<this->name<<",";
    write<<all_signals.size()<<",";
    for(it_signal=all_signals.begin();it_signal!=all_signals.end();it_signal++)
    {
        if(it_signal->second.getDrivesPointer().size()>1) //if this signal is a fanout then ++
            fanout_count++;
    }
    write<<fanout_count<<endl;
    write.close();
}

void circuit::printReconvergent(){
    cout<<"All reconvergent paths found:"<<endl;
    for(int i=0;i<clusters.size();i++)
    {
        cout<<"Cluster "<<i+1<<":"<<endl;
        clusters[i].printReconvergentPath();
//        cout<<"Signal source: "<<clusters[i].getSource()->getName()<<endl;
//        for(int t=0;t<clusters[i].getGatePaths().size();t++)
//        {
//            cout<<"Path "<<t<<": ";
//            for(int j=0;j<clusters[i].getGatePaths()[t].size();j++)
//                cout<<clusters[i].getGatePaths()[t][j]->first<<",";
//            cout<<endl;
//        }
        cout<<endl;
    }
    cout<<"human time to find reconvergent paths: "<<this->reconvergent_info.human_time<<endl;
    cout<<"cpu time to find reconvergent paths: "<<this->reconvergent_info.cpu_time<<endl;
}


void circuit::writeReconvergent(){
    ofstream write;
    write.open("Reconvergent cout.csv", ios::app);
    write<<this->name<<","<<this->clusters.size()<<","<<this->all_gates.size()<<","<<this->all_signals.size()<<","<<endl;
//    write<<"All reconvergent paths found:"<<endl;
//    for(int i=0;i<clusters.size();i++)
//    {
//        write<<"Cluster "<<i+1<<":"<<endl;
//        write<<"Signal source: "<<clusters[i].source->getName()<<endl;
//        for(int t=0;t<clusters[i].getGatePaths().size();t++)
//        {
//            write<<"Path "<<t<<": ";
//            for(int j=0;j<clusters[i].getGatePaths()[t].size();j++)
//                write<<clusters[i].getGatePaths()[t][j]->first<<",";
//            write<<endl;
//        }
//        write<<endl;
//    }
    write.close();
}

//void circuit::prepareToDFS(vector<map<string,gate>::iterator> list_of_gates){
//    this->tagAll();
//    
//    for (int i = 0; i < list_of_gates.size(); i++) 
//        all_gates.find(list_of_gates[i]->first)->second.untag();
//    
//    //cout that shows who is tagged and who is not
////    map <string,gate>::iterator it_gate;
////    for(it_gate=all_gates.begin();it_gate!=all_gates.end();it_gate++)
////    {
////        cout<<it_gate->first<<"->";
////        if(it_gate->second.isTagged())
////            cout<<"tag"<<endl;
////        else
////            cout<<"--"<<endl;
////    }
////    cout<<endl<<endl;
//}


void circuit::tagAll(){
    map<string,gate>::iterator it_gate;
    for(it_gate=all_gates.begin();it_gate!=all_gates.end();it_gate++)
    {
        it_gate->second.tagFanoutCheck();
        it_gate->second.tag();
    }
}

void circuit::resetFOLs(){
    map<string,signal>::iterator it;
    for(it=this->all_signals.begin();it!=all_signals.end();it++)
    {
        if(it->second.getSourcePointer()->getName()!="null_gate_in")
            it->second.resetFOL();
    }
}


tupla circuit::rfolReduction(vector<FOL_count> FOL, vector<FOL_count> RFOL) {
    tupla tupla_obj;
    vector<FOL_count> aux_rfol,new_rfol,multiplier;
    aux_rfol=RFOL;
    int k;
    while(aux_rfol.size()>=1)
    {
//        cout<<"last one:"<<aux_rfol.back().signal_pointer->getName()<<endl;
        int aux;
        aux=aux_rfol.back().count;
        aux_rfol.back().count=1;
        new_rfol.push_back(aux_rfol.back());
        aux_rfol.back().count=aux;
        k=aux_rfol.back().count;
        //FOL of the last member in RFOL
        multiplier=aux_rfol.back().signal_pointer->getFOL();
        //multiply everything with k
        for(int i=0;i<multiplier.size();i++)
            multiplier[i].count=multiplier[i].count*k;

//        cout<<"subtracting:"<<endl;
//        cout<<"-----FOL of:"<<aux_rfol.back().signal_pointer->getName()<<":";
//        for(int j=0;j<multiplier.size();j++)
//            cout<<multiplier[j].signal_pointer->getName()<<"("<<multiplier[j].count<<"),";
//        cout<<endl<<"----RFOL:";
//        for(int i=0;i<aux_rfol.size();i++)
//            cout<<aux_rfol[i].signal_pointer->getName()<<"("<<aux_rfol[i].count<<"),";
//        cout<<endl;
            
        
        //RFOL= RFOL - k*FOL(last RFOL)
        for(int j=0;j<multiplier.size();j++)
        {
            for(int i=0;i<aux_rfol.size();i++)
            {
                if(aux_rfol[i].signal_pointer==multiplier[j].signal_pointer)
                    aux_rfol[i].count=aux_rfol[i].count - multiplier[j].count;
                
                if(aux_rfol[i].count<=0)
                    aux_rfol.erase(aux_rfol.begin()+i);
            }
        }
    }
    
    for(int i=0;i<new_rfol.size();i++)
    {
        for(int j=0;j<FOL.size();j++)
        {
            if(new_rfol[i].signal_pointer==FOL[j].signal_pointer)
            {
                for(int k=0;k<RFOL.size();k++)
                {
                    if(RFOL[k].signal_pointer==FOL[j].signal_pointer)
                        FOL[j].count=FOL[j].count+RFOL[k].count;
                }
            }
        }
    }
    
    sort(new_rfol.begin(),new_rfol.end(),myComp());
    sort(FOL.begin(),FOL.end(),myComp());
    tupla_obj.rfol=new_rfol;
    tupla_obj.fol=FOL;
    
    return tupla_obj;
}




    //looking for duplicates
//    vector<int> counts;
//    for(int a=0;a<all_clusters.size();a++)
//    {  
//        int sum=1;
//        while(sum>0)
//        {
//            counts.clear();
//            for(int o=0;o<all_clusters[a].getGatePaths().size();o++)
//                counts.push_back(0);
//            for(int o=0;o<counts.size();o++)
//                sum=sum+counts[o];
//            
////            cout<<"cluster:"<<endl;
////            all_clusters[a].printReconvergentPath();
////            cout<<"count size:"<<counts.size()<<endl;
////            cout<<"number of paths in this cluster:"<<all_clusters[a].getGatePaths().size()<<endl;
////            cout<<"sum:"<<sum<<endl;
//            
//            for(int x=0;x<all_clusters[a].getGatePaths().size()-1;x++)
//            {
//                for(int y=x+1;y<all_clusters[a].getGatePaths().size();y++)
//                {
//                    for(int t=1;t<all_clusters[a].getGatePaths()[x].size();t++)
//                    {
//                        for (int u=1;u<all_clusters[a].getGatePaths()[y].size();u++)
//                        {
//                            
//                            if(all_clusters[a].getGatePaths()[x][t]->first==all_clusters[a].getGatePaths()[y][u]->first)
//                            {
//                                counts[x]=counts[x]+1;
//                                counts[y]=counts[y]+1;
//                            }
//                        }
//                    }
//                }
//            }
//            int aux=0;
//            sum=0;
//            for(int o=0;o<counts.size();o++)
//                sum=sum+counts[o];
//            
//            for(int o=0;o<all_clusters[a].getGatePaths().size()-1;o++)
//            {
//                if(counts[o+1]>counts[o])
//                    aux=o+1;
//                else
//                    aux=o;
//            }
//            if(sum>0)
//                all_clusters[a].erasePath(aux);
//            
//        }
//    }


void circuit::askForInputProb(){
    string aux,line,signal_name,str;
    int cont=0;
    float prob;
    ofstream write;
    ifstream read;
    stringstream ss;
    write.open("input_probabilities.txt");
    for(int b=0;b<null_gate_in.getOutputsPointer().size();b++)
        write<<null_gate_in.getOutputsPointer()[b]->getName()<<":0.5"<<endl;
    write.close();
    
//    cout<<"A file (input_probabilities.txt) was created with input probabilities, please edit it as you would like before continuing."<<endl<<endl<<"Press enter to continue."<<endl;
//    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    
    read.open("input_probabilities.txt");
    if(read.is_open())
    {

        while(getline(read,line))
        {
            aux=line;
            aux.erase(aux.find(':'),aux.size());
            signal_name=aux;
//            cout<<signal_name;

            aux=line;
            aux.erase(0,aux.find(':')+1);
            str=aux;
            //cout<<" "<<str<<endl;
            ss.clear();
            ss<<str;
            ss>>prob;
//            cout<<" "<<prob<<endl;
            for(int b=0;b<null_gate_in.getOutputsPointer().size();b++)
            {
                if(null_gate_in.getOutputsPointer()[b]->getName()==signal_name)
                {
                    cont++;
                    null_gate_in.getOutputsPointer()[b]->setBit(0);
                    null_gate_in.getOutputsPointer()[b]->setProbability(prob);
                }
            }
        }
        if(cont!=null_gate_in.getOutputsPointer().size())
            cout<<"Error, the number of input signals set on the file is not the same as expected. (askForInputProb)"<<endl;
        read.close();
    }
    else
        cout<<"Error, couldn't open input_probabilities.(askForInputProb)"<<endl;
}


//void circuit::setProbabilityOnThisSink(gate* gate_param){
//    gate_param.prepareToSolveSink();
//}