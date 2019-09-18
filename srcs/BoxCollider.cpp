#include "BoxCollider.hpp"
#include "ARenderer.hpp"
#include "Engine.hpp"
#include "BoxColliderRenderer.hpp"

BoxCollider::BoxCollider(GameObject *obj, glm::vec3 min, glm::vec3 max, glm::vec3 scale, glm::vec3 offset, bool showMesh) : ACollider(obj)
{
	this->scale = scale;
	size = max - min; 
	center = (min + size / 2.0f) + offset;
	if (showMesh)
	{
		std::shared_ptr<ARenderer> renderer(new BoxColliderRenderer(obj, this));
		obj->AddComponent(renderer);
		Engine42::Engine::AddRenderer(renderer);
	}
}

BoxCollider::~BoxCollider(void)
{
    
}

bool BoxCollider::IsCollindingWith(ACollider &other) const
{
	glm::vec3 scale = _transform->scale * this->scale;
	glm::vec3 otherScale = other.GetTransform()->scale * other.scale;
	glm::vec3 centerWorldPos = center * scale + _transform->position;
	glm::vec3 otherCenterWorldPos = other.center * otherScale + other.GetTransform()->position;
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
