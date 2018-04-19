#include "Simple2DRenderer.h"


namespace kodi {
	namespace graphics {

		void Simple2DRenderer::Submit(const Renderable2D * _renderable)
		{
			renderQueue.push_back((StaticSprite *)_renderable);
		}

		void Simple2DRenderer::Flush()
		{
			while (!renderQueue.empty()) {

				const StaticSprite* renderable = renderQueue.front();

				(renderable->GetVAO())->Bind();

				(renderable->GetIBO())->Bind();

				renderable->GetShader().setMat4("ml_matrix", math::mat4::translation(renderable->GetPosition()));
				glDrawElements(GL_TRIANGLES, renderable->GetIBO()->GetIndexCount(), GL_UNSIGNED_INT, nullptr);

				(renderable->GetIBO())->Bind();

				(renderable->GetVAO())->UnBind();

				renderQueue.pop_front();

			}
		}

	}
}