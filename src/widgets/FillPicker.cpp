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

#include "FillPicker.h"

FillPicker::FillPicker(const QString& name, int minLabelWidth)
{
    mFillList.append(FillTypes::NoFill);
    mFillList.append(FillTypes::Fill);
    mFillList.append(FillTypes::SameFillAsOutline);

    initGui(name, minLabelWidth);

    connect(mComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this, &FillPicker::selectionChanged);
}

FillPicker::~FillPicker()
{
    delete mLayout;
    delete mLabel;
    delete mComboBox;
}

void FillPicker::setFill(FillTypes fill)
{
    auto index = mComboBox->findData(mFillList.indexOf(fill));
    if(index != -1) {
        mComboBox->setCurrentIndex(index);
        setFillAndNotify(fill);
    }
}

void FillPicker::initGui(const QString& name, int minLabelWidth)
{
    mLayout = new QHBoxLayout(this);
    mLayout->setSpacing(0);

    mLabel = new QLabel(name + QStringLiteral(": "));
    if(minLabelWidth != -1) {
        mLabel->setMinimumWidth(minLabelWidth);
    }

    mComboBox = new QComboBox(this);

    mComboBox->addItem(tr("No Fill"), mFillList.indexOf(FillTypes::NoFill));
    mComboBox->addItem(tr("Fill"), mFillList.indexOf(FillTypes::Fill));
    mComboBox->addItem(tr("Same as Outline"), mFillList.indexOf(FillTypes::SameFillAsOutline));

    mLayout->addWidget(mLabel);
    mLayout->addWidget(mComboBox);

    setLayout(mLayout);
    setFixedSize(sizeHint());
}

void FillPicker::setFillAndNotify(FillTypes fill)
{
    mSelectedFill = fill;
    emit fillSelected(fill);
}

void FillPicker::selectionChanged()
{
    auto fill = mFillList[mComboBox->currentData().toInt()];
    setFillAndNotify(fill);
}

