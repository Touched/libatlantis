#ifndef SELECTOR_H_
#define SELECTOR_H_

namespace sf {

template<typename Type>
class Selector {
public:
	Selector();
	void Clear();
	void Add(Type socket);
	unsigned int Wait(float timeout=0.f);
	virtual ~Selector();
};

} /* namespace sf */

#endif /* SELECTOR_H_ */
