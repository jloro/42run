#include "RoomManager.hpp"
#include "ARenderer.hpp"
#include "Engine.hpp"
#include <gtx/rotate_vector.hpp>
#include "gtx/compatibility.hpp"
#include "GameManager.hpp"
const unsigned int	RoomManager::maxRooms = 10;

RoomManager::RoomManager() : _nbRooms(0), _rotationMax(-90), _rotateWay(2.0f), _cornerSpawned(true)
{
	_rotate = false;
	_nextRot = glm::vec3(0.0f, 0.0f, 0.0f);
	_nextPos = glm::vec3(0.0f, 0.0f, 0.0f);
	_way = glm::vec3(0.0f, 0.0f, 1.0f);
	_wayPlacement = glm::vec3(0.0f, 0.0f, 1.0f);

	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::shared_ptr<Shader> 	myShader(new Shader(shadersPath, type));
	_corridor.reset(new Model("corridor/couloir.obj"));
	_corner.reset(new Model("corridor/corner.obj"));
	Transform trans(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(40.0f, 20.0f, 40.0f), _transform);
	srand(time(0));
	for (unsigned int i = 0; i < 20; i++)
	{
		std::shared_ptr<GameObject> go(new GameObject(trans, eTags::Corridor));
		std::shared_ptr<ARenderer> renderer(new MeshRenderer(_corridor, myShader, std::shared_ptr<GameObject>(nullptr), false));
		go->AddComponent(renderer);
		corridors.push_back(go);
	}
	for (unsigned int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> go(new GameObject(trans, eTags::Corner));
		std::shared_ptr<ARenderer> renderer(new MeshRenderer(_corner, myShader, std::shared_ptr<GameObject>(nullptr), false));
		go->AddComponent(renderer);
		corners.push_back(go);
	}

	for (auto it = corridors.begin(); it != corridors.end() && _nbRooms < maxRooms - 1; it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			_rooms.push_back((*it));
			(*it)->GetTransform()->position = _nextPos;
			_nextPos += _wayPlacement * 80.0f;
			_nbRooms++;
			Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
			(*it)->GetComponent<MeshRenderer>()->SetRender(true);
		}
	}
	for (auto it = corners.begin(); it != corners.end() && _nbRooms < maxRooms; it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			_rooms.push_back((*it));
			(*it)->GetTransform()->position = _nextPos + _wayPlacement * 80.0f;
			_nextPos += _wayPlacement * 80.0f;
			_nextRot += glm::vec3(0.0f, 90.0f, 0.0f);
			_wayPlacement = glm::rotate(_wayPlacement, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			_nextPos += _wayPlacement * 80.0f;
			_nbRooms++;
			Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
			(*it)->GetComponent<MeshRenderer>()->SetRender(true);
			if (glm::distance(_wayPlacement, glm::vec3(1.0f, 0.0f, 0.0f)) < 0.1f || glm::distance(_wayPlacement, glm::vec3(-1.0f, 0.0f, 0.0f)) < 0.1f)
				_nextPos.x += _wayPlacement.x < 0.0f ? -80.0f : 80.0f;
			else
				_nextPos.z += _wayPlacement.z < 0.0f ? -80.0f : 80.0f;
		}
	}
}

RoomManager::~RoomManager() {}

bool		_sort(const std::shared_ptr<GameObject> first, const std::shared_ptr<GameObject> sec)
{
	return first->GetTransform()->position.z < sec->GetTransform()->position.z;
}

void	RoomManager::Update()
{
	if (_nbRooms < maxRooms)
	{
		if (rand() % 100 > 90 && !_cornerSpawned)
			_AddCorner(static_cast<bool>(rand() % 2));
		else
			_AddCorridor();
	}
	if (_rotate)
	{
		_transform->rotation.y -= _rotateWay;
		_transform->UpdateMatrix();
	}
	for (auto it = _rooms.begin(); it != _rooms.end(); it++)
	{
		glm::vec3 tmp = (*it)->GetTransform()->position * _way;
		if (tmp.x + tmp.y + tmp.z < 40 && (*it)->GetTag() == eTags::Corner)
		{
			if (_transform->rotation.y < _rotationMax || _transform->rotation.y > _rotationMax)
			{
				_rotate = true;
				_way = glm::rotate(_way, glm::radians(_rotateWay), glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else
				_rotate = false;
		}
		if (tmp.x + tmp.y + tmp.z < -160)
		{
			if ((*it)->GetTag() == eTags::Corner)
				_cornerSpawned = false;
			(*it)->GetComponent<MeshRenderer>()->SetRender(false);
			(*it)->GetComponent<MeshRenderer>()->Destroy();
			_rooms.erase(it);
			_nbRooms--;
			continue;
		}
		(*it)->GetTransform()->position -= _way * static_cast<float>(GameManager::speedWorld) * Engine42::Time::GetDeltaTime();
		(*it)->GetTransform()->UpdateMatrix();
	}
	_nextPos -= _way * static_cast<float>(GameManager::speedWorld) * Engine42::Time::GetDeltaTime();
}

void	RoomManager::FixedUpdate()
{

}

void	RoomManager::_AddCorner(bool left)
{
	for (auto it = corners.begin(); it != corners.end(); it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			if (left)
			{
				_rotateWay = 2.0f;
				_cornerSpawned = true;
				_rotationMax -= 90;
				_rooms.push_back((*it));
				(*it)->GetTransform()->position = _nextPos + _wayPlacement * 80.0f;
				(*it)->GetTransform()->rotation = _nextRot;
				_nextPos += _wayPlacement * 80.0f;
				_nextRot += glm::vec3(0.0f, 90.0f, 0.0f);
				_wayPlacement = glm::rotate(_wayPlacement, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				_nextPos += _wayPlacement * 80.0f;
				_nbRooms++;
				Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
				(*it)->GetComponent<MeshRenderer>()->SetRender(true);
				if (glm::distance(_wayPlacement, glm::vec3(1.0f, 0.0f, 0.0f)) < 0.1f || glm::distance(_wayPlacement, glm::vec3(-1.0f, 0.0f, 0.0f)) < 0.1f)
					_nextPos.x += _wayPlacement.x < 0.0f ? -80.0f : 80.0f;
				else
					_nextPos.z += _wayPlacement.z < 0.0f ? -80.0f : 80.0f;
				break;
			}
			else
			{
				_rotateWay = -2.0f;
				_cornerSpawned = true;
				_rotationMax += 90;
				_rooms.push_back((*it));
				(*it)->GetTransform()->position = _nextPos + _wayPlacement * 80.0f;
				(*it)->GetTransform()->rotation = _nextRot;
				(*it)->GetTransform()->rotation.y += 90.0f;
				_nextPos += _wayPlacement * 80.0f;
				_nextRot -= glm::vec3(0.0f, 90.0f, 0.0f);
				_wayPlacement = glm::rotate(_wayPlacement, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				_nextPos += _wayPlacement * 80.0f;
				_nbRooms++;
				Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
				(*it)->GetComponent<MeshRenderer>()->SetRender(true);
				if (glm::distance(_wayPlacement, glm::vec3(1.0f, 0.0f, 0.0f)) < 0.1f || glm::distance(_wayPlacement, glm::vec3(-1.0f, 0.0f, 0.0f)) < 0.1f)
					_nextPos.x += _wayPlacement.x < 0.0f ? -80.0f : 80.0f;
				else
					_nextPos.z += _wayPlacement.z < 0.0f ? -80.0f : 80.0f;
				break;
			}
		}
	}
}

void	RoomManager::_AddCorridor()
{
	for (auto it = corridors.begin(); it != corridors.end(); it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			_rooms.push_back((*it));
			(*it)->GetTransform()->position = _nextPos;
			_nextPos += _wayPlacement * 80.0f;
			(*it)->GetTransform()->rotation = _nextRot;
			_nbRooms++;
			Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
			(*it)->GetComponent<MeshRenderer>()->SetRender(true);
			break;
		}
	}
}
