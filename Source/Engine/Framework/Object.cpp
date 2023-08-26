#include "Object.h"

namespace afro
{
	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);

	}
}