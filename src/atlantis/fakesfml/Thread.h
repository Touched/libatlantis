#ifndef THREAD_H_
#define THREAD_H_

#include <cstdlib>

namespace sf {

typedef void(*FuncType)(void *);

class Thread {
public:
	Thread(FuncType Function, void *UserData=NULL);
	void Launch();
	void Wait();
	void Terminate();
	virtual ~Thread();
};

} /* namespace sf */

#endif /* THREAD_H_ */
