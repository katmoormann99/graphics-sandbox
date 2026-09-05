//============================================================================
//	Johns Hopkins University Engineering Programs for Professionals
//	605.667 Computer Graphics and 605.767 Applied Computer Graphics
//	Instructor:	Brian Russin
//
//	Original Author: David W. Nesbitt
//	Modified by Kat Moormann
//	File:    geometry_node.hpp
//	Purpose: Scene graph geometry node.
//
//============================================================================


/**
 * GeometryNode is where actual shapes are drawn.
 *
 * This node stores geometry data such as:
 *
 * - vertices
 * - triangles
 * - meshes
 * - buffers
 *
 * Unlike TransformNode and PresentationNode,
 * GeometryNode actually sends draw commands to OpenGL.
 *
 * It is usually a leaf node, meaning:
 *
 * it has no children beneath it.
 *
 * Example:
 *
 * GeometryNode
 *    draw cube
 *
 * This is where OpenGL might call:
 *
 * glDrawArrays(...)
 *
 * or
 *
 * glDrawElements(...)
 */

#ifndef __SCENE_GEOMETRY_NODE_HPP__
#define __SCENE_GEOMETRY_NODE_HPP__

#include "scene/scene_node.hpp"

namespace cg
{

/**
 * Geometry node base class. Stores and draws geometry.
 */
class GeometryNode : public SceneNode
{
  public:
    /**
     * Constructor
     */
    GeometryNode();

    /**
     * Destructor
     */
    virtual ~GeometryNode();

    /**
     * Draw this geometry node. Geometry nodes are leaf nodes and have no children.
     * @param  scene_state  Current scene state
     * 
     * By the time execution reaches this node: 
     * 
     * - TransformNode may have already positioned the object
     * - PresentationNode may have already set color/material
     * 
     * GeometryNode uses all of that information
     * and finally renders the object 
     * 
     * Example flow: 
     * 
     * TransformNode
     *      move object 
     *          ↓
     * PresentationNode
     *      make object red
     *          ↓
     * GeometryNode
     *      draw code
     */
    virtual void draw(SceneState &scene_state) override;
};

} // namespace cg

#endif
