#ifndef _INCLUDE_IO_PNG_H_
#define _INCLUDE_IO_PNG_H_

// C++ STL
#include <cstdint>

namespace maptiles {
namespace io {

class png {

public:

	static uint8_t* load(const char* fname, int &width, int &height);
	static bool     save(const char* fname, const uint8_t* buffer, int width, int height);

};

}
}


#endif
