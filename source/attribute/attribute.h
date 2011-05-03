#pragma once

#include <string>


namespace Voltam {
	namespace Attribute {
		class IAttribute {
		public:
			operator std::string() const { return "<unknown attribute>"; }
		};
	}
}
