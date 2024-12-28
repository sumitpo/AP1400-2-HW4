#ifndef UNIQUE_PTR
#define UNIQUE_PTR
template <class T> class UniquePtr {
    public:
	UniquePtr()
	{
		_p = nullptr;
	}
	UniquePtr(T *v)
	{
		_p = v;
	}
	UniquePtr(const UniquePtr &v);
	~UniquePtr()
	{
		delete _p;
	}
	T *get()
	{
		return _p;
	}
	T &operator*()
	{
		return *_p;
	}
	T *operator->()
	{
		return _p;
	}
	void reset()
	{
		delete _p;
		_p = nullptr;
	}
	void reset(T *v)
	{
		delete _p;
		_p = v;
	}
	T *release()
	{
		T *ret = _p;
		_p = nullptr;
		return ret;
	}
	operator bool() const
	{
		return _p != nullptr;
	}

    private:
	T *_p;
};

template <typename T> UniquePtr<T> make_unique(T v)
{
	UniquePtr<T> t{ new T{ v } };
	return t;
}
#endif //UNIQUE_PTR
