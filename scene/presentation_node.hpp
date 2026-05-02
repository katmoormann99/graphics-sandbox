//============================================================================
// Johns Hopkins University Engineering Programs for Professionals
// 605.667 Computer Graphics and 605.767 Applied Computer Graphics
//
// File:    presentation_node.hpp
// Purpose: Scene graph node responsible for controlling appearance.
//
// Beginner explanation:
// PresentationNode controls HOW an object looks when it is drawn.
//
// It usually does NOT draw geometry itself.
// Instead, it changes rendering settings before allowing child nodes
// (often GeometryNodes) to draw.
//
// Common things this node may control:
// - color
// - material properties
// - lighting settings
// - shader uniforms
//
// Think of it as the "appearance/styling" node in the scene graph.
//
// Example scene graph:
//
// Root SceneNode
//    └── TransformNode
//           (move object)
//           ↓
//        PresentationNode
//           (make object red)
//           ↓
//        GeometryNode
//           (draw actual triangle/cube)
//
// In this example:
// - TransformNode decides WHERE the object appears
// - PresentationNode decides HOW it looks
// - GeometryNode actually draws it
//============================================================================

#ifndef __SCENE_PRESENTATION_NODE_HPP__
#define __SCENE_PRESENTATION_NODE_HPP__

#include "scene/scene_node.hpp"

namespace cg
{

/**
 * PresentationNode inherits from SceneNode.
 *
 * That means it gets all the basic scene graph behavior from SceneNode:
 *
 * - it can be added as a child
 * - it can have its own children
 * - it can participate in draw traversal
 * - it can participate in update traversal
 *
 * What makes PresentationNode different is that it specializes in
 * appearance-related behavior.
 */
class PresentationNode : public SceneNode
{
  public:

    /**
     * Constructor
     *
     * This creates a PresentationNode object.
     *
     * The constructor usually sets:
     *
     * node_type_ = SceneNodeType::PRESENTATION
     *
     * so the system knows this is an appearance node.
     *
     * Example:
     *
     * std::shared_ptr<PresentationNode> material =
     *      std::make_shared<PresentationNode>();
     *
     * This node can then be added to the scene graph.
     */
    PresentationNode();

    /**
     * Draw function
     *
     * This function is called during scene graph traversal.
     *
     * Unlike GeometryNode:
     * - it usually does NOT draw triangles
     * - it usually does NOT call OpenGL geometry draw commands
     *
     * Instead, it prepares visual settings before child nodes draw.
     *
     * Examples of what this function might do:
     *
     * - set object color
     * - configure material properties
     * - send lighting values to shaders
     * - update shader uniforms
     *
     * After setting those properties, it usually calls:
     *
     * SceneNode::draw(scene_state);
     *
     * This tells all child nodes to continue drawing.
     *
     * Example:
     *
     * PresentationNode
     *    set color = blue
     *         ↓
     *    GeometryNode
     *         draw cube
     *
     * Result:
     * The cube appears blue.
     *
     * @param scene_state
     *
     * Shared rendering information passed through the scene graph.
     *
     * This may contain:
     * - shader variable locations
     * - matrices
     * - OpenGL state
     * - color information
     */
    void draw(SceneState &scene_state) override;
};

} // namespace cg

#endif