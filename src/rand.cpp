#include "rand.h"

int random_generator::get(const int min, const int max) {
    std::uniform_int_distribution distribution(min, max);
    return distribution(this->engine);
}

float random_generator::get(const float min, const float max) {
    std::uniform_real_distribution distribution(min, max);
    return distribution(this->engine);
}

bool random_generator::get_bool() {
    return this->get(0, 1) == 0;
}
