#include "config.h"
#include "Rendering/Shader.h"

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cout << "GLFW couldn't start" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(720, 520, "Crumb Engine", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }

    Shader shader;
    if (!shader.LoadFromFiles("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl")) {
        std::cout << "Failed to load shaders!" << std::endl;
        glfwTerminate();
        return -1;
    }

    float vertices[] = {
        -0.5f, -0.5f,    0.0f, 0.0f,
         0.5f, -0.5f,    1.0f, 0.0f,
         0.5f,  0.5f,    1.0f, 1.0f,
        -0.5f,  0.5f,    0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    unsigned char white_pixel[] = {255, 255, 255, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white_pixel);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    float projection[16] = {
        2.0f/720.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f/520.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 1.0f
    };

    float model[16] = {
        100.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 100.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    glClearColor(0.76f, 0.60f, 0.42f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        
        glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "projection"), 1, GL_FALSE, projection);
        glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "model"), 1, GL_FALSE, model);
        
        shader.SetVec4("spriteColor", 1.0f, 0.5f, 0.2f, 1.0f);
        
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);

    glfwTerminate();
    return 0;
}