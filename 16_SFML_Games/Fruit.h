#pragma once
class Fruit
{
public:
	Fruit();
	~Fruit();

	struct FruitStruct
	{
		int posX = 0;
		int posY = 0;
	} m_fruitStruct;

private:
	const int m_FRUIT_STARTING_POS = 10;
};

