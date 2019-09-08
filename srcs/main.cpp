
#include "SdlWindow.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "assimp/Importer.hpp"      // C++ importer interface
#include "assimp/scene.h"           // Output data structure
#include "assimp/postprocess.h"     // Post processing flags
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Engine.hpp"
#include "Terrain.hpp"
#include "Skybox.hpp"
#include "PrintGlm.hpp"
#include "Framebuffer.hpp"


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
	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::shared_ptr<Camera> cam(new Camera(win.GetWidth(), win.GetHeight()));

	shadersPath[0] = "shaders/Vertex.vs.glsl";
	shadersPath[1] = "shaders/Assimp.fs.glsl";
	std::shared_ptr<Shader> 	myShader(new Shader(shadersPath, type));
	Transform trans(glm::vec3(10.0f, 0.1f, -20.0f),//position
						glm::vec3(1.4f, 1.9f, 0.0f));//scale
	Engine42::Engine::SetWindow(&win);
	Engine42::Engine::AddGameObject(cam);
	std::shared_ptr<Model> terrainModel(new Terrain(10, 10, "ressources/textures/grass.png", 1, 1));
	std::shared_ptr<ARenderer> terrainARenderer(new MeshARenderer((terrainModel), myShader, Transform(glm::vec3(-50.0f, -7.5f, -50.0f))));
	Engine42::Engine::AddARenderer(terrainARenderer);
	std::shared_ptr<Skybox> sky = CreateSkyBox();
	Engine42::Engine::SetSkybox(sky);
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
	SdlWindow	win(800, 400, false, true, "Ft_Vox");
	win.CreateGlContext(4, 1, true, 24);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, win.GetWidth(), win.GetHeight());
	try
	{
		std::shared_ptr<Text>	font(new Text("ressources/fonts/Arial.ttf", ft));
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