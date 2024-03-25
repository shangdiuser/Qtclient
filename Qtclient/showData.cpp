#include "showData.h"



showData::showData(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint); // 设置无边框
    // 添加菜单项
    m_contextMenu.addAction("最小化", this, &showData::minimize);
    m_contextMenu.addAction("最大化", this, &showData::maximize);
    m_contextMenu.addAction("退出", this, &showData::closeWindow);
    ui.setupUi(this);
    connect(ui.pushButton, &QPushButton::clicked, this, &showData::initiShow);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &showData::switchWindows);
}

showData::~showData()
{}

void showData::switchWindows()
{

    showOne* showone = new showOne();
    showone->showInfo();
    showone->show();
    this->close();
}


void showData::initiShow()
{
    QString id = ui.lineEdit_2->text();
    QString name = ui.lineEdit->text();
    QByteArray buf = handle.allInfo(id, name);

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(buf, &parseError);
    if (parseError.error == QJsonParseError::NoError) {
        if (jsonDoc.isArray()) {
            QJsonArray jsonArray = jsonDoc.array();

            // 创建一个 QStandardItemModel 作为表格的数据模型
            QStandardItemModel* model = new QStandardItemModel(jsonArray.size(), 5); // 假设有5列

            // 设置表头
            model->setHorizontalHeaderLabels({ "员工编号", "姓名","职位", "部门", "上班时间", "是否迟到" });

            // 填充数据
            int row = 0;
            for (const auto& value : jsonArray) {
                if (value.isObject()) {
                    QJsonObject jsonObject = value.toObject();

                    // 获取员工信息
                    QString employeeId = jsonObject.value("employee_id").toString();
                    QString name = jsonObject.value("name").toString();
                    QString position = jsonObject.value("position").toString();
                    QString department = jsonObject.value("department").toString();
                    // 将ISO 8601格式的时间转换为QDateTime对象
                    QDateTime dateTime = QDateTime::fromString(jsonObject.value("punch_in_time").toString(), Qt::ISODate);

                    // 将QDateTime对象格式化为指定格式的字符串
                    QString formattedDateTime = dateTime.toString("yyyy-MM-dd HH:mm:ss");


                    QString punchInTime = formattedDateTime;
                    QString isLate = jsonObject.value("is_late").toString();

                    // 在模型中设置数据
                    model->setItem(row, 0, new QStandardItem(employeeId));
                    model->setItem(row, 1, new QStandardItem(name));
                    model->setItem(row, 2, new QStandardItem(position));
                    model->setItem(row, 3, new QStandardItem(department));
                    model->setItem(row, 4, new QStandardItem(punchInTime));
                    model->setItem(row, 5, new QStandardItem(isLate));

                    ++row;
                }
            }

            // 获取QTableView对象
            QTableView* tableView = ui.tableView;
            ui.tableView->resizeColumnsToContents();
            tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
            //// 设置列宽
            tableView->setColumnWidth(0, 100); // 第一列的宽度为100
            tableView->setColumnWidth(1, 100); // 第二列的宽度为100
            tableView->setColumnWidth(2, 100); // 第三列的宽度为100
            tableView->setColumnWidth(3, 150); // 第四列的宽度为150，这里设置的是上班时间的宽度，你可以根据需要调整
            tableView->setColumnWidth(4, 100); // 第五列的宽度为100

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

            ui.tableView->verticalHeader()->hide();//隐藏行头
            //   ui.tableView->verticalHeader()->setHighlightSections(false);         //选中行头不在高亮

            tableView->setModel(model);

            //  tableView->resize(600, 400); // 设置表格大小
            tableView->show();
        }
        else {
            qDebug() << "Invalid JSON format: not an array";
        }
    }
    else {
        qDebug() << "JSON parse error:" << parseError.errorString();
    }
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
