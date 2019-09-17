
#include "SdlWindow.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Engine.hpp"
#include "Terrain.hpp"
#include "Skybox.hpp"
#include "Player.hpp"
#include "FpsDisplay.hpp"
#include "GameManager.hpp"
std::shared_ptr<Skybox> CreateSkyBox()
{
	std::vector<std::string>	texturesPath{
	"ressources/textures/craterlake_ft.tga",
	"ressources/textures/craterlake_bk.tga",
	"ressources/textures/craterlake_up.tga",
	"ressources/textures/craterlake_dn.tga",
	"ressources/textures/craterlake_rt.tga",
	"ressources/textures/craterlake_lf.tga", 
	};
	std::vector<const char *>	shadersPath{"shaders/skybox.vs.glsl", "shaders/skybox.fs.glsl"};
	std::vector<GLenum> type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	std::shared_ptr<Skybox> skybox(new Skybox(texturesPath, shadersPath, type));
	return skybox;
}

bool InitModels(SdlWindow &win)
{
	std::vector<const char *>	shadersPath{ "shaders/Skeletical.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::shared_ptr<Camera> cam(new Camera(win.GetWidth(), win.GetHeight()));

	std::shared_ptr<FpsDisplay> fps(new FpsDisplay);
	Engine42::Engine::AddUIElement(fps);
	std::shared_ptr<Model>	test(new Model("ressources/obj/Running/42stud.fbx", "textures/Boy01_diffuse.jpg"));
	std::shared_ptr<Shader> 	myShader(new Shader(shadersPath, type));
	std::shared_ptr<Player> player(new Player(test, myShader, Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f))));
	Engine42::Engine::AddRenderer(player);
	Engine42::Engine::SetWindow(&win);
	Engine42::Engine::AddGameObject(cam);
	Engine42::Engine::AddGameObject(std::shared_ptr<GameManager>(new GameManager(player)));
	return true;
}
int ErrorQuit(std::string txt1, std::string txt2)
{
	if (!txt1.empty()) {std::cout << txt1 << std::endl;}
	if (!txt2.empty()) {std::cout << txt2 << std::endl;}
	SDL_Quit();
	return (EXIT_SUCCESS);
}

int				main(int ac, char **av)
{
	if (ac < -1 && av == nullptr)
		return 1;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return ErrorQuit("Erreur lors de l'initialisation de la SDL :", SDL_GetError() );
	}
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		return ErrorQuit("Failed to init freetype library", std::string());
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SdlWindow	win(800, 400, false, true, "42run");
	win.CreateGlContext(4, 1, true, 24);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, win.GetWidth(), win.GetHeight());
	try
	{
		std::shared_ptr<Text>	font(new Text("ressources/fonts/SEASRN__.ttf", ft));
		Engine42::Engine::ChangeFontUI(font);
	 	InitModels(win);
	}
	catch(const std::exception& e)
	{
		return ErrorQuit(e.what(), std::string());
	}
	Engine42::Engine::Loop();
	SDL_Quit();
}
