#define maxn 2
struct Mat{
    int mat[maxn][maxn];
    int row,col;
    Mat(int _row=2,int _col=2){
        row=_row;col=_col;
        mat[0][0]=1;mat[0][1]=0;
        mat[1][0]=0;mat[1][1]=1;
    }
    bool identity(){
        if(mat[0][0]==1&&mat[0][1]==0&&mat[1][0]==0&&mat[1][1]==1)return 1;
        else return 0;
    }
};
 
Mat mod_add(Mat a,Mat b,int p=MOD){
    Mat ans(a.row,b.col);
    memset(ans.mat,0,sizeof(ans.mat));
    for(int i=0;i<a.row;i++)      
        for(int j=0;j<a.col;j++){
            ans.mat[i][j]=a.mat[i][j]+b.mat[i][j];
            ans.mat[i][j]%=p;
        }
    return ans;
}
 
Mat mod_mul(Mat a,Mat b,int p=MOD){
    Mat ans(a.row,b.col);
    memset(ans.mat,0,sizeof(ans.mat));
    for(int i=0;i<ans.row;i++)      
        for(int k=0;k<a.col;k++)
            if(a.mat[i][k])
                for(int j=0;j<ans.col;j++)
                {
                    ans.mat[i][j]=(ans.mat[i][j]+1LL*a.mat[i][k]*b.mat[k][j])%p;
                }
    return ans;
}
Mat mod_pow(Mat a,int k,int p=MOD) {
    Mat ans(a.row,a.col);
    for(int i=0;i<a.row;i++)for(int j=0;j<a.col;j++)ans.mat[i][j]=(i==j);
    while(k){
        if(k&1)ans=mod_mul(ans,a,p);
        a=mod_mul(a,a,p);
        k>>=1;
    }
    return ans;
}
 
Mat fib(int n){
    Mat ans(2,2);
    ans.mat[0][1]=1;
    ans.mat[1][0]=1;
    ans.mat[1][1]=0;
    return mod_pow(ans,n,MOD);
}


//Question: https://codeforces.com/problemset/problem/718/C (Seg_tree+Lazy+Matrix expo)
//https://codeforces.com/contest/718/submission/187662403
