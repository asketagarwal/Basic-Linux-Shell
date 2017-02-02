#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include <fcntl.h>
#include<pwd.h>
#include<sys/stat.h>

void main()
{
	
	
	while(1)
	{	
		char buf[100];char temp[20];
		char * a=get_current_dir_name();
		printf("%s >",a);
		fflush(NULL);
		int t=read(0,buf,200);
		//buf[t]=' ';
		buf[t-1]='\0';
		//printf("%c",buf[t-1]);
		/*int posn;
		char *str=buf;
		char ar[10][20];int i=0;
		while (sscanf(str, "%255s%n", temp, &posn) == 1)
        {
            
            strcpy(ar[i++],temp);
            str += posn;
        }*/

        char *ar[10];
        char *link;
        link=strtok(buf," ");
		int i=0;
		while(link!=NULL)		
		{
			ar[i]=(char *)malloc((strlen(link)+1));
			strcpy(ar[i],link);
			link=strtok(NULL," ");
			i++;
		}
		ar[i]=NULL;
		//printf("%d\n",i);
		




       // printf("%d\n",i);
        
        
        if(strcmp(ar[0],"pwd")==0)
        {	
        	
        	printf("The present working directory is: %s\n",a);fflush(stdout);
        	
        	
        	
		}
		else if(strcmp(ar[0],"cd")==0)
		{
			int x=chdir(ar[1]);
			if(x==-1)
				perror("Error: ");
		}
		else if(strcmp(ar[0],"mkdir")==0) {
			
			int x=mkdir(ar[1], 0700);
    		if(x==-1)
    			perror("mkdir");	
		}
		else if(strcmp(ar[0],"rmdir")==0)
		{
			int x=rmdir(ar[1]);
			if(x==-1)
				perror("rmdir");

		}
		else if(strcmp(ar[0],"ls")==0)
		{
			DIR * pdir;
			struct dirent *pent=NULL;
			pdir=opendir(".");
			struct stat fileStat;

			if(!pdir)
				perror("Error: ");int j=0;
			while(pent=readdir(pdir))
			{	
				printf("\n%-30s        ",pent->d_name);
				if(i==1)
					
						continue;

				char t1[100];
				strcpy(t1,a);strcat(t1,"/");strcat(t1,pent->d_name);
				if(stat(t1,&fileStat)<0)
					perror("error");

				printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    			printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    			printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    			printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    			printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    			printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    			printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    			printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    			printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    			printf( (fileStat.st_mode & S_IXOTH) ? "x          " : "-          ");
    			printf("%d         ",fileStat.st_size);
    			struct passwd *pwd;
    			pwd=getpwuid(fileStat.st_uid);
    			printf("%s",pwd->pw_name);


					
				
				
			}
			printf("\n");
			closedir(pdir);
		}
		else if(strcmp(ar[0],"cp")==0)
		{
			if(i!=3)
				printf("Wrong no of arguments\n");
			int f1=open(ar[1],0,"r");
			if(f1==-1)
			{
				perror("File open failed");
				exit(0);
			}
			int f2=open(ar[2], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if(f2==-1)
			{
				perror("File open failed");
				exit(0);
			}
			struct stat buf1,buf2;
			char t1[100],t2[100];
			strcpy(t1,a);strcpy(t2,a);strcat(t1,"/");strcat(t2,"/");
			strcat(t1,ar[1]);strcat(t2,ar[2]);
			//printf("%s %s",t1,t2);
			if(stat(t1,&buf1)==-1 || stat(t2,&buf2)==-1)
			{
				perror("Error");
				continue;
			}
			if( access( ar[2], F_OK ) != -1 && buf1.st_mtime<buf2.st_mtime)
			{
				printf("Modification time of the second file is greater\n");
				continue;
			}
			int temp=100;
			while(temp==100)
			{
				char buf[101];
				temp=read(f1,buf,100);
				write(f2,buf,100);

			}
		}
		else if(strcmp(ar[0],"exit")==0)
			exit(0);

		else if(ar[0]==NULL)
			continue;

		else {

			char temp[3];
			temp[0]=ar[0][0];temp[1]=ar[0][1];temp[2]='\0';
			//if(strcmp(temp,"./")!=0)
			//{	printf("Inavalid command\n");continue;}
				int f=0;
				for(int x=0;x<i;x++)
				{
					if(ar[x][0]=='|')
						f=1;
				}
				int is_bg=0;
				if(ar[0][strlen(ar[0])-1]=='&')
				{
					ar[0][strlen(ar[0])-1]='\0';
					is_bg=1;
				}
			if(f!=1)
			{int id=fork();
			if(!id)
			{	int flag=0;
				for(int j=0;j<i;j++)
				{	
					
					if(ar[j][0]=='<')
					{
						flag=1;
						ar[j]=NULL;

						
						int o=open(ar[j+1],O_RDONLY);
						//printf("%s\n",ar[j+1]);


						dup2(o,0);
						close(o);
						
					}
					else if(ar[j][0]=='>')
					{
						ar[j]=NULL;
						//printf("%d ",j);
						flag=1;
						int o=open(ar[j+1], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
						dup2(o,1);
						close(o);
						
					}





				}
				//if(flag==0) exit(0);
				execvp(ar[0],ar);
				perror("Error");
			}}
			int status;
			if(!is_bg)
				wait(&status);

			 f=0;
			for(int x=0;x<i;x++)
			{
				if(ar[x][0]=='|')
					f=1;
			}
			
			if(f==0)
				continue;

			int id=fork();
			if(!id)
			{	int flag=0;
				
				if(i==3)
				{
					if(ar[1][0]=='|')
					{	flag=1;
						
						int fd[2];
						int a=pipe(fd);
						int id1=fork();
						if(!id1)
						{
							close(fd[1]);
							dup2(fd[0],0);
							execvp(ar[2],ar);
						}
						else{
							close(fd[0]);
							dup2(fd[1],1);
							execvp(ar[0],ar);
						}


					}
				}

				else if(i==5)
				{	if(ar[1][0]=='|' && ar[3][0]=='|')
					{
						flag=1;
						int fd2[2];
						int a=pipe(fd2);
						int id1=fork();
						if(!id1)
						{
							close(fd2[0]);
							int fd1[2];
							int b=pipe(fd1);
							int id2=fork();
							if(!id2)
							{
								close(fd1[0]);
								dup2(fd1[1],1);
								execvp(ar[0],ar);
							}
							else {
								close(fd1[1]);
								dup2(fd1[0],0);
								dup2(fd2[1],1);
								execvp(ar[2],ar);

							}
						}
						else{
							close(fd2[1]);
							dup2(fd2[0],0);
							execvp(ar[4],ar);
						}
					}

				}

				

				

				if(flag==0){
					printf("Invalid Piping\n");
					exit(0);
				}
			}



			
			if(!is_bg)
				wait(&status);






		}


		for(int x=0;x<i;x++)
			free(ar[i]);


		fflush(NULL);
		
		
		



	}
}