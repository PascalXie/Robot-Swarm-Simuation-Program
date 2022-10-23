#include "DataProcessTool.h"

DataProcessTool::DataProcessTool()
{

}

DataProcessTool::~DataProcessTool()
{

}

void DataProcessTool::ReadFile(string file)
{
    readfile.open(file);
    string Line;
    int space_name, space_type ,pound_sign;
    varibale v;

    if (!readfile.is_open()){
        cout << "Error: open file failed" << endl;
        return;
    }

    while(!readfile.eof()){
        getline(readfile, Line);
        space_name = Line.find(" ");
        pound_sign = Line.find("#");
        if (space_name != -1){
            v.name = Line.substr(0, space_name);
            space_type = Line.find(" ", space_name + 1);
            if (space_type != -1){
                if (pound_sign != -1) {
                    v.value = Line.substr(space_name + 1, space_type - space_name - 1);
                    v.type = Line.substr(space_type + 1, pound_sign - space_type - 2);

                    v.annotation = Line.substr(pound_sign + 1);
                } else {
                    v.value = Line.substr(space_name + 1, space_type - space_name - 1);
                    v.type = Line.substr(space_type + 1);

                }
            }

        }
        data[v.name] = v;
        v.name = "";
        v.value = "";
        v.type = "";
        v.annotation = "";
    }
}

int DataProcessTool::Get_value(string variable_name, int &v)
{
    if (data[variable_name].type == "int"){
        istringstream(data[variable_name].value.c_str()) >> v;
        return 0;
    } else {
        cout << "Get_int_value error: incorrect data type " << endl;
        return 1;
    }
}


int DataProcessTool::Get_value(string variable_name, double &v)
{
    if (data[variable_name].type == "double"){
        istringstream(data[variable_name].value.c_str()) >> v;
        return 0;
    } else {
        cout << "Get_double_value error: incorrect data type " << endl;
        return 1;
    }
}

int DataProcessTool::Get_value(string variable_name, string &v)
{
    if (data[variable_name].type == "string"){
        v = data[variable_name].value;
        return 0;
    } else {
       cout  << "Get_string_value error: incorrect data type " << endl;
       return 1;
    }
}

int DataProcessTool::Get_value(string variable_name, bool &v)
{
    if (data[variable_name].type == "bool"){
        istringstream(data[variable_name].value) >> boolalpha >> v;
        cout << boolalpha << v << endl;
        return 0;
    } else {
        cout  << "Get_bool_value error: incorrect data type " << endl;
        return 1;
    }
}

int DataProcessTool::Get_value(string variable_name, vector<int> &v)
{
    if (data[variable_name].type == "vector"){
        int Begin, End, temp;
        Begin = data[variable_name].value.find("{");
        End = data[variable_name].value.find("}");
        for (int i = Begin; i < End; i += 2){
            istringstream(data[variable_name].value.substr(i+1, 1)) >> temp;
            v.push_back(temp);
        }
        return 0;
    } else {
        cout  << "Get_vector_int_value error: incorrect data type " << endl;
        return 1;
    }
}

string DataProcessTool::Get_annotation(string variable_name)
{
    if (data[variable_name].annotation != ""){
        return data[variable_name].annotation;
    } else {
        return  "This variable does not have an annotation";
    }

}


