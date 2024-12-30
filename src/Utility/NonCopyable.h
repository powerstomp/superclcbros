#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

// Basically boost::noncopyable

class NonCopyable {
public:
	NonCopyable() = default;
	~NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
	NonCopyable(NonCopyable&&) = default;
	NonCopyable& operator=(NonCopyable&&) = default;
};

#endif
