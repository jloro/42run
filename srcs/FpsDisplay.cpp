#include "FpsDisplay.hpp"
#include "glm.hpp"
#include <string>
#include "Engine.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "cmath"

FpsDisplay::FpsDisplay() : _nbFrame(0), _lastTime(0.0f), _fps(0.0f) {}

FpsDisplay::~FpsDisplay() {}

void	FpsDisplay::Update(void)
{
	if ((((float)SDL_GetTicks()) / 1000) - _lastTime >= 1.0f)
	{
		_fps = _nbFrame;
		_nbFrame = 0;
		_lastTime += 1.0f;
	}
	_nbFrame++;
	//Engine42::Engine::GetFontUI()->RenderText(std::string("FPS: ") + std::to_string(_fps), 10.0f, SdlWindow::GetMain()->GetHeight() - 24, 1.0f, glm::vec4(1.0f)); 
	Engine42::Engine::GetFontUI()->RenderText(std::string("Score: ") + std::to_string((int)(((float)SDL_GetTicks()) / 1000)), 10.0f, SdlWindow::GetMain()->GetHeight() - 24, 1.0f, glm::vec4(1.0f)); 
}

void	FpsDisplay::FixedUpdate()
{
}
