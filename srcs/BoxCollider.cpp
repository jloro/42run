#include "BoxCollider.hpp"
#include "ARenderer.hpp"
#include "Engine.hpp"
#include "BoxColliderRenderer.hpp"
#include "gtx/rotate_vector.hpp"

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
	sizeWorld = glm::rotate(sizeWorld, glm::radians(_transform->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	sizeWorld = glm::rotate(sizeWorld, glm::radians(_transform->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	sizeWorld = glm::rotate(sizeWorld, glm::radians(_transform->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec3 otherSizeWorld = (other.size * otherScale) / 2.0f;
	otherSizeWorld = glm::abs(glm::rotate(glm::vec3(otherSizeWorld.x, 0.0f, 0.0f), glm::radians(other.GetTransform()->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) + glm::rotate(glm::vec3(0.0f, otherSizeWorld.y, 0.0f), glm::radians(other.GetTransform()->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) + glm::rotate(glm::vec3(0.0f, 0.0f, otherSizeWorld.z), glm::radians(other.GetTransform()->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)));
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
