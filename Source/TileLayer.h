#pragma once

#include "Graphics/Layers/Layer.h"
#include "Graphics/Renderers/BatchRenderer2D.h"

class TileLayer : public kodi::graphics::Layer
{
public:
	TileLayer(kodi::graphics::Shader * _shader);
	~TileLayer();
};

