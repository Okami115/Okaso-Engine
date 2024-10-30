#pragma once
#include "../Shape.h"

namespace shape
{
	class EXPORT Rectangle : public Shape
	{
	public:
		/// <summary>
		/// Create a new Rectangle
		/// </summary>
		Rectangle();

		/// <summary>
		/// Destroy Rectangle
		/// </summary>
		~Rectangle();

		/// <summary>
		/// Draw a new Rectangle
		/// </summary>
		void Draw() override;
	
	private:
		unsigned int index[6];
		float color[3];
	
	};

}
