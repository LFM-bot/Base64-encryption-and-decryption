#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
char Base64[100]= { 
 	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
 	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
 	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
 	'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/',
};
int f[9],se[9],fir[25],sec[33];
int find(char x){//用于找到该字符在base64表中的位置 
	for(int i=0;i<64;i++)
	  if(x==Base64[i])return i;
    return 64;
}
int out(int t){//用于找到原值加上对9的余数后得到新值的 原值 
	for(int i=0;i<9;i++){
		int x=(t-i),y=x+x%9;
		if(y==t)return x;
	}
}
int getnum(int s,int e,int fir[]){//将二进制数fir[s]到fir[e]转换为十进制 
	int sum=0,p=1;
	for(int i=e;i>=s;i--){
		sum+=p*fir[i];
		p*=2;
	}
	return sum;
}
int main(){
	char a[100]="i have a dream";
	char b[100];
	char c[100];
	int n=strlen(a);
	cout<<a<<endl;
	//加密1，各字母加上其值对9的余数x
	for(int i=0;i<strlen(a);i++){
		b[i]=a[i]+int(a[i])%9;
	} 
	cout<<endl<<"加密开始"<<endl;
	cout<<"1 各字母加上其值对9的余数x"<<endl;
	for(int i=0;i<n;i++)
	  cout<<b[i];
	cout<<endl; 
	//加密2，将每个字符的八位2进制ascll码中3，4，5与6，7，8交换 
	cout<<"加密2，将每个字符的八位2进制ascll码中3，4，5与6，7，8交换 " <<endl; 
	cout<<"加密中间过程如下"<<endl; 
	for(int j=0;j<n;j++){
		stack<int>s;
		int num=int(b[j]); //将b[j]的二进制ascll码保存在栈s中 
		cout<<num<<endl;
		while(num!=0){
		    s.push(num%2);
			num/=2;
		}
		int start=0;
			for(int k=8;k>=1;k--){//将栈s中的内容存到f[]中 
				if(s.size()==k){
				  f[++start]=s.top();
			      s.pop();
				}
				else f[++start]=0;
			}
		for(int i=1;i<=8;i++)
		  cout<<f[i]<<" ";
        cout<<endl;
        for(int i=1;i<=8;i++){//交换f[]中的3，4,5,与6,7,8位 
        	if(i<3)se[i]=f[i];
        	else if(3<=i&&i<=5)se[i]=f[i+3];
        	else se[i]=f[i-3];
        	cout<<se[i]<<" ";
        }
        cout<<endl;
        int sum=0,q=1;
        for(int i=8;i>=1;i--){//将新的8位二进制数f[]转换为十进制 
        	sum+=se[i]*q;
        	q*=2;
        } 
        cout<<sum;
        b[j]=char(sum);//转换为ascll码表中的字符 
        cout<<endl<<endl; 
	}
	cout<<"加密后"<<endl;
	for(int i=0;i<n;i++){//输出加密结果 
	  a[i]=b[i]; 
	  cout<<b[i];
	}
    cout<<endl<<endl;
    //加密3，base64加密
	 cout<<"加密3，base64加密"<<endl;
	 cout<<"具体加密细节如下"<<endl; 
	int m;
	if(n>n/3*3)m=n/3+1;//将加密信息的长度按3分为m段，余下1或2算一段，暂时用0填充 
	else m=n/3;
	
	for(int i=0;i<m;i++){//对每段进行处理 ,共执行m次 
		int start=0;
		for(int j=0;j<3;j++){//每段3个字符 
			stack<int>s;
			int num;//将i段的第j个字符的ascll码存入num 
			if(n-1>=i*3+j)
				num=int(a[i*3+j]);//如果i*3+j包含于n-1，则不是填充的0 
			else num=0;
			cout<<num<<"  ";
			while(num!=0){//将num的二进制形式存入栈s 
				s.push(num%2);
				num/=2;
			}
			for(int k=8;k>=1;k--){//将三个字符共24位的二进制ascll码以二进制保存在fir[1]到fir[24]中 
				if(s.size()==k){
				  fir[++start]=s.top();
			      s.pop();
				}
				else fir[++start]=0;
			}
		}
		cout<<endl<<"第"<<i<<"次"<<endl;//将fir[]输出 
		for(int k=1;k<=24;k++){
  			cout<<fir[k]<<" ";
  			if(k%8==0)cout<<"  ";
		}
		cout<<endl;
		int t=0;
		memset(sec,0,sizeof(sec));//将fir[1]到fir[24]分为4份，每份6个二级制数
		for(int k=1;k<=4;k++){    //在每6个数前填充2个0，组成4份8位二级制数
			for(int j=0;j<6;j++){ //存入sec[1]到sec[32]中，此处sec[]初值为0 
				sec[(k-1)*8+3+j]=fir[++t]; 
			}							   
		}								  
		for(int k=1;k<=32;k++){//输出sec[] 
			 cout<<sec[k]<<" ";
			 if(k%8==0)cout<<"  ";
		}
	    cout<<endl;	
		for(int k=0;k<4;k++){
			int c=0,q=1;
			for(int j=8;j>=1;j--){//将sec[]中的8位二级制数抓换为十进制 
				c+=sec[8*k+j]*q;
				q*=2;
			}
			b[i*4+k]=Base64[c];	  //转换为base64表中对应的字符，存入b[] 
			cout<<c<<" "<<Base64[c]<<" ";
		}
		cout<<endl;	
	}
	int l=n%3;//通过余数l判断有几个填充字符，修改为'=' 
	if(l==2)b[m*4-1]='=';
	else if(l==1){
		b[m*4-1]=b[m*4-2]='=';
	}
	cout<<endl<<"加密后"<<endl;//输出base64加密结果 
	for(int i=0;i<m*4;i++){
		cout<<b[i]<<" ";
	}
	cout<<endl<<endl;
    //解密1，base64
    cout<<"解密1，base64"<<endl;
    l=0;
    m=strlen(b)/4;//通过base64加密后的密码长度得到加密段数m 
    for(int i=4*m-2;i<4*m;i++)//通过'='数判断有几个值是填充的 
	  if(b[i]=='=')++l; 
	for(int i=0;i<m;i++){//对每段进行处理 
		int start=0; 
		memset(sec,2,sizeof(sec));
		for(int j=0;j<4;j++){//每段有4个字符 ,一共32个二进制位，保存在sec[1]到sec[32]中 
			stack<int>s;
			int num=find(b[i*4+j]);//找到对应字符在base64表中的位置 
			cout<<b[i*4+j]<<" ";
			while(num!=0){
				s.push(num%2);
				num/=2;
			}
			for(int k=8;k>=1;k--){//将三个字符的ascll码以二进制保存在fir中 
				if(s.size()==k){
				  sec[++start]=s.top();
			      s.pop();
				}
				else sec[++start]=0;
			}  
		}
		cout<<endl;
		for(int j=1;j<=32;j++){//输出sec[] 
    			cout<<sec[j]<<" ";
    			if(j%8==0)cout<<endl;
    		}
			for(int j=0;j<4;j++){				  //去掉填充的0，将sec[1]到sec[32]保存到fir[]中 
				for(int k=1;k<=6;k++)			  //fir[1]到fir[24] 
					fir[j*6+k]=sec[j*6+k+2*(j+1)];//2*(j+1)表示前面填充0的个数 
			}									  //每个字符填充2个0 
		for(int j=1;j<=24;j++){//输出fir[],每行6个 
			cout<<fir[j]<<" ";
			if(j%6==0)cout<<endl;
		} 
		for(int j=1;j<=24;j++){//输出fir[],每行8个
			cout<<fir[j]<<" ";
			if(j%8==0)cout<<endl;
		}
		for(int j=0;j<3;j++){
			a[i*3+j]=char(getnum(j*8+1,j*8+8,fir));//将二进制转换为十进制，并转变为对应字符，存入a[] 
			cout<<getnum(j*8+1,j*8+8,fir)<<" "<<char(getnum(j*8+1,j*8+8,fir))<<"  ";
		} 
		cout<<endl<<endl;
	}  
    int len=m*3-l;//通过=数得到最后一位非填充的下标len-1,则填充位不必输出 
    cout<<"解密完成"<<endl; 
    for(int i=0;i<len;i++)//输出解密结果 
      cout<<a[i];
    cout<<endl<<endl;
    for(int i=0;i<len;i++)
      b[i]=a[i]; 
    //2解密,将每个字符的八位2进制ascll码中3，4，5与6，7，8交换
    cout<<"2解密,将每个字符的八位2进制ascll码中3，4，5与6，7，8交换"<<endl;
    cout<<"解密过程如下"<<endl;
	for(int j=0;j<n;j++){//过程与加密几乎没有区别，可见上 
		stack<int>s;
		int num=int(b[j]); 
		cout<<num<<endl;
		while(num!=0){
		    s.push(num%2);
			num/=2;
		}
		int start=0;
			for(int k=8;k>=1;k--){// 
				if(s.size()==k){
				  f[++start]=s.top();
			      s.pop();
				}
				else f[++start]=0;
			}
		for(int i=1;i<=8;i++)
		  cout<<f[i]<<" ";
        cout<<endl;
        for(int i=1;i<=8;i++){
        	if(i<3)se[i]=f[i];
        	else if(3<=i&&i<=5)se[i]=f[i+3];
        	else se[i]=f[i-3];
        	cout<<se[i]<<" ";
        }
        cout<<endl;
        int sum=0,q=1;
        for(int i=8;i>=1;i--){
        	sum+=se[i]*q;
        	q*=2;
        } 
        cout<<sum;
        b[j]=char(sum);
        cout<<endl<<endl; 
	}
	cout<<"解密后"<<endl;
	for(int i=1;i<=n;i++)
	  cout<<b[i];
    cout<<endl<<endl; 
    //解密3，将个字符的ascll转变为加上原值关于9的余数前 
	for(int i=0;i<strlen(b);i++){
		int t=out(int(b[i]));//通过out()函数找到原值 
		c[i]=char(t);			//转化为字符 
	}
	cout<<"解密3，将个字符的ascll转变为加上原值关于9的余数前"<<endl;
	for(int i=0;i<n;i++)//输出解密结果 
	  cout<<c[i];
	cout<<endl<<endl; 
	cout<<"共计270行，加密解密完成！" ;
	return 0;
}