# include<iostream>
# include<string>
# include<conio.h>

using namespace std;

int main()
{
	string message, pass1, pass2;
	int i, n, m;
	long long int result = 0, enc_hash = 0, dec_hash, j, k, tens=1;
	cout<<"Enter the Message to be sent :  ";
	getline(cin,message);
	
	cout<<endl<<message<<endl;
	n = message.size();
    for(i=0; i<n; i++)
    {
        result = result * 31 + message[i];
    }
    cout <<result<<endl<<endl<<"The hash is :  ";
    cout <<hex<<"0x "<< result << endl;
    
    cout<<"Enter Passkey for encryption :  ";
    cin>>pass1;
    m = pass1.size();
    enc_hash = result;
    for(i=0; i<n-1; i++)
    {
        enc_hash = enc_hash + pass1[i%m]*tens;
        tens = tens*999999;
    }
    
    cout<<dec<<enc_hash<<endl<<endl;
    cout<<"The Encrypted hash is :  "<<hex<<"0x "<< enc_hash << endl;
	
	cout<<endl<<"Simulating message transmission"<<endl;

	for(j=0; j<10; j++)
	{
		cout<<".  ";
		for(k=0; k<1000000000; k++)
		{	k+=3;	}
    }
	cout<<endl;
//	cout<<"To edit message enter 1\nTo continue enter any other key  ";
//	cin>>i;
//	if(i==1)
//	{
//		//cin.clear();
//		cout<<"Enter new message :  ";
//		getline(cin,message);
//	}
	cout<<endl<<"Received Message   :   " <<message;
	cout<<endl<<"Received encrypted hash  :   " <<hex<<"0x "<<enc_hash;
	
	result = 0;
	for(i=0; i<n; i++)
    {
        result = result * 31 + message[i]; 
	}
    //cin.clear();
	cout<<endl<<"Hash of received message :   " <<hex<<"0x "<< result << endl;
	cout<<endl<<"We decrypt received encrypted hash";
	//cout<<endl<<"Enter passkey to decrypt encrypted hash :  ";
    //
	//cin>>pass2;
    
    cout<<endl;
//    m = pass2.size();
    tens = 1;
    dec_hash = enc_hash;

    for(i=0; i<n-1; i++)
    {
        dec_hash = dec_hash - pass1[i%m]*tens;
        tens = tens*999999;  }

    cout<<"Decrypted hash is :  "<<"0x "<<dec_hash<<endl<<endl;
    
    if(result == dec_hash)
    	cout<<"Since both hash of received message, and decrypted received encrypted hash \nare the same, Digital Signature is verified";
    else
    	cout<<"Since both hash of received message, and decrypted received encrypted hash \nare different, This message has been altered by unauthorized personel";
    	
  getch();
	return 0;
}
