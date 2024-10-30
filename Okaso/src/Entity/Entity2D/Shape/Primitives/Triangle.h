#pragma once
#include "../Shape.h"

namespace shape
{
	class EXPORT Triangle : public Shape
	{
	public:
		/// <summary>
		/// Create a new Triangle
		/// </summary>
		Triangle();

		/// <summary>
		/// Destroy the Triangle
		/// </summary>
		~Triangle();

		/// <summary>
		/// Draw the Triangle
		/// </summary>
		void Draw() override;
	
	private:
		unsigned int index[3];
	};
}

