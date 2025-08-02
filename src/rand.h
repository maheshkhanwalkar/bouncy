#ifndef RAND_H
#define RAND_H

#include <random>

class random_generator {
public:
    [[nodiscard]] int get(int min, int max);
    [[nodiscard]] float get(float min, float max);

    bool get_bool();

private:
    std::default_random_engine engine;
};

#endif //RAND_H
