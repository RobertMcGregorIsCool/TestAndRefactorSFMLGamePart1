#pragma once
#include "Snek.h"

class Fruit
{
public:
	Fruit();
	~Fruit();

	struct FruitStruct
	{
		Vec2Int pos = { 0,0 };
	} m_fruitStruct;

private:
	const int m_FRUIT_STARTING_POS = 10;
};

