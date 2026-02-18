#include "Page.hpp"
#include <fcntl.h> //O_Create and O_Readonly
#include <unistd.h>

PageSize CreatePageInit() {
  PageSize p;
  p.header.page_id = 0;
  p.header.record_count = 0;
  p.header.free_space_offset = sizeof(PageHeader);
  return p;
}
PageSize AddFileInit(PageSize p) {
  PageSize readMem;
  int fd = open("db.bin", O_CREAT | O_RDWR, 0644);
  if (fd < 0)
    return PageSize{};
  ssize_t wr = write(fd, &p, sizeof(PageSize));
  if (wr != sizeof(PageSize)) {
    close(fd);
    return PageSize{};
  }
  ssize_t rr = read(wr, &readMem, sizeof(PageSize));
  if (rr != sizeof(PageSize)) {
    close(fd);
    return PageSize{};
  }
  return readMem;
}