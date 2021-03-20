#pragma once

template <unsigned length>
struct FixedString
{
    char c_str[length];
    unsigned long size;
    unsigned long capacity = length + 1;
};