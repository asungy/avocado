#pragma once

#include "../data/data.hpp"

namespace influx {
    // Writes data to InfluxDB. `filepath` is used to specifie the file 
    // containing the Influx token.
    //
    // Example:
    //   stock::DataPoint data { "IBM", 112.6500, 125.3130, 111.1600, 
    //      123.5200, 103461100, 1606771800 };
    //   influx::Write("./token.txt", "stock_data_bucket", "data_org", "market_data", data);
    //
    void Write(std::string token, std::string bucket, std::string org,
               std::string measurement, stock::DataPoint data);

    // Converts a struct to the Influx line syntax
    //
    // See: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/
    std::string ToLineProtocal(
           std::string measurement, stock::DataPoint data, 
           bool timestamped);
}
