#include "alistview.h"
#include "ui_alistview.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QBrush>
#include <QResizeEvent>
#include <QDebug>

//----------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define	N	100007
#define	TL	(1<<17)
#define	L(x)	((x)<<1)
#define	R(x)	(((x)<<1)+1)
#define	H(x,y)	(((x)+(y))>>1)
struct t{
	int i,j;
	char k;
}tree[2][TL<<1];
struct a{
	int l,r;
}a[N<<1];
struct a_{
	int l,r,c;
}a_[N];
int p[N],a__[N],n,l_,y_;
int r_;
int first[N],next[N<<1];
void init(struct t *tree,int h,int l,int r){ //o(n)
	tree[h].i=0;
	tree[h].j=0;
	tree[h].k=0;
	if(r-l==1){
		return;
	}
	init(tree,L(h),l,H(l,r));
	init(tree,R(h),H(l,r),r);
}
int update(struct t *tree,int h,int l,int r,int i,int j,int x){ //o(log(n))
	int a;
	if(r-l==j-i){
		a=tree[h].j;
		tree[h].i=x;
		tree[h].j=(j-i)*x;
		tree[h].k=1;
		return tree[h].j-a;
	}
	if(tree[h].k==1){
		tree[L(h)].i=tree[R(h)].i=tree[h].i;
		tree[L(h)].j=(H(l,r)-l)*tree[h].i;
		tree[R(h)].j=(r-H(l,r))*tree[h].i;
		tree[L(h)].k=tree[R(h)].k=1;
		tree[h].i=0;
		tree[h].k=0;
	}
	if(j<=H(l,r)){
		a=update(tree,L(h),l,H(l,r),i,j,x);
		tree[h].j+=a;
		return a;
	}
	if(i>=H(l,r)){
		a=update(tree,R(h),H(l,r),r,i,j,x);
		tree[h].j+=a;
		return a;
	}
	a=update(tree,L(h),l,H(l,r),i,H(l,r),x)+update(tree,R(h),H(l,r),r,H(l,r),j,x);
	tree[h].j+=a;
	return a;
}
void query(struct t *tree,int h,int l,int r,int i,int j){ //o(log(n))
	if(tree[h].k==1){
		r_+=(j-i)*tree[h].i;
		return;
	}
	if(r-l==j-i){
		r_+=tree[h].j;
		return;
	}
	if(j<=H(l,r)){
		query(tree,L(h),l,H(l,r),i,j);
		return;
	}
	if(i>=H(l,r)){
		query(tree,R(h),H(l,r),r,i,j);
		return;
	}
	query(tree,L(h),l,H(l,r),i,H(l,r));
	query(tree,R(h),H(l,r),r,H(l,r),j);
}
int query_(struct t *tree,int h,int l,int r,int x){ //o(log(n))
	int a;
	if(tree[h].k==1){
		a=(r-l)*tree[h].i;
	}else{
		a=tree[h].j;
	}
	if(x<=0||x>a){
		return -1;
	}
	if(r-l==1){
		return l;
	}
	if(tree[h].k==1){
		return l+x-1;
	}
	if(x<=tree[L(h)].j){
		return query_(tree,L(h),l,H(l,r),x);
	}
	return query_(tree,R(h),H(l,r),r,x-tree[L(h)].j);
}
int dfs(int i,int j,int c){ //o(n)
	int k,x;
	x=1;
	for(k=first[i];k!=-1;k=next[k]){
		if(p[a[k].r]==-1){
			p[a[k].r]=i;
			x+=dfs(a[k].r,j+x,c+1);
		}
	}
	a_[i].l=j;
	a_[i].r=j+x;
	a_[i].c=c;
	a__[j]=i;
	return x;
}
void update_i(int i,int x){ //o(log(n))
	if(a_[i].l+1<a_[i].r){
		update(tree[0],1,0,y_,a_[i].l+1,a_[i].r,x);
	}
}
int query_i(int x){ //o(log(n))
	return query_(tree[0],1,0,y_,x);
}
void update_c(int i,int x){ //o(log(n))
	update(tree[1],1,0,y_,a_[i].l,a_[i].l+1,x);
}
int query_c(int i){ //o(log(n))
	r_=0;
	query(tree[1],1,0,y_,a_[i].l,a_[i].l+1);
	return (r_==1) ? 1 : 0;
}
void update_a(int i,int x){ //o(log(n))
	update(tree[1],1,0,y_,a_[i].l,a_[i].r,x);
}
int query_a(int i){ //o(log(n))
	r_=0;
	query(tree[1],1,0,y_,a_[i].l,a_[i].r);
	return (r_==a_[i].r-a_[i].l) ? 1 : 0;
}
void cat(){
	int i;
	for(i=0;i<N;i++){
		first[i]=-1;
	}
	memset(next,0,sizeof(next));
	for(i=l_-1;i>=0;i--){
		next[i]=first[a[i].l];
		first[a[i].l]=i;
	}
	for(i=0;i<n;i++){
		p[i]=-1;
		a__[i]=0;
	}
	p[a[0].l]=a[0].l;
	dfs(a[0].l,0,0);
	for(y_=1;y_<n;y_<<=1);
	init(tree[0],1,0,y_);
	init(tree[1],1,0,y_);
	update(tree[0],1,0,y_,a_[a[0].l].l,a_[a[0].l].l+1,1);
	for(i=0;i<n;i++){
		update_i(a_[i].l,1);
	}
}
void run(){
	int i,l,r;
	FILE *fp;
	fp=fopen("tree.in","rb");
	if(fp==NULL){
		return;
	}
	fscanf(fp,"%d",&n);
	l_=0;
	for(i=0;i<n-1;i++){
		fscanf(fp,"%d%d",&l,&r);
		a[l_].l=l-1;
		a[l_].r=r-1;
		a[l_+1].l=r-1;
		a[l_+1].r=l-1;
		l_+=2;
	}
	cat();
	fclose(fp);
}
//----------------------------------------------------------------------

AListView::AListView(QWidget *parent) :
	QFrame(parent),
	ui(new Ui::AListView)
{
	ui->setupUi(this);

	m_iRowCount = 0;

	m_iShowCount = 15;

#ifdef WIN32
	QFont font = ui->listView->font();
	font.setFamily("新宋体");
	font.setPointSize(9);
	ui->listView->setFont(font);
#else
	QFont font = ui->listView->font();
	font.setFamily("文泉驿正黑");
	font.setPointSize(7);
	ui->listView->setFont(font);
#endif

	ui->listView->setEditTriggers(QListView::NoEditTriggers);
	QStandardItemModel *model = new QStandardItemModel(this);
	for(int i = 0; i < m_iShowCount; i++)
	{
		QStandardItem *item = new QStandardItem("");
		model->appendRow(item);
	}
	ui->listView->setModel(model);

	m_iTopRow = 0;
	m_iScrollPos = 0;

	run();

	r_ = 0;
	query(tree[0], 1, 0, y_, 0, n);
	setRowCount(r_);
}

AListView::~AListView()
{
	delete ui;
}

void AListView::clear()
{
	setRowCount(0);
}

int AListView::rowCount()
{
	return m_iRowCount;
}

void AListView::setRowCount(int iRowCount)
{
	m_iRowCount = iRowCount;

	updateScrollPos();
	drawListView();
}

QString AListView::getText(int i)
{
	QString sText = "";
	int j = query_i(i + 1);
	if(j == -1)
	{
		return sText;
	}
	sText = QString::number(a__[j] + 1);
	int k = a_[a__[j]].r - a_[a__[j]].l;
	sText += "(" + QString::number(k) + ")";
	if(k > 1)
	{
		r_=0;
		query(tree[0], 1, 0, y_, a_[a__[j]].l, a_[a__[j]].r);
		sText = (r_ == 1 ? "+" : "-") + sText;
	}
	QString indent = "";
	if(a_[a__[j]].c < 10)
	{
		indent = QString(" ").repeated(a_[a__[j]].c);
	}
	else
	{
		indent = QString(" ").repeated(10) + "...";
	}
	sText = indent + sText;
	int r = query_c(a__[j]);
	sText = QString(r == 0 ? "□" : "√") + " " + sText;
	r = query_a(a__[j]);
	sText = QString(r == 0 ? "□" : "√") + " " + sText;
	sText = QString::number(i) + QString(" ").repeated(6 - QString::number(i).length()) + " " + sText;
	return sText;
}

QColor AListView::getColor(int i)
{
	QColor color = Qt::white;
	int j = query_i(i + 1);
	if(j == -1)
	{
		return color;
	}
	int k = 10 - a_[a__[j]].c;
	k = k < 0 ? 0 : k;
	return QColor(210 - 10 * k, 230 - 5 * k, 250);
}

void AListView::drawListView()
{
	ui->verticalScrollBar->setVisible(m_iRowCount <= m_iShowCount ? false : true);
	ui->verticalScrollBar->setMinimum(0);
	ui->verticalScrollBar->setMaximum(m_iRowCount <= m_iShowCount ? 0 : m_iRowCount - m_iShowCount);
	if(m_iScrollPos > m_iRowCount - m_iShowCount)
	{
		m_iScrollPos = m_iRowCount <= m_iShowCount ? 0 : m_iRowCount - m_iShowCount;
		updateTopRow();
	}

	for(int i = 0, j = m_iTopRow; i < m_iShowCount; i++, j++)
	{
		QStandardItemModel *model = (QStandardItemModel *)ui->listView->model();
		model->item(i)->setText(getText(j));
		model->item(i)->setBackground(QBrush(getColor(j)));
	}

	ui->verticalScrollBar->setSliderPosition(m_iScrollPos);
}

void AListView::updateTopRow()
{
	m_iTopRow = m_iScrollPos;
}

void AListView::updateScrollPos()
{
	ui->verticalScrollBar->setVisible(m_iRowCount <= m_iShowCount ? false : true);
	ui->verticalScrollBar->setMinimum(0);
	ui->verticalScrollBar->setMaximum(m_iRowCount <= m_iShowCount ? 0 : m_iRowCount - m_iShowCount);
	if(m_iScrollPos > m_iRowCount - m_iShowCount)
	{
		m_iScrollPos = m_iRowCount <= m_iShowCount ? 0 : m_iRowCount - m_iShowCount;
		updateTopRow();
	}
}

void AListView::on_verticalScrollBar_valueChanged(int value)
{
	m_iScrollPos = value;
	updateTopRow();
	drawListView();
}

void AListView::on_listView_clicked(const QModelIndex &index)
{
	int i = m_iTopRow + index.row();
	qDebug() << i;
	int j = query_i(i + 1);
	if(j == -1)
	{
		return;
	}
	qDebug() << a__[j] + 1;

	QPoint x = ui->listView->mapFromGlobal(cursor().pos());
	qDebug() << QString::number(cursor().pos().x()) + " " + QString::number(cursor().pos().y());
	qDebug() << QString::number(x.x()) + " " + QString::number(x.y());

	qDebug() << ui->listView->fontMetrics().width("0") << ui->listView->fontMetrics().width(" ") << ui->listView->fontMetrics().width("□");

	QStandardItemModel *model = (QStandardItemModel *)ui->listView->model();
	QString sText = model->item(index.row())->text();
	int w1 = ui->listView->fontMetrics().width(" ");
	int w2 = ui->listView->fontMetrics().width("□");
	int l1 = ui->listView->fontMetrics().width(sText.left(7)) + 2;
	int r1 = l1 + w2;
	int l2 = r1 + w1;
	int r2 = l2 + w2;
	int l3 = r2 + w1;
	qDebug() << l1 << r1 << l2 << r2 << l3;

	if(x.x() >= l3)
	{
		r_=0;
		query(tree[0], 1, 0, y_, a_[a__[j]].l, a_[a__[j]].r);
		update_i(a__[j], r_ == 1 ? 1 : 0);
	}

	if(x.x() >= l2 && x.x() < r2)
	{
		int r = query_c(a__[j]);
		update_c(a__[j], r == 0 ? 1 : 0);
	}

	if(x.x() >= l1 && x.x() < r1 )
	{
		int r = query_a(a__[j]);
		update_a(a__[j], r == 0 ? 1 : 0);
	}

	r_ = 0;
	query(tree[0], 1, 0, y_, 0, n);
	setRowCount(r_);
}

void AListView::resizeEvent(QResizeEvent *event)
{
	m_iShowCount = this->height() / 14;

	delete ui->listView->model();
	QStandardItemModel *model = new QStandardItemModel(this);
	for(int i = 0; i < m_iShowCount; i++)
	{
		QStandardItem *item = new QStandardItem("");
		model->appendRow(item);
	}
	ui->listView->setModel(model);

	updateScrollPos();
	drawListView();
}
