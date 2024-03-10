#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <chrono>
#include <glm/glm.hpp>

void DrawSomething()
{
    // Clear the screen (with a nice blue color)
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // --- Your drawing code starts here --- 

    // Example: Draw a white triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    // --- End of drawing code ---
}

void CleanUp(SDL_GLContext glContext, SDL_Window* window)
{
    // Destroy the OpenGL context and window
    if (glContext)
    {
        SDL_GL_DeleteContext(glContext);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }

    // Quit SDL
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char** argv)
{
    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow("GLAD Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create an OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext)
    {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Enable VSync (Swap Interval = 1)
    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        SDL_Log("Failed to set VSync: %s", SDL_GetError());
    }

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Check if GLAD initialized successfully
    std::cout << "GLAD initialized successfully!" << std::endl;
    std::cout << "OpenGL version: " << (char*)glGetString(GL_VERSION) << std::endl;

    // Main loop
    bool quit = false;
    auto lastTime = std::chrono::steady_clock::now();
    auto curTime = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> durationMicro;
    double deltaTime;
    SDL_Event event;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                quit = true;
        }
        auto curTime = std::chrono::steady_clock::now();
        durationMicro = curTime - lastTime;
        deltaTime = durationMicro.count() / 1000;
        lastTime = curTime;
        // Render using OpenGL here
        //std::cout << 1 / deltaTime << "\n";
        DrawSomething();
        SDL_GL_SwapWindow(window);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    CleanUp(glContext, window);

    return 0;
}
