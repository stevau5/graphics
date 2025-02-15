//
//  Renderer.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef Renderer_h
#define Renderer_h

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TextureLoader.h"
#include "Shader.h"


class Renderer {
public:
    // constructor
    Renderer();
    // destructor
    ~Renderer();
    // init shaders and shapes
    void Initialize(Shader &shader);
    // renders a defined quad textured
    void Render(TextureLoader &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec4 color = glm::vec4(1.0f), glm::vec2 textureScaling = glm::vec2(1.f, 1.f), glm::mat4 viewMatrix = glm::mat4(1.f), bool quad = true);
private:
    // render state
    Shader shader;
    // initializes and configures the quad's buffer and vertex attributes
    void configureQuad();
    void renderQuad();
    void configureTriangle();
    void renderTriangle();
    
    unsigned int mQuadVAO;
    unsigned int mTriangleVAO;
    unsigned int mVBO;
    unsigned int mEBO;
};

#endif /* Renderer_h */
