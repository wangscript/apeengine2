#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

#include <string>

class GameObject;

class GameComponent {
public:
	
	GameComponent() : mOwnerObj(0) {}
	virtual ~GameComponent() = 0 {}

	virtual const std::string& componentID() const = 0;
	virtual const std::string& familyID() const = 0;

	virtual void update() {}
	virtual void setup() {}

	void setOwnerObject( GameObject* obj) { 
		mOwnerObj = obj; 
	}
	
	GameObject* getOwnerObject() const { 
		return mOwnerObj; 
	}
	
	//virtual GameComponent* makeComponent() = 0;

private:
	GameObject *mOwnerObj;
};

#endif
