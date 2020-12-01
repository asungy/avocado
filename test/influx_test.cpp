#include "gtest/gtest.h" 
#include "influx.hpp"

// Tests converting the members of data structs to the Influx line protocol.
//
// For information on the Influx Line Protocol: 
// https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/
TEST(InfluxTest, ToLineProtocolTest)
{
    stock::DataPoint data {
        "IBM",     // symbol
        112.6500,  // open
        125.3130,  // high
        111.1600,  // low
        123.5200,  // close
        103461100, // volume,
        1606771800 // timestamp
    };

    // Testing timestamped == true
    std::string result = influx::ToLineProtocal("market_data", data, true);
    auto expected = "market_data,symbol=IBM open=112.650000,high=125.313000,low=111.160000,close=123.520000,volume=103461100 1606771800";
    EXPECT_STREQ(expected, result.c_str());

    // Testing timestamped == false
    result = influx::ToLineProtocal("market_data", data, false);
    expected = "market_data,symbol=IBM open=112.650000,high=125.313000,low=111.160000,close=123.520000,volume=103461100";
    EXPECT_STREQ(expected, result.c_str());
}
