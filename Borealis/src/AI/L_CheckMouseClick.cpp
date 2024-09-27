#include <BorealisPCH.hpp>
#include "AI/L_CheckMouseClick.hpp"
#include <Core/InputSystem.hpp>
#include <Core/KeyCodes.hpp>
#include <Core/LoggerSystem.hpp>
namespace Borealis
{
    void L_CheckMouseClick::on_update(float dt)
    {

        if (InputSystem::IsKeyPressed(Key::A))
        {
            // grab the current mouse pos
            //const auto& mousePos = InputHandler::get_mouse_position();

            //// we want to know where on the ground the mouse was clicked
            //const auto& plane = terrain->get_terrain_plane();

            //// find out where on the plane the click happened
            //const auto worldPos = renderer->screen_to_world(mousePos.x, mousePos.y, plane);

            // if the click point was actually on the plane
            //if (worldPos.second == true)
            
                // write the world position into the blackboard
                //auto& bb = agent->get_blackboard();
                //bb.set_value("Click Position", worldPos.first);
            BOREALIS_CORE_INFO("Key on Success");
            on_success();
    
        }
        else
        {
            BOREALIS_CORE_INFO("Key on Failure");
            on_failure();
        }

        //display_leaf_text();
    }
}