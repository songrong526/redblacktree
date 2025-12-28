#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>

const int RADIUS = 20;
const int DY = 60;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_insertBtn_clicked() {
    int val = ui->lineEdit->text().toInt();
    tree.insert(val);
    updateVisualizer();
    ui->lineEdit->clear();
}

void MainWindow::on_clearBtn_clicked() {
    tree.clear_tree();
    updateVisualizer();
}
void MainWindow::on_deleteBtn_clicked() {
    QString text = ui->lineEdit->text();
    if (text.isEmpty()) return;

    int val = text.toInt();

    // 1. 调用你现有的“重建式”删除函数
    tree.deleteNode(val);

    // 2. 更新绘图
    updateVisualizer();

    // 3. 清空输入框
    ui->lineEdit->clear();
}
void MainWindow::updateVisualizer() {
    scene->clear();
    if (tree.getRoot()) {
        drawNode(tree.getRoot(), 0, 0, 200);
    }
}

void MainWindow::drawNode(shared_ptr<Node> node, qreal x, qreal y, qreal hGap) {
    if (!node) return;

    if (node->left) {
        scene->addLine(x, y, x - hGap, y + DY, QPen(Qt::black));
        drawNode(node->left, x - hGap, y + DY, hGap / 2);
    }
    if (node->right) {
        scene->addLine(x, y, x + hGap, y + DY, QPen(Qt::black));
        drawNode(node->right, x + hGap, y + DY, hGap / 2);
    }

    QColor color = node->color ? Qt::red : Qt::black;
    scene->addEllipse(x - RADIUS, y - RADIUS, RADIUS * 2, RADIUS * 2, QPen(Qt::white), QBrush(color));

    QGraphicsTextItem* text = scene->addText(QString::number(node->data));
    text->setDefaultTextColor(Qt::white);
    text->setPos(x - text->boundingRect().width()/2, y - text->boundingRect().height()/2);
}
