#include <poll.h>

int main(int argc, char** argv){
	struct pollfd all[argc-1];
	int fd[argc-1];
	int i, k[2048];
	struct stat t;
	if (argc<2) return -1;
	for (i=1; i<argc; i++){
		if ((fd[i-1]=open(argv[i], O_NONBLOCK|O_RDONLY)<0)
			goto a;
		all[i-1].fd = fd[i-1];
		all[i-1].events = POLLIN;
	}
	if (poll(all, argc-1, 5000)<0) return -1;
	for (i=1; i<argc; i++){
		if (all[i-1].revents & POLLIN==all[i-1].revents){
			fstat(all[i-1].fd, t);
			if (read(fd, k, t.st_size)==0)
				printf("%s", k);
		}
	}
	return 0;
}