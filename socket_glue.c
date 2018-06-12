/* network stub calls */
#include <sys/time.h>
#include <vfscore/file.h>
#include <uk/alloc.h>
#include <uk/essentials.h>
#include <uk/print.h>
#include <stdio.h>
#include <errno.h>
#include <lwip/sockets.h>

#define  NET_LIB_NAME          "lwip-socket"
#define  SOCK_NET_SET_ERRNO(errcode) \
			do {\
				errno = -(errcode);\
			} while(0)


struct sock_net_file {
	struct vfscore_file vfscore_file;
	int sock_fd;
};

static int sock_fd_alloc(struct vfscore_fops *fops, int sock_fd)
{
	int ret = 0;
	int vfs_fd;
	struct sock_net_file *file = NULL;

	/* Allocate file descriptor */
	vfs_fd = vfscore_alloc_fd();
	if (vfs_fd < 0) {
		ret = -ENFILE;
		uk_printd(DLVL_ERR, "failed to allocate socket fd\n");
		goto EXIT;
	}

	file = uk_malloc(uk_alloc_get_default(), sizeof(*file));
	if (!file) {
		ret = -ENOMEM;
		uk_printd(DLVL_ERR, "failed to allocate socket fd - no mem\n");
		goto UK_MEM_ALLOC_ERR;
	}
	file->vfscore_file.fops = fops;
	file->sock_fd = sock_fd;
	uk_printd(DLVL_EXTRA, NET_LIB_NAME":allocated socket %d (%x)\n",
			file->vfscore_file.fd, file->sock_fd);
	/* Storing the information within the vfs structure */
	vfscore_install_fd(vfs_fd, &file->vfscore_file);
	ret = vfs_fd;
EXIT:
	return ret;

UK_MEM_ALLOC_ERR:
	vfscore_put_fd(vfs_fd);
	goto EXIT;
}

static int sock_net_close(struct vfscore_file *vfscore_file)
{
	int    ret = 0;
	return ret;
}

static ssize_t sock_net_write(struct vfscore_file *vfscore_file, const void *buf,
			     size_t count)
{
	int ret = 0;
	return ret;
}

static ssize_t sock_net_read(struct vfscore_file *vfscore_file, void *buf,
			    size_t count)
{
	int ret = 0;
	return ret;
}

static struct vfscore_fops sock_net_fops = {
	.close = sock_net_close,
	.write = sock_net_write,
	.read  = sock_net_read,
};

int socket(int domain, int type, int protocol)
{
	int ret = 0;
	int vfs_fd = 0xff;
	int sock_fd = 0;

	/* Create lwip_socket */
	sock_fd = lwip_socket(domain, type, protocol);
	if(0 > sock_fd) {
		uk_printd(DLVL_ERR, "failed to create socket %d\n", errno);
		ret = -1;
		goto EXIT;
	}

	/* Allocate the file descriptor */
	vfs_fd = sock_fd_alloc(&sock_net_fops, sock_fd);
	if(0 > vfs_fd) {
		uk_printd(DLVL_ERR, "failed to allocate descriptor %d\n", errno);
		ret = -1;
		/* Setting the errno */
		SOCK_NET_SET_ERRNO(vfs_fd);
		goto LWIP_SOCKET_CLEANUP;
	}

	/* Returning the file descriptor to the user */
	ret = vfs_fd;
EXIT:
	return ret;
LWIP_SOCKET_CLEANUP:
	/* Cleanup the lwip socket */
	lwip_close(sock_fd);
	goto EXIT;
}

int accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
	int ret = 0;
	return ret;
}

int bind(int s, const struct sockaddr *name, socklen_t namelen)
{
	int ret = 0;
	return ret;
}

int shutdown(int s, int how)
{
	int ret = 0;
	return ret;
}

int getpeername(int s, struct sockaddr *name, socklen_t *namelen)
{
	int ret = 0;
	return ret;
}

int getsockname(int s, struct sockaddr *name, socklen_t *namelen)
{
	int ret = 0;
	return ret;
}

int getsockopt(int s, int level, int optname, void *optval, socklen_t
		*optlen)
{
	int ret = 0;
	return ret;
}

int setsockopt (int s, int level, int optname, const void *optval,
		socklen_t optlen)
{
	int ret = 0;
	return ret;
}

int connect(int s, const struct sockaddr *name, socklen_t namelen)
{
	int ret = 0;
	return ret;
}

int listen(int s, int backlog)
{
	int ret = 0;
	return ret;
}

int recv(int s, void *mem, size_t len, int flags)
{
	int ret = 0;
	return ret;
}

int recvfrom(int s, void *mem, size_t len, int flags,
		      struct sockaddr *from, socklen_t *fromlen)
{
	int ret = 0;
	return ret;
}

int send(int s, const void *dataptr, size_t size, int flags)
{
	int ret = 0;
	return ret;
}

int sendmsg(int s, const struct msghdr *message, int flags)
{
	int ret = 0;
	return ret;
}

int sendto(int s, const void *dataptr, size_t size, int flags,
		    const struct sockaddr *to, socklen_t tolen)
{
	int ret = 0;
	return ret;
}

int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set
		*exceptset, struct timeval *timeout)
{
	int ret = -ENOTSUP;
	return ret;
}