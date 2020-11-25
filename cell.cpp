/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cell.cpp
 * Author: root
 * 
 * Created on July 12, 2016, 8:18 PM
 */

#include "classes.h"

//////////////////////////CELL/////////////////////////////
cell::cell(string param_type, vector <string> in, vector <string> out, map<string,string> pin_to_funcs){
    type=param_type;
    input=in;
    output=out;
    this->pin_to_funcs=pin_to_funcs;
    this->makePostFix(pin_to_funcs);
}
cell::cell(string type_name, vector <string> in, vector <string> out)
{
    type=type_name;
    input=in;
    output=out;
}
cell::cell(){}

void cell::printCell(){
        int i;
    cout<<"Cell type: "<<type<<endl<<"Inputs: ";
    for(i=0;i<input.size();i++)
        cout<<input[i]<<",";
    cout<<endl<<"Outputs: ";
    for(i=0;i<output.size();i++)
        cout<<output[i]<<"->"<<pin_to_funcs.at(output[i])<<",";
    cout<<endl;
}

vector<string> cell::getInput() {
    return input;
}

vector<string> cell::getOutput() {
    return output;
}

string cell::getType() {
    return type;
}

string cell::getFunc(string pin_name){
    if(this->pin_to_funcs.find(pin_name)!=pin_to_funcs.end())
        return this->pin_to_funcs.find(pin_name)->second;
    else
        cout<<"ERROR, pin name "<<pin_name<<" was not found in cell type "<<this->type<<" (getFunc)"<<endl;
}

void cell::setArea(double param){
    this->area=param;
}

void cell::setPower(double param){
    this->power=param;
}

double cell::getArea(){
    return this->area;

}
double cell::getPower(){
    return this->power;
}

void cell::makePostFix(map<string,string> param){
    string pin_name,str;
    vector <string> pins,aux;
    string func;
    stringstream ss;
    map<string,string>::iterator it;
    
    for(it=param.begin();it!=param.end();it++)
    {
        func=it->second;
        pins.clear();
        if(func.find("NET")==string::npos && func.find("P0")==string::npos)
        {
        reverse(func.begin(),func.end());
        
        for(int a=0;a<func.size();a++)
        {
            ss.clear();
            ss.str(string());
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
        if(this->pin_to_funcs_postfix.find(it->first)==pin_to_funcs_postfix.end())
            pin_to_funcs_postfix.insert(pair<string,vector<string> > (it->first,pins));
        else
            cout<<"ERROR, function already set trying to be set again (makePostFix)"<<endl;
    }
    }
    
}


vector<string> cell::getPostFix(string pin_name){
    return this->pin_to_funcs_postfix.find(pin_name)->second;
}