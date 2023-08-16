#pragma once

namespace afro
{
	template <typename T> 
	class Singleton
	{
	public:
		Singleton(const Singleton& other) {}
		Singleton& operator = (const Singleton& other) = delete;
		friend class Factory;

		static T& Instance()
		{
			static T instance;
			return instance;
		}
	protected:
		Singleton() = default;
	};
}