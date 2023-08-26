#pragma once

namespace afro
{
	template <typename T> 
	class Singleton
	{
	public:
		friend class EventManager;
		Singleton(const Singleton& other) {}
		Singleton& operator = (const Singleton& other) = delete;
		friend class Factory;
		friend class PhysicsSystem;
		static T& Instance()
		{
			static T instance;
			return instance;
		}
	protected:
		Singleton() = default;
	};


}