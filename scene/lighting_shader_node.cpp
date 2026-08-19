#include "scene/lighting_shader_node.hpp"

#include <iostream>

namespace cg
{


bool LightingShaderNode::get_locations()
{
    position_loc_ = glGetAttribLocation(shader_program_.get_program(), "vtx_position");
    if(position_loc_ < 0)
    {
        std::cout << "Error getting vtx_position location\n";
        return false;
    }
    vertex_normal_loc_ = glGetAttribLocation(shader_program_.get_program(), "vtx_normal");
    if(vertex_normal_loc_ < 0)
    {
        std::cout << "Error getting vtx_normal location\n";
        return false;
    }
    material_color_loc_ = glGetUniformLocation(shader_program_.get_program(), "material_color");
    if(material_color_loc_ < 0)
    {
        std::cout << "Error getting material_color location\n";
        return false;
    }
    pvm_matrix_loc_ = glGetUniformLocation(shader_program_.get_program(), "pvm_matrix");
    if(pvm_matrix_loc_ < 0)
    {
        std::cout << "Error getting pvm_matrix location\n";
        return false;
    }
    model_matrix_loc_ = glGetUniformLocation(shader_program_.get_program(), "model_matrix");
    if(model_matrix_loc_ < 0)
    {
        std::cout << "Error getting model_matrix location\n";
        return false;
    }

    normal_matrix_loc_ = glGetUniformLocation(shader_program_.get_program(), "normal_matrix");
    if(normal_matrix_loc_ < 0)
    {
        std::cout << "Error getting normal_matrix location\n";
        return false;
    }
    return true;
}

void LightingShaderNode::draw(SceneState &scene_state)
{
    printf("\n[LightingShaderNode::draw] ENTER\n");

    // Enable this program
    printf("  1. Activating lighting shader program\n");
    shader_program_.use();

    // Set scene state locations to ones needed for this program
    printf("  2. Copying shader locations into SceneState\n");

    scene_state.position_loc = position_loc_;
    printf("     position_loc         = %d\n", position_loc_);

    scene_state.normal_loc = vertex_normal_loc_;
    printf("     normal_loc           = %d\n", vertex_normal_loc_);

    scene_state.material_diffuse_loc = material_color_loc_;
    printf("     material_diffuse_loc = %d\n", material_color_loc_);

    scene_state.pvm_matrix_loc = pvm_matrix_loc_;
    printf("     pvm_matrix_loc       = %d\n", pvm_matrix_loc_);

    scene_state.model_matrix_loc = model_matrix_loc_;
    printf("     model_matrix_loc     = %d\n", model_matrix_loc_);

    scene_state.normal_matrix_loc = normal_matrix_loc_;
    printf("     normal_matrix_loc    = %d\n", normal_matrix_loc_);

    // Draw all children
    printf("  3. Calling SceneNode::draw() to traverse children\n");

    SceneNode::draw(scene_state);

    printf("  4. Returned from SceneNode::draw()\n");
    printf("[LightingShaderNode::draw] EXIT\n");
}

int32_t LightingShaderNode::get_position_loc() const { return position_loc_; }

int32_t LightingShaderNode::get_normal_loc() const { return vertex_normal_loc_; }

} // namespace cg


