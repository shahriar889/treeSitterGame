#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <variant>
#include <cassert>
#include <optional>


namespace DV{

    enum class DataType{
        INT,
        BOOL,
        STRING,
        MAP,
        LIST,
        EMPTY
    };

        
    
    class DataValue;
    using DataValueVariant = std::variant<int, bool, std::string, std::map<std::string, DataValue>, std::vector<DataValue>>;


    struct GetterVisitor{
    public:
        int i;
        std::string key;

        GetterVisitor(const int& index, const std::string& keyName){
            this->i = index;
            this->key = keyName;
        }

        DataValue operator()(const int& value) const;
        DataValue operator()(const bool& value) const;
        DataValue operator()( const std::string& value) const;
        DataValue operator()(const std::vector<DataValue>& vec) const;
        DataValue operator()(const std::map<std::string, DataValue>& map) const;
    };

    struct InsertVisitor{
    public:
        DataValueVariant v;
        std::string key;

        InsertVisitor(DataValueVariant value, std::string keyName)
        : v(value), key(std::move(keyName)) {}

        void operator()(std::vector<DataValue>& vec);
        void operator()(std::map<std::string, DataValue>& map);
        void operator()(int& value);
        void operator()(bool& value);
        void operator()(std::string& value);
    };



    struct printVisitor{
    public:
        void operator()(int value) const;
        void operator()(bool value) const;
        void operator()(std::string value) const;
        void operator()(std::map<std::string, DataValue> value) const;
        void operator()(std::vector<DataValue> value) const;
    };

    struct EqualityVisitor{
    public:
        DataValueVariant v;

        EqualityVisitor(DataValueVariant value): v(value) {}

        bool operator()(const int& value1) const;
        bool operator()(const bool& value1) const;
        bool operator()(const std::string& value1) const;
        bool operator()(const std::map<std::string, DataValue>& value1) const;
        bool operator()(const std::vector<DataValue>& value1) const;
    };

    struct TypeVisitor{
    public:
        DataType operator()(const int& value) const;
        DataType operator()(const bool& value) const;
        DataType operator()(const std::string& value) const;
        DataType operator()(const std::map<std::string, DataValue>& value) const;
        DataType operator()(const std::vector<DataValue>& value) const;
    };

    struct SizeVisitor{
    public:
        size_t operator()(const int& value) const;
        size_t operator()(const bool& value) const;
        size_t operator()(const std::string& value) const;
        size_t operator()(const std::map<std::string, DataValue>& value) const;
        size_t operator()(const std::vector<DataValue>& value) const;
    };

    struct SetterVisitor{
    public:
        DataValueVariant v;

        SetterVisitor(DataValueVariant& value): v(value) {}

        DataValueVariant operator()(const int& value);
        DataValueVariant operator()(const bool& value);
        DataValueVariant operator()(const std::string& value);
        DataValueVariant operator()(const std::map<std::string, DataValue>& value);
        DataValueVariant operator()(const std::vector<DataValue>& value);
    };

    struct RemoveVisitor{
    public:
        int i;
        std::string key;

        RemoveVisitor(const int& index, const std::string& keyName){
            this->i = index;
            this->key = keyName;
        }

        std::optional<DataValueVariant> operator()(const int& value);
        std::optional<DataValueVariant> operator()(const bool& value);
        std::optional<DataValueVariant> operator()(const std::string& value);
        std::optional<DataValueVariant> operator()(const std::map<std::string, DataValue>& value);
        std::optional<DataValueVariant> operator()(const std::vector<DataValue>& value);
    };

    
    class DataValue{
    private:
        DataValueVariant data;
        DataType type;
    public:
        DataValue();
    
        DataValue(const DataValueVariant& data);

        // Setter method for getting data
        void setValue(const DataValueVariant& data);
        DataValueVariant getValueVariant() const;
    
        //Function to Push_back in the vector
        void push_back_list(const DataValue& data);
        void insert_map(std::string key, const DataValue& data);
        DataValue get_list(const int& index) const;
        DataValue get_map_item(const std::string& key) const;
        size_t size() const;
        void print() const;
        bool operator==(const DataValue& other) const;
        bool isEmpty() const;
        DataType getType() const;
        std::optional<DataValueVariant> remove_from_list(const int& index);
        std::optional<DataValueVariant> remove_from_map(const std::string& key);

        };        


}



