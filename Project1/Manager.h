#pragma once
#include "Component.h"
#include "Entity.h"
#include <map>
class Manager
{
public:
	Manager();

	std::map<int, Component*> componentIdMap;
	std::map<int, Entity*> entityIdMap;

	int numberOfInstances;

	virtual ~Manager();
};

