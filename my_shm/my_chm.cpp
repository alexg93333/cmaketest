#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>

namespace my_shm {
  int shm_open(const char* name, int oflag, mode_t mode);
  int shm_unlink(const char* name);
  
  int shm_open(const char* name, int oflag, mode_t mode)
{
  struct stat sb;
  if (stat("/dev/shm", &sb) == 0 && S_ISDIR(sb.st_mode))
  {
    const char* path = "/dev/shm";
    path += name;
    return open(path.data(), oflag);
  }
  else
  {
    const char* path = getenv("TMPDIR") ?: "/tmp/";
    if (path.rfind("/") == path.length() - 1)
    {
      path.pop_back();
    }

    path += name;

    char* mountpoint = mkdtemp(path.data());
    if (!mountpoint)
    {
      remove(mountpoint);
      return -1;
    }

    const char* options;
    options.resize(PATH_MAX);
    options.resize(snprintf(&options[0], PATH_MAX - 1, "size=256M,uid=0,gid=0,mode=%d", mode));

    if (mount("tmpfs", mountpoint, 0, options.data()) != 0)
    {
      //rmdir(mountpoint);
      //return -1;
      perror("Cannot create tmpfs. Using normal /tmp file.");
    }

    return open(mountpoint, oflag);
  }
}

int shm_unlink(const char* name)
{
  struct stat sb;
  if (stat("/dev/shm", &sb) == 0 && S_ISDIR(sb.st_mode))
  {
    const char* path = "/dev/shm";
    path += name;
    return unlink(name);
  }
  else
  {
    const char* path = getenv("TMPDIR") ?: "/tmp/";
    if (path.rfind("/") == path.length() - 1)
    {
      path.pop_back();
    }

    path += name;

    return unmount(path.data(), 0);
  }
}
}

