#ifndef __OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_
#define __OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unordered_map>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include <vector>
#include <stack>

#include "rc.h"

typedef int PageNum;

//
#define BP_INVALID_PAGE_NUM (-1)
#define BP_PAGE_SIZE (1 << 12)
#define BP_PAGE_DATA_SIZE (BP_PAGE_SIZE - sizeof(PageNum))
#define BP_FILE_SUB_HDR_SIZE (sizeof(BPFileSubHeader))
#define BP_BUFFER_SIZE 50
#define MAX_OPEN_FILE 1024


typedef struct CacheNode{
  int frame_number;
  struct CacheNode *pre, *next;
  std::string id;
} CacheNode;

typedef struct {
  PageNum page_num;
  char data[BP_PAGE_DATA_SIZE];
} Page;

typedef struct {
  PageNum page_count;
  int allocated_pages;
} BPFileSubHeader;

typedef struct {
  bool dirty;
  unsigned int pin_count;
  unsigned long acc_time;
  int file_desc;
  Page page;
} Frame;

typedef struct {
  bool open;
  Frame *frame;
} BPPageHandle;

class BPFileHandle{
public:
  BPFileHandle() {
    memset(this, 0, sizeof(*this));
  }

public:
  bool bopen;
  const char *file_name;
  int file_desc;
  Frame *hdr_frame;
  Page *hdr_page;
  char *bitmap;
  BPFileSubHeader *file_sub_header;
} ;


class BPManager {
public:
  BPManager(int size = BP_BUFFER_SIZE){
    this->size = size;
    lru_map = {};
    empty_frame = {};
    //初始化hashlink
    head = new CacheNode();
    tail = new CacheNode();
    head->next = tail;
    head->pre = nullptr;
    tail->next = nullptr;
    tail->pre = head;

    this->size = size;
    this->alloc_num = 0;
    frame = new Frame[size];
    allocated = new bool[size];

    CacheNode* tmp = nullptr;
    CacheNode* index = head;

    for (int i = 0; i < size; i++) {
      allocated[i] = false;
      frame[i].pin_count = 0;
      //创建节点，不插入队列，放到空的数组里
      tmp = new CacheNode();
      tmp->frame_number = i;
      empty_frame.push(tmp);
    }
  }
  
  ~BPManager() {
    delete[] frame;
    delete[] allocated;
    size = 0;
    frame = nullptr;
    allocated = nullptr;

    //delete hashlink
    CacheNode* p = head->next;
    while(p != tail){
      CacheNode* t = p->next;
      free(p);
      p = t;
    }
    free(head);
    free(tail);
  }

  Frame *alloc() {}
  Frame *get(int file_desc, PageNum page_num) {}
  Frame *getFrame() { return frame; }
  bool *getAllocated() { return allocated; } 

  void remove(CacheNode *node);
  void setHead(CacheNode *node);
//如果get不到，直接alloc
  CacheNode* get_lru(int file_desc, PageNum page_num);
  CacheNode* alloc_lru(int file_desc, PageNum page_num);
  void dispose_lru(int file_desc, PageNum page_num);

public:
  int size;
  int alloc_num;
  Frame * frame = nullptr;
  bool *allocated = nullptr;
  std::unordered_map<std::string, CacheNode*> lru_map;
  CacheNode *head, *tail;
  std::stack<CacheNode *> empty_frame;
};

class DiskBufferPool {
public:
  RC create_file(const char *file_name);
  RC open_file(const char *file_name, int *file_id);
  RC close_file(int file_id);
  RC get_this_page(int file_id, PageNum page_num, BPPageHandle *page_handle);
  RC allocate_page(int file_id, BPPageHandle *page_handle);
  RC get_page_num(BPPageHandle *page_handle, PageNum *page_num);
  RC get_data(BPPageHandle *page_handle, char **data);
  RC dispose_page(int file_id, PageNum page_num);
  RC force_page(int file_id, PageNum page_num);
  RC mark_dirty(BPPageHandle *page_handle);
  RC unpin_page(BPPageHandle *page_handle);
  RC get_page_count(int file_id, int *page_count);
  RC flush_all_pages(int file_id);

protected:
  RC allocate_block(Frame **buf);
  RC dispose_block(Frame *buf);
  RC force_page(BPFileHandle *file_handle, PageNum page_num);
  RC force_all_pages(BPFileHandle *file_handle);
  RC check_file_id(int file_id);
  RC check_page_num(PageNum page_num, BPFileHandle *file_handle);
  RC load_page(PageNum page_num, BPFileHandle *file_handle, Frame *frame);
  RC flush_block(Frame *frame);

private:
  BPManager bp_manager_;
  BPFileHandle *open_list_[MAX_OPEN_FILE] = {nullptr};
};

DiskBufferPool *theGlobalDiskBufferPool();

#endif //__OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_
