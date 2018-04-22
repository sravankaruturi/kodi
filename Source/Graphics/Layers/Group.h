#pragma once
#include "../Renderables/Renderable2D.h"

namespace kodi
{
	namespace graphics
	{
		class Group : public Renderable2D
		{

		private:
			std::vector<Renderable2D*> renderables;
			math::mat4 transformationMatrix;

		public:

			Group();

			~Group();

			void SubmitToRenderer(Renderer2D* _renderer) const override;

			void SetTransformMatrix(const mat4& _transformMatrix) { transformationMatrix = _transformMatrix; };

			void AddRenderable(Renderable2D* _renderable);

		};
	}
}
