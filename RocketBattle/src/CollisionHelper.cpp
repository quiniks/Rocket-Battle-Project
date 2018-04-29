#include "..\include\CollisionHelper.h"

CollisionHelper::CollisionHelper()
{
}

CollisionHelper::~CollisionHelper()
{
}

void CollisionHelper::resolve(DynamicObject & p_DynamicObject, sf::Vector2f p_Normal, sf::Vector2i p_CollosionPos)
{
	p_DynamicObject.setPosition((sf::Vector2f)p_CollosionPos);//the error with sliding pixels is with the collosion pos, not velocity (facepalm)
	sf::Vector2f l_DeltaVel = -(1 + p_DynamicObject.getRestitution()) * p_Normal * (p_Normal.x * p_DynamicObject.getVelocity().x + p_Normal.y * p_DynamicObject.getVelocity().y);
	p_DynamicObject.setVelocity(p_DynamicObject.getVelocity() + l_DeltaVel);

}

sf::Vector2i CollisionHelper::rayCast(sf::Vector2i p_Start, sf::Vector2i p_Target, Terrain & p_rTerrain)
{
	int l_DeltaX = abs(p_Start.x - p_Target.x);
	int l_DeltaY = abs(p_Start.y - p_Target.y);
	int l_CurrentX = p_Start.x;
	int l_CurrentY = p_Start.y;
	int l_XInc1, l_XInc2, l_YInc1, l_YInc2;

	if (p_Target.x >= p_Start.x) {
		l_XInc1 = 1;
		l_XInc2 = 1;
	} else {
		l_XInc1 = -1;
		l_XInc2 = -1;
	}

	if (p_Target.y >= p_Start.y) {
		l_YInc1 = 1;
		l_YInc2 = 1;
	} else {
		l_YInc1 = -1;
		l_YInc2 = -1;
	}

	int l_Den, l_Num, l_NumAdd, l_NumPixels;
	if (l_DeltaX >= l_DeltaY) {
		l_XInc1 = 0;
		l_YInc2 = 0;
		l_Den = l_DeltaX;
		l_Num = l_DeltaX / 2;
		l_NumAdd = l_DeltaY;
		l_NumPixels = l_DeltaX;
	} else {
		l_XInc2 = 0;
		l_YInc1 = 0;
		l_Den = l_DeltaY;
		l_Num = l_DeltaY / 2;
		l_NumAdd = l_DeltaX;
		l_NumPixels = l_DeltaY;
	}

	int l_PrevX = p_Start.x;
	int l_PrevY = p_Start.y;
	for (int pixel = 0; pixel <= l_NumPixels; pixel++) {
		if (!p_rTerrain.isPixelEmpty(sf::Vector2u(l_CurrentX, l_CurrentY))) {
			return sf::Vector2i(l_PrevX, l_PrevY); //return prev for point before collision or return current for point of collision
		}
		l_PrevX = l_CurrentX;
		l_PrevY = l_CurrentY;

		l_Num += l_NumAdd;

		if (l_Num >= l_Den) {
			l_Num -= l_Den;
			l_CurrentX += l_XInc1;
			l_CurrentY += l_YInc1;
		}

		l_CurrentX += l_XInc2;
		l_CurrentY += l_YInc2;
	}
	
	return sf::Vector2i(0,0);
}


