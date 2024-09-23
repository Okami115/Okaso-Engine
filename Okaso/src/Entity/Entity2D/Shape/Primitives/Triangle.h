#pragma once
#include "../Shape.h"

namespace shape
{
	class EXPORT Triangle : public Shape
	{
	public:
		Triangle();
		~Triangle();
		void Draw() override;
	
	private:
		unsigned int index[3];
	};
}

