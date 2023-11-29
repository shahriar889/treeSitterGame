#include "dataValue.h"

using namespace DV;

void InsertVisitor::operator()(std::vector<DataValue>& vec){
    vec.push_back(this->v);
}

void InsertVisitor::operator()(std::map<std::string, DataValue>& map){
    map.insert(std::pair<std::string, DataValue>(key, v));
}

void InsertVisitor::operator()(int& value){
    std::cout << "Not menat to be called" << std::endl;
    return;
}

void InsertVisitor::operator()(bool& value){
    std::cout << "Not menat to be called" << std::endl;
    return;
}

void InsertVisitor::operator()(std::string& value){
    std::cout << "Not menat to be called" << std::endl;
    return;
}

DataValue GetterVisitor::operator()(const std::vector<DataValue>& vec) const{
    assert(i >= 0 && i < vec.size());
    return vec.at(i);
}

DataValue GetterVisitor::operator()(const std::map<std::string, DataValue>& map) const{
    if(map.find(key) == map.end()){
        return DataValue();
    }    
    else{
        return map.at(key);
    }
}

DataValue GetterVisitor::operator()(const int& value) const{
    DataValue temp = DataValue();
    temp.setValue(value);
    return temp;
}

DataValue GetterVisitor::operator()(const bool& value) const{
    DataValue temp = DataValue();
    temp.setValue(value);
    return temp;
}

DataValue GetterVisitor::operator()(const std::string& value) const{
    DataValue temp = DataValue();
    temp.setValue(value);
    return temp;
}



void DataValue::push_back_list(const DataValue& add) {
    if (this->getType() == DataType::LIST) {
        InsertVisitor visitor(add.getValueVariant(), "");
        std::visit(visitor, this->data);
    }
    else{
        std::cout << "Error: DataValue is not a list" << std::endl;
    }
}



void DataValue::insert_map(std::string key, const DataValue& data){
    if(this->getType() == DataType::MAP){
        InsertVisitor visitor(data.getValueVariant(), key);
        std::visit(visitor, this->data);
    }
    else{
        std::cout << "Error: DataValue is not a map" << std::endl;
    }
        
}

DataValue DataValue::get_list(const int& index) const{
    if(this->getType() == DataType::LIST)
        return std::visit(GetterVisitor{index,""}, this->data);
    else
        return DataValue();
}

DataValue DataValue::get_map_item(const std::string& key) const{
    if(this->getType() == DataType::MAP)
        return std::visit(GetterVisitor{-1,key}, this->data);
    else
        return DataValue();
}

DataType DataValue::getType() const{
    return this->type;
}

void printVisitor::operator()(int value) const{
    std::cout << value << std::endl;
}

void printVisitor::operator()(bool value) const{
    std::cout << value << std::endl;
}

void printVisitor::operator()(std::string value) const{
    std::cout << value << std::endl;
}

void printVisitor::operator()(std::map<std::string, DataValue> value) const{
    for(auto it = value.begin(); it != value.end(); it++){
        std::cout << it->first << " : ";
        std::visit(printVisitor(), it->second.getValueVariant());
    }
}

void printVisitor::operator()(std::vector<DataValue> value) const{
    for(auto it = value.begin(); it != value.end(); it++){
        std::visit(printVisitor(), it->getValueVariant());
    }
}

void DataValue::print() const{
    std::visit(printVisitor(), this->data);
}

bool EqualityVisitor::operator()(const int& value1) const{
    DataValue temp = DataValue();
    DataValue temp2 = DataValue();
    temp.setValue(v);
    temp2.setValue(value1);
    if(temp.getType() != DataType::INT){
        return false;
    }
    else{
        return temp.getValueVariant() == temp2.getValueVariant();
    }
}

bool EqualityVisitor::operator()(const bool& value1) const{
    DataValue temp = DataValue();
    DataValue temp2 = DataValue();
    temp.setValue(v);
    temp2.setValue(value1);
    if(temp.getType() != DataType::BOOL){
        return false;
    }
    else{
        return temp.getValueVariant() == temp2.getValueVariant();
    }
}

bool EqualityVisitor::operator()(const std::string& value1) const{
    DataValue temp = DataValue();
    DataValue temp2 = DataValue();
    temp.setValue(v);
    temp2.setValue(value1);
    if(temp.getType() != DataType::STRING){
        return false;
    }
    else{
        return temp.getValueVariant() == temp2.getValueVariant();
    }
}

bool EqualityVisitor::operator()(const std::map<std::string, DataValue>& value1) const{
    DataValue temp = DataValue();
    temp.setValue(v);
    if(value1.size() != temp.size())
        return false;
    for(auto it = value1.begin(); it != value1.end(); it++){
        if(it->second.getType() != temp.get_map_item(it->first).getType())
            return false;
        if(!(it->second == temp.get_map_item(it->first)))
            return false;
    }
    return true;
}



bool EqualityVisitor::operator()(const std::vector<DataValue>& value1) const{
    DataValue temp = DataValue();
    temp.setValue(v);
    if(value1.size() != temp.size())
        return false;
    for(int i = 0; i < value1.size(); i++){
        if(value1[i].getType() != temp.get_list(i).getType())
            return false;
        if(!(value1[i] == temp.get_list(i)))
            return false;
    }
    return true;
}

bool DataValue::operator==(const DataValue& other) const{
    if(this->type != other.type){
        return false;
    }
    else{
        return std::visit(EqualityVisitor{other.data}, this->data);
    }
   
}

bool DataValue::isEmpty() const{
    if(this->type == DataType::EMPTY){
        return true;
    }
    else{
        return false;
    }
}

size_t SizeVisitor::operator()(const int& value) const{
    return 1;
}

size_t SizeVisitor::operator()(const bool& value) const{
    return 1;
}

size_t SizeVisitor::operator()(const std::string& value) const{
    return 1;
}

size_t SizeVisitor::operator()(const std::map<std::string, DataValue>& value) const{
    return value.size();
}

size_t SizeVisitor::operator()(const std::vector<DataValue>& value) const{
    return value.size();
}

size_t DataValue::size() const {
    if(this->type == DataType::EMPTY){
        return 0;
    }
    else{
        return std::visit(SizeVisitor(), this->data);
    }
}

DataType TypeVisitor::operator()(const int& value) const{
    return DataType::INT;
}

DataType TypeVisitor::operator()(const bool& value) const{
    return DataType::BOOL;
}

DataType TypeVisitor::operator()(const std::string& value) const{
    return DataType::STRING;
}

DataType TypeVisitor::operator()(const std::map<std::string, DataValue>& value) const{
    return DataType::MAP;
}

DataType TypeVisitor::operator()(const std::vector<DataValue>& value) const{
    return DataType::LIST;
}

DataValueVariant DataValue::getValueVariant() const{
    return this->data;
}

DataValueVariant SetterVisitor::operator()(const int& value){
    this->v = value;
    return this->v;
}

DataValueVariant SetterVisitor::operator()(const bool& value){
    this->v = value;
    return this->v;

}

DataValueVariant SetterVisitor::operator()(const std::string& value){
    this->v = value;
    return this->v;
}

DataValueVariant SetterVisitor::operator()(const std::vector<DataValue>& value){
    std::vector<DataValue> vec;
    for(int i = 0; i < value.size(); i++){
        vec.push_back(value[i]);
    }
    this->v = vec;
    return this->v;
}

DataValueVariant SetterVisitor::operator()(const std::map<std::string, DataValue>& value){
    std::map<std::string, DataValue> map;
    for(auto it = value.begin(); it != value.end(); it++){
        map.insert(std::pair<std::string, DataValue>(it->first, it->second));
    }
    this->v = map;
    return this->v;
}

DataValue::DataValue(const DataValueVariant& data){
    this->setValue(data);
}

DataValue::DataValue(){
    this->type = DataType::EMPTY;
}

void DataValue::setValue(const DataValueVariant& value){
    this->data = std::visit(SetterVisitor{this->data}, value);
    this->type = std::visit(TypeVisitor(), this->data);
}

std::optional<DataValueVariant> RemoveVisitor::operator()(const int& value){
    std::cout << "Not meant to be called" << std::endl;
    return std::nullopt;
}

std::optional<DataValueVariant> RemoveVisitor::operator()(const bool& value){
    std::cout << "Not meant to be called" << std::endl;
    return std::nullopt;
}

std::optional<DataValueVariant> RemoveVisitor::operator()(const std::string& value){
    std::cout << "Not meant to be called" << std::endl;
    return std::nullopt;
}

std::optional<DataValueVariant> RemoveVisitor::operator()(const std::map<std::string, DataValue>& value){
    std::map<std::string, DataValue> map;
    if(value.size() == 0){
        return std::nullopt;
    }
    for(auto it = value.begin(); it != value.end(); it++){
        map.insert(std::pair<std::string, DataValue>(it->first, it->second));
    }
    if(map.find(key) == map.end()){
        return std::nullopt;
    }
    else{
        map.erase(key);
        return map;
    }
}

std::optional<DataValueVariant> RemoveVisitor::operator()(const std::vector<DataValue>& value){
    std::vector<DataValue> vec;
    if(value.size() == 0){
        return std::nullopt;
    }
    else if(this->i < 0 && this->i >= value.size()){
        return std::nullopt;
    }
    else{
        for(int j = 0; j < value.size(); j++){
            if(j != i){
                vec.push_back(value[j]);
            }
        }
        return vec;
    }
}

std::optional<DataValueVariant> DataValue::remove_from_list(const int& index){
    if(this->getType() == DataType::LIST){
        return std::visit(RemoveVisitor{index, ""}, this->data);
    }
    else{
        std::cout << "Error: DataValue is not a list" << std::endl;
        return std::nullopt;
    }
}

std::optional<DataValueVariant> DataValue::remove_from_map(const std::string& key){
    if(this->getType() == DataType::MAP){
        return std::visit(RemoveVisitor{-1, key}, this->data);
    }
    else{
        std::cout << "Error: DataValue is not a map" << std::endl;
        return std::nullopt;
    }
}