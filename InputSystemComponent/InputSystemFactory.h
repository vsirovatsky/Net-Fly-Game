#pragma once

#include "InputSystemAbstractManager.h"
#include "InputSystemManager.h"

namespace inputsystem {

	class InputSystemFactory 
	{
	public:
		static InputSystemAbstractManager * createInputSystemManager()
		{
			return new InputSystemManager();
		}
	};

}