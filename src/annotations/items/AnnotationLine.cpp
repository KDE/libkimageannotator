/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "AnnotationLine.h"

namespace kImageAnnotator {

AnnotationLine::AnnotationLine(const QPointF &startPosition, AnnotationProperties *properties) : AbstractAnnotationLine(startPosition, properties)
{
}

AnnotationLine::AnnotationLine(const AnnotationLine &other) : AbstractAnnotationLine(other)
{

}

ToolTypes AnnotationLine::toolType() const
{
	return ToolTypes::Line;
}

void AnnotationLine::updateShape()
{
	QPainterPath path(mLine->p1());
	path.lineTo(mLine->p2());
	setShape(path);
}

} // namespace kImageAnnotator
