/*
 * Copyright (c) 2015 Meltytech, LLC
 * Author: Brian Matherly <code@brianmatherly.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "scopecontroller.h"
#include "widgets/scopes/audiowaveformscopewidget.h"
#include "widgets/scopes/videowaveformscopewidget.h"
#include "docks/scopedock.h"
#include "settings.h"
#include <QDebug>
#include <QMainWindow>
#include <QMenu>

ScopeController::ScopeController(QMainWindow* mainWindow, QMenu* menu)
  : QObject(mainWindow)
{
    qDebug() << "begin";
    QMenu* scopeMenu = menu->addMenu(tr("Scopes"));
    createScopeDock<AudioWaveformScopeWidget>(mainWindow, scopeMenu);
    if (!Settings.playerGPU()) {
        createScopeDock<VideoWaveformScopeWidget>(mainWindow, scopeMenu);
    }
    qDebug() << "end";
}

void ScopeController::onFrameDisplayed(const SharedFrame& frame)
{
    emit newFrame(frame);
}

template<typename ScopeTYPE> void ScopeController::createScopeDock(QMainWindow* mainWindow, QMenu* menu)
{
    ScopeWidget* scopeWidget = new ScopeTYPE();
    ScopeDock* scopeDock = new ScopeDock(this, scopeWidget);
    scopeDock->hide();
    menu->addAction(scopeDock->toggleViewAction());
    mainWindow->addDockWidget(Qt::RightDockWidgetArea, scopeDock);
}

