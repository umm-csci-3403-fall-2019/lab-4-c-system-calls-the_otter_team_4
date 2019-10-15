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
   struct stat *buf;

   // Allocate memory for the output of 'stat'
   buf = malloc(sizeof(struct stat));

   // some error handling
   	if (stat(path, buf) != 0) {
      perror("stat");
   }


   // Check the output of stat. 
   // If st_mode indicates the file is a directory, then process it as such.
   // Otherwise, process is like a regular file.
   if (S_ISDIR(buf->st_mode)) 
   {
   	free(buf);
   	return true;
   } 
   else 
   {
   	free(buf);
   	return false;
   }

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

	// If the function is running, then we found a directory. Increment the count.
	num_dirs = num_dirs + 1;

	// Jump into this directory so we can beign working.
	chdir(path);

	// Initialize
	struct dirent *dp;
	DIR *dir = opendir(".");

	// Error handling
	if (!dir) {
		return;
	}

	// As long as there is something in the directory stream....
	while((dp = readdir(dir)) != NULL) 
	{

		 // CHECK: If the directory is NOT the current one AND not the parent...
		 if( strcmp(dp->d_name, "..") != 0  && strcmp(dp->d_name, ".") != 0) {

	   		// ... then call process_path recursively.
	  	 	process_path(dp->d_name);
		}
	}

	// Close dir when all done. Also free dp since we are done with it now.
	closedir(dir);
	free(dp);

	// Jump back up a directory.
	chdir("..");
	
}


// If we've identified a regular file, then increment the count.
void process_file(const char* path) {
  num_regular++;
}

// Here we see if the specified path gives us an actual directory, or just a regular file.
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
