#include "Engine.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
//#include "PrintGlm.hpp"

Engine42::Engine          Engine42::Engine::_inst = Engine();
Engine42::Engine::Engine(void){
	_skybox = nullptr;
	_keyboardKeys = {SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_A};
	_InitKeyboard();
}

void	Engine42::Engine::_InitKeyboard()
{
	for (auto it = _keyboardKeys.begin(); it != _keyboardKeys.end(); it++)
		_keyboard[*it] = KEY_UP;
}

Engine42::Engine::~Engine(void){}

void            Engine42::Engine::SetWindow(const SdlWindow *win) {_inst._win = win;}
void            Engine42::Engine::AddRenderer(std::list<std::shared_ptr<ARenderer>> renderers)
{
	_inst._renderers.insert(_inst._renderers.end(), renderers.begin(), renderers.end());
}
void            Engine42::Engine::AddRenderer(std::shared_ptr<ARenderer> renderer) 
{
	if (renderer != nullptr)
		_inst._renderers.push_back(renderer);
}

void            Engine42::Engine::AddFramebuffer(std::shared_ptr<Framebuffer> fbo) 
{
	if (fbo != nullptr)
	{
		_inst._framebuffers.push_back(fbo);
		_inst._renderers.push_back(fbo);
	}
}

void            Engine42::Engine::AddGameObject(std::shared_ptr<GameObject> object)
{
	if (object != nullptr)
		_inst._gameObjs.push_back(object);
}
void Engine42::Engine::SetSkybox(std::shared_ptr<Skybox> skybox)
{
	_inst._skybox = skybox;
}

void            Engine42::Engine::AddGameObject(std::list<std::shared_ptr<GameObject>> objs)
{
	_inst._gameObjs.insert(_inst._gameObjs.begin(), objs.begin(), objs.end());
}

std::shared_ptr<Text>				Engine42::Engine::GetFontUI() { return _inst._fontUI; }

void            Engine42::Engine::AddUIElement(std::shared_ptr<GameObject> object)
{
	if (object != nullptr)
		_inst._UI.push_back(object);
}
void            Engine42::Engine::ChangeFontUI(std::shared_ptr<Text> font)
{
	_inst._fontUI = font;
}
void            Engine42::Engine::ResizeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
	SdlWindow::GetMain()->SetWidth(width);
	SdlWindow::GetMain()->SetHeight(height);
	_fontUI->UpdateProj();
}
const SDL_Event &Engine42::Engine::GetEvent(){ return _inst._event;}
const Uint8 *Engine42::Engine::GetKeyInput(){ return _inst._keys;}

eKeyState		Engine42::Engine::GetKeyState(Uint8 scancode) { return _inst._keyboard[scancode];}

void	Engine42::Engine::_UpdateKeyboard()
{
	for (auto it = _keyboardKeys.begin(); it != _keyboardKeys.end(); it++)
	{
		if (_keys[*it] && _keyboard[*it] == KEY_UP)
			_keyboard[*it] = KEY_PRESS;
		else if (_keys[*it] && _keyboard[*it] == KEY_PRESS)
			_keyboard[*it] = KEY_DOWN;
		else if (!_keys[*it] && _keyboard[*it] == KEY_DOWN)
			_keyboard[*it] = KEY_RELEASE;
		else if (!_keys[*it] && _keyboard[*it] == KEY_RELEASE)
			_keyboard[*it] = KEY_UP;
	}
}

void            Engine42::Engine::createFBO(void)
{
	glGenFramebuffers(1, &_inst._fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _inst._fbo);

	glGenTextures(1, &_inst._colorBuffer);
	glBindTexture(GL_TEXTURE_2D, _inst._colorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SdlWindow::GetMain()->GetWidth(), SdlWindow::GetMain()->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _inst._colorBuffer, 0);

	glGenRenderbuffers(1, &_inst._rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _inst._rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SdlWindow::GetMain()->GetWidth(), SdlWindow::GetMain()->GetHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _inst._rbo);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	float quadVertices[] = { 
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &_inst.quadVAO);
	glGenBuffers(1, &_inst.quadVBO);
	glBindVertexArray(_inst.quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _inst.quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	std::vector<const char *>	shadersPath{"shaders/fbo.vs.glsl", "shaders/PostProcess.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	_inst._shaderFbo.reset(new PostProcess(shadersPath, type));
	_inst.AddGameObject(_inst._shaderFbo);
}

void            Engine42::Engine::Loop(void)
{
	bool        quit = false;
	float       delta = ((float)SDL_GetTicks()) / 1000;
	float       lastTime = delta;
	const float fixedTimeUpdate = 0.02f;
	float       fixedDelta = 0.02f;

	//createFBO();
	while (!quit)
	{
		delta = (((float)SDL_GetTicks()) / 1000) - lastTime;
		Time::SetDeltaTime(delta);
		_inst._event.type = SDL_USEREVENT;
		while (SDL_PollEvent(&_inst._event) != 0)
		{
			if ((_inst._event.type == SDL_WINDOWEVENT 
						&& _inst._event.window.event == SDL_WINDOWEVENT_CLOSE)
					|| (_inst._event.type == SDL_KEYDOWN 
						&& _inst._event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
			if (_inst._event.type == SDL_WINDOWEVENT && _inst._event.window.event == SDL_WINDOWEVENT_RESIZED)
				_inst.ResizeWindow(_inst._event.window.data1, _inst._event.window.data2);
		}
		_inst._keys = SDL_GetKeyboardState(NULL);
		_inst._UpdateKeyboard();
		_inst._UpdateAll();
		lastTime += delta;
		fixedDelta += delta;
		if (fixedDelta >= fixedTimeUpdate)
		{
			Time::SetFixedDeltaTime(fixedDelta);
			_inst._FixedUpdateAll();
			fixedDelta = 0.0f;
		}
		_inst._RenderAll();
	}
}

bool      Engine42::Engine::Destroy(std::shared_ptr<ARenderer> renderer)
{
    if (renderer == nullptr)
        return false;
    _inst._renderers.remove(renderer);
    return true;
}
bool		_sort(const std::shared_ptr<ARenderer> first, const std::shared_ptr<ARenderer> sec)
{
	float d1 = glm::distance(first->GetTransform()->position, Camera::instance->GetPos());
	float d2 = glm::distance(sec->GetTransform()->position, Camera::instance->GetPos());
	return d2 < d1;
}
void                         Engine42::Engine::_RenderAll(void)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	_renderers.sort(_sort);
    if (_skybox != nullptr)
        _skybox->Draw();
    for (auto it = _renderers.begin(); it != _renderers.end(); it++)
         (*it)->Draw();
    for (auto it = _UI.begin(); it != _UI.end(); it++)
         (*it)->Update();
	_win->Swap();
}
/*void                         Engine42::Engine::_RenderAll(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);  
	_renderers.sort(_sort);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto it = _framebuffers.begin(); it != _framebuffers.end(); it++)
         (*it)->genTexture();
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    if (_skybox != nullptr)
        _skybox->Draw();
    for (auto it = _renderers.begin(); it != _renderers.end(); it++)
         (*it)->Draw();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_shaderFbo->use();
	_shaderFbo->setInt("screenTexture", 2);
	glBindVertexArray(quadVAO);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _colorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	_win->Swap();
}*/
void                          Engine42::Engine::_UpdateAll(void)
{
    std::list<std::shared_ptr<GameObject>>::iterator  it;

	for (it = _gameObjs.begin(); it != _gameObjs.end(); it++)
	{
		(*it)->Update();
	}
}
void                       Engine42::Engine::ReloadShaders(void)
{
    std::for_each(_inst._renderers.begin(), _inst._renderers.end(), [] (std::shared_ptr<ARenderer> x) -> void { 
        std::shared_ptr<Shader> shader = x->GetShader(); 
        if (shader)
            shader->Reload();
        });
}
void                       Engine42::Engine::_FixedUpdateAll(void) 
{
    std::list<std::shared_ptr<GameObject>>::iterator  it;

	for (it = _gameObjs.begin(); it != _gameObjs.end(); it++)
	{
		(*it)->FixedUpdate();
	} 
}
