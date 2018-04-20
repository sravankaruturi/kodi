#pragma once

#include <deque>
#include "Renderer2D.h"
#include "../Renderables/StaticSprite.h"

namespace kodi {

	using namespace math;

	namespace graphics {

		class Simple2DRenderer : public Renderer2D {

		private:
			std::deque<const StaticSprite*> renderQueue;

		public:
			void Submit(const Renderable2D* _renderable) override;
			void Flush() override;

		};

	}

}