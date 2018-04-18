#pragma once

#include "Renderer2D.h"
#include <deque>

namespace kodi {

	using namespace math;

	namespace graphics {

		class Simple2DRenderer : public Renderer2D {

		private:
			std::deque<const Renderable2D*> renderQueue;

		public:
			void Submit(const Renderable2D* _renderable) override;
			void Flush() override;

		};

	}

}