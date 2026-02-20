#pragma once
#include<iostream>
#include <GLFW/glfw3.h>
#include <random>
#include <ctime>

constexpr int numVAOs = 1;
constexpr float chang = 600;
constexpr float kuan = 900;
float kuan_chang = kuan / chang;
constexpr int init_row = 120, init_col = 180;
constexpr float cellSize = 0.01f;
constexpr int color_init = 5;
constexpr float x_ = -0.6f, y_ = -0.8f;
constexpr int py = 0;//放置方块位置偏移量
constexpr int yidongbuchang = 6;
constexpr int zuidajiange = 20;
constexpr int delete_tianchong = 0;

// 方块形状数量
const int SHAPE_COUNT = 7;
// 每个方块的旋转状态数（通常为4，O形旋转不变）
const int ROTATION_COUNT = 4;
// 矩阵尺寸
const int MATRIX_SIZE = 4;

bool fz1 = 0, fz2 = 0;//记录方块是否被放下
int grid[init_col][init_row];//初始网格属性
int grid1[init_col][init_row];
int jiange = 0, jiange1 = 0;

// 形状数组索引：0-I, 1-O, 2-T, 3-L, 4-J, 5-S, 6-Z
const int SHAPES[SHAPE_COUNT][ROTATION_COUNT][MATRIX_SIZE][MATRIX_SIZE] = {
    // I 形
    {
        {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}},  // 旋转0
        {{0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0}},  // 旋转1
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,1}, {0,0,0,0}},  // 旋转2
        {{0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0}}   // 旋转3
    },
    // O 形
    {
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}},  // 所有旋转相同
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}},
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}},
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}
    },
    // T 形
    {
        {{0,0,0,0}, {0,1,0,0}, {1,1,1,0}, {0,0,0,0}},  // 旋转0
        {{0,0,0,0}, {0,1,0,0}, {0,1,1,0}, {0,1,0,0}},  // 旋转1
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,0}, {0,1,0,0}},  // 旋转2
        {{0,0,0,0}, {0,1,0,0}, {1,1,0,0}, {0,1,0,0}}   // 旋转3
    },
    // L 形
    {
        {{0,0,0,0}, {0,0,1,0}, {1,1,1,0}, {0,0,0,0}},  // 旋转0
        {{0,0,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,1,0}},  // 旋转1
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,0}, {1,0,0,0}},  // 旋转2
        {{0,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,0,0}}   // 旋转3
    },
    // J 形
    {
        {{0,0,0,0}, {1,0,0,0}, {1,1,1,0}, {0,0,0,0}},  // 旋转0
        {{0,0,0,0}, {0,1,1,0}, {0,1,0,0}, {0,1,0,0}},  // 旋转1
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,0}, {0,0,1,0}},  // 旋转2
        {{0,0,0,0}, {0,1,0,0}, {0,1,0,0}, {1,1,0,0}}   // 旋转3
    },
    // S 形
    {
        {{0,0,0,0}, {0,1,1,0}, {1,1,0,0}, {0,0,0,0}},  // 旋转0
        {{0,0,0,0}, {0,1,0,0}, {0,1,1,0}, {0,0,1,0}},  // 旋转1
        {{0,0,0,0}, {0,0,0,0}, {0,1,1,0}, {1,1,0,0}},  // 旋转2
        {{0,0,0,0}, {1,0,0,0}, {1,1,0,0}, {0,1,0,0}}   // 旋转3
    },
    // Z 形
    {
        {{0,0,0,0}, {1,1,0,0}, {0,1,1,0}, {0,0,0,0}},  // 旋转0
        {{0,0,0,0}, {0,0,1,0}, {0,1,1,0}, {0,1,0,0}},  // 旋转1
        {{0,0,0,0}, {0,0,0,0}, {1,1,0,0}, {0,1,1,0}},  // 旋转2
        {{0,0,0,0}, {0,1,0,0}, {1,1,0,0}, {1,0,0,0}}   // 旋转3
    }
};

// 随机数生成器类（可以放在全局或作为游戏类的成员）
class Random {
private:
    std::mt19937 rng;  // 梅森旋转算法引擎（高质量的随机数生成器）

public:
    // 构造函数：使用当前时间作为种子
    Random() {
        rng.seed(std::time(nullptr));
    }

    // 生成 [min, max] 范围内的整数
    int getInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    // 生成 [min, max) 范围内的浮点数
    double getDouble(double min, double max) {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(rng);
    }
};

Random jntm;
Random color_fz;
int fangzhi[48][init_row];//方块转换区域

void shongchong(int(&arr)[48][init_row])
{
    int a = jntm.getInt(0, SHAPE_COUNT - 1);
    int b = init_row / 10;
    int c = color_fz.getInt(1, 4);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (SHAPES[a][0][i][j])
            {
                for (int i1 = i*b; i1 < i*b+b; i1++)
                {
                    for (int j1 = j*b; j1 < j*b+b; j1++)
                    {
                        arr[i1][j1 + py] = c;
                    }
                }
            }
        }
    }
}
//进行简单复制
void copy(int(&arr1)[init_col][init_row], int(&arr2)[48][init_row])
{
    for (int i = 0; i < 48; i++)
    {
        for (int j = 0; j < init_row; j++)
        {
            if (arr2[i][j]) {
                arr1[i][j] = arr2[i][j];
            }
        }
    }
}
//删除复制内容
void delete_copy(int(&arr1)[init_col][init_row], int(&arr2)[init_col][init_row])
{
    for (int i = 0; i < init_col; i++)
    {
        for (int j = 0; j < init_row; j++)
        {
            if (arr2[i][j]) {
                arr1[i][j] = 0;
            }
        }
    }
}
void delete_copy(int(&arr2)[48][init_row])
{
    for (int i = 0; i < 48; i++)
    {
        for (int j = 0; j < init_row; j++)
        {
            if (arr2[i][j]) {
                arr2[i][j] = 0;
            }
        }
    }
}
void delete_copy(int(&arr1)[init_col][init_row], int(&arr2)[48][init_row])
{
    for (int i = 0; i < 48; i++)
    {
        for (int j = 0; j < init_row; j++)
        {
            if (arr2[i][j]) {
                arr1[i][j] = 0;
            }
        }
    }
}
//删除相同颜色元素
void delete_copy(int(&arr)[init_col][init_row])
{
    int a = 0, c = 0, d = 0, e = 0;
    std::vector<std::vector<bool>>b(init_col, std::vector<bool>(init_row));
    for (int i = 0; i < init_col; i++)
    {
        if (arr[i][0] == 0 || arr[i][0] == a) {
            a = arr[i][0]; continue;
        }
        a = arr[i][0]; c = i;
        for (int j = 0; j < init_row; )
        {
            for (int k = c; k < init_col; k++)
            {
                if (arr[k][j] == a)b[k][j] = 1;
                else break;
            }
            for (int l = c - 1; l >= 0; l--)
            {
                if (arr[l][j] == a)b[l][j] = 1;
                else break;
            }
            d = j;
            for (int m = 0; m < init_col; m++)
            {
                if (b[m][d] && d + 1 < init_row && arr[m][d + 1] == a)
                {
                    b[m][d + 1] = 1;
                    c = m;
                    j = d + 1;
                }
            }
            if (j == d)break;
            if (j == init_row - 1) {
                for (int k = 0; k < init_col; k++)
                {
                    for (int l = 0; l < init_row; l++)
                    {
                        if (b[k][l])arr[k][l] = delete_tianchong;
                    }
                }
            }
        }
        for (int k = 0; k < init_col; k++)
        {
            for (int l = 0; l < init_row; l++)
            {
                b[k][l] = 0;
            }
        }
    }
}
//A键左移
void a_anxia(int(&arr)[48][init_row])
{
    int a = 0;
    for (int i = 0; i < 48; i++)
    {
        for (int j = 0; j < init_row; j++)
        {
            if (arr[i][j] && j - yidongbuchang >= 0)
            {
                a = arr[i][j]; arr[i][j] = arr[i][j - yidongbuchang]; arr[i][j - yidongbuchang] = a;
            }
        }
    }
}
//D键右移
void d_anxia(int(&arr)[48][init_row])
{
    int a = 0;
    for (int i = 0; i < 48; i++)
    {
        for (int j = init_row - 1; j >= 0; j--)
        {
            if (arr[i][j] && j + yidongbuchang < init_row)
            {
                a = arr[i][j]; arr[i][j] = arr[i][j + yidongbuchang]; arr[i][j + yidongbuchang] = a;
            }
        }
    }
}

// 键盘回调函数
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // 只关心按键按下的事件 (按下瞬间触发)
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_W:
            std::cout << "W键按下" << std::endl;
            // 在这里添加向上移动或旋转的逻辑
            break;
        case GLFW_KEY_A:
            
            // 在这里添加向左移动的逻辑
            delete_copy(grid, fangzhi);
            a_anxia(fangzhi);
            break;
        case GLFW_KEY_S:
            
            // 在这里添加向下移动的逻辑
            if (jiange > zuidajiange)break;
            delete_copy(grid, fangzhi);
            copy(grid1, fangzhi);
            delete_copy(fangzhi);
            fz2 = 1;
            break;
        case GLFW_KEY_D:
            
            // 在这里添加向右移动的逻辑
            delete_copy(grid, fangzhi);
            d_anxia(fangzhi);
            break;
        case GLFW_KEY_SPACE:
            std::cout << "空格键按下" << std::endl;
            // 在这里添加快速下落或旋转的的逻辑
            break;
        case GLFW_KEY_ESCAPE: // 顺便加个退出功能
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        }
    }
    // 如果你需要处理按键释放，可以判断 action == GLFW_RELEASE
}

