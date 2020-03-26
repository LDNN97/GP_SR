//
// Created by LDNN97 on 2020/3/6.
//
#include "Num_OP.h"

using namespace num_sr;
using std::cin;
using std::cout;
using std::endl;
using std::swap;
using std::ifstream;

int num_sr::sample(const double * fitness){
    int ans = rand_int(0, POP_SIZE);
    for (int i = 0; i < T_S - 1; i++) {
        int tmp = rand_int(0, POP_SIZE);
        ans = (fitness[ans] < fitness[tmp]) ? ans : tmp;
    }
    return ans;
}

double num_sr::cal_fitness(const individual& indi, trx_arr xx, try_arr yy){
    double fitness = 0;
    for (int i = 0; i < train_data_size; i++)
        fitness += abs(indi::individual::calculate(indi.root, xx[i]) - yy[i]);
    return fitness;
}

double num_sr::cal_fitness(const individual& indi, tex_arr xx, tey_arr yy){
    double fitness = 0;
    for (int i = 0; i < test_data_size; i++)
        fitness += abs(indi::individual::calculate(indi.root, xx[i]) - yy[i]);
    return fitness;
}

void num_sr::num_op(){
    ifstream file_data("data.txt");
    trx_arr train_x;
    try_arr train_y;
    for (int i = 0; i < train_data_size; i++) {
        for (int j = 0; j < dim; j++)
            file_data >> train_x[i][j];
        file_data >> train_y[i];
    }
    tex_arr test_x;
    tey_arr test_y;
    for (int i = 0; i < test_data_size; i++) {
        for (int j = 0; j < dim; j++)
            file_data >> test_x[i][j];
        file_data >> test_y[i];
    }
    file_data.close();

    //Initialize
    auto pop = new individual* [POP_SIZE];
    for (int md = MIN_DEPTH; md <= INI_DEPTH; md++) {
        for (int i = 0; i < TYPE_NUM; i++) {
            pop[TYPE_NUM * 2 * (md - MIN_DEPTH) + i] = new individual();
            pop[TYPE_NUM * 2 * (md - MIN_DEPTH) + i]->build("grow", md);
        }
        for (int i = 0; i < TYPE_NUM; i++) {
            pop[TYPE_NUM * 2 * (md - MIN_DEPTH) + TYPE_NUM + i] = new individual();
            pop[TYPE_NUM * 2 * (md - MIN_DEPTH) + TYPE_NUM + i]->build("full", md);
        }
    }

    //fitness
    double fitness[POP_SIZE];
    double total;
    int best_indi;

    //Evolution
    for (int gen = 0; gen < MAX_GENERATION; gen++) {
        cout << "Generation: " << gen << endl;
        auto new_pop = new individual* [POP_SIZE];

        total = 0; best_indi = 0;
        for (int i = 0; i < POP_SIZE; i++) {
            fitness[i] = cal_fitness(*(pop[i]), train_x, train_y);
            total += fitness[i];
            best_indi = (fitness[best_indi] < fitness[i]) ? best_indi : i;
        }
        cout << " Average Fitness: " << total / double(POP_SIZE) << endl;
        cout << "Best Fitness: " << fitness[best_indi] << endl;
        cout << "Tree Size: " << pop[best_indi]->root->size << endl;

        if (fitness[best_indi] < 1e-3) {
            cout << "=====successfully!======" << endl;
            cout << endl;
            break;
        }

        for (int i = 0; i < POP_SIZE; i++) {
            int index_p1 = sample(fitness);
            int index_p2 = sample(fitness);
            auto parent1 = new individual(*pop[index_p1]);
            auto parent2 = new individual(*pop[index_p2]);

            parent1->crossover(parent2);
            individual::mutation(parent1);

            new_pop[i] = parent1;
            individual::clean(parent2->root);
            delete parent2;
        }

        swap(pop, new_pop);

        // free pointer;
        for (int i = 0; i < POP_SIZE; i++) {
            individual::clean(new_pop[i]->root);
            delete new_pop[i];
        }
        delete [] new_pop;
    }

    cout << endl;
    cout << "Test Result: " << endl;
    total = 0; best_indi = 0;
    for (int i = 0; i < POP_SIZE; i++) {
        fitness[i] = cal_fitness(*(pop[i]), test_x, test_y);
        total += fitness[i];
        best_indi = (fitness[best_indi] < fitness[i]) ? best_indi : i;
    }
    cout << "Average Error: " << total / double(POP_SIZE) << endl;
    cout << "Minimum Error: " << fitness[best_indi] << endl;

    // free pointer
    for (int i = 0; i < POP_SIZE; i++) {
        individual::clean(pop[i]->root);
        delete pop[i];
    }
    delete [] pop;
}