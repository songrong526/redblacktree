#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "redblacktree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_insertBtn_clicked();
    void on_clearBtn_clicked();

    // --- 新增：删除按钮的槽函数 ---
    void on_deleteBtn_clicked();

private:
    Ui::MainWindow *ui;
    RedBlackTree tree;
    QGraphicsScene *scene;
    void updateVisualizer();
    void drawNode(shared_ptr<Node> node, qreal x, qreal y, qreal hGap);
};
#endif
