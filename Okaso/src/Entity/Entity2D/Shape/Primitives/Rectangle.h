#pragma once
#include "../Shape.h"

namespace shape
{
	class EXPORT Rectangle : public Shape
	{
	public:
		Rectangle();
		~Rectangle();
		void Draw() override;
	
	private:
		unsigned int index[6];
		float color[3];
	
	};

}
