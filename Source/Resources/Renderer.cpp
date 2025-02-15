//
//  Renderer.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "Renderer.h"

Renderer::Renderer() {
    glGenVertexArrays(1, &mQuadVAO);
    glGenVertexArrays(1, &mTriangleVAO);
    glGenBuffers(1, &mEBO);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &mQuadVAO);
    glDeleteVertexArrays(1, &mTriangleVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);
}

void Renderer::Initialize(Shader &shader) {
    this->shader = shader;
    this->configureQuad();
    this->configureTriangle();
}

void Renderer::Render(TextureLoader &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec4 color, glm::vec2 textureScaling, glm::mat4 viewMatrix, bool quad) {
    // Prepare transformations
    this->shader.Use();
    glm::mat4 model;
    // First translate
    model = glm::translate(viewMatrix, glm::vec3(position, 0.0f));
    // Move origin of rotation to center of quad
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    // Then rotate
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    // Move origin back
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    // Last scale
    model = glm::scale(model, glm::vec3(size, 1.0f));
    
    this->shader.SetMatrix4("model", model);
    
    // Render textured quad
    this->shader.SetVector4f("v_color", color);
    
    // Set texture scaling
    glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(textureScaling.x, textureScaling.y, 1.0f));
    this->shader.SetMatrix4("textureMatrix", scale);
    
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    
    if (quad)
        this->renderQuad();
    else
        this->renderTriangle();
}

void Renderer::configureQuad() {
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 0.0f, 0.0f, 0.0f, // bottom left
        1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        0.0f, 1.0f, 0.0f, 1.0f, // top left
        1.0f, 1.0f, 1.0f, 1.0f // top right
    };
    
    unsigned int indicesArray[] {
        0, 1, 2, // First Triangle
        2, 1, 3 // Second Triangle
    };
    
    glGenBuffers(1, &mVBO);
    glBindVertexArray(mQuadVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesArray), indicesArray, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::renderQuad() {
    glBindVertexArray(mQuadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::configureTriangle() {
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.5f, 1.0f,
    };
    
    glGenBuffers(1, &mVBO);
    glBindVertexArray(mTriangleVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::renderTriangle() {
    glBindVertexArray(mTriangleVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
