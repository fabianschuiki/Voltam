#pragma once

#include "vector2d.h"
#include <gtkmm.h>
#include <boost/shared_ptr.hpp>


namespace Voltam {
	namespace Geometry {
		class BezierPath {
			
			//Operations
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
			
			typedef std::vector< boost::shared_ptr<IOperation> > Operations;
			
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
		};
	}
}
