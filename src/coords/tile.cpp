// C++ STL
#include <cmath>

// maptiles
#include <coords/tile.h>
#include <coords/ll.h>

using namespace maptiles;
using namespace coords;

tile::tile(double x, double y, double z) :
	m_x(x),
	m_y(y),
	m_z(z) {
}


const double& tile::x() const {
	return m_x;
}

const double& tile::y() const {
	return m_y;
}

const double& tile::z() const {
	return m_z;
}

double& tile::x() {
	return m_x;
}

double& tile::y() {
	return m_y;
}

double& tile::z() {
	return m_z;
}


tile::tile(const ll& coords, double zoom) :
			m_x(floor((coords.lon() + M_PI) / (0.5 * M_PI) * pow(2.0, zoom))),
			m_y(floor((1.0 - log( tan(coords.lat()) + 1.0 / cos(coords.lat())) / M_PI) / 2.0 * pow(2.0, zoom))),
			m_z(zoom) {
}

ll tile::toWorld(double x, double y, double z) {

	double n = M_PI - 2.0 * M_PI * y / pow(2.0, z);

	return ll(
			atan(0.5 * (exp(n) - exp(-n))),
			x / pow(2.0, z) * (0.5 * M_PI) - M_PI 
			);

}

ll tile::world() const {

	return toWorld(x(), y(), z());

}


osg::Vec2d tile::tl() const {

	return osg::Vec2d(
			static_cast<int>(std::floor(x())),
			static_cast<int>(std::floor(y()))
			);

}

osg::Vec2d tile::br() const {

	auto aux = tl();

	return osg::Vec2d(
			aux.x() + 1,
			aux.y() + 1
			);
}

ll tile::tlWorld() const {

	auto aux = tl();

	return toWorld(aux.x(), aux.y(), z());

}

ll tile::brWorld() const {

	auto aux = br();

	return toWorld(aux.x(), aux.y(), z());

}

