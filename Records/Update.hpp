
#ifndef UPDATE_HPP
#define UPDATE_HPP

#include "Record.hpp"
#include <string>

class Update: public Record
{
    public:
        virtual bool makeValid(uint8_t);
        virtual std::string asJSON() const;
        virtual uint32_t getDifficulty() const;
};

#endif