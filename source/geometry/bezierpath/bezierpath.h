#pragma once

#include <gtkmm.h>

#include "../../smartpointer.h"
#include "../vector2d.h"
#include "../rect.h"


namespace Voltam {
	namespace Geometry {
		class BezierPath {
			/**
			 * Inner Classes
			 */
		public:
			class Invocation;
			
			
			/**
			 * Operations
			 */
		public:
			struct IOperation {
				typedef enum {
					MoveTo,
					LineTo,
					CurveTo,
					Close
				} Type;
				virtual void execute(const Cairo::RefPtr<Cairo::Context> & cr) const = 0;
				virtual const Type getType() const = 0;
			};
			
			struct MoveToOperation : public IOperation {
				const Type getType() const { return MoveTo; }
				double2 p;
				void execute(const Cairo::RefPtr<Cairo::Context> & cr) const;
			};
			struct LineToOperation : public IOperation {
				const Type getType() const { return LineTo; }
				double2 p;
				void execute(const Cairo::RefPtr<Cairo::Context> & cr) const;
			};
			struct CurveToOperation : public IOperation {
				const Type getType() const { return CurveTo; }
				double2 c1;
				double2 c2;
				double2 p;
				void execute(const Cairo::RefPtr<Cairo::Context> & cr) const;
			};
			struct CloseOperation : public IOperation {
				const Type getType() const { return Close; }
				void execute(const Cairo::RefPtr<Cairo::Context> & cr) const;
			};
			
			typedef std::vector< SmartPointer<IOperation> > Operations;
			
		private:
			Operations operations;
			
		public:
			const Operations & getOperations() const;
			
			/**
			 * Adds the corresponding operation to the path which will yield the equivalent cairo
			 * operation when executed.
			 */
			void moveTo(double2 point);
			void lineTo(double2 point);
			void curveTo(double2 point, double2 controlPoint1, double2 controlPoint2);
			void close();
			
			/**
			 * Executes the cairo commands that will generate this path inside the given cairo
			 * context.
			 */
			void execute(const Cairo::RefPtr<Cairo::Context> & cr) const;
			
			/**
			 * Convenience wrappers around the path operation functions.
			 */
			void moveTo(double x, double y);
			void lineTo(double x, double y);
			void curveTo(double x, double y, double c1x, double c1y, double c2x, double c2y);
			
			void rect(const rectd & r);
			void rect(const double2 & origin, const double2 & size);
			void rect(double x, double y, double w, double h);
		};
	}
}

#include "invocation.h"

