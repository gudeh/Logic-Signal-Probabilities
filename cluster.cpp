/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cluster.cpp
 * Author: root
 * 
 * Created on July 28, 2017, 6:29 PM
 */

#include "classes.h"

cluster::cluster() {
    this->gate_paths={};
    this->source=NULL;
}


//cluster::cluster(const cluster& orig) {
//}

void cluster::setSource(signal* param){
    this->source=param;
}

signal* cluster::getSource(){
    return this->source;
}

void cluster::addGatePaths(vector<map<string,gate>::iterator> param){
    this->gate_paths.push_back(param);
}

vector<vector<map<string,gate>::iterator> > cluster::getGatePaths(){
    return this->gate_paths;
}

void cluster::clear(){
    this->gate_paths.clear();
    this->source=NULL;
}

void cluster::printReconvergentPath(){
    cout<<"Signal source: "<<this->source->getName()<<endl;
    for(int t=0;t<this->gate_paths.size();t++)
        {
            cout<<"Path "<<t<<": ";
            for(int j=0;j<this->gate_paths[t].size();j++)
                cout<<this->gate_paths[t][j]->first<<",";
            cout<<endl;
//            cout<<"Path's logic function: ";
//            if(this->cluster_logic_function.size()>0)
//            {
//                for(int g=0;g<this->cluster_logic_function[t].size();g++)
//                    cout<<this->cluster_logic_function[t][g]<<',';
//            }
//            cout<<endl;
        }
    
    cout<<endl;
}

void cluster::erasePath(int param){
    this->gate_paths.erase(gate_paths.begin()+param);
}


//TODO THIS IS WROOOOOOOOOOOOOOOOOOOOOOONG
//void cluster::setLogicFunction(){
//    gate gatezin;
//    signal* signalzin;
////    gatezin.get getCell().getFunc(pino) ;
//    
//    stringstream ss;
//    vector<string> postfix,aux;
//    string out_pin_name,logic_func,str;
//    cout<<"setting logic fucntion for path:"<<endl;
//    this->printReconvergentPath();
//    
//    for(int i=0;i<this->gate_paths.size();i++)
//    {
//        for(int j=this->gate_paths[i].size()-1;j>0;j--)
//        {
//            if(j!=0)
//            {
////                cout<<gate_paths[i][j]->second.getName()<<endl;
//                signalzin=gate_paths[i][j]->second.getSignalToThisGate(gate_paths[i][j-1]->second.getName());
////                cout<<"signal "<<signalzin->getName()<<endl;
//                out_pin_name=gate_paths[i][j]->second.getPinName(signalzin->getName());
//
//                logic_func=gate_paths[i][j]->second.getCell().getFunc(out_pin_name); //returns string with the logic function
//            }
//            else
//            {
//                
//            }
//            
////            for(int o=0;o<logic_func.size();o++)
////                cout<<logic_func[o]<<",";
////            cout<<endl;
//            
//            if(logic_func.find("NET")==string::npos && logic_func.find("P0")==string::npos)
//            {
//                reverse(logic_func.begin(),logic_func.end());
//                for(int a=0;a<logic_func.size();a++)
//                {
//                    ss.clear();
//                    ss<<logic_func[a];
//                    ss>>str;
////                    cout<<str<<endl;
//                    if(logic_func[a]=='!')
//                        postfix.push_back(str);
//                    else if (logic_func[a]==' ')
//                        aux.push_back("*");
//                    else if(logic_func[a]=='+' || logic_func[a]=='^' || logic_func[a]==')')
//                        aux.push_back(str);
//                    else if (logic_func[a]=='(')
//                    {
//                        while(aux.back()!=")")
//                        {
//                            postfix.push_back(aux.back());
//                            aux.pop_back();
//                        }
//                        aux.pop_back();
//                    }
//                    else if(logic_func[a]!='+' && logic_func[a]!=' ' && logic_func[a]!='^' && logic_func[a]!='(' && logic_func[a]!=')' && logic_func[a]!='!')
//                    {
////                        cout<<"aaa"<<endl;
//                        postfix.push_back(gate_paths[i][j]->second.getSignalFromPinName(str));
////                        cout<<"bbb"<<endl;
//                    }
//                        
//
//                }
//            }
//        }
//        this->cluster_logic_function.push_back(postfix);
//        postfix.clear();
////        for(int x=0;x<cluster_logic_function[i].size();x++)
////        {
////            cout<<cluster_logic_function[i][x]<<",";
////        }
////        cout<<endl;
//    }
////    this->logic_functions.insert(pair<signal*,stack> (a,b));
//}