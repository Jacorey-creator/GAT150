#pragma once
#include <string>
#include <rapidjson/include/rapidjson/document.h>
#include "Color.h"
#include "Math/Rect.h"
#include "Vector2.h"

#define READ_DATA(value, data) afro::Json::Read(value, #data, data)
#define READ_DATA_REQUIRED(value, data) afro::Json::Read(value, #data, data, true);
#define HAS_DATA(value, data) value.HasMember(#data)
#define GET_DATA(value, data) value[#data]
#define READ_NAME_DATA(value, name, data) afro::Json::Read(value, name, data)
#define READ_NAME_DATA_REQUIRED(value, name, data) afro::Json::Read(value, name, data, true)

namespace afro
{
	class Json
	{
	public:
		static bool Load(const std::string& filename, rapidjson::Document& document);
		static bool Read(const rapidjson::Value& value, const std::string& name, /*returning*/ int& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, /*returning*/ float& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name,  /*returning*/ std::string& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name,  /*returning*/ Vector2& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name,  /*returning*/ Color& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name,  /*returning*/ Rect& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name,  /*returning*/ bool& data, bool required = false);
	};

	using json_t = rapidjson::Value;
}