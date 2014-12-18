#pragma once
#ifndef SAVEABLE_H_UTH
#define SAVEABLE_H_UTH

#include <rapidjson/document.h>


namespace uth
{

    class Saveable
    {
    public:

        Saveable(){}

		virtual ~Saveable() {};


        virtual rapidjson::Value save(rapidjson::MemoryPoolAllocator<>&) const = 0;

        virtual bool load(const rapidjson::Value&) = 0;

    };
}

#endif