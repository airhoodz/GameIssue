#ifndef C_Instance_hpp
#define C_Instance_hpp

#include "Component.hpp"

class C_InstanceID : public Component
{
public:
	C_InstanceID(Object* owner);
	~C_InstanceID();

	unsigned int Get() const;

private:
	static unsigned int count;
	unsigned int id;
};

#endif

