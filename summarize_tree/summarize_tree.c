#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */

   // Initialize our stat object to be used for stat()
   struct stat buf;

   // Actual stat(). If something is wrong, then print error. 
   if (stat(path, &buf) == -1) {
      perror("stat");
   }

   // Check to see if is a directory...otherwise return break and return false
   switch (buf.st_mode & S_IFMT)
   {
      case S_IFDIR: return true;
      case S_IFIFO:  printf("FIFO/pipe\n");               break;
      case S_IFLNK:  printf("symlink\n");                 break;
      case S_IFREG:  printf("regular file\n");            break;
      case S_IFSOCK: printf("socket\n");                  break;
      case S_IFBLK:  printf("block device\n");            break;
      case S_IFCHR:  printf("character device\n");        break;
   }

	return false;
}

// Same as above
bool is_reg(const char* path) {

	struct stat buf;

	if (stat(path, &buf) == -1) {
      perror("stat");
   }

   switch (buf.st_mode & S_IFMT)
   {
   	  case S_IFREG:  return true;	
      case S_IFDIR:  printf("directory\n");               break;
      case S_IFIFO:  printf("FIFO/pipe\n");               break;
      case S_IFLNK:  printf("symlink\n");                 break;
      case S_IFSOCK: printf("socket\n");                  break;
      case S_IFBLK:  printf("block device\n");            break;
      case S_IFCHR:  printf("character device\n");        break;
  }

  return false;

}

/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {
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

	// Increment num dirs
	num_dirs = num_dirs + 1;

	struct dirent *dp;
	DIR *dir = opendir(path);

	// Unable to open directory stream
	if (!dir) {
		printf("Unable to open directory.\n");
		return;
	}

	// As long as there is something in the directory stream....
	while((dp = readdir(dir)) != NULL) 
	{
	   printf("%s\n", dp->d_name);
	}

	// Close dir when all done
	closedir(dir);

}

void process_file(const char* path) {
  num_regular = num_regular + 1;
}

void process_path(const char* path) {
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

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
