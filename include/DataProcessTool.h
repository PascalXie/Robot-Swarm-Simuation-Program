#ifndef DATAPROCESSTOOL_H
#define DATAPROCESSTOOL_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

struct varibale{
    string name = "";
    string value = "";
    string type = "";
    string annotation = "";
};


class DataProcessTool{
public:
    DataProcessTool();
    ~DataProcessTool();

public:
    void ReadFile(string file);

    int Get_value(string variable_name, int &v);
    int Get_value(string variable_name, double &v);
    int Get_value(string variable_name, string &v);
    int Get_value(string variable_name, bool &v);
    int Get_value(string variable_name, vector<int> &v);

//    int Get_int_value(string variable_name, int &v);

//    int Get_double_value(string variable_name, double &v);

//    int Get_string_value(string variable_name, string &v);

//    int Get_bool_value(string variable_name, bool &v);

//    int Get_vector_int_value(string variable_name, vector<int> &v);

    string Get_annotation(string variable_name);

private:
    ifstream readfile;
    map<string, varibale> data;
};

#endif // DATAPROCESSTOOL_H
