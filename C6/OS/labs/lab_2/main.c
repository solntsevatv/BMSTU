#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include <unistd.h> 
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h> 


typedef int func_type(const char *, const struct stat *, int); //func type for getting file info
static int myftw(char *, func_type *);
static int dopath(const char*, int, func_type *);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

#define FTW_F 1
#define FTW_D 2 
#define FTW_DNR 3 
#define FTW_NS 4
static char *fullpath; 
static size_t pathlen;

static void print_error_arg(char *error, char *fname)
{
    char str[100];
    strcpy(str, error);
    strcat(str, fname);
    perror(str);
    exit(1);
}

static void print_error_double_arg(char *error, char *arg_1, char *arg_2)
{
    char str[100];
    strcpy(str, error);
    strcat(str, arg_1);
    strcat(str, " ");
    strcat(str, arg_2);
    perror(str);
    exit(1);
}

// gets func return
static int myftw(char *pathname, func_type *func)
{
    fullpath = (char*)malloc(sizeof(char) * 1024);
    if (pathlen <= strlen(pathname)) 
    {
        pathlen = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL)
        {
            perror("ошибка вызова realloc");
            exit(1);
        }
    }
    strcpy(fullpath, pathname);
    return (dopath(fullpath, 0, func));
}

//recursive paths
static int dopath(const char *fpath, int depth, func_type* func)
{
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp; //directory
    int ret, n;
    
    if (lstat(fpath, &statbuf) < 0) // stat error
        return(func(fpath, &statbuf, FTW_NS));

    for (int i = 0; i < depth; ++i)
		printf(".\t");

    if (S_ISDIR(statbuf.st_mode) == 0) // not dir
        return(func(fpath, &statbuf, FTW_F));

    if ((ret = func(fpath, &statbuf, FTW_D)) != 0)
        return(ret);

    /*
    n = strlen(fpath);

    if (n + NAME_MAX + 2 > pathlen)
    {
        pathlen *= 2;
        if ((fpath = realloc(fpath, pathlen)) == NULL)
        {
            perror("ошибка вызова realloc");
            exit(1);
        }
    }
    */

    //fpath[n++] = '/';
    //fpath[n] = 0;

    if ((dp = opendir(fpath)) == NULL) // not accessable
        return(func(fpath, &statbuf, FTW_DNR));
    
    chdir(fpath);

    while ((dirp = readdir(dp)) != NULL)
    {
        if (strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0 )
		{
			ret = dopath(dirp->d_name, depth + 1, func);
		}
    }

    chdir("..");

    //fpath[n-1] = 0;
    
    if (closedir(dp) < 0)
        print_error_arg("невозможно закрыть каталог ", fpath);
        
    return (ret);
}

static int myfunc(const char *pathname, const struct stat *statptr, int type)
{
    switch (type) 
    {
        case FTW_F:
            printf( "-- %s i_node: %ld\n", pathname, statptr->st_ino);
            switch (statptr->st_mode & S_IFMT) 
            {
                case S_IFREG: nreg++; break;
                case S_IFBLK: nblk++; break;
                case S_IFCHR: nchr++; break;
                case S_IFIFO: nfifo++; break;
                case S_IFLNK: nslink++; break;
                case S_IFSOCK: nsock++; break;
                case S_IFDIR: // dir must be FTW_D
                print_error_arg("признак S_IFDIR для ", pathname);
            }
            break;
        case FTW_D:
            printf( "-- %s/ %ld\n", pathname, statptr->st_ino);
			ndir++; 
			break;
        case FTW_DNR:
            print_error_arg("закрыт доступ к каталогу ", pathname);
            break;
        case FTW_NS:
            print_error_arg("ошибка вызова функции stat для ", pathname);
            break;
        default:
            print_error_double_arg("неизвестный тип файла ", type, pathname);
    }
    return 0;
}


int main(int argc, char *argv[])
{
    int ret;
    if (argc != 2)
    {
        perror("Использование: ftw <начальный_каталог>");
        exit(1);
    }
    ret = myftw(argv[1], myfunc); //search
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0)
        ntot = 1;
    
    printf("\n\n");
    printf("обычные файлы = %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
    printf("каталоги = %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
    printf("специальные файлы блочных устройств = %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot);
    printf("специальные файлы символьных устройств = %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
    printf("FIFO = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
    printf("символические ссылки = %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
    printf("сокеты = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);
    exit(ret);
}