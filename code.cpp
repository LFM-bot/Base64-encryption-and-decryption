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
int find(char x){//�����ҵ����ַ���base64���е�λ�� 
	for(int i=0;i<64;i++)
	  if(x==Base64[i])return i;
    return 64;
}
int out(int t){//�����ҵ�ԭֵ���϶�9��������õ���ֵ�� ԭֵ 
	for(int i=0;i<9;i++){
		int x=(t-i),y=x+x%9;
		if(y==t)return x;
	}
}
int getnum(int s,int e,int fir[]){//����������fir[s]��fir[e]ת��Ϊʮ���� 
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
	//����1������ĸ������ֵ��9������x
	for(int i=0;i<strlen(a);i++){
		b[i]=a[i]+int(a[i])%9;
	} 
	cout<<endl<<"���ܿ�ʼ"<<endl;
	cout<<"1 ����ĸ������ֵ��9������x"<<endl;
	for(int i=0;i<n;i++)
	  cout<<b[i];
	cout<<endl; 
	//����2����ÿ���ַ��İ�λ2����ascll����3��4��5��6��7��8���� 
	cout<<"����2����ÿ���ַ��İ�λ2����ascll����3��4��5��6��7��8���� " <<endl; 
	cout<<"�����м��������"<<endl; 
	for(int j=0;j<n;j++){
		stack<int>s;
		int num=int(b[j]); //��b[j]�Ķ�����ascll�뱣����ջs�� 
		cout<<num<<endl;
		while(num!=0){
		    s.push(num%2);
			num/=2;
		}
		int start=0;
			for(int k=8;k>=1;k--){//��ջs�е����ݴ浽f[]�� 
				if(s.size()==k){
				  f[++start]=s.top();
			      s.pop();
				}
				else f[++start]=0;
			}
		for(int i=1;i<=8;i++)
		  cout<<f[i]<<" ";
        cout<<endl;
        for(int i=1;i<=8;i++){//����f[]�е�3��4,5,��6,7,8λ 
        	if(i<3)se[i]=f[i];
        	else if(3<=i&&i<=5)se[i]=f[i+3];
        	else se[i]=f[i-3];
        	cout<<se[i]<<" ";
        }
        cout<<endl;
        int sum=0,q=1;
        for(int i=8;i>=1;i--){//���µ�8λ��������f[]ת��Ϊʮ���� 
        	sum+=se[i]*q;
        	q*=2;
        } 
        cout<<sum;
        b[j]=char(sum);//ת��Ϊascll����е��ַ� 
        cout<<endl<<endl; 
	}
	cout<<"���ܺ�"<<endl;
	for(int i=0;i<n;i++){//������ܽ�� 
	  a[i]=b[i]; 
	  cout<<b[i];
	}
    cout<<endl<<endl;
    //����3��base64����
	 cout<<"����3��base64����"<<endl;
	 cout<<"�������ϸ������"<<endl; 
	int m;
	if(n>n/3*3)m=n/3+1;//��������Ϣ�ĳ��Ȱ�3��Ϊm�Σ�����1��2��һ�Σ���ʱ��0��� 
	else m=n/3;
	
	for(int i=0;i<m;i++){//��ÿ�ν��д��� ,��ִ��m�� 
		int start=0;
		for(int j=0;j<3;j++){//ÿ��3���ַ� 
			stack<int>s;
			int num;//��i�εĵ�j���ַ���ascll�����num 
			if(n-1>=i*3+j)
				num=int(a[i*3+j]);//���i*3+j������n-1����������0 
			else num=0;
			cout<<num<<"  ";
			while(num!=0){//��num�Ķ�������ʽ����ջs 
				s.push(num%2);
				num/=2;
			}
			for(int k=8;k>=1;k--){//�������ַ���24λ�Ķ�����ascll���Զ����Ʊ�����fir[1]��fir[24]�� 
				if(s.size()==k){
				  fir[++start]=s.top();
			      s.pop();
				}
				else fir[++start]=0;
			}
		}
		cout<<endl<<"��"<<i<<"��"<<endl;//��fir[]��� 
		for(int k=1;k<=24;k++){
  			cout<<fir[k]<<" ";
  			if(k%8==0)cout<<"  ";
		}
		cout<<endl;
		int t=0;
		memset(sec,0,sizeof(sec));//��fir[1]��fir[24]��Ϊ4�ݣ�ÿ��6����������
		for(int k=1;k<=4;k++){    //��ÿ6����ǰ���2��0�����4��8λ��������
			for(int j=0;j<6;j++){ //����sec[1]��sec[32]�У��˴�sec[]��ֵΪ0 
				sec[(k-1)*8+3+j]=fir[++t]; 
			}							   
		}								  
		for(int k=1;k<=32;k++){//���sec[] 
			 cout<<sec[k]<<" ";
			 if(k%8==0)cout<<"  ";
		}
	    cout<<endl;	
		for(int k=0;k<4;k++){
			int c=0,q=1;
			for(int j=8;j>=1;j--){//��sec[]�е�8λ��������ץ��Ϊʮ���� 
				c+=sec[8*k+j]*q;
				q*=2;
			}
			b[i*4+k]=Base64[c];	  //ת��Ϊbase64���ж�Ӧ���ַ�������b[] 
			cout<<c<<" "<<Base64[c]<<" ";
		}
		cout<<endl;	
	}
	int l=n%3;//ͨ������l�ж��м�������ַ����޸�Ϊ'=' 
	if(l==2)b[m*4-1]='=';
	else if(l==1){
		b[m*4-1]=b[m*4-2]='=';
	}
	cout<<endl<<"���ܺ�"<<endl;//���base64���ܽ�� 
	for(int i=0;i<m*4;i++){
		cout<<b[i]<<" ";
	}
	cout<<endl<<endl;
    //����1��base64
    cout<<"����1��base64"<<endl;
    l=0;
    m=strlen(b)/4;//ͨ��base64���ܺ�����볤�ȵõ����ܶ���m 
    for(int i=4*m-2;i<4*m;i++)//ͨ��'='���ж��м���ֵ������ 
	  if(b[i]=='=')++l; 
	for(int i=0;i<m;i++){//��ÿ�ν��д��� 
		int start=0; 
		memset(sec,2,sizeof(sec));
		for(int j=0;j<4;j++){//ÿ����4���ַ� ,һ��32��������λ��������sec[1]��sec[32]�� 
			stack<int>s;
			int num=find(b[i*4+j]);//�ҵ���Ӧ�ַ���base64���е�λ�� 
			cout<<b[i*4+j]<<" ";
			while(num!=0){
				s.push(num%2);
				num/=2;
			}
			for(int k=8;k>=1;k--){//�������ַ���ascll���Զ����Ʊ�����fir�� 
				if(s.size()==k){
				  sec[++start]=s.top();
			      s.pop();
				}
				else sec[++start]=0;
			}  
		}
		cout<<endl;
		for(int j=1;j<=32;j++){//���sec[] 
    			cout<<sec[j]<<" ";
    			if(j%8==0)cout<<endl;
    		}
			for(int j=0;j<4;j++){				  //ȥ������0����sec[1]��sec[32]���浽fir[]�� 
				for(int k=1;k<=6;k++)			  //fir[1]��fir[24] 
					fir[j*6+k]=sec[j*6+k+2*(j+1)];//2*(j+1)��ʾǰ�����0�ĸ��� 
			}									  //ÿ���ַ����2��0 
		for(int j=1;j<=24;j++){//���fir[],ÿ��6�� 
			cout<<fir[j]<<" ";
			if(j%6==0)cout<<endl;
		} 
		for(int j=1;j<=24;j++){//���fir[],ÿ��8��
			cout<<fir[j]<<" ";
			if(j%8==0)cout<<endl;
		}
		for(int j=0;j<3;j++){
			a[i*3+j]=char(getnum(j*8+1,j*8+8,fir));//��������ת��Ϊʮ���ƣ���ת��Ϊ��Ӧ�ַ�������a[] 
			cout<<getnum(j*8+1,j*8+8,fir)<<" "<<char(getnum(j*8+1,j*8+8,fir))<<"  ";
		} 
		cout<<endl<<endl;
	}  
    int len=m*3-l;//ͨ��=���õ����һλ�������±�len-1,�����λ������� 
    cout<<"�������"<<endl; 
    for(int i=0;i<len;i++)//������ܽ�� 
      cout<<a[i];
    cout<<endl<<endl;
    for(int i=0;i<len;i++)
      b[i]=a[i]; 
    //2����,��ÿ���ַ��İ�λ2����ascll����3��4��5��6��7��8����
    cout<<"2����,��ÿ���ַ��İ�λ2����ascll����3��4��5��6��7��8����"<<endl;
    cout<<"���ܹ�������"<<endl;
	for(int j=0;j<n;j++){//��������ܼ���û�����𣬿ɼ��� 
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
	cout<<"���ܺ�"<<endl;
	for(int i=1;i<=n;i++)
	  cout<<b[i];
    cout<<endl<<endl; 
    //����3�������ַ���ascllת��Ϊ����ԭֵ����9������ǰ 
	for(int i=0;i<strlen(b);i++){
		int t=out(int(b[i]));//ͨ��out()�����ҵ�ԭֵ 
		c[i]=char(t);			//ת��Ϊ�ַ� 
	}
	cout<<"����3�������ַ���ascllת��Ϊ����ԭֵ����9������ǰ"<<endl;
	for(int i=0;i<n;i++)//������ܽ�� 
	  cout<<c[i];
	cout<<endl<<endl; 
	cout<<"����270�У����ܽ�����ɣ�" ;
	return 0;
}