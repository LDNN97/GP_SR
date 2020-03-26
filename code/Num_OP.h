//
// Created by LDNN97 on 2020/3/6.
//

#ifndef GP_CPP_NUM_OP_H
#define GP_CPP_NUM_OP_H

#include "Random.h"
#include "Parameter.h"
#include "Individual.h"
#include <iostream>

namespace num_sr{
    typedef std::array<double, dim> x_arr;
    typedef std::array<x_arr, train_data_size> trx_arr;
    typedef std::array<double, train_data_size> try_arr;
    typedef std::array<x_arr, test_data_size> tex_arr;
    typedef std::array<double, test_data_size> tey_arr;

    using indi::individual;

    int sample(const double * fitness);
    double cal_fitness(const individual& indi, trx_arr xx, try_arr yy);
    double cal_fitness(const individual& indi, tex_arr xx, tey_arr yy);
    void num_op();
};

#endif //GP_CPP_NUM_OP_H
