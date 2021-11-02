//
// Created by Gohar Kunjiyan on 2020-05-06.
//

#ifndef UNTITLED1_SIMULATOR_H
#define UNTITLED1_SIMULATOR_H

#include "field.h"
#include "i_sequence.h"
#include "util_functions.h"
#include "integral_calculator.h"

#define alpha 0.27
#define gamma 0.37
#define S0 1

class simulator {
protected:
    /**
     * x field is the field for fi_ arguments*/
    field x;
    /**
    * x field is the field for the t argument in the integral*/
    field t;
    
    g_func g;


public:
    
    i_sequence sequence;

    simulator(
              field &x_, field &t_, i_sequence &seq) : x(x_), t(t_),
                                                           sequence(seq) {
                                                               g = g_func();

    }

    /**
     * calculates all I functions*/
    void fill_sequence() {
        for (int k = 1; k < sequence.upper_bound; ++k) {
            define_fi_i_for_x_field(k);
        }

    }

private:
    
    
    double calculate_sub_integral(subintegral_sub_func *func, double tau) {
        field new_f(x.a, tau, x.get_step());
        integral_calculator cal(func, new_f);
        return cal.calculate_integral();
    }
    
    
    

    /**
    * return a subintegral function which is in the degree integral*/
    subintegral_sub_func *get_sub_integral_function(int i) {
        lambda_func *lambda = new lambda_func();
        return new subintegral_sub_func(sequence.fi_(i - 1), lambda);
    }
    
    //final subintegral function
    subintegral_function *get_subintegral_function(int i, int j, double tau) {
        auto sub = get_sub_integral_function(i);
        return new subintegral_function(x.points[j], calculate_sub_integral(sub, tau), sub);
    }
    
    
    

 /* calculates i_i(x[j]), finds current value of the integral*/
    double find_fi_i_for_fixed_x(int i, int j) {
        auto sub = get_subintegral_function(i, j, x.points[j]);
        field new_f(x.a, x.points[j], x.get_step());
        integral_calculator cal(sub, new_f);
        return cal.calculate_integral();

    }

    
    /* calculates all values of the function I_i on the field x*/
    void define_fi_i_for_x_field(int i) {
           discrete_function* fi_i = new discrete_function();
           for (int j = 0; j < x.points.size(); ++j) {
               double y = (alpha * S0)/(gamma - alpha) *
               find_fi_i_for_fixed_x(i, j);
               fi_i->set_point(x.points[j], g.operator()(x.points[j]) + y);
           }
           sequence.initialize_i_i(fi_i);
       }

};

#endif //UNTITLED1_SIMULATOR_H
