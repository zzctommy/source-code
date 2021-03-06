#define N 40000
#define M 100005
#define T (N<<2)
#define mod1 39989
#define mod2 1000000000
int lastans,cnt;
pair<db,db>li[M];
int v[T];
#define lc (p<<1)
#define rc (p<<1|1)
#define val(x,y) (1.*li[x].fi*y+li[x].se)
void update(int id,int ql,int qr,int l=1,int r=N,int p=1){
	int mid=(l+r)>>1;
	if(ql<=l&&r<=qr){
		if(!v[p])return v[p]=id,void();
		db nol=val(id,l),nor=val(id,r),lal=val(v[p],l),lar=val(v[p],r);
		if(nol<=lal&&nor<=lar)return;
		if(nol>=lal&&nor>=lar)return v[p]=id,void();
		db inter=1.*(li[id].se-li[v[p]].se)/(li[v[p]].fi-li[id].fi);
		if(nol>=lal){
			if(inter<=mid)update(id,ql,qr,l,mid,lc);
			else update(v[p],ql,qr,mid+1,r,rc),v[p]=id;
		}else{
			if(inter>mid)update(id,ql,qr,mid+1,r,rc);
			else update(v[p],ql,qr,l,mid,lc),v[p]=id;
		}
		return;
	}
	if(ql<=mid)update(id,ql,qr,l,mid,lc);
	if(mid<qr)update(id,ql,qr,mid+1,r,rc);
}
int query(int X,int l=1,int r=N,int p=1){
	int res=0;
	if(v[p]&&val(v[p],X)>val(res,X))res=v[p];
	if(l==r)return res;
	int mid=(l+r)>>1,t;
	if(X<=mid)t=query(X,l,mid,lc);
	else t=query(X,mid+1,r,rc);
	if(val(res,X)<val(t,X))res=t;
	return res;
}