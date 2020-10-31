#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
const int M=N<<2;
const int inf=1e8;
int n,m,a[N];
int siz[N],dfn[N],tmr,son[N],fa[N],top[N],rev[N],ed[N],f[N][2];
struct edge{
	int nxt,to;
}e[N<<1];
int head[N],num_edge;
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
struct Matrix{
	int a[2][2];
	Matrix(){a[0][0]=a[0][1]=a[1][0]=a[1][1]=-inf;}
	int*operator[](const int&k){return a[k];}
	Matrix operator * (const Matrix&b){
		Matrix res;
//		for(int i=0;i<2;++i)
//			for(int j=0;j<2;++j)
//				for(int k=0;k<2;++k)
//					res.a[i][j]=max(res.a[i][j],a[i][k]+b.a[k][j]);
		res[0][0]=max(a[0][0]+b.a[0][0],a[0][1]+b.a[1][0]);
		res[0][1]=max(a[0][0]+b.a[0][1],a[0][1]+b.a[1][1]);
		res[1][0]=max(a[1][0]+b.a[0][0],a[1][1]+b.a[1][0]);
		res[1][1]=max(a[1][0]+b.a[0][1],a[1][1]+b.a[1][1]);
		return res;
	}
}mat[N],val[M];
void dfs1(int u,int ft){
	siz[u]=1,f[u][1]=a[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		fa[v]=u,dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
		f[u][0]+=max(f[v][0],f[v][1]);
		f[u][1]+=f[v][0];
	}
}
void dfs2(int u,int tp){
	top[u]=tp,dfn[u]=++tmr,rev[tmr]=u;
	if(son[u])dfs2(son[u],tp),ed[u]=ed[son[u]];
	else ed[u]=u;
	int g[2];g[0]=0,g[1]=a[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==son[u]||v==fa[u])continue;
		dfs2(v,v);
		g[0]+=max(f[v][0],f[v][1]);
		g[1]+=f[v][0];
	}
	mat[u][0][0]=g[0],mat[u][0][1]=g[0];
	mat[u][1][0]=g[1],mat[u][1][1]=-inf;
}
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p){val[p]=val[lc]*val[rc];}
void build(int l,int r,int p){
	if(l==r)return val[p]=mat[rev[l]],void();
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}
Matrix query(int ql,int qr,int l=1,int r=n,int p=1){
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1;
	if(qr<=mid)return query(ql,qr,l,mid,lc);
	if(mid<ql)return query(ql,qr,mid+1,r,rc);
	return query(ql,qr,l,mid,lc)*query(ql,qr,mid+1,r,rc);
}
void change(int pos,int l=1,int r=n,int p=1){
	if(l==r)return val[p]=mat[rev[l]],void();
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,l,mid,lc);
	else change(pos,mid+1,r,rc);
	pushup(p);
}
void update(int x,int v){
	mat[x][1][0]+=v-a[x],a[x]=v;
	while(x){
		Matrix lst=query(dfn[top[x]],dfn[ed[x]]);
		change(dfn[x]);
		Matrix now=query(dfn[top[x]],dfn[ed[x]]);
		x=fa[top[x]];
		mat[x][0][0]+=max(now[0][0],now[1][0])-max(lst[0][0],lst[1][0]);
		mat[x][0][1]=mat[x][0][0];
		mat[x][1][0]+=now[0][0]-lst[0][0];
	}
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	dfs1(1,0),dfs2(1,1),build(1,n,1);
	while(m--){
		int x=read(),v=read();
		update(x,v);
		Matrix t=query(dfn[1],dfn[ed[1]]);
		printf("%d\n",max(t[0][0],t[1][0]));
	}
	return 0;
}