#pragma once

#include "../data/data.hpp"

namespace influx {
    // Writes a single stock datapoint to InfluxDB.
    //
    // Example:
    //   stock::DataPoint data { "IBM", 112.6500, 125.3130, 111.1600, 
    //      123.5200, 103461100, 1606771800 };
    //   influx::Write("influxdb_token", "stock_data_bucket", "data_org", "market_data", data);
    //
    void Write(std::string token, std::string bucket, std::string org,
               std::string measurement, stock::DataPoint data);

    // Create a backup of a local InfluxDB instance
    void CreateBackup(std::string token, std::string dirpath);

    // Restore InfluxDB from backup directory
    void RestoreFromBackup(std::string token, std::string dirpath);

    // Converts a struct to the Influx line syntax
    //
    // See: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/
    std::string ToLineProtocal(
           std::string measurement, stock::DataPoint data, 
           bool timestamped);
}
