#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <algorithm>

class CommandLineParser {
    
    public:

    CommandLineParser(int argc, char **argv) {
        for (int i = 1; i < argc; i++) {
            this->m_tokens.push_back(std::string(argv[i]));
        }
    }

    const std::string& getCmdOptionValue(const std::string& option) const {
        auto it =  std::find(this->m_tokens.begin(), this->m_tokens.end(), option);
        if (it != this->m_tokens.end() && ++it != this->m_tokens.end()) {
            return *it;
        }
        static const std::string emptyString("");
        return emptyString;
    }

    bool cmdOptionExist(const std::string& option) const {
        auto it = std::find(this->m_tokens.begin(), this->m_tokens.end(), option); 
        return (it != this->m_tokens.end());
    }

    private:

    std::vector<std::string> m_tokens;
};

#endif // COMMAND_LINE_PARSER_HPP