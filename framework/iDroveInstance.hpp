// an interface that is used in App and Debugger to make debugger behave like app

#pragma once

namespace Drove {
	class Instance {
	private:

	public:
		virtual void resizeFramebuffer(int width, int height) = 0;
		virtual void run() = 0;
	};
}
