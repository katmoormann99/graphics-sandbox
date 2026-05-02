//============================================================================
// Johns Hopkins University Engineering Programs for Professionals
// 605.667 Computer Graphics and 605.767 Applied Computer Graphics
//
// File:    scene_node.hpp
// Purpose: Base class for all scene graph nodes.
//
// Beginner explanation:
// SceneNode is the general parent class for all nodes in the scene graph.
//
// Other node types, such as TransformNode, PresentationNode, and GeometryNode,
// inherit from SceneNode so they can all be treated the same way.
//
// SceneNode mainly provides:
// - a name
// - a node type
// - a list of children
// - draw/update traversal behavior
//
// It does not usually draw a shape itself.
// Instead, it helps organize the tree of objects.
//============================================================================

#ifndef __SCENE_SCENE_NODE_HPP__
#define __SCENE_SCENE_NODE_HPP__

#include "scene/graphics.hpp"
#include "scene/scene_state.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace cg
{

/**
 * SceneNodeType is used to label what kind of node something is.
 *
 * This does not create the different node types by itself.
 * It simply gives each node a category.
 *
 * For example:
 *
 * - BASE
 *   A generic SceneNode used mainly for organizing the tree structure.
 *
 * - TRANSFORM
 *   A TransformNode that controls WHERE objects appear.
 *   It can move, rotate, or scale child objects.
 *
 * - PRESENTATION
 *   A PresentationNode that controls HOW objects look.
 *   It may set color, material properties, or shader settings.
 *
 * - GEOMETRY
 *   A GeometryNode that draws the actual object.
 *   This is where vertices/shapes are rendered.
 *
 * - CAMERA
 *   A CameraNode that controls HOW the scene is viewed.
 *   It may define the camera position, viewing direction,
 *   and projection type (perspective or orthographic).
 *
 * This can be useful for debugging, printing the scene graph,
 * or checking what kind of node you are working with.
 */
enum class SceneNodeType
{
    BASE,
    PRESENTATION,
    TRANSFORM,
    GEOMETRY,
    SHADER,
    CAMERA
};

/**
 * Allows a SceneNodeType to be printed using std::cout.
 *
 * For example:
 *
 * std::cout << SceneNodeType::TRANSFORM;
 *
 * This is mostly helpful for debugging or printing the scene graph.
 */
std::ostream &operator<<(std::ostream &out, const SceneNodeType &type);

/**
 * SceneNode is the base class for all nodes in the scene graph.
 *
 * A scene graph is a tree structure used to organize rendering.
 *
 * Example:
 *
 * Root SceneNode
 *    └── TransformNode
 *           └── PresentationNode
 *                  └── GeometryNode
 *
 * In that example:
 *
 * - TransformNode controls WHERE the object appears
 * - PresentationNode controls HOW the object looks
 * - GeometryNode draws the actual object
 *
 * SceneNode provides the shared structure that lets all of those
 * different node types connect together.
 */
class SceneNode
{
  public:
    /**
     * Constructor.
     *
     * This creates a basic scene node.
     *
     * A plain SceneNode is usually used as an organizer or root node.
     * It does not usually apply a transformation, set material properties,
     * or draw geometry.
     *
     * Derived classes, such as TransformNode, PresentationNode, and
     * GeometryNode, call this constructor first before setting up their own
     * specialized behavior.
     */
    SceneNode();

    /**
     * Destructor.
     *
     * This is marked virtual because SceneNode is a base class.
     *
     * That matters because we may store derived nodes like TransformNode
     * or GeometryNode using SceneNode pointers.
     *
     * Example:
     *
     * std::shared_ptr<SceneNode> node = std::make_shared<GeometryNode>();
     *
     * A virtual destructor helps make sure the correct derived class
     * destructor is called when the object is destroyed.
     */
    virtual ~SceneNode();

    /**
     * Draw this node and its children.
     *
     * The base SceneNode version usually does not draw anything itself.
     * Its main job is to visit each child and call that child's draw()
     * function.
     *
     * This is called scene graph traversal.
     *
     * Example:
     *
     * Root SceneNode
     *    └── TransformNode
     *           └── PresentationNode
     *                  └── GeometryNode
     *
     * Calling draw() on the root eventually causes draw() to be called on
     * each child below it.
     *
     * Derived classes can override this function:
     *
     * - TransformNode::draw() changes the transformation matrix,
     *   then calls SceneNode::draw() to draw its children.
     *
     * - PresentationNode::draw() sets appearance/material information,
     *   then calls SceneNode::draw() to draw its children.
     *
     * - GeometryNode::draw() actually draws the shape.
     *
     * @param scene_state
     *        Shared rendering information passed through the scene graph.
     *        This may include shader locations, matrices, colors, and other
     *        OpenGL state needed while drawing.
     */
    virtual void draw(SceneState &scene_state);

    /**
     * Update this node and its children.
     *
     * Updating is separate from drawing.
     *
     * Drawing answers:
     *   "How should this appear on screen right now?"
     *
     * Updating answers:
     *   "Does anything need to change before the next frame?"
     *
     * For example, an update function might:
     *
     * - animate a rotation
     * - change an object's position
     * - update a camera
     * - update child nodes
     *
     * The base SceneNode version usually just calls update() on all children.
     *
     * @param scene_state
     *        Shared scene/rendering information available during update.
     */
    virtual void update(SceneState &scene_state);

    /**
     * Remove/destroy all child nodes stored under this node.
     *
     * SceneNodes form a tree using children.
     *
     * This function clears that child list.
     *
     * Example:
     *
     * Root
     *    ├── TransformNode
     *    └── GeometryNode
     *
     * Calling destroy() on Root removes its children.
     *
     * Because the children are stored with std::shared_ptr, their memory is
     * automatically cleaned up when nothing else is using them.
     */
    void destroy();

    /**
     * Add another SceneNode as a child of this node.
     *
     * This is how the scene graph tree is built.
     *
     * Example:
     *
     * root->add_child(transform);
     * transform->add_child(presentation);
     * presentation->add_child(geometry);
     *
     * This creates:
     *
     * Root
     *    └── TransformNode
     *           └── PresentationNode
     *                  └── GeometryNode
     *
     * Since the parameter is a shared_ptr<SceneNode>, this function can accept
     * any class that inherits from SceneNode, including:
     *
     * - TransformNode
     * - PresentationNode
     * - GeometryNode
     *
     * @param node
     *        The child node to attach underneath this node.
     */
    void add_child(std::shared_ptr<SceneNode> node);

    /**
     * Return what kind of node this is.
     *
     * Each node stores a SceneNodeType value.
     *
     * For example:
     *
     * - a TransformNode usually stores SceneNodeType::TRANSFORM
     * - a PresentationNode usually stores SceneNodeType::PRESENTATION
     * - a GeometryNode usually stores SceneNodeType::GEOMETRY
     *
     * This is useful for debugging or printing the scene graph.
     *
     * @return The node's SceneNodeType.
     */
    SceneNodeType node_type() const;

    /**
     * Set a readable name for this node.
     *
     * The name is mostly for debugging and organization.
     *
     * For example, instead of printing:
     *
     * TransformNode
     *
     * you might name it:
     *
     * "Car Transform"
     *
     * or:
     *
     * "Tree Geometry"
     *
     * This makes the scene graph easier to understand when printed.
     *
     * @param nm
     *        The name to assign to this node.
     */
    void set_name(const char *nm);

    /**
     * Get the readable name of this node.
     *
     * This is useful when printing or debugging the scene graph.
     *
     * @return The node's name.
     */
    const std::string &get_name() const;

    /**
     * Print this node and its children as a tree.
     *
     * This helps you visualize the scene graph.
     *
     * For example, it might print something like:
     *
     * Root
     *   TransformNode
     *     PresentationNode
     *       GeometryNode
     *
     * The level parameter controls indentation.
     * A child node is printed farther to the right than its parent.
     *
     * @param out
     *        The output stream to print to. By default, this is std::cout.
     *
     * @param level
     *        How deep this node is in the tree. The root usually starts at 0.
     */
    void print_graph(std::ostream &out = std::cout, int32_t level = 0) const;

  protected:
    /**
     * The readable name of this node.
     *
     * This is mainly for debugging and printing.
     */
    std::string name_;

    /**
     * The category/type of this node.
     *
     * Derived classes usually set this in their constructor.
     *
     * For example:
     *
     * TransformNode sets this to SceneNodeType::TRANSFORM.
     * PresentationNode sets this to SceneNodeType::PRESENTATION.
     * GeometryNode sets this to SceneNodeType::GEOMETRY.
     */
    SceneNodeType node_type_;

    /**
     * The child nodes connected underneath this node.
     *
     * This is what makes the scene graph a tree.
     *
     * A SceneNode can have zero, one, or many children.
     *
     * TransformNode and PresentationNode commonly have children because they
     * affect the nodes below them.
     *
     * GeometryNode is usually a leaf node, meaning it often has no children,
     * because it represents the actual drawable shape.
     */
    std::vector<std::shared_ptr<SceneNode>> children_;
};

} // namespace cg

#endif