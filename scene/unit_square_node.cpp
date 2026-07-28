#include "scene/unit_square_node.hpp"

#include "geometry/types.hpp"

#include <vector>

namespace cg
{
    UnitSquare::UnitSquare(int32_t position_loc, int32_t normal_loc) : GeometryNode()
    {
        std::vector<VertexAndNormal> vertex_list;
        VertexAndNormal vtx;
        vtx.normal.x = 0.0f;
        vtx.normal.y = 0.0f;
        vtx.normal.z = 1.0f;
        vtx.vertex.x = -0.5f;
        vtx.vertex.y = 0.5f;
        vtx.vertex.z = 0.0f;
        vertex_list.push_back(vtx);
        vtx.vertex.x = -0.5f;
        vtx.vertex.y = -0.5f;
        vertex_list.push_back(vtx);
        vtx.vertex.x = 0.5f;
        vtx.vertex.y = 0.5f;
        vertex_list.push_back(vtx);
        vtx.vertex.x = 0.5f;
        vtx.vertex.y = -0.5f;
        vertex_list.push_back(vtx);
        // At this point - vertex_list holds four VertexAndNormal objects in normal CPU memory
        vertex_count_ = static_cast<GLsizei>(vertex_list.size());

        // Create a buffer object and load the data
        // THe VBO will contain records arranged approx like
        // Vertex 0: [position x y z] [normal x y z]
        // Vertex 1: [position x y z] [normal x y z]
        // Vertex 2: [position x y z] [normal x y z]
        // Vertex 3: [position x y z] [normal x y z]

        // Generate a buffer name: this gives me ONE identifier that I can use for a buffer object
        // &vbo_ is the address where OpenGL writes the generated identifier
        glGenBuffers(1, &vbo_);

        // Bind the VBO 
        // OpenGL uses a state-machine design, rather than passing vbo_ directly into every operation, 
        // you bind it to a target and then operate on the currently bound object 
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);

        // Allocate and upload the data 
        glBufferData(GL_ARRAY_BUFFER, vertex_count_ * sizeof(VertexAndNormal), (GLvoid *)&vertex_list[0].vertex.x, GL_STATIC_DRAW);

        // Generate a VAO name - this asks OpenGL for one vertex array object identifier 
        glGenVertexArrays(1, &vao_);
        // Bind the VAO - this makes vao_ the currently active VAO
        // Think of it as "now recording vertex setup into vao_"
        glBindVertexArray(vao_);

        // Configuring the position attribute
        // Bind the VBO again
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);

        // Describe WHERE positions are stored
        // This tells OpenGL how to retrieve a position for each vertex
        // position_loc: GLSL shader -> layout(location = 0) in vec3 position;
        // 3: x, y, z
        // GL_FLOAT: float x, float y, float z
        // Normalize? GL_FALSE
        // Stride: Number of bytes from one position to the next position 
        // Starting offset: The position begins at byte zero inside each vertex record
        glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAndNormal), (void *)0);

        // Enable the position attribute
        // During drawing - obtain a separate position from the VBO for every vertex
        glEnableVertexAttribArray(position_loc); 

        glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAndNormal), (void *)(sizeof(Point3)));
        glEnableVertexAttribArray(normal_loc); 

        // The VAO now contains two enabled attribute descriptions: 
        // Position:
        //     shader location = position_loc
        //     source VBO      = vbo_
        //     components      = 3 floats
        //     stride          = sizeof(VertexAndNormal)
        //     offset          = 0

        // Normal:
        //     shader location = normal_loc
        //     source VBO      = vbo_
        //     components      = 3 floats
        //     stride          = sizeof(VertexAndNormal)
        //     offset          = sizeof(Point3)

        // Stop configuring this VAO
        glBindVertexArray(0);
    }

    UnitSquare::~UnitSquare(){}

    void UnitSquare::draw(SceneState &scene_state)
    {
        // activate all of the vertex configuration stored earlier
        glBindVertexArray(vao_);

        // Draw the vertices 
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count_);

        // Unbind the VAO - deactivating the square's VAO after drawing
        glBindVertexArray(0);
    }
} // namespace cg
