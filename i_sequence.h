
#ifndef DIPLOMA__FI_CALCULATOR_HPP
#define DIPLOMA__FI_CALCULATOR_HPP

#include <vector>

#include "discrete_function.h"
#include <math.h>
#include "field.h"
#include "util_functions.h"

#define E 2.71828
#define p0 0.769

extern double eps;

/**
 * This class is used to calculate discrete functions I_0, I_1, ..., I_n.
 */
class i_sequence
{
protected:

/**
 * field of x values, that are arguments for fi_ functions
 */
    field x;
    
    /**
     * Sequence of fi_i functions.
     */
    
    
public:
    std::vector<discrete_function*> i_k;
    /**
     * Returns function fi_i.
     */
    discrete_function* fi_(int i ) const
    {
        return i_k[ i ];
    }

    /**
    * The upper limit, up to which the integral is being calculated.
    */
    const int upper_bound;
    /**
     * Constructor of this calculator.
     * @param step_ Step, by which fi functions will be calculated.
     * @param upper_lim_ The upper limit, up to which the integrals will be
     *   calculated.
     */
    i_sequence( field& x_, int upper_bound_)
        : x(x_), upper_bound(upper_bound_)
    {
        calculate_i_0();
    }
    
    
    /**
     * Calculates and stores discrete function fi_i, assuming that
     * previous function fi_[i-1] is already present.
     */
    void initialize_i_i(discrete_function* fi){
        i_k.push_back(fi);
    }

    int get_current_iteration(){
        return i_k.size();
    }
    
    /**
     * Calculates functions fi, until fi_N.
     */
    void calculate_up_to( int N );
    

    
protected:
    /**
     * Calculates and stores the first function fi_0.
     */
    void calculate_i_0();
    
};

inline void i_sequence::calculate_i_0()
{
    g_func g;
    discrete_function* fi0 = new discrete_function;
    for ( int i = 0; i <= x.count; ++i )
        fi0->set_point( x.points[i], g.operator()(x.points[i])) ;
    // Store it
    i_k.resize( 1 );
    i_k[ 0 ] = fi0;
}




#endif // DIPLOMA__FI_CALCULATOR_HPP
