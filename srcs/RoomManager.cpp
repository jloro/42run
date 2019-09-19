#include "RoomManager.hpp"
#include "ARenderer.hpp"
#include "Engine.hpp"
RoomManager::RoomManager()
{
	_floor.reset(new Terrain(6, 20, "ressources/textures/grass.png", 1, 1));
	_wall.reset(new Terrain(3, 20, "ressources/textures/window_wall.png", 5, 5));

	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	_shader.reset(new Shader(shadersPath, type));
	_MakeRoom(glm::vec3(0.0f, 0.0f, 50.0f));
}

RoomManager::~RoomManager() {}

void	RoomManager::_MakeRoom(glm::vec3 pos)
{
	std::shared_ptr<Room> room(new Room(Transform(glm::vec3(pos))));
	std::shared_ptr<GameObject> terrainFloor(new GameObject(Transform(glm::vec3(0, 0.0f, -1.0f))));
	std::shared_ptr<ARenderer> terrainFloorARenderer(new MeshRenderer(_floor, _shader));
	terrainFloor->AddComponent(terrainFloorARenderer);
	Engine42::Engine::AddRenderer(terrainFloor->GetComponent<ARenderer>());
	Engine42::Engine::AddGameObject(terrainFloor);
	room->AddWall(terrainFloor);

	std::shared_ptr<GameObject> terrainWall(new GameObject(Transform(glm::vec3(30, 15.0f, -1.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(1.0f, 1.0f, 1.0f))));
	std::shared_ptr<ARenderer> terrainWallARenderer(new MeshRenderer(_wall, _shader));
	terrainWall->AddComponent(terrainWallARenderer);
	Engine42::Engine::AddRenderer(terrainWall->GetComponent<ARenderer>());
	Engine42::Engine::AddGameObject(terrainWall);
	room->AddWall(terrainWall);

	std::shared_ptr<GameObject> terrainWall2(new GameObject(Transform(glm::vec3(-30, 15.0f, -1.0f), glm::vec3(0.0f, 0.0f, -90.0f), glm::vec3(1.0f, 1.0f, 1.0f))));
	std::shared_ptr<ARenderer> terrainWallARenderer2(new MeshRenderer(_wall, _shader));
	terrainWall2->AddComponent(terrainWallARenderer2);
	Engine42::Engine::AddRenderer(terrainWall2->GetComponent<ARenderer>());
	Engine42::Engine::AddGameObject(terrainWall2);
	room->AddWall(terrainWall2);

	_rooms.push_back(room);
}

void	RoomManager::Update()
{
	for (auto it = _rooms.begin(); it != _rooms.end(); it++)
	{
		if ((*it)->GetTransform()->position.z < -50)
			(*it)->GetTransform()->position.z = 50;
		(*it)->GetTransform()->position.z -= 20 * Engine42::Time::GetDeltaTime();
		(*it)->GetTransform()->UpdateMatrix();
	}
}

void	RoomManager::FixedUpdate()
{

}
