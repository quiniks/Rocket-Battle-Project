#include "..\include\CollisionHelper.h"

CollisionHelper::CollisionHelper()
{
}

CollisionHelper::~CollisionHelper()
{
}

float CollisionHelper::dot(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.x + a.y * b.x;
}

sf::Vector2f CollisionHelper::cross(sf::Vector2f a, float scalar)
{
	return sf::Vector2f(scalar * a.y, -scalar * a.x);
}

float CollisionHelper::cross(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.y - a.y * b.x;
}

float CollisionHelper::mag(sf::Vector2f a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}

sf::Vector2f CollisionHelper::unit(sf::Vector2f a)
{
	float l_Mag = mag(a);
	return sf::Vector2f(a.x / l_Mag, a.y / l_Mag);
}


void CollisionHelper::resolve(Particle & p_Particle, sf::Vector2f p_Normal, sf::Vector2i p_CollosionPos)
{
	p_Particle.setPosition((sf::Vector2f)p_CollosionPos);
	sf::Vector2f l_DeltaVel = -(1 + p_Particle.getRestitution()) * p_Normal * (p_Normal.x * p_Particle.getVelocity().x + p_Normal.y * p_Particle.getVelocity().y);
	p_Particle.setVelocity(p_Particle.getVelocity() + l_DeltaVel);

}

void CollisionHelper::resolve(DynamicObject & p_DynamicObj, sf::Vector2f p_Normal, float p_DeltaTime)
{
	sf::Vector2f l_Displacement = p_DynamicObj.getVelocity() * p_DeltaTime;
	sf::Vector2f l_CorrectionVector = p_Normal * mag(l_Displacement);
	p_DynamicObj.setPosition(p_DynamicObj.getPosition() + l_CorrectionVector);
	//testing
	float l_VelAlongNormal = dot(p_DynamicObj.getVelocity(), p_Normal);
	sf::Vector2f l_Tangent = p_DynamicObj.getVelocity() - (p_Normal * l_VelAlongNormal);
	l_Tangent = unit(l_Tangent);

	//sf::Vector2f l_UnitTangent = sf::Vector2f(p_Normal.y, -p_Normal.x);
	float l_VelAlongTangent = dot(p_DynamicObj.getVelocity(), l_Tangent/*l_UnitTangent*/);

	sf::Vector2f l_DeltaVel1 = -(1 + p_DynamicObj.getRestitution()) * p_Normal * (p_Normal.x * p_DynamicObj.getVelocity().x + p_Normal.y * p_DynamicObj.getVelocity().y);
	sf::Vector2f l_DeltaVel2 = p_DynamicObj.getFricCo() * l_Tangent/*l_UnitTangent*/ * l_VelAlongTangent;

	p_DynamicObj.setVelocity((p_DynamicObj.getVelocity() + l_DeltaVel1) - l_DeltaVel2);
}

bool CollisionHelper::rayCast(sf::Vector2i p_Start, sf::Vector2i p_Target, Terrain & p_Terrain, sf::Vector2i& p_hitPos)
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
		if (!p_Terrain.isPixelEmpty(sf::Vector2u(l_CurrentX, l_CurrentY))) {
			p_hitPos = sf::Vector2i(l_PrevX, l_PrevY); //return prev for point before collision or return current for point of collision
			return true;
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
	
	return false;
}
bool CollisionHelper::AABBvsTerrain(sf::FloatRect p_BB, sf::Vector2f p_Pos, Terrain & p_Terrain, sf::Vector2f& p_AverageUnitNormal)
{
	//sf::Vector2f l_EdgePixel = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2u l_TopLeft = (sf::Vector2u)((sf::Vector2i)p_Pos + sf::Vector2i(-p_BB.width / 2, -p_BB.height / 2));
	sf::Vector2u l_BottomRight = (sf::Vector2u)((sf::Vector2i)p_Pos + sf::Vector2i(p_BB.width / 2, p_BB.height / 2));

	sf::Vector2f l_SumUnitNormal = sf::Vector2f(0.0f, 0.0f);
	unsigned int l_Total = 0;

	for (int i = 0; i < p_BB.height; i++) {
		//top
		sf::Vector2u l_Top = l_TopLeft + sf::Vector2u(i, 0);
		sf::Vector2u l_Left= l_TopLeft + sf::Vector2u(0, i);
		sf::Vector2u l_Bottom = l_BottomRight - sf::Vector2u(i, 0);
		sf::Vector2u l_Right = l_BottomRight - sf::Vector2u(0, i);
		if (!p_Terrain.isPixelEmpty(l_Top)) {
			l_SumUnitNormal += p_Terrain.GetNormal(l_Top.x, l_Top.y, 2);
			l_Total++;
		}
		//left
		if (!p_Terrain.isPixelEmpty(l_Left)) {
			l_SumUnitNormal += p_Terrain.GetNormal(l_Left.x, l_Left.y, 2);
			l_Total++;
		}
		//bottom
		if (!p_Terrain.isPixelEmpty(l_Bottom)) {
			l_SumUnitNormal += p_Terrain.GetNormal(l_Bottom.x, l_Bottom.y, 2);
			l_Total++;
		}
		//right
		if (!p_Terrain.isPixelEmpty(l_Right)) {
			l_SumUnitNormal += p_Terrain.GetNormal(l_Right.x, l_Right.y, 2);
			l_Total++;
		}
	}
	if (l_Total != 0) {
		p_AverageUnitNormal = l_SumUnitNormal / (float)l_Total;
		return true;
	}
	return false;
}
/*
bool CollisionHelper::OBBvsTerrain(sf::RectangleShape & p_StartBoundingBox, sf::RectangleShape & p_TargetBoundingBox, Terrain & p_Terrain, sf::Vector2i& p_CorrectionPos, sf::Vector2i& p_ContactVector, sf::Vector2i& p_ContactPos)
{
	sf::Vector2i l_BestCorrectionVector = sf::Vector2i(0, 0);
	float l_BestDist = 0.0f;
	bool l_Debounce = false;
	int l_HitFailCounter = 0;
	for (int i = 0; i < p_StartBoundingBox.getPointCount(); i++) {
		sf::Vector2i l_PointA = (sf::Vector2i)p_StartBoundingBox.getTransform().transformPoint(p_StartBoundingBox.getPoint(i));
		sf::Vector2i l_PointB = (sf::Vector2i)p_TargetBoundingBox.getTransform().transformPoint(p_TargetBoundingBox.getPoint(i));
		sf::Vector2i l_ColPoint = sf::Vector2i(0, 0);
		bool l_Hit = rayCast(l_PointA, l_PointB, p_Terrain, l_ColPoint);
		if (l_Hit) {
			float l_Dist = sqrt((l_PointA.x - l_ColPoint.x) * (l_PointA.x - l_ColPoint.x) + (l_PointA.y - l_ColPoint.y) * (l_PointA.y - l_ColPoint.y));
			if (l_Dist < l_BestDist || l_Debounce == false) {
				l_Debounce = true;
				l_BestDist = l_Dist;
				l_BestCorrectionVector = l_ColPoint - l_PointA;
				p_ContactPos = l_ColPoint;
				p_ContactVector = l_PointA - (sf::Vector2i)p_StartBoundingBox.getPosition();
			}
			p_CorrectionPos = (sf::Vector2i)p_StartBoundingBox.getPosition() + l_BestCorrectionVector;
		}
		else {
			l_HitFailCounter++;
		}
		if (l_HitFailCounter == p_StartBoundingBox.getPointCount()) {
			return false;
		}
	}
	return true;
}
*/