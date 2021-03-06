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

#include "AnnotationItemFactoryTest.h"

void AnnotationItemFactoryTest::initTestCase()
{
	QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, QStringLiteral("/tmp"));
}

void AnnotationItemFactoryTest::cleanupTestCase()
{
	QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, QStringLiteral("$HOME/.config"));
}

void AnnotationItemFactoryTest::TestCreate_Should_CreateItemAtProvidedPosition()
{
	QPointF position(10, 10);
	ToolTypes tool = ToolTypes::Line;
	auto config = new Config;
	config->setToolWidth(0, tool);
	AnnotationItemFactory itemFactory(config);

	auto item = itemFactory.create(position, tool);
	item->addPoint(QPoint(20, 20));

	QCOMPARE(item->position(), position);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnNullPtrForUnknownType()
{
	AnnotationItemFactory itemFactory(new Config);

	auto item = itemFactory.create(QPoint(0, 0), (ToolTypes) 13);

	QVERIFY(item == nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationLine_When_TypeIsLine()
{
	AnnotationItemFactory itemFactory(new Config);

	auto item = itemFactory.create(QPoint(0, 0), ToolTypes::Line);

	auto result = dynamic_cast<AnnotationLine *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationArrow_When_TypeIsArrow()
{
	AnnotationItemFactory itemFactory(new Config);

	auto item = itemFactory.create(QPoint(0, 0), ToolTypes::Arrow);

	auto result = dynamic_cast<AnnotationArrow *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationRect_When_TypeIsRect()
{
	AnnotationItemFactory itemFactory(new Config);

	auto item = itemFactory.create(QPoint(0, 0), ToolTypes::Rect);

	auto result = dynamic_cast<AnnotationRect *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationEllipse_When_TypeIsEllipse()
{
	AnnotationItemFactory itemFactory(new Config);

	auto item = itemFactory.create(QPoint(0, 0), ToolTypes::Ellipse);

	auto result = dynamic_cast<AnnotationEllipse *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationNumber_When_TypeIsNumber()
{
	AnnotationItemFactory itemFactory(new Config);

	auto item = itemFactory.create(QPoint(0, 0), ToolTypes::Number);

	auto result = dynamic_cast<AnnotationNumber *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestClone_Should_ReturnNewItemOfSameType()
{
	QPointF position(10, 10);
	ToolTypes tool = ToolTypes::Line;
	auto config = new Config;
	config->setToolWidth(0, tool);
	AnnotationItemFactory itemFactory(config);
	auto item = itemFactory.create(position, tool);
	item->addPoint(QPoint(20, 20));

	auto clonedItem = itemFactory.clone(item);

	QVERIFY(clonedItem != item);
	QCOMPARE(clonedItem->toolType(), item->toolType());
}

void AnnotationItemFactoryTest::TestClone_Should_IncrementZValueForClonedItem()
{
	QPointF position(10, 10);
	ToolTypes tool = ToolTypes::Line;
	auto config = new Config;
	config->setToolWidth(0, tool);
	AnnotationItemFactory itemFactory(config);
	auto item = itemFactory.create(position, tool);
	item->addPoint(QPoint(20, 20));

	auto clonedItem = itemFactory.clone(item);

	QVERIFY(clonedItem->zValue() > item->zValue());
}

QTEST_MAIN(AnnotationItemFactoryTest);
