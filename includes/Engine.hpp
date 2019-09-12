#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <iostream>
# include <list>

# include "IGameObject.hpp"
# include "SdlWindow.hpp"
# include "Time.hpp"
# include "Skybox.hpp"
# include "Renderer.hpp"
# include "Framebuffer.hpp"
# include "PostProcess.hpp"
# include "Text.hpp"
#include "Player.hpp"


namespace Engine42
{
	class Engine 
	{

		public: 
			/*	constructors / destrucors	*/
			virtual ~Engine(void); 

			/*	public variables	*/
			/*	public functions	*/
			static void            AddRenderer(std::list<std::shared_ptr<Renderer>> renderers);
			static void            AddRenderer(std::shared_ptr<Renderer> renderer);
			static void            AddRenderer(std::shared_ptr<Player> renderer);
			static void            AddFramebuffer(std::shared_ptr<Framebuffer>  fbo);
			static void            SetWindow(const SdlWindow *win);
			static void            AddGameObject(std::shared_ptr<Engine42::IGameObject> object);
			static void            AddGameObject(std::list<std::shared_ptr<Engine42::IGameObject>> objects);
			static void            AddUIElement(std::shared_ptr<Engine42::IGameObject> object);
			static void            ChangeFontUI(std::shared_ptr<Text> font);
			static void            SetSkybox(std::shared_ptr<Skybox> skybox);
			static void            AddPostProcessShader(std::shared_ptr<Shader> postProcessShader);
			static std::shared_ptr<Text> GetFontUI();


			static void            Loop(void);
			static const SDL_Event &GetEvent();
			static const Uint8     *GetKeyInput();
			static bool             Destroy(std::shared_ptr<Renderer> renderer);
			static void             ReloadShaders(void);
			void             ResizeWindow(int width, int height);

			static void	createFBO();
		private:
			unsigned int _fbo;
			unsigned int _colorBuffer;
			unsigned int _rbo;
			unsigned int quadVAO;
			unsigned int quadVBO;
			std::shared_ptr<PostProcess>	_shaderFbo;
			/*  private constructor*/
			Engine(void); 
			/*	private variables	*/
			static Engine                       _inst;
			std::list<std::shared_ptr<Renderer>>           _renderers;
			std::list<std::shared_ptr<Framebuffer>>			_framebuffers;
			std::list<std::shared_ptr<Engine42::IGameObject>>   _gameObjs;
			std::list<std::shared_ptr<Engine42::IGameObject>>   _UI;
			std::shared_ptr<Text>					_fontUI;

			SDL_Event                           _event;
			const Uint8                         *_keys;
			const SdlWindow                     *_win;
			std::shared_ptr<Skybox>             _skybox;       
			/*	private functions	*/
			void                                _RenderAll(void);
			void                                _UpdateAll(void);
			void                                _FixedUpdateAll(void);

	};
}

#endif
