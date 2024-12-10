#ifndef DOCKMANAGERWINDOW_H
#define DOCKMANAGERWINDOW_H

#include "DockManager.h"
#include "DockWidget.h"
#include <QVBoxLayout>

class CDockManagerWindow : public ads::CDockWidget
{
    Q_OBJECT

public:
    CDockManagerWindow(const QString& name, QWidget* parent = nullptr);
    virtual ~CDockManagerWindow();

private:
    ads::CDockManager* DockManager = nullptr;

    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;

    QString formatDockName(const QString& dockName) const;
    void initContent();
};

#endif // DOCKMANAGERWINDOW_H
