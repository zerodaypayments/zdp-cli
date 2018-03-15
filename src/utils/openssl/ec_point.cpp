#include "ec_point.h"

namespace zdp {
	namespace crypto {
		namespace openssl {
			
			ec_point::ec_point(ec_group& group) {
				pt = EC_POINT_new(group.get());
			}
			
			ec_point::~ec_point() {
				if (pt != nullptr) {
					EC_POINT_free(pt);
					pt = nullptr;
				}
			}
			
			EC_POINT* ec_point::get() {
				return pt;
			}
		
		} /* namespace openssl */
	} /* namespace crypto */
} /* namespace zdp */
