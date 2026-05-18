// Project Identifier: B99292359FFD910ED13A7E6C7F9705B874262D79
#ifndef RUNNER_H
#define RUNNER_H

#include "Castle.h"
#include "Router.h"
#include <istream>
#include <ostream>
#include <vector>

class Runner {
public:
    Runner(bool useStackMode, char outputModeChar);

    Castle& readCastle(std::istream& input);

    void printMapOutput(std::ostream& output, Castle& castle);
    void printListOutput(std::ostream& output, const std::vector<PathNode>& path);

    void run(std::istream& input, std::ostream& output, std::ostream& error);

private:
    bool useStack;
    char outputMode;
    Castle ourCastle;
};

#endif // RUNNER_H