//
//  Shader.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "Shader.h"

#include <iostream>

Shader &Shader::Use() {
    glUseProgram(this->mID);
    return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource) {
    int sVertex, sFragment;
    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "vertex");
   
    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "fragment");
    
    // Shader Program
    printf("Linking Program\n");
    this->mID = glCreateProgram();
    glAttachShader(this->mID, sVertex);
    glAttachShader(this->mID, sFragment);
    glLinkProgram(this->mID);
    checkCompileErrors(this->mID, "program");

    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
}

void Shader::SetInteger(const char *name, int value, bool useShader) {
    if (useShader)
        this->Use();
    glUniform1i(glGetUniformLocation(this->mID, name), value);
}

void Shader::SetVector3f(const char *name, const glm::vec3 &value, bool useShader) {
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->mID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char *name, const glm::vec4 &value, bool useShader) {
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->mID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char *name, const glm::mat4 &matrix, bool useShader) {
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->mID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(int object, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "program") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER: Compile-time error: Type: " << type << "\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER: Link-time error: Type: " << type << "\n" << infoLog << std::endl;
        }
    }
}
