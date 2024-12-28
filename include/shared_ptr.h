#ifndef SHARED_PTR
#define SHARED_PTR

template <class T> class SharedPtrObj {
    public:
	SharedPtrObj()
	{
	}
	int count()
	{
		return ref_cnt;
	}
	int add()
	{
		ref_cnt += 1;
		return ref_cnt;
	}
	int minus()
	{
		ref_cnt -= 1;
		if (ref_cnt == 0)
			delete _p;
		return ref_cnt;
	}
	T *get()
	{
		return _p;
	}
	void set(T *v)
	{
		_p = v;
		ref_cnt = 1;
	}
	~SharedPtrObj()
	{
	}

    private:
	T *_p;
	int ref_cnt;
};
template <class T> class SharedPtr {
    public:
	SharedPtr()
	{
		spObj = nullptr;
	}
	SharedPtr(T *v)
	{
		spObj = new SharedPtrObj<T>();
		spObj->set(v);
	}
	~SharedPtr()
	{
		if (nullptr != spObj && 0 == spObj->minus())
			delete spObj;
		spObj = nullptr;
	}
	SharedPtr(const SharedPtr &sp)
	{
		spObj = sp.spObj;
		spObj->add();
	}
	SharedPtr &operator=(const SharedPtr &sp)
	{
		if (this == &sp) {
			return *this;
		}
		if (nullptr != this->spObj && 0 == this->spObj->minus())
			delete this->spObj;
		this->spObj = sp.spObj;
		this->spObj->add();
		return *this;
	}
	int use_count()
	{
		if (nullptr == spObj)
			return 0;
		return spObj->count();
	}
	T operator*()
	{
		return *(spObj->get());
	}
	T *get()
	{
		if (spObj == nullptr)
			return nullptr;
		return spObj->get();
	}
	T *operator->()
	{
		return spObj->get();
	}
	operator bool() const
	{
		return spObj != nullptr && spObj->get() != nullptr;
	}
	void reset()
	{
		if (nullptr != spObj) {
			spObj->minus();
			spObj = nullptr;
		}
	}
	void reset(T *v)
	{
		if (nullptr != spObj && 0 == spObj->minus())
			delete spObj;
		spObj = new SharedPtrObj<T>();
		spObj->set(v);
	}

    private:
	SharedPtrObj<T> *spObj;
};

template <typename T> SharedPtr<T> make_shared(T v)
{
	SharedPtr<T> p{ new T{ v } };
	return p;
}

#endif //SHARED_PTR
