#include "showData.h"



showData::showData(QWidget *parent)
	: QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint); // 设置无边框
    // 添加菜单项
    m_contextMenu.addAction("最小化", this, &showData::minimize);
    m_contextMenu.addAction("最大化", this, &showData::maximize);
    m_contextMenu.addAction("退出", this, &showData::closeWindow);
    ui.setupUi(this);
    

}

showData::~showData()
{}

void showData::initiShow()
{
    ui.tableView->setStyleSheet("selection-background-color:skyblue; selection-color: white;QTableView QCornerHeader::section { background-color: skyblue; }"); //设置tableWidget QSS样式表，背景为红色，字体为白色
    //ui.tableView->hideColumn(0);	//隐藏第一列
    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//一次选一行
    ui.tableView->setFocusPolicy(Qt::NoFocus);	//去掉虚线框
    // ui.tableView->setSortingEnabled(true);	//增加表头排序功能

    ui.tableView->horizontalHeader()->setFixedHeight(30);    //固定列头高度为30像素
    ui.tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");   //设置tableWidget列头QSS样式表，背景为天蓝
   ui.tableView->verticalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
  //  ui.tableView->setStyleSheet("QTableView QCornerHeader::section { background-color: skyblue; }");



    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表头拉伸
    ui.tableView->horizontalHeader()->setHighlightSections(false);       //选中列头不在高亮

   // ui.tableView->verticalHeader()->hide();//隐藏行头
    //   ui.tableView->verticalHeader()->setHighlightSections(false);         //选中行头不在高亮

    // 获取QTableView对象
    QTableView* tableView = ui.tableView;

    // 创建模型
    QStandardItemModel* model = new QStandardItemModel(this);

    // 设置行数、列数
    int rowCount = 8; // 例如，5行
    int columnCount = 5; // 例如，3列
    model->setRowCount(rowCount);
    model->setColumnCount(columnCount);

    // 填充数据
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; ++column) {
            QString data = QString("Row %1, Column %2").arg(row).arg(column);
            model->setItem(row, column, new QStandardItem(data));
        }
    }

    // 将模型设置到TableView中
    tableView->setModel(model);
}


void showData::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void showData::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void showData::contextMenuEvent(QContextMenuEvent* event)
{
    m_contextMenu.exec(event->globalPos());
}


void showData::minimize()
{
    this->showMinimized();
}

void showData::maximize()
{
    if (this->isMaximized())
        this->showNormal();
    else
        this->showMaximized();
}

void showData::closeWindow()
{
    this->close();
}
