#ifndef _NO_COPY_H_
#define _NO_COPY_H_

class NonCopyable  
{ 
public:
  NonCopyable() {};  
  NonCopyable(const NonCopyable&) = delete;  
  NonCopyable& operator=(const NonCopyable&) = delete;  
};  

#endif