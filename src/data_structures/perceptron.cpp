//given by Rosenblat
//inspiration from retina of eye
//seems like single feed forward network
#include<iostream>
using namespace std;

int main()
{
	int  m,n;
	float lr, t;
	cout<<"enter no.of features , no.of training datasets , threshold and learning rate : \n";
	cin>> m>>n>>t>>lr;

	int wt2[m];
	
	int input[n][m];
	cout<<"enter the input matrix row wise "<<endl;

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>input[i][j];
		}
	}

	int  target2[n];

	

	cout<<"Enter the target in bipolar: "<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>target2[i];
	}

	for(int i=0;i<m;i++)
	{
		//step 1: initialise all wts to 0
		wt2[i]=0;
	}
	int y_out;

	for(int j=0;j<n;j++)
	{
		cout<<"\n########### training set j="<<j<<endl;
int y_in=0;
		for(int i=0; i<m;i++)
		{
			 y_in+= wt2[i]*input[j][i];
			}
			 cout<< "y_in = "<<y_in<<endl;

			 if(y_in > t)
			 	y_out=1;
			 else if(y_in < -1*t)
			 	y_out=-1;
			 else
			 	y_out=0;
//			 cout<<"wt2 at i="<<i<<" is "<<wt2[i]<<endl;

			 cout<< "y_out = "<<y_out<<endl;


			 if(y_out != target2[j])
			 {
			 			for(int i=0; i<m;i++)

			 				wt2[i]+= (lr *target2[j] *input[j][i]);
			 			cout<<"updated weights :\n";
			 for (int i = 0; i < m; ++i)
	{
		/* code */
		cout<<wt2[i]<<" ";
	}

			 }

			 else
			 	{cout<<"\ntarget and y_out are equal. stop the training";
			 	break;
			 }

		
	
	}
	cout<<"\n************OUTPUT**************\nafter 1 epoch:  weights: "<<endl;

	
	for (int i = 0; i < m; ++i)
	{
		/* code */
		cout<<wt2[i]<<" ";
	}



	return 0;
}