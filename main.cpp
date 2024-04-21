/*
 * @Date: 2024-04-20 22:20:04
 * @LastEditors: gyt vocvocal@163.com
 * @LastEditTime: 2024-04-21 21:55:01
 * @FilePath: /fusion_dempster/main.cpp
 */
#include <iostream>
#include <iterator>
#include <vector>

#define NUM_SUBSETS 8

// Dempster证据组合（两个证据源）
std::vector<double> combine_dempster_two(const std::vector<double> &bba1, const std::vector<double> &bba2)
{
    std::vector<double> combined(NUM_SUBSETS, 0.0);
    double K = 0.0;

    for (int i = 1; i < NUM_SUBSETS; i++)
    {
        for (int j = 1; j < NUM_SUBSETS; j++)
        {
            if ((i & j) == 0) // i和j完全冲突
            {
                K += bba1[i] * bba2[j];
            }
        }
    }

    for (int i = 1; i < NUM_SUBSETS; i++)
    {
        for (int j = 1; j < NUM_SUBSETS; j++)
        {
            if ((i & j) != 0) // i和j有交集
            {
                int indx = i & j;
                combined[indx] += (bba1[i] * bba2[j]) / (1.0 - K);
            }
        }
    }

    return combined;
}

// 多个证据源组合
std::vector<double> combine_dempster_multi(const std::vector<std::vector<double>> &bba_sources)
{
    if (bba_sources.empty())
    {
        std::cout << "证据源空" << std::endl;
        std::exit(-1);
    }
    std::vector<double> combined = bba_sources[0];

    // 递归结合剩余的证据源
    for (size_t i = 1; i < bba_sources.size(); ++i)
    {
        combined = combine_dempster_two(combined, bba_sources[i]);
    }
    return combined;
}
void calculate_bel_and_pl(const std::vector<double> &combined, std::vector<double> &bel, std::vector<double> &pl)
{
    for (int i = 0; i < NUM_SUBSETS; i++)
    {

        for (int j = 0; j < NUM_SUBSETS; j++)
        {
            if ((i & j) == j)
            {
                bel[i] += combined[j];
            }
        }

        for (int j = 0; j < NUM_SUBSETS; j++)
        {
            if ((i & j) != 0)
            {
                pl[i] += combined[j];
            }
        }
    }
}

int main()
{
    std::vector<std::vector<double>> bba_sources = {
        {0, 0.4, 0.3, 0.1, 0.1, 0, 0, 0.1},   // CIA    001本 010萨 100霍
        {0, 0.2, 0.2, 0.5, 0.05, 0, 0, 0.05}, // NSA

    };

    std::vector<double> combined = combine_dempster_multi(bba_sources);

    std::cout << "Combined BBA from multiple sources: " << std::endl;
    std::cout << "空集：" << combined[0] << " 本拉登：" << combined[1] << " 萨达姆：" << combined[2] << " 本、萨：" << combined[3]
              << " 霍梅尼：" << combined[4] << " 本、霍：" << combined[5] << " 霍、萨：" << combined[6] << " 全集：" << combined[7] << std::endl;
    std::vector<double> bel(NUM_SUBSETS, 0.0);
    std::vector<double> pl(NUM_SUBSETS, 0.0);
    calculate_bel_and_pl(combined, bel, pl);
    std::cout << "Combined Beliefs:" << std::endl;
    for (int i = 0; i < NUM_SUBSETS; i++)
    {
        std::cout <<bel[i]<<" ";
    }
    std::cout << std::endl;
    std::cout << "Combined Plausibilities:" << std::endl;
    for (int i = 0; i < NUM_SUBSETS; i++)
    {
          std::cout<<pl[i]<<" ";
    }
     std::cout << std::endl;
    return 0;
}