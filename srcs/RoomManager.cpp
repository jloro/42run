#include "RoomManager.hpp"
#include "ARenderer.hpp"
#include "Engine.hpp"
#include <gtx/rotate_vector.hpp>

const unsigned int	RoomManager::maxRooms = 10;

RoomManager::RoomManager() : _nbRooms(0)
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
	/*
	for (int i = 0; i < 30; i++)
	{
		float p = rand() % 100;
		if (p < 90)
		{
			tag = eTags::Corridor;
			trans.position += _way * 80.0f;
			trans.rotation = _nextRot;
		} else
		{
			tag = eTags::Corner;
			trans.position += _way * 160.0f;
			_nextRot += glm::vec3(0.0f, 90.0f, 0.0f);
			_way = glm::rotate(_way, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		std::shared_ptr<GameObject> go(new GameObject(trans, tag));
		if (p >= 90)
		{
			if (glm::distance(_way, glm::vec3(1.0f, 0.0f, 0.0f)) < 0.1f || glm::distance(_way, glm::vec3(-1.0f, 0.0f, 0.0f)) < 0.1f)
				trans.position.x += _way.x < 0.0f ? -80.0f : 80.0f;
			else
				trans.position.z += _way.z < 0.0f ? -80.0f : 80.0f;
		}
		std::shared_ptr<ARenderer> renderer;
		if (p < 90)
		{
			renderer.reset(new MeshRenderer(_corridor, myShader, std::shared_ptr<GameObject>(nullptr), true));
		}
		else
		{
			renderer.reset(new MeshRenderer(_corner, myShader, std::shared_ptr<GameObject>(nullptr), true));
		}
		Engine42::Engine::AddRenderer(renderer);
		go->AddComponent(renderer);
		_rooms.push_back(go);
	}
	_way = glm::vec3(0.0f, 0.0f, 1.0f);
	*/
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

	//_lastRoom.reset(new Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(40.0f, 20.0f, 40.0f), _transform));
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
			//_lastRoom = (*it)->GetTransform();
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
		if (rand() % 100 < 95)
			_AddCorridor();
		else
			_AddCorner();
	}
	if (_rotate)
	{
		_transform->rotation.y -= 1;
		_transform->UpdateMatrix();
	}
	for (auto it = _rooms.begin(); it != _rooms.end(); it++)
	{
		glm::vec3 tmp = (*it)->GetTransform()->position * _way;
		if (tmp.x + tmp.y + tmp.z < 40 && (*it)->GetTag() == eTags::Corner)
		{
			if (_transform->rotation.y > -90)
			{
				_rotate = true;
				_way = glm::rotate(_way, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				std::cout <<_way << std::endl;
			}
			else
				_rotate = false;
			//(*it)->GetTransform()->position.z = _rooms.back()->GetTransform()->position.z + 80.0f;
		}
		//if (!_rotate)
		(*it)->GetTransform()->position -= _way * 90.0f * Engine42::Time::GetDeltaTime();
		if (tmp.x + tmp.y + tmp.z < -160)
		{
			(*it)->GetComponent<MeshRenderer>()->SetRender(false);
			(*it)->GetComponent<MeshRenderer>()->Destroy();
			_rooms.erase(it);
			_nbRooms--;
			continue;
		}
		(*it)->GetTransform()->UpdateMatrix();
	}
	_nextPos -= _way * 90.0f * Engine42::Time::GetDeltaTime();
	//_rooms.sort(_sort);
}

void	RoomManager::FixedUpdate()
{

}

glm::vec3	RoomManager::rotate(glm::vec3& vec, float angle, glm::vec3 normal)
{
	glm::vec3 ret = glm::rotate(vec, glm::radians(angle), normal);

	if (ret.x < 0.1f)
		ret.x = 0.0f;
	if (ret.y < 0.1f)
		ret.y = 0.0f;
	if (ret.z < 0.1f)
		ret.z = 0.0f;

	if (ret.x > 0.9f)
		ret.x = 1.0f;
	if (ret.y > 0.9f)
		ret.y = 1.0f;
	if (ret.z > 0.9f)
		ret.z = 1.0f;
	return ret;
}

void	RoomManager::_AddCorner()
{
	for (auto it = corners.begin(); it != corners.end(); it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
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
			//_lastRoom = (*it)->GetTransform();
			break;
		}
	}
}
