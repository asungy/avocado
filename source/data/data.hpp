#pragma once

namespace stock {
    // Holds information on a security at a given time
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
