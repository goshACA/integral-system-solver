#ifndef DIPLOMA__SPLINE_NUMBERICAL_INTEGRATION_HPP
#define DIPLOMA__SPLINE_NUMBERICAL_INTEGRATION_HPP

#include <algorithm>
#include <vector>
#include <cmath>



#include "util_functions.h"
#include "field.h"



/**
 * This class performs numerical integration of given function with Riemann sum
 * method.
 */
class integral_calculator {

protected:
    /**
     * The function, which is being integrated.
     */

    integral_func *f;
    /**
    * t field is used for iterating through t values*/
    field t;


public:
    /**
     * Constructor
     * @param f_ The function, which is being integrated.
     */
    integral_calculator(integral_func *f_,  field &t_)
            : f(f_),  t(t_) {}

    double calculate_integral() const;
};


/**
 * calculates integral for fixed I_ with fixed x argument
 */
inline double integral_calculator::calculate_integral() const {

    double step = t.get_step();


    double result = 0;
    for(int  i = 1; i < t.count; ++i){
         result += f->operator()((t.points[i] + t.points[i-1])/2) * step;
    }
    return result;
}


#endif // DIPLOMA__SPLINE_NUMBERICAL_INTEGRATION_HPP
