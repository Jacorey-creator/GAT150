#include "Json.h"
#include <rapidjson/include/rapidjson/istreamwrapper.h>
#include "Logger.h"
#include "Core/FileIO.h"
#include <sstream>
#include "Color.h"

bool afro::Json::Load(const std::string& filename, rapidjson::Document& document)
{
    std::string buffer;
    if (!readFile(filename,buffer))
    {
        WARNING_LOG("Cannot open file: " << filename);
        return false;
    }
    std::stringstream stream(buffer);
    rapidjson::IStreamWrapper istream(stream);
    // parse stream to json
    document.ParseStream(istream);
    
    if (!document.IsObject())
    {
        WARNING_LOG("Json file cannot be parsed: " << filename);
        return false;
    }
    return true;
}

bool afro::Json::Read(const rapidjson::Value& value, const std::string& name, int& data, bool required)
{
    if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
    {
        if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
        return false;
    }
    data = value[name.c_str()].GetInt();

    return false;
}

bool afro::Json::Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required)
{
    if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
    {
        if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
        return false;
    }
    data = value[name.c_str()].GetBool();

    return false;
}

bool afro::Json::Read(const rapidjson::Value& value, const std::string& name, float& data, bool required)
{
    if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
    {
        if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
        return false;
    }
    data = value[name.c_str()].GetFloat();
    
    return false;
}

bool afro::Json::Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required)
{
    if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
    {
        if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
        return false;
    }
    data = value[name.c_str()].GetString();
    
    return true;
}

bool afro::Json::Read(const rapidjson::Value& value, const std::string& vname, Vector2& data, bool required)
{
    // check if 'name' member exists and is an array with 2 elements
    if (!value.HasMember(vname.c_str()) || !value[vname.c_str()].IsArray() || value[vname.c_str()].Size() != 2)
    {
        if (required) ERROR_LOG("Cannot read required json data: " << vname.c_str());
        return false;
    }
    // create json array object
    auto& array = value[vname.c_str()];
    // get array values
    for (rapidjson::SizeType i = 0; i < array.Size(); i++)
    {
        if (!array[i].IsNumber())
        {
            if (required) ERROR_LOG("Invalid json data type: " << vname.c_str());
            return false;
        }
        data[i] = array[i].GetFloat();
    }
    return true;
}

bool afro::Json::Read(const rapidjson::Value& value, const std::string& name, Color& data, bool required)
{

    // check if 'name' member exists and is an array with 4 elements
    if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
    {
        if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
        return false;
    }
    // create json array object
    auto& array = value[name.c_str()];
    // get array values
    for (rapidjson::SizeType i = 0; i < array.Size(); i++)
    {
        if (!array[i].IsNumber())
        {
            if (required) ERROR_LOG("Invalid json data type: " << name.c_str());
            return false;
        }
        data[i] = array[i].GetFloat();
    }
    return true;
}

bool afro::Json::Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool required)
{

    // check if 'name' member exists and is an array with 4 elements
    if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
    {
        if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
        return false;
    }
    // create json array object
    auto& array = value[name.c_str()];
    // get array values
    for (rapidjson::SizeType i = 0; i < array.Size(); i++)
    {
        if (!array[i].IsNumber())
        {
            if (required) ERROR_LOG("Invalid json data type: " << name.c_str());
            return false;
        }
        data[i] = array[i].GetInt();
    }
    return true;
}

bool afro::Json::Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool required)
{
    if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
    {
        if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
        return false;
    }
    // create json array object
    auto& array = value[name.c_str()];
    // get array values
    for (rapidjson::SizeType i = 0; i < array.Size(); i++)
    {
        if (!array[i].IsNumber())
        {
            if (required) ERROR_LOG("Invalid json data type: " << name.c_str());
            return false;
        }
        data.push_back(array[i].GetInt());
    }
    return true;
}


//fix
bool afro::Json::Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool required)
{
    if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
    {
        if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
        return false;
    }
    // create json array object
    auto& array = value[name.c_str()];
    // get array values
    for (rapidjson::SizeType i = 0; i < array.Size(); i++)
    {
        if (!array[i].IsString())
        {
            if (required) ERROR_LOG("Invalid json data type: " << name.c_str());
            return false;
        }
        data.push_back(array[i].GetString());
    }
    return true;
}





