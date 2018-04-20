#pragma once

#include <GL/glew.h>
#include "../../Math/Math.h"
#include <vector>

namespace kodi {
	namespace graphics {

		class Renderable2D;

		class Renderer2D {

		protected:

			// Manakkikkada Stack endhuku?
			std::vector<math::mat4> transformationStack;
			const math::mat4* transformationStackBack;

		protected:

			Renderer2D()
			{
				transformationStack.push_back(math::mat4::identity());
				transformationStackBack = &transformationStack.back();
			}

		public:

			void PushToTransformationStack(const math::mat4& _matrix, bool _override = false)
			{
				if ( _override)
				{
					transformationStack.push_back(_matrix);
				}else
				{
					transformationStack.push_back(*transformationStackBack * _matrix);
				}
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