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
std::vector<std::vector<bool>>b(init_col, std::vector<bool>(init_row));

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
class delete_xingtongyanse {
private:
    std::vector<int>shuxing;
    std::vector<int>shuxingliebiao;
    std::vector<int> zhenghe;
    std::vector<int>you_;
    std::vector<int>zuo_;
    const int rows, cols;
    int(&arr)[init_col][init_row];
public:
    delete_xingtongyanse(int(&arr)[init_col][init_row], int c, int r) :rows(r), cols(c), shuxing(r* c), zhenghe(r* c), arr(arr),
        you_(init_col), zuo_(init_col) {
    }
    void dy(const std::vector<int>& arr1)
    {
        int a = init_col * init_row;
        for (int i = 0; i < a; i++)
        {
            if (i % init_row == 0)std::cout << std::endl;
            std::cout << arr1[i] << ' ';
        }
        std::cout << std::endl;
    }
    void biaojishuxing()
    {
        int size = rows * cols;
        // 确保labels数组足够大
        if (shuxing.size() < size) {
            shuxing.resize(size);
        }
        // 第一遍：初步标记
        int nextLabel = 1;
        int shangyige = 0;
        int shang = 0, zuo = 0, ls = 0;
        shuxingliebiao.clear();
        shuxingliebiao.push_back(0); // 占位
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {

                ls = j * rows + i;
                if (arr[j][i] == 0) {
                    shuxing[j * rows + i] = 0;
                    continue;
                }
                // 检查左边和上边（4连通）
                if (j > 0 && arr[j][i] == arr[j - 1][i])shang = shuxing[(j - 1) * rows + i];
                else shang = 0;
                if (i > 0 && arr[j][i] == arr[j][i - 1])zuo = shuxing[j * rows + i - 1];
                else zuo = 0;
                if (shang == 0 && zuo == 0) {
                    shuxing[ls] = nextLabel++;
                    shuxingliebiao.push_back(nextLabel - 1);
                }
                else if (shang != 0 && zuo == 0) {
                    shuxing[ls] = shang;
                }
                else if (shang == 0 && zuo != 0) {
                    shuxing[ls] = zuo;
                }
                else {
                    // 两者都非0，需要合并
                    int minLabel = std::min(shang, zuo);
                    int maxLabel = std::max(shang, zuo);
                    shuxing[ls] = minLabel;

                    if (minLabel != maxLabel) {
                        // 记录等价关系
                        while (shuxingliebiao[maxLabel] != maxLabel) {
                            maxLabel = shuxingliebiao[maxLabel];
                        }
                        while (shuxingliebiao[minLabel] != minLabel) {
                            minLabel = shuxingliebiao[minLabel];
                        }
                        if (maxLabel != minLabel) {
                            shuxingliebiao[maxLabel] = minLabel;
                        }
                    }
                }
            }
        }
        // 第二遍：合并等价标签
        for (int i = 0; i < size; ++i) {
            if (shuxing[i] != 0) {
                int label = shuxing[i];
                while (shuxingliebiao[label] != label) {
                    label = shuxingliebiao[label];
                    continue;
                }
                zhenghe[i] = label;
            }
            else {
                zhenghe[i] = 0;
            }
        }
    }
    void delete_kaishi()
    {
        int c = 0;
        for (int i = 0; i < cols; i++)
        {
            if (zhenghe[i * rows])you_[i] = zhenghe[i * rows];
            if (zhenghe[i * rows + rows - 2])zuo_[i] = zhenghe[i * rows + rows - 2];
        }
        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (you_[j] && zuo_[i] && you_[j] == zuo_[i]) {
                    c = you_[j];
                    for (int a = 0; a < cols; a++)
                    {
                        for (int b = 0; b < rows; b++) {
                            if (zhenghe[a*rows+b] == c)arr[a][b] = 0;
                        }
                    }
                    you_.assign(cols, 0);
                    zuo_.assign(cols, 0);
                    shuxing.assign(cols * rows, 0);
                    shuxingliebiao.clear();
                    zhenghe.assign(cols * rows, 0);
                    return ;
                }
            }
        }
        you_.assign(cols, 0);
        zuo_.assign(cols, 0);
        shuxing.assign(cols * rows, 0);
        shuxingliebiao.clear();
        zhenghe.assign(cols * rows, 0);
    }

};
delete_xingtongyanse nmjj(grid1, init_col, init_row);
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

