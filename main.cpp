#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread> 
#include "Utils.h"
#include "fangkuai.h"
using namespace std;



const int TARGET_FPS = 60;
const std::chrono::milliseconds FRAME_DURATION(1000 / TARGET_FPS); 

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo;  // 添加顶点缓冲区对象
GLuint offsetLoc;
float x = 0.0f;
float inc = 0.01f;
float window_bili = 0;

struct Vertex {
    float x, y, r, g, b;
};

glm::vec3 colors[color_init] = {
    glm::vec3(0.55f,0.55f,0.55f),/*灰*/
    glm::vec3(0.30f,0.65f,1.00f),/*蓝*/
    glm::vec3(0.78f,0.82f,0.74f),/*绿*/
    glm::vec3(0.95f,0.85f,0.60f),/*黄*/
    glm::vec3(1.00f,0.65f,0.55f)/*红*/
};//颜色

std::vector<Vertex>vertices;

void _3_3muoban(int (&arr)[init_col][init_row])
{
    
    int c = 0, d = 0, e = 0, f = 0;
    for (int i = init_col-1; i >= 0; i-- )
    {
        for (int j = 0; j < init_row; j++)
        {
            if (arr[i][j]==0)continue;
            c = j - 1; d = j + 1; e = i + 1;
            if (e >= init_col)continue;
            if (arr[e][j] == 0) {
                if (e + 1 < init_col&&arr[e + 1] == 0) {
                    f = arr[i][j]; arr[i][j] = arr[e + 1][j]; arr[e + 1][j] = f;   continue;
                }
                f = arr[i][j]; arr[i][j] = arr[e][j]; arr[e][j] = f; continue;
            }
            if (c >= 0 && arr[e][c] == 0)
            {
                f = arr[i][j]; arr[i][j] = arr[e][c]; arr[e][c] = f; continue;
            }
            if (d < init_row && arr[e][d] == 0)
            {
                f = arr[i][j]; arr[i][j] = arr[e][d]; arr[e][d] = f; continue;
            }
            if(fz2)fz1 = 1;
        }
    }
}

void copy(int(&arr1)[init_col][init_row], int(&arr2)[init_col][init_row])
{
    for (int i = 0; i < init_col; i++)
    {
        for (int j = 0; j < init_row; j++)
        {
            if (arr2[i][j]) {
                arr1[i][j] = arr2[i][j];
            }
        }
    }
}

void colorinit(int (&grid)[init_col][init_row],glm::vec3 (&colors)[color_init], std::vector<Vertex>&vertices,const float &cellSize)
{
    for (int col = 0; col < init_col; ++col) {
        for (int row = 0; row < init_row; ++row) {
            int colorIndex = grid[col][row];
            //if (colorIndex == 0) continue;
            // 根据colorIndex获取颜色，例如预定义的颜色数组
            glm::vec3 color = colors[colorIndex];
            float x0 = row * cellSize + x_;
            float y0 = -(col * cellSize + y_);
            float x1 = x0 + cellSize;
            float y1 = y0 + cellSize;
            // 三角形1
            vertices.push_back({ x0, y0, color.r, color.g, color.b });
            vertices.push_back({ x1, y0, color.r, color.g, color.b });
            vertices.push_back({ x0, y1, color.r, color.g, color.b });
            // 三角形2
            vertices.push_back({ x1, y0, color.r, color.g, color.b });
            vertices.push_back({ x1, y1, color.r, color.g, color.b });
            vertices.push_back({ x0, y1, color.r, color.g, color.b });

        }
    }
}

// 定义三角形顶点数据（3个顶点，每个顶点xyz三个分量）
float vertexPositions[] = {
    -1.0f, -1.0f, 0.0f,  // 顶点0
     1.0f, -1.0f, 0.0f,  // 顶点1
     1.0f,  1.0f, 0.0f   // 顶点2
};

void init(GLFWwindow * window)
{ 

    renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");

    // 创建并绑定VAO
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);

    // 创建并绑定VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

    GLint kuan_changLoc = glGetUniformLocation(renderingProgram, "kuan_chang");
    glProgramUniform1f(renderingProgram, kuan_changLoc, kuan_chang);// 传递屏幕长宽比

    glfwSetKeyCallback(window, key_callback);

    shongchong(fangzhi);
}

void display(GLFWwindow* window, double currentTime) {
    auto frameStart = std::chrono::steady_clock::now();  // 记录帧开始时间
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    if (fz1 && fz2&&jiange>=zuidajiange) {
        fz1 = 0; fz2 = 0; jiange = 0;
        shongchong(fangzhi);
    }
    if (jiange1 >= 10) {
        delete_copy(grid1);
        jiange1 = 0;
    }
    glfwPollEvents();
    copy(grid, grid1);
    copy(grid, fangzhi);
    colorinit(grid, colors, vertices, cellSize);
    delete_copy(grid, grid1);
    _3_3muoban(grid1);
    // 将顶点数据发送到VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // 设置顶点属性指针
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex,x));
    glEnableVertexAttribArray(0);  // 启用顶点属性（与layout location = 0对应）

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // 设置顶点颜色属性指针
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex,r)));
    glEnableVertexAttribArray(1);  // 启用顶点颜色属性（与layout location = 1对应）

    glUseProgram(renderingProgram);


    // 绘制三角形（使用顶点数组中的数据）
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    auto frameEnd = std::chrono::steady_clock::now();    // 记录帧结束时间
    auto elapsed = frameEnd - frameStart;                 // 计算本帧实际耗时
    if (elapsed < FRAME_DURATION) {
        std::this_thread::sleep_for(FRAME_DURATION - elapsed);
    }//智能停顿机制
    vertices.clear();
    if(fz2)jiange++;
    jiange1++;
}

int main(void) {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(chang, kuan, "Chapter 2 - program 6", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao[0]);
    glDeleteBuffers(1, &vbo);
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}