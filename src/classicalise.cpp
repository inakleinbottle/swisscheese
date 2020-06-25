

#include "include/swisscheese.hpp"


namespace swisscheese {
namespace classicalise {


template<class DISK>
DISK combine_disks(const DISK &d1, const DISK &d2, 
    typename DISK::distfun dist, 
    typename DISK::combinefun combinefun) 
{
    typedef Disk_t::Centre Centre_t;
    typedef typename Disk_t::distfun;

    double distance = dist(d1, d2);

    double r = (distance + d1.radius + d2.radius) / 2.0;
    double coeff = (r - d1.radius) / distance;
    
    Centre_t new_centre = combinefun(d1, d2, coeff);

    return DISK {new_center, r};
}



}  // end classicalise
}  // End swisscheese