#include "ACollider.hpp"
#include <iostream>
#include "ColliderRenderer.hpp"
#include "Engine.hpp"

ACollider::ACollider(GameObject *obj, glm::vec3 min, glm::vec3 max, glm::vec3 scale, glm::vec3 offset, bool showMesh) : AComponent(obj)
{
	this->scale = scale;
	size = max - min; 
	center = (min + size / 2.0f) + offset;
	//transform.reset(new Transform(glm::vec3(0.0f), glm::vec3(0.0f), scale, obj->GetTransform()));
	if (showMesh)
	{
		std::shared_ptr<ARenderer> renderer(new ColliderRenderer(obj, this));
		obj->AddComponent(renderer);
		Engine42::Engine::AddRenderer(renderer);
	}
}

ACollider::~ACollider(void)
{
    
}

bool ACollider::IsCollindingWith(ACollider &other)
{
	glm::vec3 scale = _transform->scale * this->scale;
	glm::vec3 otherScale = other._transform->scale * other.scale;
	glm::vec3 centerWorldPos = center * scale + _transform->position;
	glm::vec3 otherCenterWorldPos = other.center * otherScale + other._transform->position;
	glm::vec3 sizeWorld = (size * scale) / 2.0f;
	glm::vec3 otherSizeWorld = (other.size * otherScale) / 2.0f;
	if (abs(centerWorldPos.x - otherCenterWorldPos.x) < sizeWorld.x + otherSizeWorld.x)
	{
		if (abs(centerWorldPos.y - otherCenterWorldPos.y) < sizeWorld.y + otherSizeWorld.y)
		{
			if (abs(centerWorldPos.z - otherCenterWorldPos.z) < sizeWorld.z + otherSizeWorld.z)
				return true;
		}
	}
	return false;
}
