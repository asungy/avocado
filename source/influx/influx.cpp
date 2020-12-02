#include "httplib/httplib.h"

#include "influx.hpp"

#include <fstream>
#include <iostream>

namespace influx {

    // Reads the Influx user token from a specified file and returns the header value used in the 
    // Authorization header.
    //
    // If an error occurs while trying to read the file, a `runtime_error` is thrown.
    std::string GetTokenFromFile(std::string filepath);

    void Write(std::string filepath, std::string bucket, std::string org,
               std::string measurement, stock::DataPoint data)
    {
        httplib::Client cli("localhost", 8086);

        httplib::Headers headers{
            { "Authorization", GetTokenFromFile(filepath) },
            { "Accept", "application/json" },
            { "Content-Type", "text/plain; charset=utf-8" }
        };

        httplib::Params params{
            { "bucket", bucket.c_str() },
            { "org", org.c_str() }
        };

        std::string body{ ToLineProtocal(measurement, data, false) }; 

        if (auto res = cli.Post("/api/v2/write", headers, params, body))
        {
            // TODO: Replace with logging
            std::cout << "Body: " << res->body << std::endl;
        }
        else
        {
            std::cout << "Error: " << res.error() << std::endl;
        }
    }

    std::string ToLineProtocal(std::string measurement, stock::DataPoint data, bool timestamped)
    {
        std::string result{measurement};
        // Appending tag
        result += ",symbol=" + data.symbol;
        // Appending fields
        result += " open=" + std::to_string(data.open);
        result += ",high=" + std::to_string(data.high);
        result += ",low=" + std::to_string(data.low);
        result += ",close=" + std::to_string(data.close);
        result += ",volume=" + std::to_string(data.volume);
        if (timestamped)
            result += " " + std::to_string(data.timestamp);
        return result;
    }

    std::string GetTokenFromFile(std::string filepath)
    {
        std::ifstream token_file{ filepath };
        if (token_file.is_open())
        {
            std::string token_val;
            std::getline(token_file, token_val);
            token_file.close();

            std::string token{"Token "};
            token.append(token_val);
            return token;
        }

        throw std::runtime_error("Error occurred while trying to read token from file.");
    }
}
