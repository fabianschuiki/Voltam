#pragma once
#include "Node.h"
#include "../lib/Symbol.h"


namespace Circuit
{
	class TwoGateNode : public Node
	{
		public:
			TwoGateNode() { symbol = NULL; }
			
			void setGateA(const Vector & v);
			void setGateB(const Vector & v);
			const Vector & getGateA() const { return gateA; }
			const Vector & getGateB() const { return gateB; }
			
			lib::Symbol * symbol;
			
		private:
			Vector gateA, gateB;

		protected:
			void generateGeometry();
	};
}
