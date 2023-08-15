#include "Json.h"
#include <rapidjson/include/rapidjson/istreamwrapper.h>
#include "Logger.h"
#include "Core/FileIO.h"
#include <sstream>

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

bool afro::Json::Read(const rapidjson::Value& value, const std::string& name, float& data, bool required)
{
    if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsFloat())
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




