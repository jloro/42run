#include "ACollider.hpp"
#include <iostream>
#include "ColliderRenderer.hpp"
#include "Engine.hpp"

ACollider::ACollider(GameObject *obj, glm::vec3 min, glm::vec3 max, glm::vec3 scale, glm::vec3 offset, bool showMesh) : AComponent(obj)
{
	(void)scale;
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
	glm::vec3 centerWorldPos = center * _transform->scale + _transform->position;
	glm::vec3 otherCenterWorldPos = other.center * other._transform->scale + other._transform->position;
	glm::vec3 scale = (size * _transform->scale) / 2.0f;
	glm::vec3 otherScale = (other.size * other._transform->scale) / 2.0f;
	if (abs(centerWorldPos.x - otherCenterWorldPos.x) < scale.x + otherScale.x)
	{
		if (abs(centerWorldPos.y - otherCenterWorldPos.y) < scale.y + otherScale.y)
		{
			if (abs(centerWorldPos.z - otherCenterWorldPos.z) < scale.z + otherScale.z)
				return true;
		}
	}
	return false;
}
