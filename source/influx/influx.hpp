#pragma once

#include "../data/data.hpp"

namespace influx {
    void Write(std::string filepath, stock::DataPoint data);
    std::string ToLineProtocal(std::string measurement, stock::DataPoint data, bool timestamped);
}
