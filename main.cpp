#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<fstream>
#include<string>

// puppycat cube
GLfloat vxCube[] = {
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

        // plane
        -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
};

GLfloat vxQuad[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f,  1.0f,  1.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 1.0f
};

GLuint load_texture(const GLchar *path);
void create_shader_program(
        const char *pathVertex, const char *pathFragment,
        GLuint &vertexShader, GLuint &fragmentShader, GLuint& shaderProgram);
void specify_cube_vertex_attributes(GLuint shader_program);
void specify_quad_vertex_attributes(GLuint shader_program);

std::string read_shader(const char *filename);

int main() {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "brix", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        return -3;
    }

    // Create a vertex array object for each framebuffer
    GLuint vaoCube, vaoQuad;
    glGenVertexArrays(1, &vaoCube);
    glGenVertexArrays(1, &vaoQuad);

    // Create a vertex buffer object per framebuffer and copy the vertex data to it
    GLuint vboCube, vboQuad;
    glGenBuffers(1, &vboCube);
    glGenBuffers(1, &vboQuad);
    glBindBuffer(GL_ARRAY_BUFFER, vboCube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vxCube), vxCube, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vxQuad), vxQuad, GL_STATIC_DRAW);

//    GLuint elements[] = {
//        0, 1, 2,
//        2, 3, 0
//    };
//    GLuint ebo;
//    glGenBuffers(1, &ebo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Create and compile the vertex and fragment shaders for the cube and quad
    GLuint cubeVertexShader, cubeFragmentShader, cubeShaderProgram;
    create_shader_program(
            "shaders/cubeVertex.glsl", "shaders/cubeFragment.glsl",
            cubeVertexShader, cubeFragmentShader, cubeShaderProgram);

    GLuint quadVertexShader, quadFragmentShader, quadShaderProgram;
    create_shader_program(
            "shaders/quadVertex.glsl", "shaders/quadFragment.glsl",
            quadVertexShader, quadFragmentShader, quadShaderProgram);

    // Specify the layout of the vertex data
    glBindVertexArray(vaoCube);
    glBindBuffer(GL_ARRAY_BUFFER, vboCube);
    specify_cube_vertex_attributes(cubeShaderProgram);

    glBindVertexArray(vaoQuad);
    glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
    specify_quad_vertex_attributes(quadShaderProgram);

    // Load textures
    GLuint texCat = load_texture("resources/cat.png");
    GLuint texPup = load_texture("resources/pup.png");

    glUseProgram(cubeShaderProgram);
    glUniform1i(glGetUniformLocation(cubeShaderProgram, "texKitten"), 0);
    glUniform1i(glGetUniformLocation(cubeShaderProgram, "texPuppy"), 1);

    GLint uniModel = glGetUniformLocation(cubeShaderProgram, "model");

    glUseProgram(quadShaderProgram);
    glUniform1i(glGetUniformLocation(quadShaderProgram, "texFramebuffer"), 0);

    // Create a framebuffer for rendering on the side
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Data texture to hold color buffer
    GLuint texColorBuffer;
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Attach image to framebuffer
    glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    // Create renderbuffer object
    GLuint rboDepthStencil;
    glGenRenderbuffers(1, &rboDepthStencil);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil);

    // View transformation
    // glm::lookAt : The first parameter specifies the position of the camera,
    //  the second the point to be centered on-screen and the third the up axis.
    //  Here up is defined as the Z axis, which implies that the XY plane is the "ground".
    glm::mat4 view = glm::lookAt(glm::vec3(2.5f, 2.5f, 2.5f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 0.0f, 1.0f));

    glUseProgram(cubeShaderProgram);

    GLint uniView = glGetUniformLocation(cubeShaderProgram, "view");
    glad_glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    // Perspective projection matrix
    // glm::perspective : The first parameter is the vertical field-of-view,
    // the second parameter the aspect ratio of the screen and the last two parameters
    // are the near and far planes.
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(cubeShaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    // Global time uniform
    GLint globalTime = glGetUniformLocation(cubeShaderProgram, "globalTime");
    auto t_start = std::chrono::high_resolution_clock::now();

    GLint uniColor = glGetUniformLocation(cubeShaderProgram, "overrideColor");

    while (!glfwWindowShouldClose(window)) {
        // Bind framebuffer and draw 3D scene with cube
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glBindVertexArray(vaoCube);
        glEnable(GL_DEPTH_TEST);
        glUseProgram(cubeShaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texCat);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texPup);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        glUniform1f(globalTime, (sin(time * 4.0f) + 1.0f) / 2.0f);

        // A 2D transformation
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, time * glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

//         If we were using the ebo: glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//         But we're not:
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glEnable(GL_STENCIL_TEST);

        // Draw the plane
        glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilMask(0xFF); // Write to stencil buffer
        glDepthMask(GL_FALSE);  // Temporarily disable writing to the depth buffer when drawing the floor
        glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer (0 default)

        glDrawArrays(GL_TRIANGLES, 36, 6);

        // Draw the translated and reflected cube
        glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass test if stencil value is 1
        glStencilMask(0x00); // Don't write to the stencil buffer
        glDepthMask(GL_TRUE); // Write to the depth buffer again

        model = glm::scale(
                glm::translate(model, glm::vec3(0, 0, -1)),
                glm::vec3(1, 1, -1));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        // Dim reflection
        glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);

        glDisable(GL_STENCIL_TEST);

        // Bind default framebuffer and draw contents of the framebuffer we just drew to
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindVertexArray(vaoQuad);
        glDisable(GL_DEPTH_TEST);
        glUseProgram(quadShaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

    glDeleteRenderbuffers(1, &rboDepthStencil);
    glDeleteTextures(1, &texColorBuffer);
    glDeleteFramebuffers(1, &framebuffer);

    glDeleteTextures(1, &texPup);
    glDeleteTextures(1, &texCat);

    glDeleteProgram(cubeShaderProgram);
    glDeleteShader(cubeFragmentShader);
    glDeleteShader(cubeVertexShader);

    glDeleteBuffers(1, &vboCube);
    glDeleteBuffers(1, &vboQuad);
    glDeleteVertexArrays(1, &vaoCube);
    glDeleteVertexArrays(1, &vaoQuad);

    glfwTerminate();
    return 0;
}

GLuint load_texture(const GLchar *path)
{
    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    SOIL_load_OGL_texture(
            path, SOIL_LOAD_AUTO, texture,
            SOIL_FLAG_MIPMAPS|SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_COMPRESS_TO_DXT
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return texture;
}

void create_shader_program(
        const char *pathVertex,
        const char *pathFragment,
        GLuint &vertexShader,
        GLuint &fragmentShader,
        GLuint& shaderProgram
) {
    // Create and compile the vertex and fragment shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertex_src = read_shader(pathVertex);
    const char *cstr = vertex_src.c_str();
    glShaderSource(vertexShader, 1, &cstr, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string frag_src = read_shader(pathFragment);
    const char *frag_cstr = frag_src.c_str();
    glShaderSource(fragmentShader, 1, &frag_cstr, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
}

void specify_cube_vertex_attributes(GLuint shader_program)
{
    GLint posAttrib = glGetAttribLocation(shader_program, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);

    GLint colAttrib = glGetAttribLocation(shader_program, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                          8*sizeof(float), (void*)(3*sizeof(float)));

    GLint texAttrib = glGetAttribLocation(shader_program, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
                          8*sizeof(float), (void*)(6*sizeof(float)));
}

void specify_quad_vertex_attributes(GLuint shader_program)
{
    GLint posAttrib = glGetAttribLocation(shader_program, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    GLint texAttrib = glGetAttribLocation(shader_program, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
}

std::string read_shader(const char *filename)
{
    std::ifstream ifs(filename);
    std::string res((std::istreambuf_iterator<char>(ifs)),
                    (std::istreambuf_iterator<char>()));
    return res;
}

