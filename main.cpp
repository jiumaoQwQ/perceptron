#include <glm/glm.hpp>

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

static glm::vec2 w = {0.0f, 0.0f};
static float b = 0;
static float n = 0.01f;

std::vector<glm::vec2> x;
std::vector<float> y;

float sign(float x)
{
    if (x >= 0)
        return 1.0f;
    else
        return -1.0f;
}

float f(glm::vec2 const &x)
{
    return sign(glm::dot(w, x) + b);
}

void read_data(std::string file_path)
{
    std::ifstream os(file_path);
    std::string s;
    while (os >> s)
    {
        glm::vec2 tmpX;
        float tmpY;

        auto i = s.find_first_of(',');
        std::stringstream(s.substr(0, i)) >> tmpX.x;

        s = s.substr(i + 1);
        auto i1 = s.find_first_of(',');
        std::stringstream(s.substr(0, i1)) >> tmpX.y;

        s = s.substr(i1 + 1);
        std::stringstream(s) >> tmpY;

        x.push_back(tmpX);
        y.push_back(tmpY);
    }
    os.close();
}

int main()
{
    read_data("./Iris.txt");
    bool ok = false;
    int train_data_size = x.size() * 0.75;
    while (!ok)
    {
        ok = true;
        for (int i = 0; i < train_data_size; i++)
        {
            glm::vec2 xi = x[i];
            float yi = y[i];
            if (yi * f(xi) <= 0.0f)
            {
                w += n * yi * xi;
                b += n * yi;
            }
            if (yi * f(xi) <= 0.0f)
            {
                ok = false;
            }
        }
    }

    int correct_cnt = 0;
    int error_cnt = 0;
    for (int i = train_data_size; i < x.size(); i++)
    {
        glm::vec2 xi = x[i];
        float yi = y[i];
        if (yi * f(xi) <= 0.0f)
        {
            error_cnt++;
        }
        else
        {
            correct_cnt++;
        }
    }

    std::cout << "w:" << w.x << " " << w.y << " "
              << "b:" << b << std::endl;
    std::cout << "accuracy:" << correct_cnt * 1.0f / (correct_cnt + error_cnt) << std::endl;
    return 0;
}