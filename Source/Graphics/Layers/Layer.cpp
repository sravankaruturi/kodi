#include "Layer.h"
#include "../Renderers/BatchRenderer2D.h"

namespace kodi
{
	namespace graphics
	{
		Layer::Layer(Renderer2D* _renderer, Shader* _shader, mat4 _projectionMatrix)
			: renderer2D(_renderer), shader(_shader), projectionMatrix(_projectionMatrix)
		{

			auto error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error : " << error << std::endl;
			}

#if KODI_THROW_EXCEPTIONS
			_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

			shader->Enable();

			error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error : " << error << std::endl;
			}

#if KODI_THROW_EXCEPTIONS
			_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

			shader->setMat4("pr_matrix", projectionMatrix);

			error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error : " << error << std::endl;
			}

#if KODI_THROW_EXCEPTIONS
			_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

			GLint tex_ids[RENDERER_MAX_TEXTURES];
			for ( auto i = 0 ; i < RENDERER_MAX_TEXTURES ; i++)
			{
				tex_ids[i] = i;
			}
			shader->SetIntArray("textures",  RENDERER_MAX_TEXTURES, tex_ids);

			error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error : " << error << std::endl;
			}

#if KODI_THROW_EXCEPTIONS
			_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

			shader->Disable();
		}

		void Layer::ClearRenderables()
		{
			// TODO: This might cause memory leaks? Deleting objects here for now. But that might cause several issues when I want to resuse the sprites?
			//for (auto& renderable : renderables)
			//{
			//	delete renderable;
			//}
			this->renderables.clear();
		}

		Layer::~Layer()
		{
			delete renderer2D;

			// This only complicates freeing up memory.
			//for (auto& renderable : renderables)
			//{
			//	delete renderable;
			//}
		}

		void Layer::Add(Renderable2D* _renderable)
		{
			renderables.push_back(_renderable);
		}

		void Layer::Render()
		{
			shader->Enable();

			renderer2D->Begin();

			for ( const Renderable2D* iterator : renderables)
			{
				// renderer2D->Submit(iterator);
				iterator->SubmitToRenderer(renderer2D);
			}

			renderer2D->End();

			renderer2D->Flush();

		}
	}
}


