#pragma once
#include "Node.h"
#include "../lib/Symbol.h"


namespace Circuit
{
	class TwoGateNode : public Node
	{
		public:
			TwoGateNode() { symbol = NULL; }
			
			void setGateA(const double2 & v);
			void setGateB(const double2 & v);
			const double2 & getGateA() const { return gateA; }
			const double2 & getGateB() const { return gateB; }
			
			lib::Symbol * symbol;
			
		private:
			double2 gateA, gateB;

		protected:
			void generateGeometry();
	};
}
