#include "error.h"
#include "mem.h"
#include "vector.h"

#include <string.h>


void vec_init(Vector * vec, Dt_Size cap)
{
    if (cap)
    {
        Dt_ValuePtr * mem = (Dt_ValuePtr*)DT_ALLOCATE(sizeof(Dt_ValuePtr) * cap);
        vec->capacity = cap;
        vec->used_size = 0;
        vec->data = mem;
    }
    else
    {
        vec->capacity = 0;
        vec->used_size = 0;
        vec->data = NULL;
    }
}

void vec_deinit(Vector * _this)
{
    for (Dt_Size i = 0; i < _this->used_size; i++)
    {
        DT_invokeMethod0(_this->data[i], Dt_M_DecRef);
    }
}

inline void vec_insert(Vector * _this, Dt_Int index, Dt_ValuePtr value)
{
    DT_incRef(value);

    if (index == -1) // push_back
    {
        if (_this->capacity > _this->used_size) // append
        {
            _this->data[_this->used_size] = value;
            _this->used_size++;
        }
        else // re-allocate
        {
            const Dt_Size new_cap = _this->capacity * 2;
            Dt_ValuePtr * mem =
                (Dt_ValuePtr*)DT_ALLOCATE(sizeof(Dt_ValuePtr) * new_cap);

            memcpy(mem, _this->data, sizeof(Dt_ValuePtr) * _this->capacity);
            mem[_this->used_size] = value;
            DT_DEALLOCATE(_this->data);

            _this->capacity = new_cap;
            _this->used_size++;
            _this->data = mem;
        }
    }
    else // insert
    {
        if (index < 0)
            index = _this->used_size + index;

        if (index < 0 || (Dt_Size)index >= _this->used_size)
        {
            __Dt_private_raise_error(Dt_IndexError,
                "index out of range (elem-num=%u, index=%i)",
                _this->used_size, index);
        }

        if (_this->capacity > _this->used_size)
        {
            for (Dt_Size i = _this->used_size; i > index; i--)
                _this->data[i] = _this->data[i - 1];

            _this->data[index] = value;
            _this->used_size++;
        }
        else // re-allocate
        {
            const Dt_Size new_cap = _this->capacity * 2;
            Dt_ValuePtr * mem =
                (Dt_ValuePtr*)DT_ALLOCATE(sizeof(Dt_ValuePtr) * new_cap);

            memcpy(mem, _this->data, sizeof(Dt_ValuePtr) * index);
            memcpy(mem + index, _this->data + index + 1,
                sizeof(Dt_ValuePtr) * (_this->capacity - index));
            mem[index] = value;
            DT_DEALLOCATE(_this->data);

            _this->capacity = new_cap;
            _this->used_size++;
            _this->data = mem;
        }
    }
}

inline void vec_remove(Vector * _this, Dt_Int index)
{
    Dt_ValuePtr value;

    if (index == -1) // pop_back
    {
        _this->used_size--;
        value = _this->data[_this->used_size];
    }
    else // erase
    {
        if (index < 0)
            index = _this->used_size + index;

        if (index < 0 || (Dt_Size)index >= _this->used_size)
        {
            __Dt_private_raise_error(Dt_IndexError,
                "index out of range (elem-num=%u, index=%i)",
                _this->used_size, index);
        }

        _this->used_size--;
        value = _this->data[index];

        for (Dt_Size i = _this->used_size; i > index; i--)
            _this->data[i - 1] = _this->data[i];

    }

    DT_decRef(value);
}
