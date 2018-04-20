#include "Group.h"

namespace kodi
{
	namespace graphics
	{
		Group::Group()
		{

		}

		void Group::SubmitToRenderer(Renderer2D* _renderer) const
		{
			_renderer->PushToTransformationStack(transformationMatrix);
			for(const auto iterator : renderables)
			{
				iterator->SubmitToRenderer(_renderer);
			}
			_renderer->PopFromTransformationStack();
		}

		void Group::AddRenderable(Renderable2D* _renderable)
		{

			renderables.push_back(_renderable);

		}
	}
}