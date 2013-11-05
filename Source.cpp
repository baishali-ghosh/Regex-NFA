#include<iostream>
#include<cstdio>
#include<cstring>
//Second right link for a*
//alter display function for a*
using namespace std;
struct node
{
	char data;
	node *rlink;
//	node *rlink2;
	node *llink;
};
struct node * append(struct node *q, char ele);
void add(struct node *q, char ele);
void display(struct node* q, int);
void displayn(struct node* q, char, char);
char states[]={'A', 'B', 'C', 'D', 'E','G', 'H', 'I','J','K','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char dig[]={'1','2','3','4','5','6','7','8','9'};
int main()
{
	int i=0,j=0, k=0, l=0, m=0, p=0, size=0, flag=0,sc=0, dg=0, eo=0, chk=0, tmp, cnt=0;
	char str[50], temp[50], from, to; 
	char regex[20][50];
	int nofstates;
	cout<<"Enter the regular expression: ";
	fflush(stdin);
	cin>>str;
	//Initializing strings
	for(i=0;i<20;i++)
    strcpy(regex[i],"");	
	//If there are | split into separate regular expressions of form r1, r2, ...rn
    //Extracting first regex
    i=0;
    while(str[i]!='|' && str[i]!='\0')
    {
      regex[l][m]=str[i];
	  m++;i++;
	}
	regex[l][m]='\0';
	m=0;l++;
	//Extracting the remaining regexes
	for(i=0;i<strlen(str);i++)
	{
	  if(str[i]=='|')
	  {
	    j=i+1;//points to first character of next regex
	    for(k=j;str[k]!='|';k++);//points to last char of regex
	    for(p=j;p<k;p++)
	    {
		  regex[l][m]=str[p];
	      m++;
	    }
	    regex[l][m]='\0';
	    m=0;
	    l++;
	  }  
	//l gives a count of the total no. of regexes present in the original string
    }
    for(i=0;i<l;i++)
    {
    	cout<<regex[i]<<" ";
    }
    cout<<endl;
    cout<<"No. of regular expressions: "<<l<<endl;
    struct node *adjlist[l];
	for(i=0;i<l;i++)
	{
		adjlist[i]='\0';		
	}
    //In creating a nfa, we can deal with 5 cases.
    for(int i=0;i<l;i++)
    {
    	//cout<<"5 cases:\n";
	    cout<<regex[i]<<" "<<endl; 
	    if(regex[i][1]=='\0')//condition for determining lambda and single terminal regex
	    {
		    if(stricmp(regex[i],"L")==0)//L denotes lambda
    	    {
    		    adjlist[i]=append(adjlist[i], 'S');//S is start state.
    		    adjlist[i]=append(adjlist[i], 'F');//F is final state.
		    }   
        	else 
        	{
           		adjlist[i]=append(adjlist[i], 'S');
    	   		adjlist[i]=append(adjlist[i], 'F');
			}
		}
		else
		{
		    flag=0;
			for(int p=0;regex[i][p]!='\0';p++)//check if asterisk occurs anywhere in the regex
			{
				if(regex[i][p]=='*')
			    {
			    	flag=1;
			    }
			}
			if(flag==0)//n-terminal regex without *
			{
				size=0;	
				for(int p=0;regex[i][p]!='\0';p++)//sizeof the regex
				{
				  size++;
			    }
		    	for(int p=0;regex[i][p]!='\0';p++)
				{
				  if(p==0)
				  {
				    adjlist[i]=append(adjlist[i], 'S');
				  }
				  else if(p<size)
			      {
			        adjlist[i]=append(adjlist[i], states[sc]);
			        sc++;
			      }
			    }
			    adjlist[i]=append(adjlist[i], 'F');
			}
		    else//dealing with a* type regexes
		    {
		       size=0;	
			   for(int p=0;regex[i][p]!='\0';p++)//sizeof the regex
			   {
				  size++;
		       }  
			    if(size==2)//star over single terminal
			    {
			    	adjlist[i]=append(adjlist[i], 'S');
			     	adjlist[i]=append(adjlist[i], '1');	
			     	adjlist[i]=append(adjlist[i], '2');
			     	adjlist[i]=append(adjlist[i], 'F');	
			     	add(adjlist[i],'1');
			    }
			    else
				{
			    	//cout<<size;
					for(int p=0;regex[i][p]!='\0';p++)
			  		{	 
			     	  if(regex[i][1]=='*'&&eo==0)//the first part of the regex is a* like in a*b
			     	  	{
			     			adjlist[i]=append(adjlist[i], 'S');
			     			temp[cnt]='S';cnt++;
			     			adjlist[i]=append(adjlist[i], dig[dg]);
							tmp=dig[dg];dg++;
			     			adjlist[i]=append(adjlist[i], dig[dg]);
			     			dg++;
			     			adjlist[i]=append(adjlist[i], dig[dg]);
			     			temp[cnt]=dig[dg];cnt++;
							dg++;
							eo=1;
							size-=2;	
						}
			     	    else if(size>1)
						{		
			     		    cout<<"In here.\n";
							adjlist[i]=append(adjlist[i], dig[dg]);	
			     		    size--;
			     		    dg++;
			     		    if(size==1)
			     		    size--;
						}
						else if(size==0 && chk==0)
						{
						 adjlist[i]=append(adjlist[i], 'F');
						 chk=1;
					    }    
						add(adjlist[i],tmp);
			  	 	  }
			  	     /* else if(regex[i][p+1]=='*'&&p==size-2)//ab*
			  	 	  {
			  	   		 adjlist[i]=append(adjlist[i], '1');
			     		 adjlist[i]=append(adjlist[i], '2');	
			     		 adjlist[i]=append(adjlist[i], 'F');
			     		 add(adjlist[i],'1');
			  	 	  }	*/
			  	}
			         
			}  
		}
    }
    //We can rep the nfa in term of transitions from one state to the other on applying an input symbol
	for(i=0;i<l;i++)
	{
		size=0;
		for(int p=0;regex[i][p]!='\0';p++)//sizeof the regex
				{
				  size++;
			    }
	    display(adjlist[i], size);
	    for(int p=0;regex[i][p]!='\0';p++)
		{
			if(regex[i][p+1]=='*')	
	    	displayn(adjlist[i],temp[0],temp[1]);
	    }
	}
    return 0;	
}
void add(struct node *q, char ele)  
{
	struct node* temp;int count=0;
	while(q!='\0')
	{
		count++;
		if(q->data==ele)
	    {
	     temp=q;
	    }
	    if(count==3)
		{
		  q->llink=temp; 
	    }
	    q=q->rlink;
	} 
}
struct node * append(struct node *q, char ele)  
{
    //cout<<"\n\nFunction";
    struct node *temp, *r;
    if(q=='\0')
    {
             //cout<<"\nHead node";
             r=new node;
		     r->data=ele;
		     r->rlink='\0';
		     r->llink='\0';
		     q=r;
		     return q;
	}
    else	     
    {
        //cout<<"\nNext node";
		temp=q;
		while(temp->rlink!='\0')
		{
			temp=temp->rlink;
		}		
		r=new node;
		r->data=ele;
		r->rlink='\0';
		r->llink='\0';
		temp->rlink=r;
		return q;
	}
}
void display(struct node* q, int count)
{
    cout<<"\nDisplaying adjacency list\n";
    //cout<<count;
	while(q!=NULL)
	{
		if(count==0)
		cout<<q->data<<" ";
		else
		{
			cout<<q->data<<" : ";
			count--;
		}
		q=q->rlink;
	} 
	cout<<endl;
}

void displayn(struct node* q, char from, char to)
{
	struct node *temp;
	while(q!='\0')
	{
	    if(q->llink!='\0')
          {
           cout<<from<<" : "<<to<<endl;
		   cout<<q->data<<" : ";
           q=q->llink;
           cout<<q->data;
           q=q->rlink;
          }
		q=q->rlink;
	} 
  
}
