// This file is part of Dust Racing (DustRAC).
// Copyright (C) 2011 Jussi Lind <jussi.lind@iki.fi>
//
// DustRAC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// DustRAC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DustRAC. If not, see <http://www.gnu.org/licenses/>.

#include "../common/config.hpp"
#include "mainwindow.hpp"
#include "aboutdlg.hpp"
#include "game.hpp"

#include <QAction>
#include <QApplication>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QMenu>
#include <QMenuBar>

#include <MCLogger>

MainWindow * MainWindow::m_instance = nullptr;

MainWindow::MainWindow(int hRes, int vRes, bool fullScreen)
  : m_aboutDlg(new AboutDlg(this))
{
    if (!m_instance)
    {
        m_instance = this;
    }
    else
    {
        qFatal("MainWindow already instantiated!");
    }

    setWindowTitle(QString(Config::Game::GAME_NAME) + " " + Config::Game::GAME_VERSION);
    setWindowIcon(QIcon(":/logo.png"));

    if (!fullScreen)
    {
        // Set window size & disable resize
        resize(hRes, vRes);
        setMinimumSize(hRes, vRes);
        setMaximumSize(hRes, vRes);

        // Try to center the window.
        QRect geometry(QApplication::desktop()->availableGeometry());
        move(geometry.width() / 2 - width() / 2, geometry.height() / 2 - height() / 2);
    }
}

MainWindow * MainWindow::instance()
{
    return MainWindow::m_instance;
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    event->accept();
    emit closed();
    Game::instance().exitGame();
}
