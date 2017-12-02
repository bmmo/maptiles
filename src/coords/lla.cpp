// maptiles
#include <coords/lla.h>
#include <tools/math.h>

// C++ STL
#include <utility>

using namespace maptiles;
using namespace coords;

lla::lla(double lat, double lon, double alt) :
	ll(lat, lon),
	m_alt(alt) {
}

lla::lla(const ll& other, double alt /* = 0.0 */) :
	ll(other),
	m_alt(alt) {
}

