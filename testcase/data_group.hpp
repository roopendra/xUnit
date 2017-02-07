#ifndef __DATA_GROUP_HPP_
#define __DATA_GROUP_HPP_

#include <iostream>
#include <vector>
using namespace std;

class SEQ_BASE
{
public:
    SEQ_BASE():get_count(0),set_count(0),can_set(true){}
    virtual ~SEQ_BASE(){}
    int count(){ return set_count; }
protected:
    virtual void clear() = 0;
    int get_count;
    int set_count;
    bool can_set;
};

const int MAX_PARA_NUM = 6;

template <class T> class DATA_SEQ: public SEQ_BASE
{
public:
    T operator()(T v1) { return _(v1).ret(); }
    T operator()(T v1, T v2) { return _(v1)(v2); }
    T operator()(T v1, T v2, T v3) { return _(v1)(v2,v3); }
    T operator()(T v1, T v2, T v3, T v4) { return _(v1)(v2,v3,v4); }
    T operator()(T v1, T v2, T v3, T v4, T v5) { return _(v1)(v2,v3,v4,v5); }
    T operator()(T v1, T v2, T v3, T v4, T v5, T v6) { return _(v1)(v2,v3,v4,v5,v6); }
    //Now support 6 para...could add....
    //T operator() ...
    DATA_SEQ():_values(0){}
    ~DATA_SEQ(){ clear(); }
protected:
    virtual void clear(){ _values.clear(); }
private:
    T ret()
    {
	can_set = false;
	//if get value num si more than set_count, return the last value
	if(get_count < set_count)
	    return _values[get_count++];
	else
	    return _values[set_count-1];
    }
    DATA_SEQ<T> & _(T v)
    {
	if(can_set)
	{
	    _values.push_back(v);
	    set_count++;
	}
	return *this;
    }
    vector<T> _values;
};

class DATA_GROUP
{
public:
    DATA_GROUP():set_count(MAX_PARA_NUM+1),get_count(0),seq_num(0),seq_idx(0),can_set(true){}
    ~DATA_GROUP(){ clear(); }
    template <class T> DATA_SEQ<T> & operator[] (T&)
    {
	DATA_SEQ<T> *seq;
	if(can_set)
	{
	    //at first loop, create new DATA_SEQ
	    seq = new DATA_SEQ<T>;
	    _data.push_back(seq);
	    seq_num++;
	    //cout << "seq_num: " << seq_num << endl;
	}
	else
	{
	    //at other loop, get exist seq
	    seq = static_cast<DATA_SEQ<T> *>(_data[seq_idx]);
	    setCount(seq->count());
	    //cout << "exist_seq_count: " << exist_seq->count() << endl;
	    seq_idx = (seq_idx + 1) % seq_num;
	}
	return *seq;
    }
    bool getting()
    {
	if(seq_num > 0)
	    can_set = false;
	return get_count++ < set_count;
    }
    int current() { return get_count - 1; }
private:
    void setCount(int count)
    {
	if(count > MAX_PARA_NUM)
	    return;
	//first set or set the max value
	if(set_count > MAX_PARA_NUM || count > set_count)
	    set_count = count;
    }
    void clear()
    {
	vector<SEQ_BASE*>::iterator it;
	for(it = _data.begin(); it != _data.end(); ++it)
	    delete *it;
	_data.clear();
    }
    vector<SEQ_BASE*> _data;
    int set_count;
    int get_count;
    int seq_num;
    int seq_idx;
    bool can_set;
};

#endif

