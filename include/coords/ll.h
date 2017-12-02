#ifndef _INCLUDE_LLA_H_
#define _INCLUDE_LLA_H_

namespace maptiles {
namespace coords   {	

// Forward Declaration
class tile;

class ll {

public:

	ll(double lat, double lon);
	ll(const tile& t);

	static ll     fromDeg(double lat, double lon);
	
	const double& lat() const    { return m_lat; }
	const double& lon() const    { return m_lon; }
	double&       lat()          { return m_lat; }
	double&       lon()          { return m_lon; }

	double        latDeg() const;
	double        lonDeg() const;

protected:

	double m_lat;
	double m_lon;

};

}
}


#endif
