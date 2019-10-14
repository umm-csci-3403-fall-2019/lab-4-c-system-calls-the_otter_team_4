#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

int getdir() {
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd, "\n");
   } else {
       perror("getdir() error\n");
       return 1;
   }
   return 0;
}

bool is_dir(const char* path) {

	printf("\n==== checking is_dir ====\n");

  /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */

   // Initialize our stat object to be used for stat()

   struct stat *buf;

   // Actual stat(). If something is wrong, then print error. 
   // if (stat(path, &buf) == -1) {
   //    perror("stat");
   // }

   // printf("File type:                ");

           // switch (buf.st_mode & S_IFMT) {
           // case S_IFBLK:  printf("block device\n");            break;
           // case S_IFCHR:  printf("character device\n");        break;
           // case S_IFDIR:  printf("directory\n");               break;
           // case S_IFIFO:  printf("FIFO/pipe\n");               break;
           // case S_IFLNK:  printf("symlink\n");                 break;
           // case S_IFREG:  printf("regular file\n");            break;
           // case S_IFSOCK: printf("socket\n");                  break;
           // default:       printf("unknown?\n");                break;
           // }
           // return false;


   // Check to see if is a directory...otherwise return break and return false
   // if(stat(path, &buf) == 0) {
   // 	if (S_ISDIR(buf.st_mode)) {
   // 		return true;
   // 	}

 //   	printf("Not a directory\n");
 //   	return false;
 //   }
 //   	printf("Checkdir failed. Something's wrong\n");
	// return false;

   buf = malloc(sizeof(struct stat));

   getdir();

   stat(path, buf);
   if (S_ISDIR(buf->st_mode)) {
   	free(buf);
   	printf("*** directory identified: ");
   	printf(path);
   	printf("\n");
   	return true;
   } else {
   	free(buf);
   	printf("!!! directory not identified: ");
   	printf(path);
   	printf("\n");
   	return false;
   }

}

// Same as above
// bool is_reg(const char* path) {

// 	struct stat buf;

// 	if (stat(path, &buf) == -1) {
//       perror("stat");
//    }

//    switch (buf.st_mode & S_IFMT)
//    {
//    	  case S_IFREG:  printf("regular file\n");		return true;	
//   }

//   printf("not a regular file\n");
//   return false;

// }

/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {

	printf("\n==== processing directory ====\n");
	getdir();

  /*
   * Update the number of directories seen, use opendir() to open the
   * directory, and then use readdir() to loop through the entries
   * and process them. You have to be careful not to process the
   * "." and ".." directory entries, or you'll end up spinning in
   * (infinite) loops. Also make sure you closedir() when you're done.
   *
   * You'll also want to use chdir() to move into this new directory,
   * with a matching call to chdir() to move back out of it when you're
   * done.
   */

	// If the function is running, then we found a directory. Increment the count.
	num_dirs = num_dirs + 1;

	// Initialize
	struct dirent *dp;
	DIR *dir = opendir(path);

	// Error handling
	if (!dir) {
		printf("Unable to open directory.\n");
		return;
	}

	chdir(path);

	// As long as there is something in the directory stream....
	while((dp = readdir(dir)) != NULL) 
	{

		 if( strcmp(dp->d_name, "..") != 0  && strcmp(dp->d_name, ".") != 0) {
	   		// Print the filename
	  	 	printf("%s\n", dp->d_name);

	  	 	char str[PATH_MAX];
	  	 	strcpy(str, path);
	  	 	strcpy(str, "/");
	  	 	strcpy(str, dp->d_name);

	  	 	printf("Path constructed.");
	  	 	printf(str);
	   		// If it IS A DIRECTORY...call process directory recursively.
	   		// Note: This is not ready to run. chdir() needs to happen at some point before the recursion
	   		// Also: See Nic's notes above on the '.' and '..' directories
	  	 	chdir(dp->d_name);
	  	 	process_path(dp->d_name);
		}
	}

	// Close dir when all done
	printf("Moving up a directory...\n");
	chdir("..");
	closedir(dir);

}

void process_file(const char* path) {
  num_regular = num_regular + 1;
  printf("Processing file\n");
}

void process_path(const char* path) {
	printf("\n==== processing path ====\n");
	printf(path);
	printf("\n==============================\n");
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  printf("*************\n");
  printf("*************\n");
  printf("*************\n");
  printf("\n==== running main ====\n");

  num_dirs = 0;
  num_regular = 0;

  printf("Argv1: \n");
  printf(argv[1]);
  printf("\n");

  process_path(argv[1]);


  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
