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
	return sqrtf(a.x * a.x + a.y * a.y);
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
		if (!p_Terrain.isPixelEmpty(sf::Vector2i(l_CurrentX, l_CurrentY))) {
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
	sf::Vector2i l_TopLeft = (sf::Vector2i)p_Pos + sf::Vector2i(-p_BB.width / 2, -p_BB.height / 2);
	sf::Vector2i l_BottomRight = (sf::Vector2i)p_Pos + sf::Vector2i(p_BB.width / 2, p_BB.height / 2);

	sf::Vector2f l_SumUnitNormal = sf::Vector2f(0.0f, 0.0f);
	unsigned int l_Total = 0;

	for (int i = 0; i < p_BB.height; i++) {
		//top
		sf::Vector2i l_Top = l_TopLeft + sf::Vector2i(i, 0);
		sf::Vector2i l_Left= l_TopLeft + sf::Vector2i(0, i);
		sf::Vector2i l_Bottom = l_BottomRight - sf::Vector2i(i, 0);
		sf::Vector2i l_Right = l_BottomRight - sf::Vector2i(0, i);
		if (!p_Terrain.isPixelEmpty(l_Top)) {
			l_SumUnitNormal += p_Terrain.getNormal(l_Top.x, l_Top.y, 2);
			l_Total++;
		}
		//left
		if (!p_Terrain.isPixelEmpty(l_Left)) {
			l_SumUnitNormal += p_Terrain.getNormal(l_Left.x, l_Left.y, 2);
			l_Total++;
		}
		//bottom
		if (!p_Terrain.isPixelEmpty(l_Bottom)) {
			l_SumUnitNormal += p_Terrain.getNormal(l_Bottom.x, l_Bottom.y, 2);
			l_Total++;
		}
		//right
		if (!p_Terrain.isPixelEmpty(l_Right)) {
			l_SumUnitNormal += p_Terrain.getNormal(l_Right.x, l_Right.y, 2);
			l_Total++;
		}
	}
	if (l_Total != 0) {
		p_AverageUnitNormal = l_SumUnitNormal / (float)l_Total;
		return true;
	}
	return false;
}
bool CollisionHelper::AABBvsAABB(sf::FloatRect p_BB1, sf::Vector2f p_Pos1, sf::FloatRect p_BB2, sf::Vector2f p_Pos2)
{
	sf::Vector2u l_TopLeft1 = (sf::Vector2u)((sf::Vector2i)p_Pos1 + sf::Vector2i(-p_BB1.width / 2, -p_BB1.height / 2));
	sf::Vector2u l_TopLeft2 = (sf::Vector2u)((sf::Vector2i)p_Pos2 + sf::Vector2i(-p_BB2.width / 2, -p_BB2.height / 2));

	sf::Vector2u l_BottomRight1 = (sf::Vector2u)((sf::Vector2i)p_Pos1 - sf::Vector2i(-p_BB1.width / 2, -p_BB1.height / 2));
	sf::Vector2u l_BottomRight2 = (sf::Vector2u)((sf::Vector2i)p_Pos2 - sf::Vector2i(-p_BB2.width / 2, -p_BB2.height / 2));

	if (l_BottomRight1.x < l_TopLeft2.x || l_TopLeft1.x > l_BottomRight2.x) {
		return false;
	}
	if (l_BottomRight1.y < l_TopLeft2.y || l_TopLeft1.y > l_BottomRight2.y) {
		return false;
	}
	return true;
}
bool CollisionHelper::AABBvsCircle(sf::CircleShape p_Circle1, sf::Vector2f p_Pos1, sf::FloatRect p_BB2, sf::Vector2f p_Pos2)
{
	sf::Vector2f l_Diff = p_Pos2 - p_Pos1;
	sf::Vector2f l_DiffConstrained;
	if (l_Diff.x < 0) {
		l_DiffConstrained.x = std::max(l_Diff.x, -p_BB2.width / 2.0f);
	}
	else {
		l_DiffConstrained.x = std::min(l_Diff.x, p_BB2.width / 2.0f);
	}
	if (l_Diff.y < 0) {
		l_DiffConstrained.y = std::max(l_Diff.y, -p_BB2.height / 2.0f);
	}
	else {
		l_DiffConstrained.y = std::min(l_Diff.y, p_BB2.height / 2.0f);
	}
	float l_Pen = -(mag(l_Diff - l_DiffConstrained) - p_Circle1.getRadius());
	if (l_Pen > 0) {
		return true;
	}
	return false;
}