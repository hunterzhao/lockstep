#include <sys/timerfd.h>
#include <time.h>
#include "timer_event.h"
#include "reactor.h"
#include "log.h"
#include "type.h"

namespace game
{
TimerEvent::TimerEvent(Reactor* reactor, int fd, int msecond, OnTimer timer)
   : SocketEvent(reactor, fd), 
     msecond_(msecond), 
     timer_(timer)
{

}


TimerEvent::~TimerEvent()
{

}

int TimerEvent::init()
{
   struct itimerspec new_value;
   struct timespec now;
   if (clock_gettime(CLOCK_REALTIME, &now) == -1)
   {
      DLOG(ERROR) << "clock error";
   }
    
   //start time of timer 
   new_value.it_value.tv_sec = now.tv_sec + 2;
   new_value.it_value.tv_nsec = now.tv_nsec;

   //loop time
   new_value.it_interval.tv_sec = msecond_ / 1000;
   new_value.it_interval.tv_nsec = (msecond_ % 1000) * 1000000;

   if (timerfd_settime(fd_, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
   {
      DLOG(ERROR) << "timerfd_settime";
      perror("timerfd");
   }
    
   if (reactor_->registerHandler(this, EVENT_IN) < 0)
   {
       return -1;
   }
   return 1;
}

int TimerEvent::onEvent(int event)
{
   if (event & EVENT_ERR)
   {
      LOG(ERROR) << "error";
      closeInNextLoop();
   }

   if (event & EVENT_IN)
   {
      excuteTimingTask();
   }   
   reactor_->modifyHandler(this, EVENT_IN);
   return 1;
}

void TimerEvent::close()
{
   DLOG(WARNING) << "remove timer event";
   reactor_->removeHandler(this);
   ::close(fd_);
}

void TimerEvent::excuteTimingTask()
{
   uint64_t id;
 //  printf("time is out\n");
   ::read(fd_, &id, sizeof(uint64_t));
   timer_();
 //  struct timespec now;
 //  if (clock_gettime(CLOCK_REALTIME, &now) == -1)
 //  {
 //     DLOG(ERROR) << "clock error";
 //  }
 //  printf("%d %d\n", now.tv_sec, now.tv_nsec / 1000000 );
 //  
}
}
