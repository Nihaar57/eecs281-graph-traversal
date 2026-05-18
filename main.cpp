// Project Identifier: B99292359FFD910ED13A7E6C7F9705B874262D79
#include "Runner.h"
#include <iostream>
#include <getopt.h>
#include <cctype>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    ios_base::sync_with_stdio(false);
    bool useStack = false;
    bool useQueue = false;
    char outputMode = 'M';
    bool showHelp = false;

    const char* short_opts = "sqo:h";
    const struct option long_opts[] = {
        { "stack", no_argument, nullptr, 's' },
        { "queue", no_argument, nullptr, 'q' },
        { "output", required_argument, nullptr, 'o' },
        { "help", no_argument, nullptr, 'h' },
        { nullptr, 0, nullptr, 0 }
    };

    int opt;
    while (true)
    {
        opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
        if (opt == -1)
        {
            break;
        }
        else if (opt == 's')
        {
            useStack = true;
        }
        else if (opt == 'q')
        {
            useQueue = true;
        }
        else if (opt == 'o')
        {
            if (optarg && optarg[0])
            {
                outputMode = (char) toupper((unsigned char)optarg[0]);
            }
        }
        else if (opt == 'h')
        {
            showHelp = true;
        }
        else
        {
            cerr << "Error: Unknown option\n";
            return 1;
        }
    }
    if (showHelp == true)
    {
        cout << "Usage: ./superMarco [--stack|--queue] [--output M|L]\n";
        cout << "  --stack, -s    Use stack-based routing\n";
        cout << "  --queue, -q    Use queue-based routing\n";
        cout << "  --output, -o   Output format: M (map) or L (list)\n";
        cout << "  --help, -h     Show this help message\n";
        return 0;
    }

    if (useStack == useQueue)
    {
        cerr << "Error: Stack or queue can only be specified once\n";
        return 1;
    }

    try
    {
        Runner runner(useStack, outputMode);
        runner.run(cin, cout, cerr);
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}