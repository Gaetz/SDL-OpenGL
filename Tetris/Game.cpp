#include "Game.h"

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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window) {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Window initialised");
		}
		else isRunning = false;

		context = SDL_GL_CreateContext(window);
		if (context) {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Context initialised");
		}
		else isRunning = false;

#if defined(_WIN32) || defined(_WIN64)
		GLenum initGLEW(glewInit());
		if (initGLEW == GLEW_OK)
		{
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "GLEW initialised");
		}
		else isRunning = false;
#endif

		isRunning = true;
	}
	else {
		isRunning = false;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL initialisation failed");
	}
}


void Game::load()
{
	shader = Shader("assets/shaders/basique2D.vert", "assets/shaders/basique2D.frag");
	shader.load();
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}


void Game::update()
{
}


void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader.getProgramID());

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);

	glUseProgram(0);
	SDL_GL_SwapWindow(window);
}


void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Bye :)");
}
