#pragma once
#include "Component.h"
#include "Physics.h"
#include "Manager.h"

enum ComponentType
{
	CompPhysics
};
class EntityFactory
{
	Manager* manager;
public:
	EntityFactory();
	virtual ~EntityFactory();

	template < typename T>
	int CreateComponent()
	{
		Component* newComp = new T();
		int id = manager->numberOfInstances;
		newComp->entityId = id;
		manager->componentIdMap[id] = newComp;
	}


	int AddComponent(ComponentType compType)
	{
		//CreateComponent<Physics>();
	}
	
};

