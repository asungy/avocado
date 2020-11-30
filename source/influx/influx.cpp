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

    void Run(std::string filepath)
    {
        httplib::Client cli("localhost", 8086);

        httplib::Headers headers{
            { "Authorization", GetTokenFromFile(filepath) },
            { "Accept", "application/json" },
            { "Content-Type", "text/plain; charset=utf-8" }
        };

        httplib::Params params{
            { "bucket", "test_bucket" },
            { "org", "test" }
        };

        std::string body{"market_data,symbol=AAPL open=120"}; 

        if (auto res = cli.Post("/api/v2/write?bucket=test_bucket&org=test", headers, body, "text/plain"))
        {
            std::cout << "Body: " << res->body << std::endl;
        }
        else
        {
            std::cout << "Error: " << res.error() << std::endl;
        }
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
