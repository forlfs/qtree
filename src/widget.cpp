#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

	//m_lv = new AListView(ui->frameListView); //最大化时大小不会变
	m_lv = new AListView();
	ui->frameListView->layout()->addWidget(m_lv);
}

Widget::~Widget()
{
	delete ui;
}
