#include "game.h"
#include "resource_manager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "scene.h"
#include "scene_game.h"

Game::Game()
{
}


Game::~Game()
{
}


void Game::init(const char * title, int xPos, int yPos, int width, int height, bool isFullscreen)
{
	int flags = SDL_WINDOW_OPENGL;
	if (isFullscreen) {
		flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Subsystems initialised");

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		// Window
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window) {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Window initialised");
		}
		else isRunning = false;

		windowWidth = width;
		windowHeight = height;

		// OpenGL context
		context = SDL_GL_CreateContext(window);
		if (context) {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Context initialised");
		}
		else isRunning = false;

		// OpenGL setup
		GLenum initGLEW(glewInit());
		if (initGLEW == GLEW_OK)
		{
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "GLEW initialised");
		}
		else isRunning = false;
		glViewport(0, 0, width, height);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		isRunning = true;
	}
	else {
		isRunning = false;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL initialisation failed");
	}
}


void Game::load()
{
	// Load shaders
	ResourceManager::loadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", nullptr, "sprite");
	ResourceManager::loadShader("assets/shaders/rect.vert", "assets/shaders/rect.frag", nullptr, "rect");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowWidth), static_cast<GLfloat>(windowHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::getShader("sprite").use();
	ResourceManager::getShader("sprite").setInteger("image", 0);
	ResourceManager::getShader("sprite").setMatrix4("projection", projection);
	ResourceManager::getShader("rect").use();
	ResourceManager::getShader("rect").setMatrix4("projection", projection);
	// Set render-specific controls
	sRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));;
	gRenderer = new GeometryRenderer(ResourceManager::getShader("rect"));;

	// Game scene
	changeScene(SceneGame::Instance());
}

void Game::handleEvents(Uint32 dt)
{
	scenes.back()->handleEvent(dt);
}

void Game::update(Uint32 dt)
{
	scenes.back()->update(dt);
}


void Game::render()
{
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	scenes.back()->draw(sRenderer, gRenderer);

	SDL_GL_SwapWindow(window);
}


void Game::clean()
{
	ResourceManager::clear();
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Bye :)");
}

void Game::changeScene(Scene * scene)
{
	// cleanup the current state
	if (!scenes.empty()) {
		scenes.back()->clean();
		scenes.pop_back();
	}

	// store and load the new state
	scene->setGame(this);
	scenes.push_back(scene);
	scenes.back()->load();
}

void Game::pushScene(Scene * scene)
{
	// pause current state
	if (!scenes.empty()) {
		scenes.back()->pause();
	}

	// store and init the new state
	scenes.push_back(scene);
	scenes.back()->load();
}

void Game::popScene()
{
	// cleanup the current state
	if (!scenes.empty()) {
		scenes.back()->clean();
		scenes.pop_back();
	}

	// resume previous state
	if (!scenes.empty()) {
		scenes.back()->resume();
	}
}
