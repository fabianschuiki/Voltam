#pragma once
#include "Node.h"


namespace Circuit
{
	class TwoGateNode : public Node
	{
		public:
			void setGateA(const Vector & v);
			void setGateB(const Vector & v);
			const Vector & getGateA() const { return gateA; }
			const Vector & getGateB() const { return gateB; }
			
		private:
			Vector gateA, gateB;

		protected:
			void generateGeometry();
	};
}
