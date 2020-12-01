#pragma once

namespace stock {
    struct DataPoint
    {
        std::string symbol;
        double open;
        double high;
        double low;
        double close;
        unsigned int volume;
        time_t timestamp;
    };
}
