#include "FpsDisplay.hpp"
#include "glm.hpp"
#include <string>
#include "Engine.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "cmath"
#include "GameManager.hpp"

FpsDisplay::FpsDisplay() {}

FpsDisplay::~FpsDisplay() {}

void	FpsDisplay::Update(void)
{
	Engine42::Engine::GetFontUI()->RenderText(std::string("Score: ") + std::to_string(GameManager::instance->GetScore()), 10.0f, SdlWindow::GetMain()->GetHeight() - 24, 1.0f, glm::vec4(1.0f)); 
}

void	FpsDisplay::FixedUpdate()
{
}
