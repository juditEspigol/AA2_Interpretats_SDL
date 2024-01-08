//Using SDL and standard IO
#include <iostream>

// Managers
#include "RenderManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

//Scenes
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Gameplay.h"


int main(int argc, char* args[])
{
    srand(NULL(TIME));

    RENDERER.Init(); 

    // CREATE SCENES
    SCENE_M.AddScene(GAMEPLAY, new Gameplay());
    SCENE_M.AddScene(MAIN, new MainMenu());
    SCENE_M.AddScene(SPLASH, new SplashScreen());

    SCENE_M.SetCurrentScene(SPLASH);
    SCENE_M.GetCurrentScene()->OnEnter();

    while (!IM.GetQuitEvent())
    {
        TIME.Update();

        if (TIME.ShouldUpdateGame())
        {
            IM.Listen(); 

            // UPDATE
            SCENE_M.GetCurrentScene()->Update(TIME.GetDeltaTime());

            // DRAW
            SDL_RenderClear(RENDERER.GetRenderer());
            SCENE_M.GetCurrentScene()->Render();
            SDL_RenderPresent(RENDERER.GetRenderer());

            // TIME CONTROL
            TIME.ResetDeltaTime(); 

            // CHANGE SCENE
            if (SCENE_M.GetCurrentScene()->GetIsFinished())
            {
                std::string nextScene = SCENE_M.GetCurrentScene()->OnExit(); 
                SCENE_M.SetCurrentScene(nextScene); 
                SCENE_M.GetCurrentScene()->OnEnter(); 
            }
        }
    }
    return 0;
}