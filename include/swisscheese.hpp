#ifndef __SWISSCHEESE_HEADER__
#define __SWISSCHEESE_HEADER__


#include <vector>
#include <cstddef>
#include <numeric>
#include <iostream>

using std::vector;

namespace swisscheese {



template <class POINT, typename RADIUS = double>
class Disk {
    public:
    typedef POINT point_t;
    typedef Disk<POINT> Self;
    typedef RADIUS radius_t;

    typedef radius_t (*distfun)(const point_t&, const point_t&);
    typedef void (*combinefun)(point_t&, const point_t&, radius_t);


    Disk();
    Disk(point_t centre, radius_t radius) : 
        _centre{centre}, 
        _radius{radius} 
    {}

    inline radius_t radius() const {
        return _radius;
    }

    inline point_t centre() const {
        return _centre;
    }

    inline point_t overlap(const Self &other, distfun dist) const {
        return dist(this->_centre, other.centre()) - this->_radius - other.radius();
    }

    inline bool inside_proper(const Self &other, distfun dist) const {
        return (dist(this->centre(), other.centre()) < (other.radius() - this->_radius));
    }

    inline bool inside(const Self &other, distfun dist) const {
        return (dist(this->centre(), other.centre()) <= (other.radius() - this->_radius));
    }

    inline bool contains_proper(const Self &other, distfun dist) const {
        return other.inside_proper(*this, dist);
    }

    inline bool contains(const Self &other, distfun dist) const {
        return other.inside(*this, dist);
    }

    inline bool operator==(const Self &other) const {
        return (this->_centre == other.centre()
                && this->_radius == other.radius());
    }

    private:
    POINT _centre;
    RADIUS _radius;
};

template<class POINT, typename RADIUS = double>
std::ostream &operator<<(std::ostream &os, Disk<POINT, RADIUS> &disk) {
    POINT c = disk.centre();
    RADIUS r = disk.radius();
    return os << "Disk(" << c << ", " << r << ")";
}


template <class POINT, typename RADIUS = double> 
class SwissCheese {
    public:
    typedef POINT point_t;
    typedef RADIUS radius_t;
    typedef Disk<POINT, RADIUS> Disk_t;

    typedef typename Disk_t::combinefun combine_func;
    typedef typename Disk_t::distfun distance_func;

    public:
    SwissCheese(point_t centre, radius_t radius, combine_func combine, distance_func dist)
        : outer_disk {centre, radius},
          _combine {combine},
          _dist {dist},
          buffer {}
    {}

    inline void insert(point_t centre, radius_t radius) {
        buffer.push_back(Disk_t {centre, radius});
    }

    inline size_t length() const {
        return buffer.size();
    }

    inline Disk_t& operator[](const size_t i) {
        if (i == 0) {
            return outer_disk;
        } else {
            return buffer[i-1];
        }   
    }

    inline radius_t radius_sum() const {
        radius_t val = radius_t(0);
        for (Disk_t item : buffer ) {
            val += item.radius();
        }
        return val;
    }

    inline radius_t discrepancy() const {
        return outer_disk.radius() - radius_sum();
    }

    private:
    inline void reserve(const size_t i) {
        buffer.reserve(i);
    }

    inline void shrink_to_fit() {
        buffer.shrink_to_fit();
    }

    private:
    Disk_t outer_disk; 
    vector<Disk_t> buffer;

    distance_func _dist;
    combine_func _combine;
    
    
    };


namespace classicalise {
        
template<class DISK>
DISK combine_disks(
    const DISK &d1, const DISK &d2, 
    typename DISK::distfun dist, 
    typename DISK::combinefun combinefunc
) 
{
    typedef typename DISK::point_t Centre_t;
    Centre_t p1 = d1.centre();
    Centre_t p2 = d2.centre();

    double distance = dist(p1, p2);

    double r = (distance + d1.radius() + d2.radius()) / 2.0;
    double coeff = (r - d1.radius()) / distance;
    
    // updates p1
    combinefunc(p1, p2, coeff);

    return DISK {p1, r};
}
    
    
}


} // end swisscheese

#endif // multiple include guard