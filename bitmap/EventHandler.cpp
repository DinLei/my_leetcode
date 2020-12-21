#include "../interfaces/EventHandler.h"
#include <stdio.h>
#include <stdexcept>
#include <stdlib.h>
#include <pthread.h>

static const std::string EVENT_FILE_SUFFIX = ".touch";
static const int MONITOR_INTERVAL_SECOND = 10;

bool UpdateAux(void *ptr) {
  AutoUpdate *p = static_cast<AutoUpdate *>(ptr);
  p->Update();
  return true;
}

EventHandler::EventHandler(const std::string &file, HandleFunc handle,
                           void *ptr) : handle_(handle), ptr_(ptr) {
  file_ = file;
  mTime_ = 0;
  struct stat fileStat;
  if (stat(file_.c_str(), &fileStat) == 0) mTime_ = fileStat.st_mtime;
}

EventFile * EventFile::spInstance = NULL;
bool EventFile::mDestroyed = false;

EventFile * EventFile::instance() {
  if (spInstance == NULL) {
    if (mDestroyed) {
      throw std::logic_error(
              "Attempting to use EventFile after "
              "destroying it.");
    }
    spInstance = new EventFile;
  }

  return spInstance;
}

void EventFile::destroy() {
  if (mDestroyed) {
    throw std::logic_error(
            "Attempting to destroy EventFile after "
            "destroying it.");
  }
  delete spInstance;
  spInstance = NULL;
  mDestroyed = true;
}

void EventFile::RegistHandler(const std::string &file, HandleFunc handle,  void *ptr) {
	/*
	if (spInstance->is_null())
		spInstance = spInstance->instance();
	*/
  std::string monitorFile = file + EVENT_FILE_SUFFIX;
//  DEBUG(LOGNAME, "watching file [%s]", monitorFile.c_str());
  pthread_mutex_lock(&spInstance->lock);
  spInstance->pool_.push_back(EventHandler(monitorFile, handle, ptr));
  pthread_mutex_unlock(&spInstance->lock);
}

void EventFile::UnRegistHandler(const std::string &file, void *ptr) {
  std::string monitorFile = file + EVENT_FILE_SUFFIX;
//  DEBUG(LOGNAME, "remove watch file [%s,%x]", monitorFile.c_str(), ptr);

  int index = -1;
  // printf("lock1 %d %s %x\n", spInstance->pool_.size(), file.c_str(), ptr);
  pthread_mutex_lock(&spInstance->lock);
  try {
    for (std::vector<EventHandler>::iterator iter = spInstance->pool_.begin();
         iter != spInstance->pool_.end(); iter++) {
      if (iter->file_ == monitorFile && iter->ptr_ == ptr) {
        // printf("erase %s\n", iter->file_.c_str());
        iter = spInstance->pool_.erase(iter);
      }
      if (iter == spInstance->pool_.end()) break;
    }
  }
  catch (...) {
    printf("UnRegistHandler error: %s.", "erase event error");
//    ERROR(LOGNAME, "erase event error");
  }
  pthread_mutex_unlock(&spInstance->lock);
  // printf("unlock1 %d\n", spInstance->pool_.size());
}

EventFile::EventFile() {
  pthread_t tid;
  pthread_mutex_init(&lock, NULL);
  if (pthread_create(&tid, NULL, startMonitor, NULL) != 0) {
//    ERROR(LOGNAME, "[EventFile] pthread_create failed.");
    exit(-1);
  }
}

EventFile::~EventFile() {};

void *EventFile::startMonitor(void *) {
//  Service <ConfigurationSettings> pSetting;
//  std::string time_s = pSetting->getSetting("main/monitor_interval_second");
  std::string time_s = "";
  int sleep_time = MONITOR_INTERVAL_SECOND;
  if (!time_s.empty()) {
    sleep_time = atoi(time_s.c_str());
    if (sleep_time < 0) {
      sleep_time = MONITOR_INTERVAL_SECOND;
    }
  }
  while (true) {
//    DEBUG(LOGNAME, "event sleeping %d seconds", sleep_time);
    sleep(sleep_time);

    skip_sleep:
    std::vector<EventHandler>::iterator it;
    pthread_mutex_lock(&spInstance->lock);
    // printf("lock\n");
    for (it = spInstance->pool_.begin(); it != spInstance->pool_.end(); it++) {
      // printf("--> (%d)%x,", spInstance->pool_.size(), it->ptr_);
      // printf("%s\n", it->file_.c_str());
      struct stat fileStat;
      if (stat(it->file_.c_str(), &fileStat) != 0) {
        continue;
      }

      if (it->mTime_ == fileStat.st_mtime) {
        continue;
      }
      it->mTime_ = fileStat.st_mtime;
      break;
    }

    EventHandler *handler = NULL;
    if (it != spInstance->pool_.end()) handler = &(*it);
    // 在unlock前不能调用handler方法，因为handle_方法会调用Update方法，而Update方法中可能存在UnRegis/Regis导致死锁
    // 所以要先确定好handler需要被执行后，unlock之后，再调用handler的handle方法
    pthread_mutex_unlock(&spInstance->lock);
    // printf("unlock\n");

    bool flag = false;
    if (handler != NULL) {
      // printf("go...\n");
      try {
        // 其实是调用注册过来的handle_方法，即UpdateAux方法，UpdateAux方法调用ptr的Update方法
        handler->handle_(handler->ptr_);
      }
      catch (...) {
//        ERROR(LOGNAME, "call handler error");
      }
      flag = true;
    }

    if (flag) goto skip_sleep;
  }
  return NULL;
}

