#include <string.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#else 
#include <dirent.h>
#endif
#include <sys/stat.h>

void dir_create(const char *name) {
#ifdef __linux__
	mkdir(name, 0755);
#else
	_mkdir(name);
#endif
}

void dir_create_recursive(char *name) {
	char *path = strtok(name, "/\\");
	char buffer[1024]="";
	while (path != NULL) {
		strcat(buffer, path);
		dir_create(buffer);
		strcat(buffer, "/");
		path = strtok(NULL, "/\\");
	}
}

void dir_list_files(char* directory_path,void (*file_handle)(char* file_path)){
	DIR* direct=opendir(directory_path);
	if(direct==NULL){
		return;
	}
	struct dirent* infile;
	while((infile=readdir(direct))){
		struct stat buffer;
		int status;
		status=stat(infile->d_name,&buffer);
		if(status==-1){

		}
		else if(buffer.st_mode & S_IFREG){
			file_handle(infile->d_name);
		}

	}

}
