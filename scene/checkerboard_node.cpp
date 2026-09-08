#include "scene/checkerboard_node.hpp"

namespace cg{
    CheckerboardNode::CheckerboardNode(bool enabled) : PresentationNode(), enabled_(enabled){};

    void CheckerboardNode::draw(SceneState &scene_state)
    {   
        // Where in the shader? 
        // What value?
        glUniform1i(scene_state.use_checkerboard_loc, enabled_ ? 1 : 0);
        SceneNode::draw(scene_state);

        // MAKE SURE WE TURN THIS BACK OFF
        // Restore normal rendering for anything drawn afterwards!
        glUniform1i(scene_state.use_checkerboard_loc, 0);

    }
}