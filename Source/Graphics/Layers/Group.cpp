#include "Group.h"

namespace kodi
{
	namespace graphics
	{
		Group::Group()
		{

		}

		Group::~Group()
		{
			// Manam add chesina renderablesni annitinee delete cheyyaali.
			for (auto iterator : renderables)
			{
				delete iterator;
			}
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