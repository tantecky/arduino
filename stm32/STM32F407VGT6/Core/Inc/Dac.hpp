#ifndef C8C4C8E5_C4BB_4FD6_8D73_2DA7EEBA7082
#define C8C4C8E5_C4BB_4FD6_8D73_2DA7EEBA7082

#include "main.h"
#include "actor.hpp"

class Dac : public Actor<uint16_t>
{
private:
    DAC_HandleTypeDef *handle_;
    const uint32_t channel_;
    const uint16_t minValue_;
    const uint16_t maxValue_;
    uint16_t value_;

public:
    Dac(DAC_HandleTypeDef *handle, uint32_t channel,
        const uint16_t minValue, const uint16_t maxValue) : handle_(handle),
                                                            channel_(channel),
                                                            minValue_(minValue),
                                                            maxValue_(maxValue)

    {
    }

    void init(const uint16_t initValue = 0);
    void setValue(const uint16_t value) override;
    const uint16_t getMinValue() const override { return minValue_; }
    const uint16_t getMaxValue() const override { return maxValue_; }
};

#endif /* C8C4C8E5_C4BB_4FD6_8D73_2DA7EEBA7082 */