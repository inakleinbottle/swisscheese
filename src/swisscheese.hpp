#include <vector>
#include <cstddef>
#include <numeric>

using std::vector;

template <class POINT, class RADIUS>
class Disk {
    public:
    typedef RADIUS radius_t;
    typedef POINT point_t;
    typedef Disk<POINT, RADIUS> Self;

    typedef radius_t (*distfun)(const point_t, const point_t);

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
        return (dist(this->centre(), other.centre()) < other.radius());
    }

    inline bool inside(const Self &other, distfun dist) const {
        return (dist(this->centre(), other.centre()) <= other.radius());
    }

    inline bool contains_proper(const Self &other, distfun dist) const {
        return other.inside_proper(*this, dist);
    }

    inline bool contains(const Self &other, distfun dist) const {
        return other.inside(*this, dist);
    }

    private:
    POINT _centre;
    RADIUS _radius;
};


template <class POINT, class RADIUS> 
class SwissCheese {
    public:
    using point_t=POINT;
    using radius_t=RADIUS;
    using disk_t=Disk<POINT, RADIUS>;

    

    public:
    SwissCheese(point_t centre, radius_t radius) :
        outer_disk {centre, radius},
        buffer {}
    {}

    inline void insert(point_t centre, radius_t radius) {
        buffer.push_back(disk_t {centre, radius});
    }

    inline size_t length() const {
        return buffer.size();
    }

    inline disk_t& operator[](const size_t i) {
        if (i == 0) {
            return outer_disk;
        } else {
            return buffer[i-1];
        }   
    }

    inline radius_t radius_sum() const {
        radius_t val = radius_t(0);
        for (disk_t item : buffer ) {
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
    disk_t outer_disk; 
    vector<disk_t> buffer;
};