#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define	N	100000
#define	RAND()	(((long long)rand()<<16)+rand())
int p[N],c[N];
void init(int n){
	int i;
	for(i=0;i<n;i++){
		p[i]=i;
		c[i]=1;
	}
}
int find(int i){
	for(;i!=p[i];i=p[i]){
		p[i]=p[p[i]];
	}
	return i;
}
int join(int i,int j){
	int l=find(i),r=find(j);
	if(l==r){
		return 0;
	}
	if(c[l]<c[r]){
		l^=r;
		r^=l;
		l^=r;
	}
	p[r]=l;
	c[l]+=c[r];
	return 1;
}
void run(){
	int i,l,r;
	srand(time(0));
	printf("%d\n",N);
	init(N);
	for(i=0;i<N-1;i++){
		l=RAND()%N+1;
		r=RAND()%N+1;
		if(join(l-1,r-1)==0){
			i--;
			continue;
		}
		printf("%d %d\n",l,r);
	}
}
int main(){
	freopen("tree.in","wb",stdout);
	run();
	return 0;
}
