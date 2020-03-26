//
// Created by LDNN97 on 2020/3/1.
//

#ifndef GP_CPP_PARAMETER_H
#define GP_CPP_PARAMETER_H

#include <string>

const int MIN_DEPTH = 3;
const int INI_DEPTH = 5;
const int MUT_DEPTH = 3;
const int MAX_GENERATION = 100;
const int T_S = 6; // Tournament Size
const double C_P = 0.5; // Crossover Probability
const double M_P = 0.2; // Mutation Probability
const int TYPE_NUM = 5;
const int POP_SIZE = (INI_DEPTH - MIN_DEPTH + 1) * TYPE_NUM * 2;

// !!!!!Remember to change the tree_node code about the terminal node!!!!!!

// GP Meta-Function Set
const int n_f = 4;
const std::string function_node[n_f]{"+", "-", "*", "/"};

//=====SR=====
const int n_t = 4;
const int dim = 4;
const std::string terminal_node[n_t]{"1", "2", "3", "4"};
const int train_data_size = 100;
const int test_data_size = 20;

#endif //GP_CPP_PARAMETER_H
