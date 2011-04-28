#pragma once

#include <vector>

#include "../../smartpointer.h"
#include "../../geometry/bezierpath/invocation.h"


namespace Voltam {
	namespace Library {
		class Symbol {
		public:
			class Terminal;
			class Signal;
			
		public:
			typedef std::vector< SmartPointer<Geometry::BezierPath::Invocation> > PathInvocations;
			typedef std::vector< SmartPointer<Terminal> > Terminals;
			
		/*private:*/
			PathInvocations pathInvocations;
			Terminals terminals;
		};
	}
}

#include "terminal.h"

