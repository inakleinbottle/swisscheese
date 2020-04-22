#include <vector>
#include <cstddef>
#include <numeric>

using std::vector;

template <class POINT, class RADIUS>
class Disk {
    public:
    typedef RADIUS radius_t;
    typedef POINT point_t;

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
        return buffer[i];
    }

    inline radius_t radius_sum() const {
        return std::accumulate(buffer.begin(), buffer.end(), radius_t(0));
    }

    inline radius_t discrepancy() const {
        return outer_disk.radius() - radius_sum();
    }


    private:
    disk_t outer_disk; 
    vector<disk_t> buffer;
};