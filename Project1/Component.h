#pragma once
//#include "EntityFactory.h"

class Component
{
public:
	Component();
	virtual ~Component();

public:
	int entityId;

	void Update();
};

