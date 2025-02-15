//
//  GUIGameMenu.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUIMainMenu.h"

#include "GUIButton.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "EventManager.h"
#include "TextRenderer.h"
#include "AudioEngine.h"
#include "Game.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


GUIMainMenu::GUIMainMenu() { }

bool GUIMainMenu::Initialize() {
    // set scale
    SetScale(glm::vec2(EventManager::GetScreenWidth(), EventManager::GetScreenHeight()));
    
    // start game
    std::shared_ptr<GUIButton> startGame(new GUIButton); // selection 0
    startGame->SetName("startGame");
    startGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2 - 100.0f));
    startGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    startGame->SetForeColor(glm::vec3(1.0f));
    startGame->SetHoverColor(glm::vec4(0.0f));
    startGame->SetText("Start Game");
    // continue (?) will need to cache if we do
    std::shared_ptr<GUIButton> continueGame(new GUIButton); // selection 1
    continueGame->SetName("continueGame");
    continueGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2));
    continueGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    continueGame->SetForeColor(glm::vec3(1.0f));
    continueGame->SetHoverColor(glm::vec4(0.0f));
    continueGame->SetText("Continue");
    // start game
    std::shared_ptr<GUIButton> quitGame(new GUIButton); // selection 2
    quitGame->SetName("quitGame");
    quitGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2 + 100.0f));
    quitGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    quitGame->SetForeColor(glm::vec3(1.0f));
    quitGame->SetHoverColor(glm::vec4(0.0f));
    quitGame->SetText("Quit Game");
    
    AddElement(startGame);
    AddElement(continueGame);
    AddElement(quitGame);
    
    return true;
}

void GUIMainMenu::Update(float dt) { }

void GUIMainMenu::RenderBackground(Renderer *renderer, TextRenderer *text) {
    // render background
    renderer->Render(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(EventManager::GetScreenWidth(), EventManager::GetScreenHeight()), 0.0f);
    // render title
    text->RenderText("GOLDEN SPHERE", 320.0f, EventManager::GetScreenHeight() / 2 - 300.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
}

void GUIMainMenu::Activate() {
    Game::GetInstance()->GetAudio()->StopAll();
#if defined(PLATFORM_OSX)	
	Game::GetInstance()->GetAudio()->Play("Sounds/caketown.wav", true);
#else
	Game::GetInstance()->GetAudio()->Play("../Assets/Sounds/caketown.wav", true);
#endif

}

void GUIMainMenu::Deactivate() {
	if (!(Game::GetInstance()->GetGameState() == GameState::GAME_LEVEL))
	{
#if defined(PLATFORM_OSX)	
		Game::GetInstance()->GetAudio()->Stop("Sounds/caketown.wav");
#else
		Game::GetInstance()->GetAudio()->Stop("../Assets/Sounds/caketown.wav");
#endif
	}
}

void GUIMainMenu::ButtonPressed(std::shared_ptr<GUIButton> button) {
    std::string buttonName = button->GetName();
    if (buttonName == "startGame") {
        Game::GetInstance()->SwitchStates(GAME_LEVEL);
    } else if (buttonName == "continueGame") {
        fprintf(stderr, "Continue Button Not Yet Set!\n");
    } else if (buttonName == "quitGame") {
        Game::GetInstance()->SwitchStates(GAME_NULL);
    } else {
        // do nothing
    }
}
