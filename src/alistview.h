#ifndef ALISTVIEW_H
#define ALISTVIEW_H

#include <QFrame>
#include <QVector>

namespace Ui {
class AListView;
}

class AListView : public QFrame
{
	Q_OBJECT

public:
	explicit AListView(QWidget *parent = 0);
	~AListView();

	void clear();
	int rowCount();
	void setRowCount(int iRowCount);

private:
	Ui::AListView *ui;

	int m_iRowCount;

	int m_iShowCount;
	int m_iTopRow;
	int m_iScrollPos;

	QString getLineNoText(int i);
	QString getText(int i);
	QColor getColor(int i);
	void drawListView();

	void updateTopRow();
	void updateScrollPos();

	void resizeEvent(QResizeEvent *event);

private slots:
	void on_verticalScrollBar_valueChanged(int value);
	void on_listView_clicked(const QModelIndex &index);
};

#endif // ALISTVIEW_H
