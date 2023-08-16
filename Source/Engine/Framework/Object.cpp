#include "Object.h"

namespace afro
{
	bool Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name)

		return true;
	}
}