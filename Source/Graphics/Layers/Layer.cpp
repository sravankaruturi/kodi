﻿#include "Layer.h"
#include "../Renderers/BatchRenderer2D.h"

namespace kodi
{
	namespace graphics
	{
		Layer::Layer(Renderer2D* _renderer, Shader* _shader, mat4 _projectionMatrix)
			: renderer2D(_renderer), shader(_shader), projectionMatrix(_projectionMatrix)
		{
			shader->Enable();
			shader->setMat4("pr_matrix", projectionMatrix);

			GLint tex_ids[RENDERER_MAX_TEXTURES];
			for ( auto i = 0 ; i < RENDERER_MAX_TEXTURES ; i++)
			{
				tex_ids[i] = i;
			}
			shader->SetIntArray("textures",  RENDERER_MAX_TEXTURES, tex_ids);

			shader->Disable();
		}

		Layer::~Layer()
		{
			delete renderer2D;

			for (auto& renderable : renderables)
			{
				delete renderable;
			}
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


