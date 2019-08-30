#pragma once
#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"
#include <stdlib.h>
#include <ctime>

class BallComponent : public Component
{
public:
	BallComponent(int sp, Vector2D vel) : speed(sp), velocity(vel)
	{

	}

	int GetRandomNumber(int min, int max)
	{
		return rand() % max + min;
	}

	//float calc_angle(float y1, float y2, int height)
	//{
	//	float rely = y1 + height / 2 - y2;
	//	rely /= height / 2;
	//	return rely * 3.142 / 5.0;
	//}

	~BallComponent()
	{}

	void Init() override
	{
		//srand(time(NULL));

		transform = &entity->getComponent<TransformComponent>();

		//transform->velocity = velocity;
	}

	void Update() override
	{
		/*	transform->position.x += xvel;
			transform->position.y += yvel;

			if (transform->position.y < 1)
			{
				yvel = -yvel;
			}

			if (transform->position.y + this->transform->height < 599 )
			{
				yvel = -yvel;
			}*/

	}

	//void ResetBall()
	//{
	//	transform->position.x = GetRandomNumber(2, -2);
	//	transform->position.y = GetRandomNumber(2, -2);
	//}

private:
	TransformComponent *transform;
	int xvel, yvel;
	int speed = 0;
	Vector2D velocity;
};
