
#include <vector>
#include <functional>

#include <SDL2/SDL.h>
#include <ECS/System/kinematics.h>
#include <ECS/System/rendering.h>
#include "Sprite.h"
#include "ECS/Event/events.h"

using namespace std;

void SDLWindowSize(int* w, int* h);


void RegisterKeyboardEvent(Uint32 event, Sint32 key, function<void(const Uint32&, const Sint32&)> slot);
void RegisterKeyboardEvents(Uint32 event, vector<Sint32>& keys, std::function<void(const Uint32&, const Sint32&)> slot);



namespace GAME{

    static unsigned int shipId;
    static bool bGameIsOn;

    void OnEscPressed(const Uint32&, const Sint32&);
    void OnArrowKeyPressed(const Uint32&, const Sint32&);
    void OnFirePressed(const Uint32&, const Sint32&);


    void GameInitialization()
    {

        //My Keyboard slots
        auto arrowKeysGroup = std::vector<Sint32>{
                SDLK_RIGHT,
                SDLK_LEFT,
                SDLK_UP,
                SDLK_DOWN
        };
        RegisterKeyboardEvents(SDL_KEYDOWN, arrowKeysGroup, OnArrowKeyPressed);
        RegisterKeyboardEvent(SDL_KEYDOWN, SDLK_ESCAPE, OnEscPressed);
        RegisterKeyboardEvent(SDL_KEYDOWN, SDLK_SPACE, OnFirePressed);


        /* Create Sprite */
        auto shipTexturePath = std::string(RES_DIR)+"hero.png";
        shipId = GTech::Sprite::CreateSprite(shipTexturePath);

        int width;
        int height;
        SDLWindowSize(&width, &height);
        GTech::Sprite::SetPosition(shipId, glm::vec3(width >> 1, height >> 1, 0));

        //Init Systems
        ECS::RenderingSystem::InitRenderingSystem();
        ECS::KinematicsSystem::InitKinematicsSystem();

        //Subscribe Entity into Systems
        ECS::RenderingSystem::SubscribeEntity(shipId);

    }

    void MainLoop()
    {
        bGameIsOn = true;
        while (bGameIsOn)
        {
            ECS::UpdateEvents();
            ECS::RenderingSystem::DrawSprites();
            ECS::RenderingSystem::UpdateRenderingSystem();
            ECS::KinematicsSystem::UpdateKinematicsSystem();
        }
    }

    void OnFirePressed(const uint32_t& kbEvent, const int32_t& kbKey){

        auto resPath = std::string(RES_DIR)+"orangebolt.png";
        auto boltId = GTech::Sprite::CreateSprite(resPath);

        ECS::KinematicsSystem::SubscribeEntity(boltId);
        ECS::RenderingSystem::SubscribeEntity(boltId);

        auto& componentManager  = ECS::ComponentManager::GetInstance();
        auto& entityManager     = ECS::EntityManager::GetInstance();
        auto [posId, speedId, accelId] = componentManager.GetComponentRaw<ECS::EntityInformationComponent_>(entityManager.GetComponentsIds(shipId)[0])->GetKinematicTupleIds();

        GTech::Sprite::SetPosition(boltId, componentManager.GetComponentRaw<ECS::PositionComponent_>(posId)->position);

    }
    void OnEscPressed(const Uint32& kbEvent, const Sint32& kbKey){

        std::cout << "GAME::OnEscPressed "  << __FUNCTION__ << std::endl;
        bGameIsOn = false;
    }

    void OnArrowKeyPressed(const Uint32& kbEvent, const Sint32& kbKey){


        if (kbKey ==  SDLK_LEFT){
            std::cout << __FUNCTION__ << ": ";
            std::cout << " Left";
            std::cout << "\n";
        } else if (kbKey == SDLK_RIGHT) {
            std::cout << __FUNCTION__ << ": ";
            std::cout << " Right";
            std::cout << "\n";
        } else if (kbKey == SDLK_DOWN) {
            std::cout << __FUNCTION__ << ": ";
            std::cout << " Down";
            std::cout << "\n";
        } else if (kbKey == SDLK_UP) {
            std::cout << __FUNCTION__ << ": ";
            std::cout << " Up";
            std::cout << "\n";
        }

    }

};
