#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QWidgetAction>
#include <QLabel>
#include <QCalendarWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QInputDialog>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QToolBar>

#include "DockAreaWidget.h"
#include "DockAreaTitleBar.h"
#include "DockAreaTabBar.h"
#include "FloatingDockContainer.h"
#include "DockComponentsFactory.h"
#include "dockmanagerwindow.h"

using namespace ads;


CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    CDockManager::setConfigFlag(CDockManager::OpaqueSplitterResize, true);
    CDockManager::setConfigFlag(CDockManager::XmlCompressionEnabled, false);
    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);
    DockManager = new CDockManager(this);

    CDockManagerWindow* dock1 = new CDockManagerWindow("dock1", this);
    CDockAreaWidget* areaWidget = DockManager->addDockWidget(DockWidgetArea::LeftDockWidgetArea, dock1);
    ui->menuView->addAction(dock1->toggleViewAction());

    CDockManagerWindow* dock2 = new CDockManagerWindow("dock2", this);
    DockManager->addDockWidget(DockWidgetArea::CenterDockWidgetArea, dock2, areaWidget);
    ui->menuView->addAction(dock2->toggleViewAction());

    dock1->toggleView(true);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

//============================================================================
void CMainWindow::closeEvent(QCloseEvent* event)
{
    // Delete dock manager here to delete all floating widgets. This ensures
    // that all top level windows of the dock manager are properly closed
    DockManager->deleteLater();
	QMainWindow::closeEvent(event);
}


