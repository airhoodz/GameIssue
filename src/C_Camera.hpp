#ifndef C_Camera_hpp
#define C_Camera_hpp

#include "Component.hpp"


class C_Camera : public Component
{
public:
	C_Camera(Object* owner);

	void LateUpdate(float deltaTime) override;


private:

};

#endif
