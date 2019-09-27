#include "GameManager.hpp"
#include "Engine.hpp"
#include <cmath>
#include "ACollider.hpp"

const unsigned int	GameManager::speedWorld = 80.0f;
std::shared_ptr<GameManager>	GameManager::instance = nullptr;

GameManager::GameManager(std::shared_ptr<Player> player) : player(player), _score(0)
{
	if (instance == nullptr)
		instance = std::shared_ptr<GameManager>(this);
	_score = 0;
	_timeScore = 0.0f;
	_rooms.reset(new RoomManager);
	Engine42::Engine::AddGameObject(_rooms);
	if ((_music = Mix_LoadMUS("ressources/sounds/music01.wav")) == NULL)
	{
		std::cout << "error : \n" <<  Mix_GetError() << std::endl;
	}
	if (_music != NULL)
	{
		Mix_VolumeMusic(10);
		/*int channel =*/Mix_PlayMusic(_music, -1);
		//Mix_Volume(channel, 1);
	}
	if ((_coinSound = Mix_LoadWAV("ressources/sounds/coin.wav")) == NULL)
	{
		std::cout << "error : \n" <<  Mix_GetError() << std::endl;
	}
	else
	{
		Mix_VolumeChunk(_coinSound, 70);
	}
	_tag = eTags::GameManager;
}
int						GameManager::GetScore(void) const {return _score;};

GameManager::~GameManager() 
{
	Mix_FreeMusic(_music);
	_music = NULL;
}

void	GameManager::Update()
{
	for (auto it = _rooms->obstacles->obstacles.begin(); it != _rooms->obstacles->obstacles.end(); it++)
	{
		if ((*it)->GetComponent<MeshRenderer>()->IsRender() && player->GetComponent<ACollider>()->IsCollindingWith(*(*it)->GetComponent<ACollider>()))
		{
			(*it)->GetComponent<MeshRenderer>()->SetRender(false);
			(*it)->GetComponent<MeshRenderer>()->Destroy();
			_rooms->obstacles->obstacles.erase(it);
			if ((*it)->GetTag() == eTags::Coin)
			{
				_score += 10;
				Mix_PlayChannel(-1, _coinSound, 0);
			}
			else
			{
				Die();
				break;
			}
		}
	}
	_timeScore +=Engine42::Time::GetDeltaTime();
	if (_timeScore > 0.5f && !player->GetDead()) 
	{ 
		++_score;
		_timeScore -= 0.5f;
	}
	//Engine42::Engine::GetFontUI()->RenderText(std::string("Score: ") + std::to_string(_score), 10.0f, SdlWindow::GetMain()->GetHeight() - 24, 1.0f, glm::vec4(1.0f));
}

void	GameManager::Die()
{
	player->_character->ChangeAnimation(1);
	player->SetDead(true);
	_rooms->Stop();
}
void	GameManager::FixedUpdate()
{
	
}
void GameManager::IncreaseScore(int amount)
{
	_score += amount;
}

void	GameManager::Reset()
{
	Engine42::Engine::Clear();
	player->SetDead(false);
	player->_character->ChangeAnimation(0);
	_rooms->Reset();
	Engine42::Engine::AddGameObject(_rooms);
	player->GetTransform()->position = glm::vec3(0.0f);
	Engine42::Engine::AddGameObject(player);
	Engine42::Engine::AddRenderer(player->GetComponent<MeshRenderer>());
	if (_music != NULL)
	{
		Mix_PlayMusic(_music, -1);
	}
	_score = 0;
	_timeScore = 0.0f;
}
