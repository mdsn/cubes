#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<fstream>
#include<iostream>
#include<string>

const float width = 800.0f;
const float height = 600.0f;

void make_cube(std::vector<GLfloat>& vec, float x, float y, float z);
GLuint gen_buffer(GLsizei size, GLfloat *data);

GLuint load_texture(const GLchar *path);

GLuint load_program(const char *pathv, const char *pathf);

void specify_cube_vertex_attributes(GLuint shader_program);

struct Camera {
    glm::vec3 pos{0.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};

    float yaw{0}, pitch{0};

    Camera(glm::vec3 cPos) : pos(cPos) {}

    void update(float dx, float dy) {
        yaw += dx;
        pitch += dy;
        pitch = glm::clamp(pitch, -89.0f, 89.0f);
    }

    glm::vec3 front() {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, -glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        return glm::normalize(make_vec3(glm::vec4{0.0f, 0.0f, 1.0f, 0.0f} * rotation));
    }

    glm::mat4 view() {
        return glm::lookAt(pos, pos + front(), up);
    }
};

struct State {
    GLFWwindow *window;
    Camera camera{glm::vec3{0, 0, -3.0}};
};

// All global state
State g;

void handle_mouse_input() {
    const float sensitivity = 0.1;
    static double px{0};
    static double py{0};
    double cx, cy;
    if (px || py) {
        glfwGetCursorPos(g.window, &cx, &cy);
        float dx = (px - cx) * sensitivity;
        float dy = (cy - py) * sensitivity;
        px = cx;
        py = cy;
        g.camera.update(dx, dy);
    } else {
        glfwGetCursorPos(g.window, &px, &py);
    }
}

int main() {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    g.window = glfwCreateWindow(width, height, "brix", NULL, NULL);
    if (!g.window) {
        glfwTerminate();
        return -2;
    }

    glfwSetInputMode(g.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(g.window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwMakeContextCurrent(g.window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        return -3;
    }

    // glm::perspective : The first parameter is the vertical field-of-view,
    //    the second parameter the aspect ratio of the screen and the last two parameters
    //    are the near and far planes.
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), width / height, 1.0f, 10.0f);

    //   --------------- Cube -----------------

    // Create a vertex array object for each framebuffer
    GLuint vaoCube;
    glGenVertexArrays(1, &vaoCube);
    glBindVertexArray(vaoCube);

    // Create a vertex buffer object per framebuffer and copy the vertex data to it
    std::vector<GLfloat> vec;
    make_cube(vec, 0, 0, 0);
    make_cube(vec, 1, 0, 0);

//    GLuint vboCube = gen_buffer(sizeof(vxCube), vxCube);
    GLuint vboCube = gen_buffer(vec.size() * sizeof(GLfloat), vec.data());
    GLuint cube_program = load_program("shaders/cubeVertex.glsl", "shaders/cubeFragment.glsl");

    glUseProgram(cube_program);

    glBindBuffer(GL_ARRAY_BUFFER, vboCube);
    specify_cube_vertex_attributes(cube_program);

    // Load textures
    GLuint texCat = load_texture("resources/cat.png");
    GLuint texPup = load_texture("resources/pup.png");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texCat);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texPup);
    glUniform1i(glGetUniformLocation(cube_program, "texKitten"), 0);
    glUniform1i(glGetUniformLocation(cube_program, "texPuppy"), 1);

    // Get uniform locations
    GLint uniModel = glGetUniformLocation(cube_program, "model");
    GLint uniView = glGetUniformLocation(cube_program, "view");
    GLint uniTime = glGetUniformLocation(cube_program, "time");

    glUniformMatrix4fv(glGetUniformLocation(cube_program, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

    // ---------------- Loop ------------------
    auto t_start = std::chrono::high_resolution_clock::now();
    auto t_now = t_start;
    auto t_prev = t_start;
    bool wireframe = false;

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(g.window)) {
        // Update elapsed time
        float t_delta = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_prev).count();

        t_prev = t_now;
        t_now = std::chrono::high_resolution_clock::now();
        float elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        if (glfwGetKey(g.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(g.window, GL_TRUE);
        }

        handle_mouse_input();

        auto speed = 5.0f * t_delta;
        if (glfwGetKey(g.window, GLFW_KEY_S) == GLFW_PRESS) { g.camera.pos -= g.camera.front() * speed; }
        if (glfwGetKey(g.window, GLFW_KEY_W) == GLFW_PRESS) { g.camera.pos += g.camera.front() * speed; }
        if (glfwGetKey(g.window, GLFW_KEY_A) == GLFW_PRESS) {
            g.camera.pos -= glm::normalize(glm::cross(g.camera.front(), g.camera.up)) * speed;
        }
        if (glfwGetKey(g.window, GLFW_KEY_D) == GLFW_PRESS) {
            g.camera.pos += glm::normalize(glm::cross(g.camera.front(), g.camera.up)) * speed;
        }
        if (glfwGetKey(g.window, GLFW_KEY_R) == GLFW_PRESS) {
            wireframe = !wireframe;
            glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
        }

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = g.camera.view();

        // Draw the cube
        glUseProgram(cube_program);
        glBindVertexArray(vaoCube);
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
        glUniform1f(uniTime, (sin(elapsedTime * 4.0f) + 1.0f) / 2.0f);
        glDrawArrays(GL_TRIANGLES, 0, 72);

        glfwSwapBuffers(g.window);
        glfwPollEvents();
        if (glfwWindowShouldClose(g.window)) {
            break;
        }
    }

    glDeleteTextures(1, &texPup);
    glDeleteTextures(1, &texCat);

    glDeleteProgram(cube_program);

    glDeleteBuffers(1, &vboCube);
    glDeleteVertexArrays(1, &vaoCube);

    glfwTerminate();
    return 0;
}

// --------------- cube --------------------

void make_cube(std::vector<GLfloat>& vec, float x, float y, float z) {
#define FACES 6
    const float n{0.5};
    // 6 faces, 4 vertices per face, 3 components per vertex
    const float positions[FACES][4][3]{
            {{-1, -1, -1}, {1,  -1, -1}, {1,  1,  -1}, {-1, 1,  -1}},   // ABCD
            {{-1, -1, -1}, {-1, -1, 1},  {-1, 1,  1},  {-1, 1, -1}},    // AEHD
            {{-1, -1, 1},  {1,  -1, 1},  {1,  1,  1},  {-1, 1,  1}},    // EFGH
            {{1,  -1, -1}, {1,  -1, 1},  {1,  1,  1},  {1,  1,  -1}},   // BFGC
            {{-1, -1, -1}, {-1, -1, 1},  {1,  -1, 1},  {1,  -1, -1}},   // AEFB
            {{-1, 1,  -1}, {-1, 1,  1},  {1,  1,  1},  {1,  1,  -1}}    // DHGC
    };
    // wind triangles counter-clockwise to face front
    const int indices[FACES][6]{
            {0, 3, 1, 1, 3, 2},     // ADB, BDC
            {0, 3, 1, 1, 3, 2},     // ADE, EDH
            {0, 3, 1, 1, 3, 2},     // EHF, FHG
            {0, 3, 1, 1, 3, 2},     // BCF, FCG
            {1, 0, 2, 2, 0, 3},     // EAF, FAB
            {1, 0, 2, 2, 0, 3}      // HDG, GDC
    };
    // texture coordinates
    const float uv[FACES][4][2]{
            {{0, 0}, {1, 0}, {1, 1}, {0, 1}},
            {{0, 0}, {1, 0}, {1, 1}, {0, 1}},
            {{0, 0}, {1, 0}, {1, 1}, {0, 1}},
            {{0, 0}, {1, 0}, {1, 1}, {0, 1}},
            {{0, 0}, {1, 0}, {1, 1}, {0, 1}},
            {{0, 0}, {1, 0}, {1, 1}, {0, 1}},
    };

    for (int i = 0; i < FACES; i++) {
        for (int j = 0; j < 6; j++) {
            int ix = indices[i][j];
            vec.push_back(x + n * positions[i][ix][0]);
            vec.push_back(y + n * positions[i][ix][1]);
            vec.push_back(z + n * positions[i][ix][2]);
            vec.push_back(uv[i][ix][0]);
            vec.push_back(uv[i][ix][1]);
        }
    }
}

// ------------------ gl stuff -------------------

GLuint gen_buffer(GLsizei size, GLfloat *data) {
    GLuint name;
    glGenBuffers(1, &name);
    glBindBuffer(GL_ARRAY_BUFFER, name);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return name;
}

GLuint load_texture(const GLchar *path) {
    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    SOIL_load_OGL_texture(
            path, SOIL_LOAD_AUTO, texture,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return texture;
}

void specify_cube_vertex_attributes(GLuint shader_program) {
    GLint posAttrib = glGetAttribLocation(shader_program, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

    GLint texAttrib = glGetAttribLocation(shader_program, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
                          5 * sizeof(float), (void *) (3 * sizeof(float)));
}

// ---------------- shader stuff ----------------

std::string read_file(const char *path) {
    std::ifstream ifs(path);
    std::string res((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    return res;
}

GLuint make_shader(GLenum type, const char *source) {
    GLuint name = glCreateShader(type);
    glShaderSource(name, 1, &source, NULL);
    glCompileShader(name);
    GLint success{0};
    glGetShaderiv(name, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint log_size{0};
        glGetShaderiv(name, GL_INFO_LOG_LENGTH, &log_size);
        std::vector<GLchar> log(log_size);
        glGetShaderInfoLog(name, log_size, &log_size, log.data());
        std::string err = std::string(log.begin(), log.end());
        std::cerr << "shader compilation failed: " << err << std::endl;
    }
    return name;
}

GLuint load_shader(GLenum type, const char *path) {
    std::string source = read_file(path);
    return make_shader(type, source.c_str());
}

GLuint make_program(GLuint vsh, GLuint fsh) {
    GLuint name = glCreateProgram();
    glAttachShader(name, vsh);
    glAttachShader(name, fsh);
    glBindFragDataLocation(name, 0, "outColor");
    glLinkProgram(name);
    GLint success{0};
    glGetProgramiv(name, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        GLint log_size{0};
        glGetProgramiv(name, GL_INFO_LOG_LENGTH, &log_size);
        std::vector<GLchar> log(log_size);
        glGetProgramInfoLog(name, log_size, &log_size, log.data());
        std::string err = std::string(log.begin(), log.end());
        std::cerr << "program linkage failed: " << err << std::endl;
    }
    glDetachShader(name, vsh);
    glDetachShader(name, fsh);
    glDeleteShader(vsh);
    glDeleteShader(fsh);
    return name;
}

GLuint load_program(const char *pathv, const char *pathf) {
    GLuint vsh = load_shader(GL_VERTEX_SHADER, pathv);
    GLuint fsh = load_shader(GL_FRAGMENT_SHADER, pathf);
    return make_program(vsh, fsh);
}
