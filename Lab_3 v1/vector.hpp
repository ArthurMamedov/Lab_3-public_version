#pragma once
#include<cassert>
#include<iostream>
namespace KoSTL {
	using uint = unsigned int;

	template<class T> class vector {
	protected:
		T* vec_;
		uint size_;
		uint capacity_;
	public:
		vector();
		vector(std::initializer_list<T> init);
		vector(const vector<T>& other);
		vector(uint _size, T _val);
		~vector();
		void clear();
		void push_back(T val);
		T pop_back();
		void insert(uint _where, T* _first, T* _last);
		void insert(T* _where, T* _first, T* _last);
		void insert(uint _where, T _val);
		void insert(T* _where, T _val);
		void reserve(uint size);
		void resize(uint size, T val);
		void shrink_to_fit();
		uint size() const;
		uint capacity() const;
		bool empty() const;
		T* begin() const;
		T* end() const;
		T& front();
		void erase(const uint _where);
		void erase(const uint _first, const uint _last);
		//void erase(const T* _where);
		void erase(const T* _first, const T* _last);
		T& back();
		T& operator[](uint _index);
		const T& operator[](uint _index) const;
		vector<T> operator=(const vector<T>& other);
	};

	template<class T>
	inline vector<T> vector<T>::operator=(const vector<T>& other) {
		if (capacity_ < other.size_) {
			delete[] vec_;
			size_ = other.size_;
			capacity_ = other.capacity_;
			vec_ = new T[capacity_];
			memmove(vec_, other.vec_, size_ * sizeof(T));
		}
		else {
			size_ = other.size_;
			memmove(vec_, other.vec_, size_ * sizeof(T));
		}
		return *this;
	}

	template<class T>
	inline vector<T>::vector() {
		size_ = 0;
		capacity_ = 0;
		vec_ = nullptr;
	}

	template<class T>
	inline vector<T>::vector(std::initializer_list<T> init) {
		for (auto _init : init)
			push_back(_init);
	}

	template<class T>
	inline vector<T>::vector(const vector<T>& other) {
		size_ = other.size_;
		capacity_ = other.capacity_;
		vec_ = new T[capacity_];
		for (uint c = 0; c < size_; c++) {
			vec_[c] = other.vec_[c];
		}
	}

	template<class T>
	inline vector<T>::vector(uint _size, T _val) {
		size_ = _size;
		capacity_ = _size;
		vec_ = new T[capacity_];

		for (uint i = 0; i < size_; ++i)
			vec_[i] = _val;
	}

	template<class T>
	inline void vector<T>::clear() {
		size_ = 0;
	}

	template<class T>
	inline vector<T>::~vector() {
		delete[] vec_;
	}

	template<class T>
	inline void vector<T>::push_back(T val) {
		if (size_ == capacity_) {
			if (capacity_ > 0)
				capacity_ *= 2;
			else
				capacity_ = 10;
			T* tmp = new T[capacity_];
			memmove(tmp, vec_, size_ * sizeof(T));
			delete[] vec_;
			vec_ = tmp;
		}
		vec_[size_++] = val;
	}

	template<class T>
	inline T vector<T>::pop_back() {
		if (size_ < 1) {

			throw std::exception("An attempt into pop_back from an empty vector");
		}
		return vec_[--size_];
	}

	template<class T>
	inline void vector<T>::insert(uint _where, T* _first, T* _last) {
		assert((0 <= _where and _where <= size_) and _first <= _last);

		uint diff = _last - _first;
		if (size_ + diff <= capacity_) {
			for (uint c = _where; c < diff; c++)
				std::swap(vec_[c], vec_[c + diff]);
			for (uint c = _where; c < diff + _where; c++)
				vec_[c] = *(_first + c - _where);
			size_ += diff;
			return;
		}
		else {
			uint tmp_size = size_ + diff;
			T* tmp = new T[tmp_size];

			for (uint i = 0; i < _where; ++i)
				tmp[i] = vec_[i];
			for (uint i = 0; i < diff; ++i)
				tmp[i + _where] = *(_first + i);
			for (uint i = 0; i < size_ - _where; ++i)
				tmp[_where + i + diff] = vec_[_where + i];

			delete[] vec_;
			size_ = tmp_size;
			capacity_ = tmp_size;
			vec_ = tmp;
			return;
		}
	}

	template<class T>
	inline void vector<T>::insert(T* _where, T* _first, T* _last) {
		uint index = _where - begin();
		insert(index, _first, _last);
	}

	template<class T>
	inline void vector<T>::insert(uint _where, T _val) {
		assert(0 <= _where && _where <= size_);

		push_back(_val);

		if (_where != size_) {
			for (size_t i = size_ - 1; i > _where; --i)
				vec_[i] = vec_[i - 1];
			vec_[_where] = _val;
		}
	}
	template<class T>
	inline void vector<T>::insert(T* _where, T _val) {
		assert(begin() <= _where and _where <= end());
		uint tmp = _where - begin();
		push_back(_val);
		if (tmp != size_) {
			for (size_t c = size_ - 1; c > tmp; --c)
				vec_[c] = vec_[c - 1];
			vec_[tmp] = _val;
		}
	};

	template<class T>
	inline void vector<T>::reserve(uint size) {
		T* tmp = new T[size + capacity_];

		memmove(tmp, vec_, size_ * sizeof(T));

		delete[] vec_;
		vec_ = tmp;
		capacity_ = capacity_ + size;
	}

	template<class T>
	inline void vector<T>::resize(uint size, T val) {
		if (size == size_) {
			return;
		}
		else if (size > size_) {
			if (capacity_ < size) {
				capacity_ = size;
				T* tmp = new T[capacity_];
				for (uint i = 0; i < size_; ++i)
					tmp[i] = vec_[i];
				for (uint i = size_; i < size; ++i)
					tmp[i] = val;
				size_ = size;
				delete[] vec_;
				vec_ = tmp;
				return;
			}
			else {
				for (uint i = size_; i < size; ++i)
					vec_[i] = val;
				size_ = size;
				return;
			}
		}
		else {
			size_ = size;
			return;
		}
	}

	template<class T>
	inline void vector<T>::shrink_to_fit() {
		if (capacity_ > size_)
		{
			T* tmp = new T[size_];
			memmove(tmp, vec_, size_ * sizeof(T));

			delete[] vec_;
			vec_ = tmp;
			capacity_ = size_;
		}
	}

	template<class T>
	inline uint vector<T>::size() const {
		return size_;
	};

	template<class T>
	inline uint vector<T>::capacity() const {
		return capacity_;
	};

	template<class T>
	inline bool vector<T>::empty() const {
		return (size_ > 0 ? false : true);
	}

	template<class T>
	inline T* vector<T>::begin() const {
		return vec_;
	}

	template<class T>
	inline T* vector<T>::end() const {
		return &vec_[size_];
	}

	template<class T>
	inline T& vector<T>::front() {
		assert(size_ > 0);
		return vec_[0];
	}

	template<class T>
	inline void vector<T>::erase(const uint _where) {
		assert(0 <= _where and _where < size_);
		--size_;
		for (size_t c = _where; c < size_; c++)
			std::swap(vec_[c], vec_[c + 1]);
	}

	template<class T>
	inline void vector<T>::erase(const uint _first, const uint _last) {
		assert(_first < _last and _first >= 0 and _last <= size_);
		uint diff = _last - _first;
		size_ -= diff;
		for (size_t c = _first; c < size_; c++) {
			std::swap(vec_[c], vec_[c + diff]);
		}
	}

	template<class T>
	inline void vector<T>::erase(const T* _first, const T* _last) {
		assert(_last >= _first and _first >= begin() and _last <= end());
		uint diff = _last - _first;
		size_ -= diff;
		for (size_t c = _first - begin(); c < size_; c++) {
			std::swap(vec_[c], vec_[c + diff]);
		}
	}

	template<class T>
	inline T& vector<T>::back() {
		return vec_[size_ - 1];
	}

	template<class T>
	inline T& vector<T>::operator[](uint _index) {
		if (_index < 0 or _index > size_) throw std::exception("bad index");
		return vec_[_index];
	}

	template<class T>
	inline const T& vector<T>::operator[](uint _index) const {
		if (_index < 0 or _index > size_) throw std::exception("bad index");
		return vec_[_index];
	}
}