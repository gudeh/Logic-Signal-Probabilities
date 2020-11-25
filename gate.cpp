/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gate.cpp
 * Author: root
 * 
 * Created on July 12, 2016, 8:16 PM
 */

#include "classes.h"
#include <algorithm>

bool isInPath(vector<FOL_count> FOL, vector<FOL_count> primaries){
    for(int i=0;i<primaries.size();i++)
    {
        for(int j=0;j<FOL.size();j++)
        {
            if(primaries[i].signal_pointer==FOL[j].signal_pointer)
                return true;
        }
    }
    return false;
};

bool isPrimary(signal* sig,vector<FOL_count> primaries){
    for(int i=0;i<primaries.size();i++)
    {
        if(primaries[i].signal_pointer->getName()==sig->getName())
            return true;
    }
    return false;
};

//////////////////////////GATE/////////////////////////////
gate::gate(){
this->name="";
level=0;
tagged=false;
tagged_fanout_check=false;
is_sink=false;
visit_count=0;
};
gate::gate(string cell_name, string cell_type){
    level=0;
    name=cell_name;
    type=cell_type;
    tagged=false;
    tagged_fanout_check=false;
    is_sink=false;
    visit_count=0;
}
gate::gate(library mylibrary,string cell_name, string cell_type){
    level=0;
    tagged=false;
    tagged_fanout_check=false;
    is_sink=false;
    cell celll;
    name=cell_name;
    visit_count=0;
    celll=mylibrary.findCell(cell_type);
    try{        
        if(celll.getType()==cell_type)
        {
            type=cell_type;
            this->cell_obj=celll;
        }
        else throw 1;
    }
    catch (int a){
        cout<<"Celula "<<cell_name<<" nao encontrada, ou seu tipo "<<cell_type<<" bate com o mapa."<<endl;
    }
}

void gate::setName(string param){
    this->name=param;
}
void gate::printGate(){
    cout<<"GATE-> Name:"<<name<<", Type:"<<type<<", Inputs:";
    for(int i=0; i<inputs.size();i++)
        cout<<inputs[i]->getName()<<",";
    cout<<" Outputs:";
    for(int i=0; i<outputs.size();i++)
        cout<<outputs[i]->getName()<<",";
    cout<<endl;
    if(this->is_sink)
    {
        cout<<"This gate is a sink. Primary sources:("<<primary_RFOL.size()<<")";
        for(int i=0;i<this->primary_RFOL.size();i++)
            cout<<primary_RFOL[i].signal_pointer->getName()<<",";
        
//        map<signal*,multipleSource>::iterator map_cluster;
//        for(map_cluster=input_to_cluster.begin();map_cluster!=input_to_cluster.end();map_cluster++)
//        {
//            cout<<"sink's input signal:"<<map_cluster->first->getName()<<endl;
//            map_cluster->second.printMultipleSource();
////            for(int i=0;i<map_cluster->second.getGatePaths().size();i++)
////            {
//////                cout<<map_cluster->second.getSource()->getName()<<":";
////                for(int j=map_cluster->second.getGatePaths()[i].size()-1;j>=0;j--)
////                    cout<<map_cluster->second.getGatePaths()[i][j]->first<<",";
//                    
//                cout<<endl;
////            }
//        }
//        
//        map<signal*,vector<map<string,gate>::iterator> >::iterator it2;
//        for(it2=this->input_to_gates.begin();it2!=this->input_to_gates.end();it2++)
//        {  
//            cout<<it2->first->getName()<<endl;
//            for(int i=0;i<it2->second.size();i++)
//                cout<<it2->second[i]->first<<",";
//            cout<<endl;
//        }
//        cout<<endl;
    }
    cout<<endl<<"---------------------"<<endl;
}
void gate::pushInput(signal* param){
    this->inputs.push_back(param);
}

void gate::pushOutput(signal* param){
    this->outputs.push_back(param);
}

string gate::getName(){
    return this->name;
}

string gate::getType(){
    return this->type;
}

vector<signal*> gate::getInputsPointer(){
    return this->inputs;
}

vector<signal*> gate::getOutputsPointer(){
    return this->outputs;
}

bool gate::isCircuitInput(){
    for(int i=0; i<this->inputs.size();i++)
    {
        if(inputs[i]->getSourcePointer()->getName()=="")
        {
            return true;
        }
    }
    return false;
}

bool gate::isFinalLevel(){
    for(int i=0;i<inputs.size();i++)
    {
        if(inputs[i]->getSourcePointer()->getName()!="null_gate_in")
        {
            if(inputs[i]->getSourcePointer()->getLevel()<this->getLevel())
                return false; 
        }
    }
    return true;
}

string gate::isFinalSetSink(vector<FOL_count> primaries){
//    cout<<"isfinalsetsink on gate "<<this->name<<endl;
    for(int i=0;i<inputs.size();i++)
    {
        if(inputs[i]->getSourcePointer()->getName()!="null_gate_in")
        {
            if(!inputs[i]->getSourcePointer()->isTagged())
            {
//                cout<<"FOL of "<<inputs[i]->getName()<<":";
//                for(int l=0;l<inputs[i]->getFOL().size();l++)
//                    cout<<inputs[i]->getFOL()[l].signal_pointer->getName()<<",";
//                cout<<endl;
                for (int x = 0; x < primaries.size(); x++) 
                {
                    for(int j=0;j<inputs[i]->getFOL().size();j++)
                    {
                        if(primaries[x].signal_pointer==inputs[i]->getFOL()[j].signal_pointer && primaries[x].signal_pointer!=inputs[i])
                            return inputs[i]->getSourcePointer()->getName();
                    }
                }  
            }
        }
    }
    return "final";
}

bool gate::isFinalReconverg(){
    for(int i=0;i<this->inputs.size();i++)
    {
        if(!inputs[i]->isFOLSet())
            return false;
    }
    return true;
}

bool gate::isFinal(){
    for(int i=0;i<inputs.size();i++)
    {
        if(inputs[i]->getSourcePointer()->getName()!="null_gate_in")
        {
            if(!inputs[i]->getSourcePointer()->isTagged())
                return false;
        }
    }
    return true;
}

//bool gate::isFinalSetSinkent(){
//    for(int i=0;i<inputs.size();i++)
//    {
//        if(inputs[i]->getSourcePointer()->getName()!="null_gate_in")
//            return false;
//    }
//    return true;
//}



bool gate::isCircuitOutput(string signal_name){
    for(int i=0; i<this->outputs.size();i++)
    {
        if(outputs[i]->getName()==signal_name)
            return true;
    }
    return false;
}

signal* gate::getSignalToSmallerLvl(){
    for(int i=0;i<inputs.size();i++)
    {
        if(inputs[i]->getSourcePointer()->getName()!="null_gate_in")
        {
            if(inputs[i]->getSourcePointer()->getLevel()<this->getLevel())
//                cout<<"Returning: "<<inputs[i]->getName()<<endl;
                return inputs[i];
        }
    }
}
void gate::tag(){
    tagged=true;
}
bool gate::isTagged(){
    if(tagged)
        return true;
    else
        return false;
}
bool gate::isTaggedFanoutCheck(){
    if(tagged_fanout_check)
        return true;
    else 
        return false;
}
void gate::tagFanoutCheck(){
    this->tagged_fanout_check=true;
}
void gate::untagFanoutCheck(){
    this->tagged_fanout_check=false;
}
int gate::getLevel(){
    return this->level;
}

void gate::setLevel(int param){
    level=param;
}

cell gate::getCell(){
    return this->cell_obj;
}


void gate::setMapPinSignal(map<string,signal*> param){
    this->pin_and_signal=param;
}

int gate::getBits(vector<string> prefix){
    vector<int> stackzin;
    bool invert=false;
    int a,b;

//    for(int c=0;c<prefix.size();c++)
//    {
//        cout<<prefix[c]<<",";
//    }
//    cout<<endl;
    for(int i=0;i<prefix.size();i++)
    {
        if (prefix[i]!="+" && prefix[i]!="*" && prefix[i]!="!" && prefix[i]!="^")
        {
//            write2<<pin_and_signal.find(prefix[i])->second->getName()<<"----->"<<pin_and_signal.find(prefix[i])->second->getProbability()<<endl;
            stackzin.push_back(pin_and_signal.find(prefix[i])->second->getBit());
        }
        else if(prefix[i]=="^")
        {
            a=stackzin.back();
            stackzin.pop_back();
            b=stackzin.back();
            stackzin.pop_back();
            stackzin.push_back((int) (a ^ b));
        }
        else if(prefix[i]=="+")
        {
            a=stackzin.back();
            stackzin.pop_back();
            b=stackzin.back();
            stackzin.pop_back();
            stackzin.push_back((int)(a | b));
        }
        else if(prefix[i]=="*")
        {
            a=stackzin.back();
            stackzin.pop_back();
            b=stackzin.back();
            stackzin.pop_back();
            stackzin.push_back((int)(a & b));
        }
        else if(prefix[i]=="!")
        {
            
            a=stackzin.back();
            stackzin.pop_back();
            if(a==0)
                stackzin.push_back(1);
            else
                stackzin.push_back(0);
        }
    }
//    cout<<"returning:"<<stackzin.back()<<endl;
    return stackzin.back();
}



double gate::getNumbers(vector<string> prefix){
    vector<double> stackzin;
    stackzin.clear();
    bool invert=false;
    double a,b;
//    ofstream write,write2;
//    write.open("otuzin.txt", ofstream::app);
//    write2.open("outzin2.txt", ofstream::app);
    
//    cout<<"gate:"<<this->name<<" Pin_and_signal: "<<endl;
//    for(map<string,signal*>::iterator it=this->pin_and_signal.begin();it!=pin_and_signal.end();it++)
//    {
//        cout<<it->first<<"---->"<<it->second->getName();
//        cout<<endl;
//    }
    
    
//    cout<<"prefix recebido:";
//    for (int j=0;j<prefix.size();j++)
//    {
////        if(pin_and_signal.find(prefix[j])==pin_and_signal.end())
////            cout<<"ERRO UNEXPECTED WTF!"<<prefix[j]<<"-"<<endl;
//        cout<<prefix[j]<<",";
//    }
//    cout<<endl;
    
//    write<<"Resolving:";
//    for(int a=0;a<prefix.size();a++)
//    {
//        write<<prefix[a]<<",";
//
//    }
//    write<<endl;
    if(prefix.size()>1)
    {
        for(int i=0;i<prefix.size();i++)
        {
    //        cout<<"analizing token "<<prefix[i]<<endl;
            if (prefix[i]!="+" && prefix[i]!="*" && prefix[i]!="!" && prefix[i]!="^")
            {
    //            write2<<pin_and_signal.find(prefix[i])->second->getName()<<"----->"<<pin_and_signal.find(prefix[i])->second->getProbability()<<endl;
                stackzin.push_back(pin_and_signal.find(prefix[i])->second->getProbability());
//                cout<<prefix[i]<<" entrou no stackzin com valor "<<pin_and_signal.find(prefix[i])->second->getProbability()<<endl;
//                cout<<prefix[i]<<" esta relacionado com signal "<<pin_and_signal.at(prefix[i])->getName()<<endl;
            }
            else if(prefix[i]=="^")
            {
                a=stackzin.back();
                stackzin.pop_back();
                b=stackzin.back();
                stackzin.pop_back();
                stackzin.push_back((a+b)- (2*(a*b)));
//                cout<<a<<"^"<<b<<"="<<stackzin.back()<<endl;
            }
            else if(prefix[i]=="+")
            {
                a=stackzin.back();
                stackzin.pop_back();
                b=stackzin.back();
                stackzin.pop_back();
                stackzin.push_back((a+b)- (a*b));
//                cout<<a<<"+"<<b<<"="<<stackzin.back()<<endl;
            }
            else if(prefix[i]=="*")
            {
    //            cout<<"Need 2 variables on stackzin, there is "<<stackzin.size()<<endl;
                a=stackzin.back();
                stackzin.pop_back();
                b=stackzin.back();
                stackzin.pop_back();
                stackzin.push_back(a*b);
//                cout<<a<<"*"<<b<<"="<<stackzin.back()<<endl;
            }
            else if(prefix[i]=="!")
            {
                a=stackzin.back();
                stackzin.pop_back();
                stackzin.push_back(1.0-a);
//                cout<<"!"<<a<<"="<<stackzin.back()<<endl;
            }
        }
    }
    else if (prefix.size()==1)
    {
        stackzin.push_back(this->inputs[0]->getProbability());
    }

//    cout<<"Stackzin:";
//    for(int a=0;a<stackzin.size();a++)
//        cout<<stackzin[a]<<",";
//    cout<<endl;
    
    return stackzin.back();
}

//int gate::makeSignalProbability(vector <string> prefix,string pin_name){
//    map<string,signal*>::iterator it_pin;
//    vector<string> aux;
//    int i=0,prob;
//    bool negate=false;
//
//    aux=prefix;
//    while(!aux.empty())
//    {
//        if(aux[i]=="!")
//            negate=true;
//        else if(aux[i]=='+' || aux[i]=='^' || aux[i]==')')
//        {
//            prefix.erase(0,prefix[i]+1);
////            while(getNumbers());
//        }
//        i++;
//    }
//    it_pin=this->pin_and_signal.find(pin_name);
//    it_pin->second->setProbability();
//}

bool gate::isDone(){
    for(int i=0;i<outputs.size();i++)
    {
        for(int j=0;j<outputs[i]->getDrivesPointer().size();j++)
        {
            if(!outputs[i]->getDrivesPointer()[j]->isTagged())
                return false;
        }
    }
    return true;
}

bool gate::hasAllBitInputSet(){
//    cout<<"HasAllBitInputSet:"<<endl;
    for(int i=0;i<this->inputs.size();i++)
    {
//        cout<<inputs[i]->getName()<<":"<<inputs[i]->getBit()<<endl;
        
        if(this->inputs[i]->getBit()<0)
        {
//            cout<<"returnou falso"<<endl;
            return false;
        }
    }
    return true;
}
bool gate::hasAllInputSet(){
    for(int i=0;i<this->inputs.size();i++)
    {
        if(this->inputs[i]->getProbability()<0)
            return false;
    }
    return true;
}

void gate::untag(){
    this->tagged=false;
}

gate* gate::getNextGate(){
    for(int a=0;a<this->inputs.size();a++)
    {
        if(!inputs[a]->getSourcePointer()->isTagged())
        {
            if(inputs[a]->getSourcePointer()->getName()!="null_gate_in")
                return inputs[a]->getSourcePointer();
        }
//        else
//            return;
    }
    cout<<"ERROR, no untagged gate connected to gate "<<this->getName()<<"(getNextGate)"<<endl;
    
}

gate* gate::getNextGateReconverg(){
    for(int a=0;a<this->inputs.size();a++)
    {
        if(!inputs[a]->isFOLSet())
            return inputs[a]->getSourcePointer();
//        else
//            return;
    }
    cout<<"ERROR, no unset FOL signal connected to gate "<<this->getName()<<"(getNextGateReconverg)"<<endl;
}

gate* gate::getNextGateSetSink(vector<FOL_count> primaries){
    for(int a=0;a<this->inputs.size();a++)
    {
        
        if(!inputs[a]->getSourcePointer()->isTagged())
        {
            if(inputs[a]->getSourcePointer()->getName()!="null_gate_in")
            {
                for (int i = 0; i < primaries.size(); i++) 
                {
                    for(int j=0;j<inputs[a]->getFOL().size();j++)
                    {
                        if(primaries[i].signal_pointer==inputs[a]->getFOL()[j].signal_pointer)
                            return inputs[a]->getSourcePointer();
                    }
                }  
            }
                
        } 
    }
    cout<<"ERROR, no untagged gate connected to gate "<<this->getName()<<"(getNextGateSetSink)"<<endl;
    
}

void gate::propagateBit(){
    string func,func_aux,pin_name,str;
    vector <string> pins,aux;
    stringstream ss;
    ofstream write;
//    write.open("outnaguentomais.txt", ofstream::app);
    
    for(int i=0;i<this->cell_obj.getOutput().size();i++)
    {
        func=this->cell_obj.getFunc(this->cell_obj.getOutput()[i]);
//        cout<<"Pin "<<this->cell_obj.getOutput()[i]<<" has function:"<<func<<endl;
        func_aux=func;
        
        if(func.find("NET")==string::npos && func.find("P0")==string::npos)
        {
            reverse(func.begin(),func.end());
//            cout<<"func reverse:"<<func<<endl;
            for(int a=0;a<func.size();a++)
            {
                ss.clear();
                ss<<func[a];
                ss>>str;
                if(func[a]=='!')
                    pins.push_back(str);
                else if (func[a]==' ')
                {
                    if(func[a-1]!='+' && func[a-1]!='^' && func[a-1]!='!')
                    {
                        if(func[a+1]!='+' && func[a+1]!='^' && func[a+1]!='!')
                            aux.push_back("*");
                    }
                }
                
                else if(func[a]=='+' || func[a]=='^' || func[a]==')')
                    aux.push_back(str);
                else if (func[a]=='(')
                {
                    while(aux.back()!=")")
                    {
                        pins.push_back(aux.back());
                        aux.pop_back();
                    }
                    aux.pop_back();
                }
                else
                {
                    pin_name.clear();
                    if(func[a+1]!='+' && func[a+1]!=' ' && func[a+1]!='^' && func[a+1]!=')' && func[a+1]!='(' && func[a+1]!='!')
                    {
                        pin_name.push_back(func[a+1]);
                        pin_name.push_back(func[a]);
                        a++;
                    }
                    else
                        pin_name.push_back(func[a]);
                    pins.push_back(pin_name);
                }
            }
//            if(getBits(pins)==1)
//                pin_and_signal.find(cell_obj.getOutput()[i])->second->addDumbProbability();
        this->pin_and_signal.find(cell_obj.getOutput()[i])->second->setBit(getBits(pins));
//        cout<<this->getName()<<":"<<pin_and_signal.find(cell_obj.getOutput()[i])->second->getName()<<":"<<pin_and_signal.find(cell_obj.getOutput()[i])->second->getBit()<<endl;
        }
    }
    
}

void gate::clear(){
    this->inputs.clear();
    this->outputs.clear();
    if(this->name!="null_gate_in" || this->name!="null_gate_out")
    {
        this->tagged=false;
        this->tagged_fanout_check=false;
    }
    this->level=0;
    visit_count=0;
}

void gate::setVisitCount(int param){
    this->visit_count=param;
}

int gate::getVisitCount(){
    return this->visit_count;
}
    
void gate::checkToTag(){
    this->visit_count++;
    int count=0;
    for(int f=0;f<outputs.size();f++)
        count=count+outputs[f]->getDrivesPointer().size();
    count=count+this->inputs.size();
    count=count*2;
    if(visit_count==count)
    {
        cout<<this->name<<" was tagged. with "<<visit_count<<" visits. count:"<<count<<endl;
        this->tag();
    }
}

void gate::addCluster(cluster param){
    this->is_sink=true;
    signal* signal_pointer;
    multipleSource cluster_obj;
//    vector<vector<map<string,gate>::iterator> > paths;
    for(int i=0;i<param.getGatePaths().size();i++)
    {
        //getting input signal name
        if(param.getGatePaths()[i].size()==1)
        {
            for(int u=0;u<param.getGatePaths()[i][0]->second.getInputsPointer().size();u++)
            {
                if(param.getGatePaths()[i][0]->second.getInputsPointer()[u]->getName()==param.getSource()->getName())
                {
                    signal_pointer=param.getGatePaths()[i][0]->second.getInputsPointer()[u];
                    break;
                }
            }
        }
        else
            signal_pointer=param.getGatePaths()[i][1]->second.getSignalToThisGate(param.getGatePaths()[i][0]->first);
        
            cout<<"confere>>>"<<signal_pointer->getName()<<":"<<signal_pointer<<endl;
        //put path on new cluster
        if(input_to_cluster.find(signal_pointer)==input_to_cluster.end())
        {
            cluster_obj.clear();
            cluster_obj.addSourceAndPath(param.getSource(),param.getGatePaths()[i]);
            this->input_to_cluster.insert(pair<signal*,multipleSource> (signal_pointer,cluster_obj));
        }
        else
            input_to_cluster.find(signal_pointer)->second.addSourceAndPath(param.getSource(),param.getGatePaths()[i]);
            
        //creating auxiliar list of gates
        if(input_to_gates.find(signal_pointer)==input_to_gates.end())
            input_to_gates.insert(pair<signal*,vector<map<string,gate>::iterator> > (signal_pointer,param.getGatePaths()[i]));
        else
        {
            //adding all gates from path to unary list
            for(int j=0;j<param.getGatePaths()[i].size();j++)
            {
                if(find(input_to_gates.find(signal_pointer)->second.begin(),input_to_gates.find(signal_pointer)->second.end(),param.getGatePaths()[i][j]) == input_to_gates.find(signal_pointer)->second.end())
                    input_to_gates.find(signal_pointer)->second.push_back(param.getGatePaths()[i][j]);
            }
        }
            
    }
}


signal* gate::getSignalToThisGate(string gate_destination){
    for(int i=0;i<this->outputs.size();i++)
    {
        for(int j=0;j<this->outputs[i]->getDrivesPointer().size();j++)
        {
            if(this->outputs[i]->getDrivesPointer()[j]->getName()==gate_destination)
                return outputs[i];
        }
    }
    cout<<"ERROR: gate "<<gate_destination<<" wasn't found in "<<this->name<<" as a destination. (getSignalToThisGate)"<<endl;
}
    
string gate::getPinName(string signal_name){
    map<string,signal*>::iterator it;
    for(it=pin_and_signal.begin();it!=pin_and_signal.end();it++)
    {
        if(it->second->getName()==signal_name)
            return it->first;
    }
}

signal* gate::getSignalFromPinName(string pin_name){
        return(this->pin_and_signal.find(pin_name)->second);
}

//void gate::setFunctionOnInputs(){
//    map<signal*,multipleSource>::iterator map_cluster;
//    map<signal*,vector<vector<map<string,gate>::iterator> > >::iterator map_iterator;
//    vector<map <string,gate>::iterator> gates_stack;
//    
//    //for each sink's input signal
//    for(map_cluster=input_to_cluster.begin();map_cluster!=input_to_cluster.end();map_cluster++)
//    {
//        //source gate from sunk's input signal, start DFS from here
//        gates_stack.push_back(map_cluster->first->getSourcePointer());
//
//
//    }
//}

map<signal*,multipleSource> gate::getMapInputToCluster(){
    return this->input_to_cluster;
}

bool gate::isOnCluster(string other_gate_name){
    map <signal*,vector<map<string,gate>::iterator> >::iterator it;
    for(it=input_to_gates.begin();it!=input_to_gates.end();it++)
    {
        for(int i=0;i<it->second.size();i++) 
        {
            if(it->second[i]->first==other_gate_name)
                return true;
        }
    }
    return false;
}

bool gate::isSink(){
    return this->is_sink;
}

vector<map<string,gate>::iterator> gate::getUnaryGateList(signal* input_obj){
    return this->input_to_gates.find(input_obj)->second;
}

void gate::setLogicFunctionOnOutputs(gate* sink,vector<FOL_count> primaries){
//    gate sink;
//    sink=input_to_cluster.begin()->second.getMapSourceToPaths().begin()->second[0][0]->second;
    probability_variable prob;
    vector<probability_variable> prob_vec,aux;
    string func,func_aux,pin_name,str;
    stringstream ss,to_double;
    
    for(int i=0;i<this->outputs.size();i++)
    {
        prob_vec.clear();
        func=this->cell_obj.getFunc(getPinName(outputs[i]->getName()));
         func_aux=func;
//         cout<<"func:"<<func<<endl;
        if(func.find("NET")==string::npos && func.find("P0")==string::npos)
        {
//            reverse(func.begin(),func.end());
//            cout<<"func:"<<func<<endl;
            for(int a=0;a<func.size();a++)
            {
                ss.clear();
                ss<<func[a];
                ss>>str;
                //check each variable in the output function
                //if it is an operator, just copy
                if(func[a]=='!' || func[a]==' ' || func[a]=='+' || func[a]=='^' || func[a]==')' || func[a]=='(')
                {
                    if(func[a]==' ')
                    {
                        if(func[a-1]!='+' && func[a-1]!='^' && func[a-1]!='!' && func[a+1]!='+' && func[a+1]!='^' && func[a+1]!='!')
                        {
                            str='*';
        //                    cout<<"->"<<func[a]<<endl;
                            prob.is_number=false;
                            prob.is_operand=false;
                            prob.is_operator=true;
                            prob.variable=str;
                            prob_vec.push_back(prob);
                            
                        }
                    }
                    else
                    {
                        prob.is_number=false;
                        prob.is_operand=false;
                        prob.is_operator=true;
                        prob.variable=str;
                        prob_vec.push_back(prob);
                    }
                }
                //if it is an operand, get its function and copy
                else if (func[a]!='.')
                {
                    //solving for pins with more then one character
                    if(func[a+1]!='!' && func[a+1]!=' ' && func[a+1]!='+' && func[a+1]!='^' && func[a+1]!=')' && func[a+1]!='(')
                    {
                        ss.clear();
                        ss<<func[a];
                        ss<<func[a+1];
                        ss>>str;
                        a++;
                    }
//                    cout<<"->"<<func[a]<<"="<<pin_and_signal.find(str)->second->getName()<<endl;
                    //error check
                    if(pin_and_signal.find(str) != pin_and_signal.end())
                    {
//                        cout<<"str:"<<str<<". signal:"<<pin_and_signal.find(str)->second->getName()<<endl;;
                        //if signal inside function is a source
                        if(isPrimary(pin_and_signal.find(str)->second,primaries))
                        {
//                            cout<<"signal "<<pin_and_signal.find(str)->second->getName()<<" is a source"<<endl;
                            prob.is_number=false;
                            prob.is_operator=false;
                            prob.is_operand=true;
                            prob.variable=pin_and_signal.find(str)->second->getName();
                            prob_vec.push_back(prob);
                        }
//                            cout<<"ERROR, signal "<<pin_and_signal.find(str)->first<<" has no probability neither logic funciton set (setLogicFunctionOnOutputs)"<<endl;
                        
                        //if it is not a source
                        else 
                       {
//                            cout<<"signal "<<pin_and_signal.find(str)->second->getName()<<" is NOT a source"<<endl;
                            
                            //if it is not a part of the reconvergent path (AND it is not a source)  save its probability value
                            if(!isInPath(pin_and_signal.find(str)->second->getFOL(),primaries) && !isPrimary(pin_and_signal.find(str)->second,primaries))
                            {
//                                cout<<"lalal"<<endl;
                                prob.is_number=true;
                                prob.is_operand=false;
                                prob.is_operator=false;
//                                to_double.str(std::string());
//                                to_double<<pin_and_signal.find(str)->second->getProbability();
//                                prob.variable=to_double.str();
                                prob.variable=pin_and_signal.find(str)->second->getName();
//                                cout<<to_double.str()<<endl;
//                                prob.variable=pin_and_signal.find(str)->second->getName();
                                prob_vec.push_back(prob);
                            }
                            //if it is a part of the reconvergent path, save all its function.
                            else
                            {
//                                prob_vec.clear();
//                                prob.is_number=false;
//                                prob.variable="(";
//                                prob_vec.push_back(prob);
                                aux.clear();
                                aux=pin_and_signal.find(str)->second->getLogicFunction(sink->getName());
//                                cout<<"antes do insert>>"<<str<<":";
//                                for(int q=0;q<aux.size();q++)
//                                    cout<<aux[q].variable;
//                                cout<<endl;
//                                cout<<"antes do insert>>"<<str<<":";
//                                cout<<"o que ja ta:";
//                                for(int q=0;q<prob_vec.size();q++)
//                                    cout<<prob_vec[q].variable;
//                                cout<<endl;
                                
                                for(int z=0;z<aux.size();z++)
                                    prob_vec.push_back(aux[z]);
//                                prob_vec.insert(prob_vec.end(),aux.begin(),aux.end());
//                                prob.is_number=false;
//                                prob.variable=")";
//                                prob_vec.push_back(prob);
                            }
                        }
                    }
                    else
                        cout<<"Pin "<<str<<" was not found in map from gate "<<this->name<<endl;
                }
                
//                cout<<"Not ready>>>";
//                cout<<this->outputs[i]->getName()<<":";
//                for(int q=0;q<prob_vec.size();q++)
//                    cout<<prob_vec[q].variable;
//                cout<<endl;
            }
        }
//         cout<<"setting output "<<this->outputs[i]->getName()<<" with:";
//         for(int x=0;x<this->outputs[i]->getLogicFunction().size();x++)
//             cout<<this->outputs[i]->getLogicFunction()[x].variable;
//        cout<<endl;
//        
//         ofstream write;
//         write.open("debug.txt",ios::app);
//            write<<this->name<<":";
//            for(int i=0;i<prob_vec.size();i++)
//                write<<prob_vec[i].variable;
//            write<<endl;
//            write.close();
//         }
         this->outputs[i]->setLogicFunction(sink->getName(),prob_vec);
//         cout<<this->outputs[i]->getName()<<":";
//         for(int j=0;j<this->outputs[i]->getLogicFunction(sink.getName()).size();j++)
//             cout<<this->outputs[i]->getLogicFunction(sink.getName())[j].variable;
//        cout<<endl;
    }
//    this->cell_obj.getFunc();
    this->pin_and_signal;
}


void gate::setPRFOL(vector<FOL_count> primaries){
    this->is_sink=true;
    this->primary_RFOL=primaries;
}

vector<FOL_count> gate::getPRFOL(){
    return this->primary_RFOL;
}

bool gate::isThisASource(string signal_name){
    for(int i=0;i<this->primary_RFOL.size();i++)
    {
        if(primary_RFOL[i].signal_pointer->getName()==signal_name)
            return true;
    }
    return false;
}

void gate::setGateProbability(){
//    cout<<"Analising gate "<<this->getName()<<" with type "<<this->cell_obj.getType()<<endl;
    string func,pin_name,str;
    vector <string> pins,aux;
    stringstream ss;
//    ofstream write;
//    write.open("outnaguentomais.txt", ofstream::app);
    
    for(int i=0;i<this->cell_obj.getOutput().size();i++)
    {
        func=this->cell_obj.getFunc(this->cell_obj.getOutput()[i]);
//        cout<<endl;
//        cout<<"Pin "<<this->cell_obj.getOutput()[i]<<" has function:"<<func<<endl;
        
        if(func.find("NET")==string::npos && func.find("P0")==string::npos)
        {
            pins=cell_obj.getPostFix(this->cell_obj.getOutput()[i]);
//            pins=this->makePostFix(func);
            
//        cout<<"Queues for pin "<<this->cell_obj.getOutput()[i]<<":"<<endl<<"pin names:";
//             cout<<"getting numbers:";
//        for(int b=pins.size()-1;b>=0;b--)
//            cout<<pins[b]<<",";
//        cout<<endl;
//        cout<<"result:"<<getNumbers(pins)<<endl;
//        cout<<"calling getNumbers for this prefix"<<endl;
//        cout<<"source from signal "<<this->pin_and_signal.find(cell_obj.getOutput()[i])->second->getName()<<" is the gate "<<this->pin_and_signal.find(cell_obj.getOutput()[i])->second->getSourcePointer()->getName()<<endl; 
//            cout<<"gate:"<<this->name<<" output_name:"<<cell_obj.getOutput()[i];//<<" function:"<<cell_obj.getFunc(cell_obj.getOutput()[i]);
            
            this->pin_and_signal.find(cell_obj.getOutput()[i])->second->setProbability(getNumbers(pins));
            //write<<"setting "<<getNumbers(pins)<<" in "<<pin_and_signal.find(cell_obj.getOutput()[i])->second->getName()<<endl;
        }
        else
            cout<<"ERROR: This probabily is a sequencial circuit.(setGateProbabilities)"<<endl;
    }
}

void gate::setSinkProbability(circuit* circuit_obj){
//    cout<<"Setting sink "<<this->name<<endl;
    vector <probability_variable> prob_vec;
    vector <string> postfix_pin_names;
    vector<probability_variable> postfix_source_names;
    probability_variable prob;
    
    //for each pin output
    for(int i=0;i<cell_obj.getOutput().size();i++)
    {
        //get its postfixed logic function with input pins
        
        postfix_pin_names=cell_obj.getPostFix(cell_obj.getOutput()[i]);
//        cout<<"Before:";
//        for(int j=0;j<postfix_pin_names.size();j++)
//            cout<<postfix_pin_names[j]<<"|";
//        cout<<endl;
        
        int control=2,counter=0;
        while(find(postfix_pin_names.begin(),postfix_pin_names.end(),"^")!=postfix_pin_names.end())
        {
            counter=0;
            vector<string> one,two,inserter;
            vector<string>::iterator initial_it,its;
            one.clear();
            two.clear();
            inserter.clear();
            initial_it=find(postfix_pin_names.begin(),postfix_pin_names.end(),"^");
            its=initial_it;
            while(control>0)
            {
                its--;
                if(*its=="*" || *its=="+" || *its=="^" ||*its=="sum")
                    control++;
                else
                {
//                    cout<<"THIS SHOULD BE A VARIABLE:"<<*its<<endl;
                    control--;
                }
                one.push_back(*its);
                counter++;
                if(control==1)
                {
                    two=one;
                    one.clear();
                }
            }
//            cout<<"one:";
//            for(int j=0;j<one.size();j++)
//                cout<<one[j]<<"|";
//            cout<<endl;
//            cout<<"two:";
//            for(int j=0;j<two.size();j++)
//                cout<<two[j]<<"|";
//            cout<<endl;
            
            inserter.push_back("sum");
            inserter.push_back("*");
            inserter.insert(inserter.end(),one.begin(),one.end());
            inserter.push_back("!");
            inserter.insert(inserter.end(),two.begin(),two.end());
            inserter.push_back("*");
            inserter.push_back("!");
            inserter.insert(inserter.end(),one.begin(),one.end());
            inserter.insert(inserter.end(),two.begin(),two.end());
            reverse(inserter.begin(),inserter.end());
//            cout<<"inserter:";
//            for(int j=0;j<inserter.size();j++)
//                cout<<inserter[j]<<"|";
//            cout<<endl;
//            cout<<"counter:"<<counter<<endl;
//            cout<<"iterator as int:"<<distance( postfix_pin_names.begin(), initial_it )<<endl;
//            cout<<"BEFORE INSERT:";
//            for(int j=0;j<postfix_pin_names.size();j++)
//                cout<<postfix_pin_names[j]<<"|";
//            cout<<endl;
            if(postfix_pin_names.size()==counter+1)
            {
                postfix_pin_names.clear();
                postfix_pin_names.insert(postfix_pin_names.begin(),inserter.begin(),inserter.end());
            }
            else
            {
                postfix_pin_names.insert(initial_it+1,inserter.begin(),inserter.end());
                initial_it=find(postfix_pin_names.begin(),postfix_pin_names.end(),"^");
//                cout<<"iterator as int:"<<distance( postfix_pin_names.begin(), initial_it )<<endl;
                postfix_pin_names.erase(initial_it-counter-1,initial_it);
//                cout<<"AFTER erase:";
//                for(int j=0;j<postfix_pin_names.size();j++)
//                    cout<<postfix_pin_names[j]<<"|";
//                cout<<endl;
            }
                
            
//            cout<<"AFTER INSERT:";
//            for(int j=0;j<postfix_pin_names.size();j++)
//                cout<<postfix_pin_names[j]<<"|";
//            cout<<endl;
//            
//            cout<<"Before WITHOUT ^:";
//            for(int j=0;j<postfix_pin_names.size();j++)
//                cout<<postfix_pin_names[j]<<"|";
//            cout<<endl;
            
        }
        
//        cout<<"___________________________"<<endl;
        //build postfix output logic function with sources
        for(int j=0;j<postfix_pin_names.size();j++) 
        {
            if(postfix_pin_names[j]!="+" && postfix_pin_names[j]!=" " && postfix_pin_names[j]!="^" && postfix_pin_names[j]!=")" && postfix_pin_names[j]!="(" && postfix_pin_names[j]!="!" && postfix_pin_names[j]!="*" && postfix_pin_names[j]!="sum")
            {
//                cout<<postfix_pin_names[j]<<"("<<this->getSignalFromPinName(postfix_pin_names[j])->getName()<<")"<<"--->";
                postfix_source_names=makePostFix(this->getSignalFromPinName(postfix_pin_names[j])->getLogicFunction(this->name));
                prob_vec.insert(prob_vec.end(),postfix_source_names.begin(),postfix_source_names.end());
//                for(int k=0;k<this->getSignalFromPinName(postfix_pin_names[j])->getLogicFunction(this->name).size();k++)
            }
            else if (postfix_pin_names[j]=="!" || postfix_pin_names[j]=="+"  || postfix_pin_names[j]=="*" || postfix_pin_names[j]==")" || postfix_pin_names[j]=="(" || postfix_pin_names[j]=="sum")
            {
                
                prob.is_operand=false;
                prob.is_operator=true;
                prob.is_number=false;
                prob.variable=postfix_pin_names[j];
                prob_vec.push_back(prob);
            }
//            cout<<endl;
//            cout<<"During:";
//            for(int k=0;k<prob_vec.size();k++)
//                cout<<prob_vec[k].variable;//<<"("<<prob_vec[k].is_number<<")";
//            cout<<endl;
        }
//        cout<<"After:";
//        for(int k=0;k<prob_vec.size();k++)
//            cout<<prob_vec[k].variable;//<<"("<<prob_vec[k].is_number<<")";
//        cout<<endl;
        
//        cout<<"Postfix pin name:";
//        for(int k=0;k<postfix_pin_names.size();k++)
//            cout<<postfix_pin_names[k];
//        cout<<endl;
        float answer=0.0,sources_probability=1.0;
        map<string,source_data> source_to_bit;
        map<string,source_data>::iterator it;
        source_data data;
        source_to_bit.clear();
        sources_probability=1.0;
        //generate possible sources bit combinations
        for(int k=0;k<this->getSignalFromPinName(cell_obj.getOutput()[i])->getPRFOL().size();k++)
        {
            data.bit=false;
            data.probability=1-this->getSignalFromPinName(cell_obj.getOutput()[i])->getPRFOL()[k].signal_pointer->getProbability();
            source_to_bit.insert(pair<string,source_data> (this->getSignalFromPinName(cell_obj.getOutput()[i])->getPRFOL()[k].signal_pointer->getName(),data));
//            cout<<"SOURCE PROB:"<<this->getSignalFromPinName(cell_obj.getOutput()[i])->getPRFOL()[k].signal_pointer->getProbability()<<endl;
//            sources_probability=sources_probability*this->getSignalFromPinName(cell_obj.getOutput()[i])->getPRFOL()[k].signal_pointer->getProbability();
        }

        for(int n=0;n<pow(2,source_to_bit.size());n++)
        {
//            for(int k=0;k<prob_vec.size();k++)
//                cout<<prob_vec[k].variable;//<<"("<<prob_vec[k].is_number<<")";
//            cout<<endl;
            if(n%1000==0)
                cout<<"Working on iteration: "<<n<<endl;
            
            sources_probability=1.0;
            int a;
            for(it=source_to_bit.begin(),a=0;it!=source_to_bit.end();it++,a++)
            {
                if(n%(int)(pow(2,a))==0)
                {
                    it->second.bit=!it->second.bit;
                    it->second.probability=1-it->second.probability;
                }
                sources_probability=sources_probability*it->second.probability;
            }
//            cout<<"sink:"<<this->name<<". sources:";
//            for(it=source_to_bit.begin();it!=source_to_bit.end();it++)
//                cout<<it->first<<"("<<it->second.bit<<"),";
//            cout<<endl;
            vector<float> stack;
            stack.clear();
            float num1,num2;
//            cout<<"prob_vec:";
//            for(int k=0;k<prob_vec.size();k++)
//                cout<<prob_vec[k].variable;
//            cout<<endl;
            for(int k=0;k<prob_vec.size();k++)
            {
//                cout<<"stack:";
//                for(int u=0;u<stack.size();u++)
//                    cout<<stack[u]<<",";
//                cout<<"/prob_vec[k]:"<<prob_vec[k].variable<<endl;
                
                if(prob_vec[k].is_number)
                {
//                    cout<<"prob:"<<circuit_obj->getSignalPointer(prob_vec[k].variable)->getProbability()<<"("<<circuit_obj->getSignalPointer(prob_vec[k].variable)->getName()<<")"<<endl;
                    stack.push_back(circuit_obj->getSignalPointer(prob_vec[k].variable)->getProbability());
                }
//                    stack.push_back(::atof(prob_vec[k].variable.c_str()));
                
                else if(prob_vec[k].is_operand)
                {
//                    cout<<"entrou"<<endl;
                    if(source_to_bit.find(prob_vec[k].variable)!=source_to_bit.end())
                    {
                        if(source_to_bit.find(prob_vec[k].variable)->second.bit)
                            stack.push_back(1.0);
                        else
                            stack.push_back(0.0);
                    }
                    else
                        cout<<"ERROR, "<<prob_vec[k].variable<<" wasnt found as a primary source."<<endl;
                }
                
                else if(prob_vec[k].is_operator)
                {
//                    cout<<"LALALAL"<<endl;
                    if(prob_vec[k].variable.find("*")!=string::npos)
                    {
//                        cout<<"POPPOP"<<endl;
                        num1=stack.back();
                        stack.pop_back();
                        num2=stack.back();
                        stack.pop_back();
                        stack.push_back(num1*num2);
                    }
                    else if(prob_vec[k].variable.find("!")!=string::npos)
                    {
                        num1=1-stack.back();
                        stack.pop_back();
//                        cout<<"PUSHIN"<<num1<<endl;
                        stack.push_back(num1);
                    }
                    else if(prob_vec[k].variable.find("+")!=string::npos)
                    {
                        num1=stack.back();
                        stack.pop_back();
                        num2=stack.back();
                        stack.pop_back();
                        stack.push_back(num1+num2-(num1*num2));
                    }
                    else if(prob_vec[k].variable.find("sum")!=string::npos)
                    {
                        num1=stack.back();
                        stack.pop_back();
                        num2=stack.back();
                        stack.pop_back();
                        stack.push_back(num1+num2);
                    }
                    else if(prob_vec[k].variable.find("^")!=string::npos)
                    {
                        num1=stack.back();
                        stack.pop_back();
                        num2=stack.back();
                        stack.pop_back();
                        stack.push_back(num1+num2-2*(num1*num2));
                    }
                    
                } 
            }
            if(stack.size()!=1)
            {
                cout<<"ERROR, unexpected stack size."<<endl;
//                cout<<"stack:";
//                for(int u=0;u<stack.size();u++)
//                    cout<<stack[u]<<",";
//                cout<<endl;
            }
//            cout<<"last one:"<<stack[0]<<endl;
//            cout<<"sources_prob:"<<sources_probability<<endl;
//   
            stack[0]=stack[0]*sources_probability;
            answer=answer+stack[0];
//            cout<<"answer:"<<answer<<"stack[0]"<<stack[0]<<endl;
        }
        
        this->pin_and_signal.find(cell_obj.getOutput()[i])->second->setProbability(answer);
    }
//    this->outputs[i];
//    prob_vec=inputs[i]->getLogicFunction(this->name);

    
}

vector<probability_variable> gate::makePostFix(vector<probability_variable> sources){
    vector<probability_variable> prob_vec,aux;
    probability_variable prob;
    
//    cout<<endl<<"1:";
//    for(int x=0;x<sources.size();x++)
//        cout<<sources[x].variable;
//    cout<<endl;
    reverse(sources.begin(),sources.end());
    
    
    for(int i=0;i<sources.size();i++)
    {
//        cout<<sources[i].variable<<endl;
        if(sources[i].variable.find("!")!=string::npos)
        {
            prob.is_operand=false;
            prob.is_operator=true;
            prob.is_number=false;
            prob.variable=sources[i].variable;
            prob_vec.push_back(prob);
//                pins.push_back(str);
        }
//        else if (sources[i].variable.find(" ")!=string::npos)
//        {
//            prob.is_number=false;
//            prob.variable="*";
//            cout<<"adicionando asterisco->"<<prob.variable<<endl;
//            aux.push_back(prob);
//        }

        else if(sources[i].variable.find("+")!=string::npos || sources[i].variable.find("^")!=string::npos || sources[i].variable.find(")")!=string::npos || sources[i].variable.find("*")!=string::npos)
        {
            prob.is_operand=false;
            prob.is_operator=true;
            prob.is_number=false;
            prob.variable=sources[i].variable;
            aux.push_back(prob);
        }
        else if (sources[i].variable.find("(")!=string::npos)
        {
//            cout<<"aux:";
//            for(int uu=0;uu<aux.size();uu++)
//                cout<<aux[uu].variable;
//            cout<<endl;
            while(aux.back().variable.find(")")==string::npos)
            {
                prob_vec.push_back(aux.back());
//                pins.push_back(aux.back());
                aux.pop_back();
            }
            aux.pop_back();
        }
        else
        {
//            pin_name.clear();
//            if(func[a+1]!="+" || func[a+1]!=" " && func[a+1]!="^" && func[a+1]!=")" && func[a+1]!="(" && func[a+1]!="!")
//            {
//                pin_name.push_back(func[a+1]);
//                pin_name.push_back(sources[i].variable);
//                a++;
//            }
//            else
//                pin_name.push_back(sources[i].variable);
//            pins.push_back(pin_name);
            prob_vec.push_back(sources[i]);
        }
        
    }
//    cout<<"2:";
//    for(int y=0;y<prob_vec.size();y++)
//        cout<<prob_vec[y].variable;
//    cout<<endl;
    return prob_vec;
}