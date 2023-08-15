#pragma once
#include <string>
#include <rapidjson/include/rapidjson/document.h>
#include "Vector2.h"

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
	};
}