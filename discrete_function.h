
#ifndef DIPLOMA__DISCRETE_FUNCTION_HPP
#define DIPLOMA__DISCRETE_FUNCTION_HPP

#include <map>



/**
 * This class represents a discrete funciton (i.e. such function which is
 * defined only on some discrete and finite domain).
 */
class discrete_function {
protected:
    typedef std::map<double, double> points_type;

    /**
     * Collection of (Xi, Yi) pairs.
     */
    points_type points;

public:
     double max_x, max_y = -1;
    /// Sets value of this function at 'x' to be 'y'.
    void set_point(double x, double y) {
        points[correct(x)] = y;
        if(y > max_y){
            max_y = y;
            max_x = x;
        }
    }

    /// Returns value of this function at 'x'.
    double get_point(double x) const {
        return points.at(correct(x));
    }

    /// Tests if this function is defined on 'x'.
    bool has_point(double x) const { return points.count(correct(x)) == 1; }

    /// Removes value of this function for 'x'.
//    void remove_point(double x) const { points.erase(correct(x)); }

    /**
     * Returns value of this discrete function at point 'x'.
     */
    double operator()(double x) const {return get_point(x); }


    /**
    * Operations that can be applied on a discrete_function
    */
    discrete_function operator/(double value) {
        discrete_function result;
        for (std::map<double, double>::iterator it = this->points.begin(); it != this->points.end(); ++it) {
            result.points[it->first] = points[it->first] / value;
        }
        return result;
    }

    discrete_function operator*(double value) {
        discrete_function result;
        for (std::map<double, double>::iterator it = this->points.begin(); it != this->points.end(); ++it) {
            result.points[it->first] = points[it->first] * value;
        }
        return result;
    }

    friend discrete_function operator-(discrete_function &f1, discrete_function &f2);

protected:
    /**
     * Considering some floating-point precision errors, returns the
     * closest x' to given x, on which this function is defined, only
     * in case if such x' is closer to x than some EPS.
     * Otherwise, returns given x.
     */
    double correct(double x) const;
};




// Inline methods


inline double discrete_function::correct(double x) const {
    const double EPS = 1e-6; // The maximal roundness error
    auto it = points.lower_bound(x);
    // Check if we have an adjacent point
    if (it == points.end())
        return x; // no left adjacent point
    // Check if we are too close to left adjacent point
    if (x - it->first <= EPS)
        return it->first;
    // Check if we are too close to right adjacent point
    ++it;
    if (it == points.end())
        return x; // no right adjacent point
    if (it->first - x <= EPS)
        return it->first;
    // Otherwise return given value
    return x;
}

discrete_function operator-(discrete_function &f1, discrete_function &f2) {
    discrete_function result;
    for (auto it = f1.points.begin(); it != f1.points.end(); ++it) {
        result.points[it->first] = f1.points[it->first] - f2.points[it->first];
    }
    return result;
}


#endif // DIPLOMA__DISCRETE_FUNCTION_HPP
