#ifndef _INCLUDE_COORDS_LLA_H_
#define _INCLUDE_COORDS_LLA_H_

// maptiles
#include <coords/ll.h>

namespace maptiles {
namespace coords   {

class lla : public ll {

public:

	lla(double lat, double lon, double alt);
	lla(const ll& other, double alt = 0.0);

	const double& alt() const { return m_alt; }
	double&       alt()       { return m_alt; }

protected:

	double m_alt;

};


}
}

#endif
