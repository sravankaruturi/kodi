#pragma once
#include "Renderable2D.h"

#include <GL/glew.h>
#include "../Math/Math.h"

namespace kodi {
	namespace graphics {

		class Renderer2D {

		protected:

			// Manakkikkada Stack endhuku?
			std::vector<mat4> transformationStack;
			const mat4* transformationStackBack;

		protected:

			Renderer2D()
			{
				transformationStack.push_back(mat4::identity());
				transformationStackBack = &transformationStack.back();
			}

		public:

			void PushToTransformationStack(const mat4& _matrix)
			{
				transformationStack.push_back(_matrix);
				transformationStackBack = &transformationStack.back();
			}

			void PopFromTransformationStack()
			{
				transformationStack.pop_back();
				transformationStackBack = &transformationStack.back();
			}

			virtual void Submit(const Renderable2D* _renderable) = 0;
			virtual void Flush() = 0;

			// Ivi Implement Cheyyakapoyinaa Simple2DRendererki pedhdha nashtam ledhu.
			virtual void Begin() {}
			virtual void End() {}

		};

	}
}