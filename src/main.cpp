#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <GL/glew.h>

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "WindowManager.h"
#include "Settings.h"
#include <iostream>

int main()
{
	WindowManager windowManager;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		return -1;
	}

	// Create SDL window
	SDL_Window* window = SDL_CreateWindow("Warehouse Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowManager.camera.screenWidth, windowManager.camera.screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window)
	{
		SDL_Quit();
		return -1;
	}

	// Create SDL GL context
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	if (!gl_context)
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	// Initialize OpenGL loader
	if (glewInit())
	{
		SDL_GL_DeleteContext(gl_context);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	// Setup ImGui
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGuiIO& io = ImGui::GetIO();

	// Main loop
	while (Settings::appRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				Settings::appRunning = false;
		}

		// Start the ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		//the application code
		windowManager.Draw();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		SDL_GetWindowSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}