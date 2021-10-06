#include<iostream.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h> 
#include<process.h> 

struct  marks_criteria 
{ 
	int sc_min , com_min , arts_min , seat_sc , seat_com , seat_arts; 
} crit;   


struct  administrator 
{ 
	char user_name[50] ;
    char password[10]; 
}admin;   


class student 
{ 
private:
     char name[20]; 
     int  regno, m_eng, m_math, m_sc, m_sst , m_lang; 
     int  pref_code, stream;       // Sc=1, Com=2; Arts=3    
 public: 
	 void new_file(); 
	 void input_data(); 
	 void allot_stream(); 
	 int get_stream(); 
	 void display(); 
	 int show_per() 
	 { return(  (m_eng+m_math+m_sc+m_sst+m_lang )/5  ); }   
};

void  welcome(); 
void  menu(); 
int  verify_password(); 
void  assign_user(); 
void  input_criteria(); 
void read_criteria(); 
void  read_student(); 
void  create_eligible_sc(); 
void  create_eligible_com(); 
void  create_eligible_arts(); 
void  read_eligible_sc(); 
void  read_eligible_com(); 
void  read_eligible_arts(); 
char  *stream_name(int strm); 
void  thanks();   

student s;

void main() 
{   welcome();   // cout< <"welcome"; 
    fstream   fin,  fout; 
    fstream   fsc,  fcom,  farts; 
	int  opt=1,  ch;   
	while(opt!=8) 
	{  
		cout<<"\n\t====================== MAIN MENU  ==========================\n"; 
		cout<<"\n\t[1] CREATE / MODIFY ADMISSION CRITERIA(Administrator only)"; 
		cout<<"\n\n\t[2] ENTER STUDENT'S DATA "; 
                        cout<<"\n\n\t[3] ALLOTMENT OF STREAM"; 
		cout<<"\n\n\t[4] DISPLAY CRITERIA FOR SELECTION";
		cout<<"\n\n\t[5] DISPLAY ALLOTMENT OF STUDENT'S STREAM";  
		cout<<"\n\n\t[6] QUIT"; 
		cout<<"\n\t==========================================================\n";
		
        cout<<"\n\n\t\tEnter your choice : "; 
		cin>>opt; 
		
		switch(opt) 
		{ 
case 1: int p; 
	assign_user(); 
	p=verify_password(); 
	if (p==0) 
		input_criteria(); 
	else 
	{ 
	    cout<<"\n\tYou are Not a Valid User."; 
	    cout<<"\n\tU Dont have the Authority to Create Question Bank. Bye\n\n"; 
	} 
	break;                                             
case 2: int option;
        cout<<"\nWhat do u want --\n\n\n\n\n\tCreate a new student information file or Append to the existing file?\n\n\t(press 1 for new creation and 2 for appending)"; 
		cin>>option; 
		if(option) 
			s.new_file(); 
		else  
			s.input_data(); 
		break;   
			
case 3: fin.open("student" ,ios::in|ios::out);   
	    fsc.open("elig_sc",ios::out); 
		fcom.open("eligcom",ios::out); 
		farts.open("eligart",ios::out);   
				
		while ( fin.read(  (char*) &s , sizeof(s) ) )
		{
			s.allot_stream();   
			s.get_stream();  
			if (s.get_stream()==0)  
				cout<<"\nApplication Rejected. Not Eligible\n";   cin.ignore();
				if (s.get_stream()==1)
				{
					fsc.write( (char*) & s, sizeof(s));
					cout<<"\nApplication Accepted.Elligible";
				}     
				if (s.get_stream()==2) 
			    { 
				    fcom.write((char*)& s,sizeof(s));
				    cout<<"\nApplication Accepted.Elligible";
				}

				if (s.get_stream()==3) 
				{  
					farts.write((char*)& s,sizeof(s));
					cout<<"\nApplication Accepted.Elligible";
				}
				} 
				fin.close(); 
				fsc.close(); 
				fcom.close(); 
				farts.close(); 
				
                cout<<"\n*******************************************"; 
				cout<<"\n\n\tSTREAM ALLOCATION DONE."; 
	            cout<<"\n*******************************************";
				break;
 case 4:  read_criteria(); 
cout<<"\n Minimum Overall Percentage Required for Science Stream : "<<crit.sc_min;
cout<<"\n Minimum Overall Percentage Required for Commerce Stream : "<<crit.com_min;
cout<<"\n Minimum Overall Percentage Required for Arts Stream: "<<crit.arts_min;
                                                                        break;
			case 5:  cout<<"\n Enter 1 for Sc, 2 for Com, 3 for Arts : "; 
			    cin>>ch;
                if (ch==1) 
					read_eligible_sc();   
				if (ch==2) 
					read_eligible_com(); 
				if (ch==3) 
					read_eligible_arts();   
				break; 
                
            case 6:  thanks();     //	cout< <"\nTHANKS BYE "; //
				exit(0);             

 } //END OF SWITCH
} // END OF WHILE
} //END OF MAIN





void   assign_user() 
{
    strcpy(admin.user_name, "shaikhhamza");  
    strcpy(admin.password, "hamster");    
} 

int verify_password() 
{
	char u_name[10]; 
	char u_pwd[10];
            int x=1; 
	
            cout<<"\n\n Enter user name : "; 
	cin>>u_name; 
            cout<<"\n\n Enter Password : "; 
	cin>>u_pwd; 
	
            x=strcmp(admin.user_name,u_name); 
	if (x==1)  
		x=strcmp(admin.password,u_pwd);   
return(x);   
} 

void  student::allot_stream() 
{ 
	int   per=( m_eng + m_math + m_sc + m_sst + m_lang )/5; 
	read_criteria();   
	switch (pref_code) 
	{ 
	    case 1: 
			if (per >= crit.sc_min) 
				stream=pref_code; 
			else 
				stream=0;   
			break; 
		case 2: 
			if (per >= crit.com_min) 
				stream=pref_code; 
			else 
				stream=0; 
			break; 
		case 3: 
			if (per >= crit.arts_min) 
				stream=pref_code; 
			else 
				stream=0; 
			break; 
 }//END OF SWITCH
}//END OF FUNCTION

int student::get_stream() 
{ 
	return(stream); 
}     

void input_criteria() 
{ 
	fstream fout; 
	fout.open("criteria" ,ios::in|ios::out); 
	
	cout<<"\nEnter the required marks for SCIENCE stream(in percentage):"; 
	cin>>crit.sc_min; 
	
	cout<<"\nEnter No. of Seats for SCIENCE stream:"; 
	cin>>crit.seat_sc; 
	
	cout<<"\nEnter the required marks for COMMERCE stream(in percentage):"; 
	cin>>crit.com_min; 
	
	cout<<"\nEnter No. of Seats for COMMERCE stream:"; 
	cin>>crit.seat_com; 
	
	cout<<"\nEnter the required marks for ARTS stream(in percentage):"; 
	cin>>crit.arts_min; 
	
	cout<<"\nEnter No. of Seats for ARTS stream:"; 
	cin>>crit.seat_arts; 
	
	fout.write( (char*)& crit, sizeof(crit)  );  /*Writes the Min %age req. for streams and no. of seats for       the streams to the file "criteria" */
    fout.close(); 
}   

void read_criteria() 
{ 
	fstream fin; 
	fin.open("criteria" ,ios::in); 
	fin.read( (char*)& crit, sizeof(crit) ); 
	fin.close();   
}   

void  student::input_data() 
{
    fstream fin; 
	fin.open("student",ios::app|ios::out); 
	
	char  ans; 
	while(1) 
	{ 
		cout<<"Enter the Name of the Student : "; 
	    gets(name); 
		
		cout<<"Enter the Roll Number of the Student : "; 
		cin>>regno; 
		
		cout<<"Enter marks in English : "; 
		cin>>m_eng; 
		
		cout<<"Enter marks in Mathematics : "; 
		cin>>m_math; 
		
		cout<<"Enter marks in Science : "; 
		cin>>m_sc; 
		
		cout<<"Enter marks in Social Studies : "; 
		cin>>m_sst; 
		
		cout<<"Enter marks in Language : "; 
		cin>>m_lang; 
		
		cout<<"==================STREAM PREFERED?================ \n"; 
		cout<<"\t"<<"[1] for SCIENCE\n"; 
		cout<<"\t"<<"[2] for COMMERCE\n"; 
		cout<<"\t"<<"[3] for ARTS "; 
		
		cout<<"\n=======================================\n\tENTER PREFERENCE CODE : "; 
		cin>>pref_code; 
		
		stream=-1; 
		
		fin.write( (char*)&s, sizeof(s) ); 
		
        cout<<"\n\tEnter More Student ? (y/n)"; 
		cin>>ans; 
		if (ans=='n') 
			break; 
	} 
	fin.close(); 
}

void  student::new_file() 
{ 
                fstream fin; 
	    fin.open("student",ios::out); 
	
	char  ans; 
	while(1) 
	{ 
		cout<<"\nEnter the Name of the Student : "; 
		cin>>(name); 
		
		cout<<"Enter the Roll Number of the Student : "; 
		cin>>regno; 
		
		cout<<"Enter marks in English : "; 
		cin>>m_eng; 
		
		cout<<"Enter marks in Mathematics : "; 
		cin>>m_math; 
		
		cout<<"Enter marks in Science : "; 
		cin>>m_sc; 
		
		cout<<"Enter marks in Social Studies : "; 
		cin>>m_sst; 
		
		cout<<"Enter marks in Language : "; 
		cin>>m_lang; 
		
		cout<<"\n==================STREAM PREFERED?================ \n"; 
		cout<<"\t"<<"[1] for SCIENCE\n"; 
		cout<<"\t"<<"[2] for COMMERCE\n"; 
		cout<<"\t"<<"[3] for ARTS "; 
		
		cout<<"\n=======================================\n\tENTER PREFERENCE CODE : "; 
		cin>>pref_code;
		
		stream=-1; 
		
		fin.write( (char*)&s , sizeof(s) ); 

        cout<<"\n\tEnter More Student ? (y/n)"; 
		cin>>ans; 
		if (ans=='n') 
			break; 
	} 
	fin.close(); 
}

void student::display() 
{   
cout<<"\n============================================\n"; 
cout<<"\n\tNAME : "<<name;
cout<<"\n\tREGISTRATION NO: "<<regno;
cout<<"\n\tPERCENTAGE OF MARKS : "<<(  (m_eng+m_math+m_sc+m_sst+m_lang)/5  )<<"%";
cout<<"\n\tSTREM APPLIED FOR : "<<stream_name(pref_code);
cout<<"\n\tSTREAM ALLOTED	: "<<stream_name(stream);  
cout<<"\n============================================\n";
}

void read_student() 
{ 
	fstream fin; 
    char c; 
	fin.open("student" ,ios::in); 
	while( fin.read(  (char*) & s ,sizeof(s) ) )
	{ 
		s.display(); 
		cout<<"\n\tPress any No. to continue "; 
		cin>>c; 
		
		cout<<"\n"; 
	} 
	fin.close();   
}

void read_eligible_sc() 
{ 
	char ans; 
	
	fstream fout; 
	fout.open("elig_sc", ios::in); 
	fout.seekg(0); 
	while( fout.read((char*)&s,sizeof(s))) 
	{ 
		s.display(); 
		cout<<"\n\t Continue (y/n)? ";   
		cin>>ans;   
		
		if (ans=='n') 
		break;   
	} 
	fout.close();   
}   

void read_eligible_com() 
{ 
	char ans; 
	
	fstream fout; 
	fout.open("eligcom",ios::in);   
	while( fout.read( (char*)&  s,sizeof(s) ) )
	{ 
		s.display(); 
		cout<<"\n\t Continue (y/n)? ";   
		cin>>ans;   
		if (ans=='n') 
			break;   
	} 
	fout.close(); 
}  

void read_eligible_arts() 
{ 
	char ans; 
	
	fstream fout; 
	fout.open("eligart",ios::in);   
	while(  fout.read( (char*)&  s, sizeof(s)  )  ) 
	{ 
		s.display(); 
		cout<<"\n\t Continue (y/n)? ";   
		cin>>ans;   
		
		if (ans=='n') 
			break;   
	} 
	fout.close(); 
} 



char * stream_name(int strm) 
{ 
	switch(strm) 
	{ 
	    case -1: 
			return("Not assigned"); 
			break; 
		case 0: 
			return("Nill"); 
				break; 
		case 1: 
			return("Science"); 
			break;
		case 2: 
			return("Commerce"); 
				break; 
		case 3: 
			return("Arts"); 
			break; 
		default: 
			return("None"); 
	}  
}

void welcome() 
{ 
	int z;
	cout<<"\n\n\n\tCOMPUTER PROJECT (******** ON STREAM ALLOCATION *******)"; 
	cout<<"\n\n\t\t\t\t   BY :-"; 
	cout<<"\n\n\t\t\t* SHAIKH HAMZA MOHAMED YUNUS"<<"\t XII B05 "; 
	cout<<"\n\n\t\t\t* OSMAN AHMED"<<"\t XIIB05 "; 
	cout<<"\n\n\t\t\t* SOHAIL SALIM"<<"\t XII B05 "; 
	cout<<"\n\n\t\t\t* ANAS SIRAJ"<<"\t XII B05 ";	
    cout<<" \n\n\n\t\t press any number and 'ENTER' to continue: "; 
	cin>>z;
} 


void thanks() 
{ 
	int w; 
   cout<<"\n\n\n\n\n\n\n\n\n\n\t********** T H A N K Y O U   F O R   W O R K I N G *******"; 
    cout<<"\n\n\n\n\n\n\n\t\tpress any number and then 'ENTER' to exit"; 
    cin>>w; 
}