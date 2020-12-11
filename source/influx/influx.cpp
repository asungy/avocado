#include "httplib/httplib.h"
#include "spdlog/spdlog.h"

#include "influx.hpp"

#include <iostream>

namespace influx {

    void Write(std::string token, std::string bucket, std::string org,
               std::string measurement, stock::DataPoint data)
    {
        httplib::Client cli("localhost", 8086);
        token = std::string("Token ") + token;

        httplib::Headers headers{
            { "Authorization", token },
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
            if (res->status >= 400)
                spdlog::error("Error: {}", res->body);
            else
                spdlog::info("Data successfully written to '{}' bucket.", bucket);
        }
        else
        {
            spdlog::error("Error occurred writing to Influx database: {}.", res.error());
        }
    }

    void CreateBackup(std::string token, std::string filepath)
    {
        std::string command{ "influx backup " };
        command += filepath;
        command += std::string(" -t ") + token;

        FILE * proc_stream = popen(command.c_str(), "r");
        if (proc_stream == nullptr) 
        {
            std::string message = std::string("Failed to create pipe or process. ") +
                                  std::string("Command: ") + command;
            throw std::runtime_error(message);
        }

        std::array<char, 128> buffer{};
        std::string result{};
        while (!feof(proc_stream))
        {
            if (fgets(buffer.data(), 128, proc_stream) != nullptr)
                result += buffer.data();
        }

        int result_code = pclose(proc_stream);
        if (result_code != EXIT_SUCCESS) {
            spdlog::error("Error occurred when closing pipe and/or process.");
        }

        std::cout << result << std::endl;
    }

    std::string ToLineProtocal(std::string measurement, stock::DataPoint data, 
                            bool timestamped)
    {
        std::string result{measurement};
        // Appending tag
        result += ",symbol=" + data.symbol;
        // Appending fields
        result += " open="   + std::to_string(data.open);
        result += ",high="   + std::to_string(data.high);
        result += ",low="    + std::to_string(data.low);
        result += ",close="  + std::to_string(data.close);
        result += ",volume=" + std::to_string(data.volume);
        if (timestamped)
            result += " " + std::to_string(data.timestamp);
        return result;
    }
}
