#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<fstream>
#include<iostream>
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

GLfloat vxFloor[] = {
        -10.0f, 0.0f, -10.0f,
        -10.0f, 0.0f, 10.0f,
        10.0f, 0.0f, 10.0f,
        10.0f, 0.0f, -10.0f,
};

const float width = 800.0f;
const float height = 600.0f;

GLuint load_texture(const GLchar *path);
void create_shader_program(
        const char *pathVertex, const char *pathFragment,
        GLuint &vertexShader, GLuint &fragmentShader, GLuint& shaderProgram);
void specify_cube_vertex_attributes(GLuint shader_program);
void specify_floor_vertex_attributes(GLuint shader_program);

std::string read_shader(const char *filename);

// Cursor position
double cx{0}, cy{0};
void cursor_update(GLFWwindow *window, double x, double y) {
    cx = x; cy = y;
}

struct Camera {
    glm::vec3 pos{0.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};

    double px{0}, py{0};
    float yaw{0}, pitch{0};

    Camera(glm::vec3 cPos) : pos(cPos), px(cx), py(cy) {}

    void update() {
        float sensitivity = 0.1;
        float dx = (px - cx) * sensitivity;
        float dy = (cy - py) * sensitivity;
        px = cx; py = cy;
        yaw += dx;
        pitch += dy;
        pitch = glm::clamp(pitch, -89.0f, 89.0f);
    }

    glm::vec3 front() {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, -glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        return glm::normalize(make_vec3(glm::vec4{0.0f, 0.0f, 0.1f, 0.0f} * rotation));
    }

    glm::mat4 view() {
        update();
        return glm::lookAt(pos, pos + front(), up);
    }
};

int main() {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(width, height, "brix", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -2;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwGetCursorPos(window, &cx, &cy);
    glfwSetCursorPosCallback(window, cursor_update);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        return -3;
    }

    // glm::perspective : The first parameter is the vertical field-of-view,
    //    the second parameter the aspect ratio of the screen and the last two parameters
    //    are the near and far planes.
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), width / height, 1.0f, 10.0f);
    // Camera parameters
    Camera camera{glm::vec3{2.0}};

    //   --------------- Cube -----------------

    // Create a vertex array object for each framebuffer
    GLuint vaoCube;
    glGenVertexArrays(1, &vaoCube);
    glBindVertexArray(vaoCube);

    // Create a vertex buffer object per framebuffer and copy the vertex data to it
    GLuint vboCube;
    glGenBuffers(1, &vboCube);
    glBindBuffer(GL_ARRAY_BUFFER, vboCube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vxCube), vxCube, GL_STATIC_DRAW);

    GLuint cubeVertexShader, cubeFragmentShader, cubeShaderProgram;
    create_shader_program("shaders/cubeVertex.glsl", "shaders/cubeFragment.glsl",
                          cubeVertexShader, cubeFragmentShader, cubeShaderProgram);

    glUseProgram(cubeShaderProgram);
    specify_cube_vertex_attributes(cubeShaderProgram);

    // Load textures
    GLuint texCat = load_texture("resources/cat.png");
    GLuint texPup = load_texture("resources/pup.png");
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texCat);
    glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, texPup);
    glUniform1i(glGetUniformLocation(cubeShaderProgram, "texKitten"), 0);
    glUniform1i(glGetUniformLocation(cubeShaderProgram, "texPuppy"), 1);

    // Get uniform locations
    GLint uniModel = glGetUniformLocation(cubeShaderProgram, "model");
    GLint uniView = glGetUniformLocation(cubeShaderProgram, "view");
    GLint uniTime = glGetUniformLocation(cubeShaderProgram, "time");

    glUniformMatrix4fv(glGetUniformLocation(cubeShaderProgram, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

    //   --------------- Floor -----------------

    GLuint vaoFloor;
    glGenVertexArrays(1, &vaoFloor);
    glBindVertexArray(vaoFloor);

    GLuint vboFloor;
    glGenBuffers(1, &vboFloor);
    glBindBuffer(GL_ARRAY_BUFFER, vboFloor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vxFloor), vxFloor, GL_STATIC_DRAW);

    GLuint elements[] = {
            0, 1, 3,
            1, 2, 3,
    };
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Create and compile the vertex and fragment shaders
    GLuint floorVertexShader, floorFragmentShader, floorShaderProgram;
    create_shader_program("shaders/floorVertex.glsl", "shaders/floorFragment.glsl",
                          floorVertexShader, floorFragmentShader, floorShaderProgram);

    // Specify the layout of the vertex data
    glUseProgram(floorShaderProgram);
    specify_floor_vertex_attributes(floorShaderProgram);

    // floorplane uniforms
    GLint uniFloorModel = glGetUniformLocation(floorShaderProgram, "model");
    GLint uniFloorView = glGetUniformLocation(floorShaderProgram, "view");

    glUniformMatrix4fv(glGetUniformLocation(floorShaderProgram, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

    // ---------------- Loop ------------------
    auto t_start = std::chrono::high_resolution_clock::now();
    auto t_now = t_start;
    auto t_prev = t_start;

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        // Update elapsed time
        float t_delta = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_prev).count();

        t_prev = t_now;
        t_now = std::chrono::high_resolution_clock::now();
        float elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        }

        auto speed = 5.0f * t_delta;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera.pos -= camera.front() * speed; }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera.pos += camera.front() * speed; }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.pos -= glm::normalize(glm::cross(camera.front(), camera.up)) * speed;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera.pos += glm::normalize(glm::cross(camera.front(), camera.up)) * speed;
        }

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.view();

        // Draw the cube
        glUseProgram(cubeShaderProgram);
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
        glUniform1f(uniTime, (sin(elapsedTime * 4.0f) + 1.0f) / 2.0f);
        glBindVertexArray(vaoCube);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw the floor
        glUseProgram(floorShaderProgram);
        glBindVertexArray(vaoFloor);
        glUniformMatrix4fv(uniFloorModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniFloorView, 1, GL_FALSE, glm::value_ptr(view));
//        // The second parameter specifies the number of indices to draw, the third parameter specifies
//        // the type of the element data and the last parameter specifies the offset.
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    glDeleteTextures(1, &texPup);
    glDeleteTextures(1, &texCat);

    glDeleteProgram(cubeShaderProgram);
    glDeleteShader(cubeFragmentShader);
    glDeleteShader(cubeVertexShader);

    glDeleteBuffers(1, &vboCube);
    glDeleteVertexArrays(1, &vaoCube);

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
        const char *pathVertex, const char *pathFragment,
        GLuint &vertexShader, GLuint &fragmentShader, GLuint& shaderProgram
) {
    // Create and compile the vertex and fragment shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertex_src = read_shader(pathVertex);
    const char *cstr = vertex_src.c_str();
    glShaderSource(vertexShader, 1, &cstr, NULL);
    glCompileShader(vertexShader);
    GLint success = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint logSize = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<GLchar> errorLog(logSize);
        glGetShaderInfoLog(vertexShader, logSize, &logSize, &errorLog[0]);
        std::string s = std::string(errorLog.begin(), errorLog.end());
        std::cout << "vertex shader compilation failed: " << s << std::endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string frag_src = read_shader(pathFragment);
    const char *frag_cstr = frag_src.c_str();
    glShaderSource(fragmentShader, 1, &frag_cstr, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint logSize = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<GLchar> errorLog(logSize);
        glGetShaderInfoLog(fragmentShader, logSize, &logSize, &errorLog[0]);
        std::string s = std::string(errorLog.begin(), errorLog.end());
        std::cout << "fragment shader compilation failed: " << s << std::endl;
    }

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

//    GLint colAttrib = glGetAttribLocation(shader_program, "color");
//    glEnableVertexAttribArray(colAttrib);
//    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
//                          8*sizeof(float), (void*)(3*sizeof(float)));

    GLint texAttrib = glGetAttribLocation(shader_program, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
                          8*sizeof(float), (void*)(6*sizeof(float)));
}

void specify_floor_vertex_attributes(GLuint shader_program) {
    GLint posAttrib = glGetAttribLocation(shader_program, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

std::string read_shader(const char *filename)
{
    std::ifstream ifs(filename);
    std::string res((std::istreambuf_iterator<char>(ifs)),
                    (std::istreambuf_iterator<char>()));
    return res;
}

