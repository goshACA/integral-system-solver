//
// Created by Gohar Kunjiyan on 2020-05-06.
//

#ifndef UNTITLED1_FIELD_H
#define UNTITLED1_FIELD_H

#include "vector"

/**
    *Field is used in discrete algorithms, currently in the integration*/
class field {
public:
    double a, b;
    int count;
    std::vector<double> points;

    field(double a_, double b_, double step_) {
        a = a_;
        b = b_;
        step = step_;
        count = (b - a) / step_;
        init_points();
    }

    double get_step() const {
        return step;
    }

private:
    double step;

    void init_points() {
        for (int i = 0; i < count + 1; ++i) {
            points.push_back(a + i * step);
        }
    }
};

#endif //UNTITLED1_FIELD_H
