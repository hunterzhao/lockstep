#ifndef _DLOG_H_
#define _DLOG_H_
#include <glog/logging.h>
#include <string>
#include <fstream>

namespace game
{
class GLogHelper
{
public:
    GLogHelper(char* program);
 
    ~GLogHelper();

    void initGlog();
    
    //将信息输出到单独的文件和 DLOG(ERROR)
    static void SignalHandle(const char* data, int size);
};
}
#endif
