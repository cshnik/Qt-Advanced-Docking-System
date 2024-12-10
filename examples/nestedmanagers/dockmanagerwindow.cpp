#include "dockmanagerwindow.h"
#include <QTableWidget>
#include <QPlainTextEdit>
#include <DockAreaWidget.h>

using namespace ads;

CDockManagerWindow::CDockManagerWindow(const QString& name, QWidget* parent) : CDockWidget(name, parent)
{
    DockManager = new CDockManager(this);
    setWidget(DockManager);

    initContent();
}

CDockManagerWindow::~CDockManagerWindow()
{
    delete DockManager;
    DockManager = nullptr;
}


void CDockManagerWindow::showEvent(QShowEvent* event)
{
  CDockWidget::showEvent(event);
  DockManager->show();
}

void CDockManagerWindow::hideEvent(QHideEvent* event)
{
  DockManager->hideManagerAndFloatingWidgets();
  CDockWidget::hideEvent(event);
}

QString CDockManagerWindow::formatDockName(const QString& dockName) const
{
    return QString("%1: %2").arg(windowTitle()).arg(dockName);
}

void CDockManagerWindow::initContent()
{
    // Set central widget
    QPlainTextEdit* w = new QPlainTextEdit();
    w->setPlaceholderText("This is the central editor. Enter your text here.");
    CDockWidget* CentralDockWidget = new CDockWidget("CentralWidget");
    CentralDockWidget->setWidget(w);
    auto* CentralDockArea = DockManager->setCentralWidget(CentralDockWidget);
    CentralDockArea->setAllowedAreas(DockWidgetArea::OuterDockAreas);

    // create other dock widgets
    QTableWidget* table = new QTableWidget();
    table->setColumnCount(3);
    table->setRowCount(10);
    CDockWidget* TableDockWidget = new CDockWidget(formatDockName("Table 1"));
    TableDockWidget->setWidget(table);
    TableDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    TableDockWidget->resize(250, 150);
    TableDockWidget->setMinimumSize(200,150);
    auto TableArea = DockManager->addDockWidget(DockWidgetArea::LeftDockWidgetArea, TableDockWidget);

    table = new QTableWidget();
    table->setColumnCount(5);
    table->setRowCount(1020);
    TableDockWidget = new CDockWidget(formatDockName("Table 2"));
    TableDockWidget->setWidget(table);
    TableDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    TableDockWidget->resize(250, 150);
    TableDockWidget->setMinimumSize(200,150);
    DockManager->addDockWidget(DockWidgetArea::BottomDockWidgetArea, TableDockWidget, TableArea);

    QTableWidget* propertiesTable = new QTableWidget();
    propertiesTable->setColumnCount(3);
    propertiesTable->setRowCount(10);
    CDockWidget* PropertiesDockWidget = new CDockWidget(formatDockName("Properties"));
    PropertiesDockWidget->setWidget(propertiesTable);
    PropertiesDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    PropertiesDockWidget->resize(250, 150);
    PropertiesDockWidget->setMinimumSize(200,150);
    DockManager->addDockWidget(DockWidgetArea::RightDockWidgetArea, PropertiesDockWidget, CentralDockArea);
}
