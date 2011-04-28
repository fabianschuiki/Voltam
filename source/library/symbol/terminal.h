#pragma once

#include <vector>
#include <string>

#include "../../smartpointer.h"
#include "signal.h"
#include "../../geometry/vector2d.h"


namespace Voltam {
	namespace Library {
		class Symbol::Terminal {
		public:
			typedef std::vector< SmartPointer<Signal> > Signals; 
		
		public:
			std::string name;
			Signals signals;
			
			double2 root;
			double2 tip;
		};
	}
}

