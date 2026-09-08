#ifndef __SCENE_CHECKERBOARD_NODE_HPP__
#define __SCENE_CHECKERBOARD_NODE_HPP__

#include "scene/color4.hpp"
#include "scene/presentation_node.hpp"

namespace cg
{
    class CheckerboardNode : public PresentationNode
    {
        public:

            CheckerboardNode(bool enabled);
            void draw(SceneState &scene_state) override;

        protected:
            bool enabled_;
    };
}
#endif