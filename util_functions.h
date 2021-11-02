//
//  util_functions.h
//  corona
//
//  Created by Gohar Kunjiyan on 1/28/21.
//  Copyright © 2021 Gohar Kunjiyan. All rights reserved.
//

#ifndef util_functions_h
#define util_functions_h
#include <math.h>
#include "discrete_function.h"
#define E 2.71828
#define alpha 0.27
#define gamma 0.37

const double DEF_K_FOR_LAMBDA = 1;
const double DELTA = 0.6;
const double LAMBDA_COEF = 0.9916;

extern double eps;
class g_func{
public:
    
    
public:
    g_func(){}
   
    double operator()(double t) const {
        return (eps/(gamma - alpha)) * (pow(E, -alpha*t) - pow(E, -gamma*t));
    }
};

class lambda_func{
public:
    double k;
    
public:
    
    lambda_func()
    : k(DEF_K_FOR_LAMBDA) {}
    lambda_func(double k)
    : k(k) {}
    
    /**
     * Returns value of this  function at point 't'.
     */
    double operator()(double t) const {
        //double cos_res = cos(k*t) * cos(k*t);
        return LAMBDA_COEF * pow(E, -DELTA*t);
    }
};

 class integral_func {
 public:
   virtual double operator()(double t) const = 0;
};

//function lambda(t)*I_k(t)
class subintegral_sub_func: public integral_func{
    discrete_function *i_K;
    lambda_func *lambda;
public:
    subintegral_sub_func(discrete_function *i_n_, lambda_func *lambda)
               : i_K(i_n_), lambda(lambda) {}
    
     double operator()(double t) const {
       return lambda->operator()(t)*i_K->operator()(t);
    }
};

//the final function
class subintegral_function: public integral_func {
protected:
    
    subintegral_sub_func *sub;
    /**
     the value of the exponent's degree 
     */
    double sub_int_res;
    

    /**
     * The value of x.
     */
    double x;

public:
    /**
     * Constructor.
     */
    subintegral_function(double x_, double sub_int_res_, subintegral_sub_func *sub)
            : x(x_),  sub_int_res(sub_int_res_), sub(sub) {}

    /**
     * Returns value fo the subintegral expression, for given 't (in our case x is equivalent of t and t is equivalent of tau)'.
     */
    double operator()(double t) const {
        double val = (pow(E, -alpha*(x - t)) - pow(E, -gamma*(x - t))) * sub->operator()(t) * pow(E, -sub_int_res);
        return val;
    }

};



#endif /* util_functions_h */
