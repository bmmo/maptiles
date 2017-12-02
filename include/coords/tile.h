#ifndef _INCLUDE_COORDSTILE_H_
#define _INCLUDE_COORDSTILE_H_

// OSG
#include <osg/Vec3d>
#include <osg/Vec2d>

namespace maptiles {
namespace coords {	

// Forward Declaration
class ll;

class tile {

public:	

	tile(double x, double y, double z);
	tile(const ll& coords, double zoom);


	const double& x() const;
	const double& y() const;
	const double& z() const;
	double&       x();
	double&       y();
	double&       z();

	static ll     toWorld(double x, double y, double z);

	ll            world()   const;
	osg::Vec2d    tl()      const;
	osg::Vec2d    br()      const;
	ll            tlWorld() const;
	ll            brWorld() const;

protected:

	double m_x;
	double m_y;
	double m_z;

};

}
}

#endif
