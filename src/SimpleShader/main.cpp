#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <iostream>

int main(){

    /*
    This SDL Init commands tries to start SDL's video subsystem (for creating windows/rendering).
    In SDL, it returns 0 on success and a negative value on failure.
    */
    if (!SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    /*
    Request a core profile OpenGL context (modern OpenGL, no deprecated features)
    Enable double buffering, so rendering happens off-screen and then swaps to the screen to avoid flickering
    Asks for a 24-bit depth buffer, which helps OpenGL correctly determine which objects appear in front of others
    */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window *window = SDL_CreateWindow(
        "graphics-sandbox",
        1024,
        1024,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!window){
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    if (!gl_context){
        std::cerr << "OpenGL context failed! " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /*
    Setting glewExperimental to true is basically saying "alos look for new OpenGL features"
    glewInit() does the setup work so functions like creating shaders or buffers actually work later.
    Without this, the program might no recognize the new OpenGL commands
    */
    glewExperimental = GL_TRUE;
    GLenum glew_result = glewInit();

    if (glew_result != GLEW_OK){
        std::cerr << "GLEW failed: " << glewGetErrorString(glew_result) << std::endl;
        return 1;
    }

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    /*
    This is the core render loop
    This is what keeps the program alive, and will process all the user input/events, 
    clears the screen, draws a new frame, and displays it
    SDL Event Objects: Keyboard input, mouse movement, window closing, controller input, etc
    This loop repeatedly: 
    1. Check user input/events
    2. Update game/app state
    3. Render graphics
    4. Display frame
    5. Repeat
    */
    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT){
                running = false;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
            {
                running = false;
            }
        }

        glViewport(0, 0, 1024, 1024);
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}