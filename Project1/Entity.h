#pragma once
#include <vector>
#include "Component.h"
class Entity
{
public:
	Entity();

	std::vector<int> components;

	int parent;

	virtual ~Entity();
};

