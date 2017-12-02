// maptiles
#include <coords/ll.h>
#include <coords/lla.h>
#include <coords/tile.h>
#include <tools/math.h>

// C++ STL
#include <utility>

using namespace maptiles;
using namespace coords;

ll::ll(double lat, double lon) :
	m_lat(lat),
	m_lon(lon) {
}		

ll::ll(const tile& t) :
	ll(t.world()) {
}

ll ll::fromDeg(double lat, double lon) {
	return ll(
			lat * tools::math::torad(),
			lon * tools::math::torad()); 
}

double ll::latDeg() const {
	return lat() * tools::math::todeg();
}

double ll::lonDeg() const {
	return lon() * tools::math::todeg();
}

