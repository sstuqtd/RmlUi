/*
 * Copyright (c) 2006 - 2008
 * Wandering Monster Studios Limited
 *
 * Any use of this program is governed by the terms of Wandering Monster
 * Studios Limited's Licence Agreement included with this program, a copy
 * of which can be obtained by contacting Wandering Monster Studios
 * Limited at info@wanderingmonster.co.nz.
 *
 */

#include "DecoratorDefender.h"
#include <RmlUi/Core/Math.h>
#include <RmlUi/Core/Element.h>
#include <RmlUi/Core/Texture.h>
#include <ShellOpenGL.h>

DecoratorDefender::~DecoratorDefender()
{
}

bool DecoratorDefender::Initialise(const Rml::String& image_source, const Rml::String& image_path)
{
	image_index = LoadTexture(image_source, image_path);
	if (image_index == -1)
	{
		return false;
	}

	return true;
}

/// Called on a decorator to generate any required per-element data for a newly decorated element.
Rml::DecoratorDataHandle DecoratorDefender::GenerateElementData(Rml::Element* RMLUI_UNUSED_PARAMETER(element)) const
{
	RMLUI_UNUSED(element);

	return Rml::Decorator::INVALID_DECORATORDATAHANDLE;
}

// Called to release element data generated by this decorator.
void DecoratorDefender::ReleaseElementData(Rml::DecoratorDataHandle RMLUI_UNUSED_PARAMETER(element_data)) const
{
	RMLUI_UNUSED(element_data);
}

// Called to render the decorator on an element.
void DecoratorDefender::RenderElement(Rml::Element* element, Rml::DecoratorDataHandle RMLUI_UNUSED_PARAMETER(element_data)) const
{
	RMLUI_UNUSED(element_data);

	Rml::Vector2f position = element->GetAbsoluteOffset(Rml::Box::PADDING);
	Rml::Vector2f size = element->GetBox().GetSize(Rml::Box::PADDING);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, (GLuint) GetTexture(image_index)->GetHandle(element->GetRenderInterface()));
	Rml::Colourb colour = element->GetProperty< Rml::Colourb >("color");
	glColor4ubv(colour);
	glBegin(GL_QUADS);

		glVertex2f(position.x, position.y);
		glTexCoord2f(0, 1);

		glVertex2f(position.x, position.y + size.y);
		glTexCoord2f(1, 1);

		glVertex2f(position.x + size.x, position.y + size.y);
		glTexCoord2f(1, 0);

		glVertex2f(position.x + size.x, position.y);
		glTexCoord2f(0, 0);

	glEnd();
	glColor4ub(255, 255, 255, 255);
}
