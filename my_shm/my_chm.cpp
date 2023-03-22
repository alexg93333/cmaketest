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
      std::string path = "/dev/shm";
      path += name;
      return open(path.data(), oflag);
    }
    else
    {
      std::string path = getenv("TMPDIR") ?: "/tmp/";
      if (path.rfind("/") == path.length() - 1)
      {
        path.pop_back();
      }

      path += "/shm";

      char* tmp_dir = mkdtemp(path.data());
      std::string mountpoint = tmp_dir ?: "";
      if (mountpoint.empty())
      {
        if (errno != EEXIST)
        {
          return -1;
        }
        else
        {
          mountpoint = path;
        }
      }

      std::string options;
      options.resize(PATH_MAX);
      options.resize(snprintf(&options[0], PATH_MAX - 1, "size=256M,uid=0,gid=0,mode=%d", mode));

      if (mount("tmpfs", mountpoint.data(), 0, options.data()) != 0)
      {
        perror("Cannot create tmpfs. Using normal /tmp file.");
      }

      std::string file = mountpoint;
      file += name;
      return open(file.data(), oflag);
    }
  }

  int shm_unlink(const char* name)
  {
    struct stat sb;
    if (stat("/dev/shm", &sb) == 0 && S_ISDIR(sb.st_mode))
    {
      std::string path = "/dev/shm";
      path += name;
      return unlink(name);
    }
    else
    {
      std::string path = getenv("TMPDIR") ?: "/tmp/";
      if (path.rfind("/") == path.length() - 1)
      {
        path.pop_back();
      }

      path += "/shm";
      path += name;

      return unmount(path.data(), 0);
    }
  }
  
}

