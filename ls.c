#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


void myls(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    int spaces = depth*4;
    char buff[20];
    struct passwd pwent;  
    struct passwd *pwentp; 
    struct group grp;  
  	struct group *grpt;
    char buf[1024];
    char buf1[1024]; 
    
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
   // chdir(dir);
    while((entry = readdir(dp)) != NULL) 
    {
        lstat(entry->d_name,&statbuf);    
		strftime(buff, sizeof(buff), "%b %d %H:%M", localtime(&statbuf.st_atime));

            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 ||strcmp("..",entry->d_name) == 0)
            {
                continue;
			}
    			printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
    			printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
    			printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
    			printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
    			printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
    			printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
    			printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
    			printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
    			printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
    			printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
    			getpwuid_r(statbuf.st_uid, &pwent, buf, sizeof(buf), &pwentp);
    			getgrgid_r (statbuf.st_gid, &grp, buf1, sizeof(buf1), &grpt);
                printf("%*s %3d %s %s %5lld %10s %s\n",spaces,"",statbuf.st_nlink,pwent.pw_name, grp.gr_name, statbuf.st_size, buff, entry->d_name);
                
                    
    }
  // chdir("..");
    closedir(dp);
}

/*  Now we move onto the main function.  */

int main(int argc, char* argv[])
{
    char *topdir, pwd[2]=".";
    if (argc != 2)
    {
        topdir=pwd;
	}
    else
	{
        topdir=argv[1];
    }
   // printf("Scan of %s\n",topdir);
    myls(topdir,0);
   // printf("done.\n");
    
    return 0;
}